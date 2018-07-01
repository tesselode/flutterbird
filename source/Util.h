#pragma once

// https://stackoverflow.com/a/707426
inline int wrap(int kX, int const kLowerBound, int const kUpperBound)
{
	int range_size = kUpperBound - kLowerBound + 1;

	if (kX < kLowerBound)
		kX += range_size * ((kLowerBound - kX) / range_size + 1);

	return kLowerBound + (kX - kLowerBound) % range_size;
}

// http://musicdsp.org/archive.php?classid=5#93
inline float interpolate(float x, float y0, float y1, float y2, float y3)
{
	// 4-point, 3rd-order Hermite (x-form) 
	float c0 = y1;
	float c1 = 0.5f * (y2 - y0);
	float c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
	float c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);
	return ((c3 * x + c2) * x + c1) * x + c0;
}