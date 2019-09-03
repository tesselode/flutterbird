#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Util.h"
#include <vector>

const int tapeLengthInSeconds = 10;

using namespace iplug;
using namespace igraphics;

class Flutterbird : public Plugin
{
public:
	Flutterbird(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
	void InitTape();
	double GetSample(std::vector<double>& tape, double position);
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;

	std::vector<double> tapeL;
	std::vector<double> tapeR;
	std::vector<float> floatTapeL;
	std::vector<float> floatTapeR;
	int writePosition = 0;
	double readPosition = 0.0;
#endif
};
