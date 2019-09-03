#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include "Util.h"
#include <vector>

const int tapeLengthInSeconds = 10;

enum Parameter
{
	Osc1Frequency,
	Osc1ToPitch,
	NumParameters,
};

using namespace iplug;
using namespace igraphics;

class Flutterbird : public Plugin
{
public:
	Flutterbird(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
	void OnReset();
#endif

private:
#if IPLUG_DSP
	void InitTape();
	double GetSample(std::vector<double>& tape, double position);
	void UpdateOscillators();
	double GetTargetReadPosition();
	bool IsPitchModulationActive();
	void UpdateReadPosition();
	double GetReadPosition();

	double dt = 0.0;
	std::vector<double> tapeL;
	std::vector<double> tapeR;
	std::vector<float> floatTapeL;
	std::vector<float> floatTapeR;
	int writePosition = 0;
	double relativeReadPosition = 0.0;
	Oscillator osc1;
#endif
};
