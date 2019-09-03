#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Flutterbird::Flutterbird(const InstanceInfo& info)
: Plugin(info, MakeConfig(0, 1))
{
#if IPLUG_DSP
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
			ImGui::Text("Read position:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(readPosition).c_str());
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
	readPosition = 0.0;
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

void Flutterbird::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		auto inL = inputs[0][s];
		auto inR = inputs[1][s];
		tapeL[writePosition] = inL;
		tapeR[writePosition] = inR;
		floatTapeL[writePosition] = tapeL[writePosition];
		floatTapeR[writePosition] = tapeR[writePosition];
		writePosition++;
		if (writePosition == std::size(tapeL))
			writePosition = 0;
		readPosition += .5;
		auto outL = GetSample(tapeL, readPosition);
		auto outR = GetSample(tapeR, readPosition);
		outputs[0][s] = outL;
		outputs[1][s] = outR;
	}
}
#endif
