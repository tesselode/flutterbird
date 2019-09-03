#pragma once

#include <cmath>
#include "Util.h"

enum class Waveform
{
	Sine,
	NumWaveforms,
};

class Oscillator
{
public:
	void update(double dt, double frequency)
	{
		phase += frequency * dt;
		while (phase > 1) phase--;
	}

	double get(Waveform waveform)
	{
		switch (waveform)
		{
		case Waveform::Sine:
			return .5 + .5 * sin(phase * twoPi);
		default:
			return 0.0;
		}
	}

private:
	double phase = 0.0;
};