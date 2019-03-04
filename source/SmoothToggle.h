#pragma once

/*
	A switch that, when flipped, smoothly transitions from 0-1 or vice versa.
	Used for parameters that would cause popping noises if they were not
	transitioned smoothly.
*/
class SmoothToggle
{
public:
	bool on = false;
	double value = 0.0;
	double speed = 100.0;

	void Update(double dt)
	{
		if (on && value < 1.0)
		{
			value += speed * dt;
			if (value > 1.0) value = 1.0;
		}
		if (!on && value > 0.0)
		{
			value -= speed * dt;
			if (value < 0.0) value = 0.0;
		}
	}
};

