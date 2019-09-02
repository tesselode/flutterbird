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
	NumWaveforms
};

class Oscillator
{
public:
	void Oscillator::Reset() { phase = 0.0; }

	double Oscillator::Next(double dt, Waveforms waveform, double frequency)
	{
		phase += frequency * dt;
		while (phase > 1.0) phase -= 1.0;

		switch (waveform)
		{
		case Waveforms::Sine:
			return .5 + .5 * sin(phase * twoPi);
		case Waveforms::Triangle:
			return 1.0 - abs(2.0 * phase - 1.0);
		case Waveforms::Saw:
			return phase;
		case Waveforms::Square:
			return phase < 0.5 ? 0.0 : 1.0;
		case Waveforms::Drift:
			driftVelocity += random() * 10000.0 * frequency * dt;
			driftVelocity -= driftVelocity * 2.0 * sqrt(frequency) * dt;
			driftPhase += driftVelocity * dt;
			return .5 + .5 * sin(driftPhase);
		}
	}

private:
	double phase = 0.0;
	double driftVelocity = 0.0;
	double driftPhase = 0.0;
};

