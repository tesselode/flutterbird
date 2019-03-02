#pragma once

#include <cmath>
#include <iomanip>
#include "IPlug_include_in_plug_hdr.h"
#include "Knob.h"
#include "Oscillator.h"
#include "ThemeColors.h"
#include <vector>
#include "Util.h"
#include "SmoothToggle.h"
#include <sstream>
#include <string>
#include "SvgSwitchControl.h"

const int tapeLength = 10;
const int numOscillators = 4;

enum class Parameters
{
	Osc1Waveform,
	Osc1Frequency,
	Osc1TempoSyncEnabled,
	Osc1TempoSyncTime,
	Osc1ToPitch,
	Osc1ToVolume,
	Osc1ToPanning,
	Osc2Waveform,
	Osc2Frequency,
	Osc2TempoSyncEnabled,
	Osc2TempoSyncTime,
	Osc2ToPitch,
	Osc2ToVolume,
	Osc2ToPanning,
	Osc3Waveform,
	Osc3Frequency,
	Osc3TempoSyncEnabled,
	Osc3TempoSyncTime,
	Osc3ToPitch,
	Osc3ToVolume,
	Osc3ToPanning,
	Osc4Waveform,
	Osc4Frequency,
	Osc4TempoSyncEnabled,
	Osc4TempoSyncTime,
	Osc4ToPitch,
	Osc4ToVolume,
	Osc4ToPanning,
	GlobalToPitch,
	GlobalToVolume,
	GlobalToPanning,
	Mix,
	TestTone,
	NumParameters,
};

enum class TempoSyncTimes
{
	EightBars,
	SixBars,
	FourBars,
	ThreeBars,
	TwoBars,
	DottedWhole,
	Whole,
	DottedHalf,
	Half,
	TripletHalf,
	DottedQuarter,
	Quarter,
	TripletQuarter,
	DottedEighth,
	Eighth,
	TripletEighth,
	DottedSixteenth,
	Sixteenth,
	TripletSixteenth,
	NumTempoSyncTimes,
};

class Flutterbird : public IPlug
{
public:
	Flutterbird(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
	void InitBuffer();
	void OnReset() override;
	IParam* GetParam(Parameters parameter);
	void OnParamChange(int paramIdx);
	void OnParamChangeUI(int paramIdx, EParamSource source = kUnknown);
	bool SerializeState(IByteChunk& chunk) const override;
	int UnserializeState(const IByteChunk& chunk, int startPos);
#endif

private:
#if IPLUG_DSP
	void InitParameters();
	double TempoSyncToFrequency(TempoSyncTimes value);
	void UpdateOscillators();
	double GetReadPosition();
	void UpdateVolume();
	void UpdatePanning();
	double GetSample(std::vector<double>& buffer, double position);

	double dt = 0.0;
	bool playingPrevious = false;
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
	SmoothToggle testToneSwitch;
	double testTonePhase = 0.0;
#endif

#if IPLUG_EDITOR
	void InitGraphics();

	ITextControl* parameterNameLabel;
	ITextControl* parameterValueLabel;
	Knob* osc1FrequencyKnob;
	Knob* osc2FrequencyKnob;
	Knob* osc3FrequencyKnob;
	Knob* osc4FrequencyKnob;
#endif
};
