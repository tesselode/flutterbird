#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Flutterbird::Flutterbird(const InstanceInfo& info)
: Plugin(info, MakeConfig((int)Parameter::NumParameters, 1))
{
#if IPLUG_DSP
	GetParam((int)Parameter::Osc1Frequency)->InitDouble("Oscillator 1 frequency", 5.0, 1.0, 10.0, .01, "hz");
	GetParam((int)Parameter::Osc1ToPitch)->InitDouble("Oscillator 1 to pitch", 0.0, -1.0, 1.0, .01);

	InitTape();
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

double Flutterbird::GetSample(std::vector<double>& tape, double position)
{
	int p0 = wrap(floor(position) - 1, 0, std::size(tape) - 1);
	int p1 = wrap(floor(position), 0, std::size(tape) - 1);
	int p2 = wrap(ceil(position), 0, std::size(tape) - 1);
	int p3 = wrap(ceil(position) + 1, 0, std::size(tape) - 1);

	auto x = position - floor(position);
	auto y0 = tape[p0];
	auto y1 = tape[p1];
	auto y2 = tape[p2];
	auto y3 = tape[p3];

	return interpolate(x, y0, y1, y2, y3);
}

void Flutterbird::UpdateOscillators()
{
	osc1.update(dt, GetParam((int)Parameter::Osc1Frequency)->Value());
}

double Flutterbird::GetTargetReadPosition()
{
	auto osc1Value = osc1.get(Waveform::Sine);
	return osc1Value * GetParam((int)Parameter::Osc1ToPitch)->Value();
}

bool Flutterbird::IsPitchModulationActive()
{
	if (GetParam((int)Parameter::Osc1ToPitch)->Value() != 0.0) return true;
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
		auto outL = GetSample(tapeL, readPosition);
		auto outR = GetSample(tapeR, readPosition);
		outputs[0][s] = outL;
		outputs[1][s] = outR;

		// increment the write position for the next sample
		writePosition++;
		if (writePosition == std::size(tapeL))
			writePosition = 0;
	}
}

void Flutterbird::OnReset()
{
	dt = 1.0 / GetSampleRate();
	InitTape();
}
#endif
