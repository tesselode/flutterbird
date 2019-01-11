#include "Oscillator.h"

double Oscillator::Next(double dt, Waveforms waveform, double frequency)
{
	phase += frequency * dt;
	while (phase > 1.0) phase -= 1.0;

	switch (waveform)
	{
	case Waveforms::Sine:
		return .5 + .5 * sin(phase * 4.0 * acos(0.0));
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
