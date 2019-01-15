#pragma once

#include <cmath>
#include "IPlug_include_in_plug_hdr.h"
#include "Knob.h"
#include "Oscillator.h"
#include "ThemeColors.h"
#include <vector>
#include "Util.h"
#include "SvgSwitchControl.h"

const int tapeLength = 10;
const int numOscillators = 4;

enum class Parameters
{
	Osc1Waveform,
	Osc1Frequency,
	Osc1ToPitch,
	Osc1ToVolume,
	Osc1ToPanning,
	Osc2Waveform,
	Osc2Frequency,
	Osc2ToPitch,
	Osc2ToVolume,
	Osc2ToPanning,
	Osc3Waveform,
	Osc3Frequency,
	Osc3ToPitch,
	Osc3ToVolume,
	Osc3ToPanning,
	Osc4Waveform,
	Osc4Frequency,
	Osc4ToPitch,
	Osc4ToVolume,
	Osc4ToPanning,
	GlobalToPitch,
	GlobalToVolume,
	GlobalToPanning,
	InfinitePanning,
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
	void UpdatePanning();
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
	double relativeReadPosition = 0.0;
	double volume = 1.0;
	double panning = 0.0;

	double testTonePhase = 0.0;
#endif

#if IPLUG_EDITOR
	void InitGraphics();
#endif
};
