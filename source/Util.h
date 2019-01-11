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
	/*
	interpolation code from Polynomial Interpolators for
	High-Quality Resampling of Oversampled Audio by Olli Niemitalo
	http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
	*/

	// 4-point, 2nd-order Watte tri-linear (x-form)
	float ym1py2 = y0 + y3;
	float c0 = y1;
	float c1 = (3 / 2.0) * y2 - (1 / 2.0) * (y1 + ym1py2);
	float c2 = 1 / 2.0 * (ym1py2 - y1 - y2);
	return (c2*x + c1)*x + c0;
}

// random numbers

// https://stackoverflow.com/questions/1640258/need-a-fast-random-generator-for-c
static unsigned long x = 123456789, y = 362436069, z = 521288629;
inline unsigned long xorshift(void)
{
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;
	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;
	return z;
}

const double xorshiftMultiplier = 2.0 / ULONG_MAX;
inline double random()
{
	return -1.0 + xorshift() * xorshiftMultiplier;
}
