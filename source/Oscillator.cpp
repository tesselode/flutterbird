#include "Oscillator.h"

double Oscillator::Next(double dt, Waveforms waveform, double frequency)
{
	phase += frequency * dt;
	while (phase > 1.0) phase -= 1.0;

	switch (waveform)
	{
	case Waveforms::Sine:
		return .5 * (1.0 + sin(phase * 4.0 * acos(0.0)));
	case Waveforms::Triangle:
		return phase < .5 ? phase * 2.0 : 1.0 - (phase - .5) * 2.0;
	case Waveforms::Saw:
		return phase;
	case Waveforms::Square:
		return phase < .5 ? 0.0 : 1.0;
	case Waveforms::Drift:
		return 0.0;
	}
}
