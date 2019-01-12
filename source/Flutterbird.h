#pragma once

#include <cmath>
#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include <vector>

const int tapeLength = 10;
const int numOscillators = 4;
const int safetySamples = 2;

enum class Parameters
{
	Osc1Waveform,
	Osc1Frequency,
	Osc1ToPitch,
	Osc1ToVolume,
	Osc2Waveform,
	Osc2Frequency,
	Osc2ToPitch,
	Osc2ToVolume,
	Osc3Waveform,
	Osc3Frequency,
	Osc3ToPitch,
	Osc3ToVolume,
	Osc4Waveform,
	Osc4Frequency,
	Osc4ToPitch,
	Osc4ToVolume,
	GlobalToPitch,
	GlobalToVolume,
	Mix,
	TestTone,
	NumParameters,
};

class Flutterbird : public IPlug
{
public:
	Flutterbird(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
	void InitBuffer();
	void OnReset() override;
#endif

private:
#if IPLUG_DSP
	void InitParameters();
	void UpdateOscillators();
	double GetReadPosition();
	void UpdateVolume();
	double GetSample(std::vector<double>& buffer, double position);

	double dt = 0.0;
	int bufferLength = 0;
	std::vector<double> bufferL;
	std::vector<double> bufferR;
	Oscillator osc1;
	Oscillator osc2;
	Oscillator osc3;
	Oscillator osc4;
	double osc1Value = 0.0;
	double osc2Value = 0.0;
	double osc3Value = 0.0;
	double osc4Value = 0.0;
	int writePosition = 0;
	double readPosition = 0.0;
	double volume = 1.0;

	double testTonePhase = 0.0;
#endif
};
