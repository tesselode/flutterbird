#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#if IPLUG_DSP
void Flutterbird::InitParameters()
{
	GetParam(Osc1Frequency)->InitDouble("Oscillator 1 frequency", 5.0, 1.0, 10.0, .01, "hz");
	GetParam(Osc1ToPitch)->InitDouble("Oscillator 1 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam(Osc2Frequency)->InitDouble("Oscillator 2 frequency", 5.0, 1.0, 10.0, .01, "hz");
	GetParam(Osc2ToPitch)->InitDouble("Oscillator 2 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam(Osc3Frequency)->InitDouble("Oscillator 3 frequency", 5.0, 1.0, 10.0, .01, "hz");
	GetParam(Osc3ToPitch)->InitDouble("Oscillator 3 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam(Osc4Frequency)->InitDouble("Oscillator 4 frequency", 5.0, 1.0, 10.0, .01, "hz");
	GetParam(Osc4ToPitch)->InitDouble("Oscillator 4 to pitch", 0.0, -1.0, 1.0, .01);
}

void Flutterbird::InitTape()
{
	tapeL.clear();
	tapeR.clear();
	floatTapeL.clear();
	floatTapeR.clear();
	auto numberOfSamples = tapeLengthInSeconds * GetSampleRate();
	for (int i = 0; i < numberOfSamples; i++)
	{
		tapeL.push_back(0.0);
		tapeR.push_back(0.0);
		floatTapeL.push_back(0.0);
		floatTapeR.push_back(0.0);
	}
	writePosition = 0;
	relativeReadPosition = 0.0;
}

void Flutterbird::CreateOscillators()
{
	for (int i = 0; i < numberOfOscillators; i++)
		oscillators.push_back(Oscillator());
}
#endif

Flutterbird::Flutterbird(const InstanceInfo& info)
: Plugin(info, MakeConfig((int)Parameter::NumParameters, 1))
{
#if IPLUG_DSP
	InitParameters();
	InitTape();
	CreateOscillators();
#endif

#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
	mMakeGraphicsFunc = [&]()
	{
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};
	
	mLayoutFunc = [&](IGraphics* pGraphics)
	{
		pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
		pGraphics->AttachPanelBackground(COLOR_GRAY);
		pGraphics->AttachImGui([this](IGraphics* pGraphics) {
			ImGui::PlotLines("Tape L", &floatTapeL[0], std::size(tapeL), writePosition, 0, -1.0, 1.0, ImVec2(0, 100));
			ImGui::PlotLines("Tape R", &floatTapeR[0], std::size(tapeR), writePosition, 0, -1.0, 1.0, ImVec2(0, 100));
			ImGui::Text("Write position:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(writePosition).c_str());
			ImGui::Text("Relative read position:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(relativeReadPosition).c_str());
		});
	};
#endif
}

#if IPLUG_DSP
double Flutterbird::GetSample(std::vector<double>& tape, double position)
{
	int sampleIndex0 = wrap(floor(position) - 1, 0, std::size(tape) - 1);
	int sampleIndex1 = wrap(floor(position), 0, std::size(tape) - 1);
	int sampleIndex2 = wrap(ceil(position), 0, std::size(tape) - 1);
	int sampleIndex3 = wrap(ceil(position) + 1, 0, std::size(tape) - 1);

	auto x = position - floor(position);
	auto y0 = tape[sampleIndex0];
	auto y1 = tape[sampleIndex1];
	auto y2 = tape[sampleIndex2];
	auto y3 = tape[sampleIndex3];

	return interpolate(x, y0, y1, y2, y3);
}

void Flutterbird::UpdateOscillators()
{
	for (int i = 0; i < numberOfOscillators; i++)
		oscillators[i].update(dt, GetParam(oscillatorFrequencyParameters[i])->Value());
}

double Flutterbird::GetTargetReadPosition()
{
	auto target = 0.0;
	for (int i = 0; i < numberOfOscillators; i++)
	{
		auto oscToPitch = GetParam(oscillatorToPitchParameters[i])->Value();
		if (oscToPitch == 0.0) continue;
		auto oscValue = oscillators[i].get(Sine);
		if (oscToPitch < 0.0)
		{
			oscToPitch *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target += oscToPitch * oscValue;
	}
	return target;
}

bool Flutterbird::IsPitchModulationActive()
{
	for (int i = 0; i < numberOfOscillators; i++)
		if (GetParam(oscillatorToPitchParameters[i])->Value() != 0.0) return true;
	return false;
}

void Flutterbird::UpdateReadPosition()
{
	auto followSpeed = IsPitchModulationActive() ? 1.0 : 10.0;
	relativeReadPosition += (GetTargetReadPosition() - relativeReadPosition) * followSpeed * dt;
}

double Flutterbird::GetReadPosition()
{
	return writePosition - relativeReadPosition * GetSampleRate();
}

void Flutterbird::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		UpdateOscillators();
		UpdateReadPosition();

		// write the input signal to the tape
		tapeL[writePosition] = inputs[0][s];
		tapeR[writePosition] = inputs[1][s];
		floatTapeL[writePosition] = tapeL[writePosition];
		floatTapeR[writePosition] = tapeR[writePosition];

		// read from the tape and output the interpolated signal
		auto readPosition = GetReadPosition();
		outputs[0][s] = GetSample(tapeL, readPosition);
		outputs[1][s] = GetSample(tapeR, readPosition);

		// increment the write position for the next sample
		writePosition++;
		if (writePosition == std::size(tapeL)) writePosition = 0;
	}
}

void Flutterbird::OnReset()
{
	dt = 1.0 / GetSampleRate();
	InitTape();
}
#endif
