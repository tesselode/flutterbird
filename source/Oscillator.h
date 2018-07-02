#pragma once

#include <cmath>

enum class Waveforms
{
	Sine,
	Triangle,
	Saw,
	Square,
	Drift,
	numWaveforms
};

class Oscillator
{
public:
	double Next(double dt, Waveforms waveform, double frequency);

private:
	double phase = 0.0;
};

