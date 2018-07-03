#pragma once

#include <cmath>
#include "Util.h"

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
	double driftVelocity = 0.0;
	double driftPhase = 0.0;
};

