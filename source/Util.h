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
inline float interpolate(float x, float y0, float y1, float y2, float y3, float y4, float y5)
{
	// Optimal 2x (6-point, 5th-order) (z-form)
	// Olli Niemitalo
	// http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
	float z = x - 1 / 2.0;
	float even1 = y3 + y2, odd1 = y3 - y2;
	float even2 = y4 + y1, odd2 = y4 - y1;
	float even3 = y5 + y0, odd3 = y5 - y0;
	float c0 = even1 * 0.40513396007145713 + even2 * 0.09251794438424393
		+ even3 * 0.00234806603570670;
	float c1 = odd1 * 0.28342806338906690 + odd2 * 0.21703277024054901
		+ odd3 * 0.01309294748731515;
	float c2 = even1 * -0.191337682540351941 + even2 * 0.16187844487943592
		+ even3 * 0.02946017143111912;
	float c3 = odd1 * -0.16471626190554542 + odd2 * -0.00154547203542499
		+ odd3 * 0.03399271444851909;
	float c4 = even1 * 0.03845798729588149 + even2 * -0.05712936104242644
		+ even3 * 0.01866750929921070;
	float c5 = odd1 * 0.04317950185225609 + odd2 * -0.01802814255926417
		+ odd3 * 0.00152170021558204;
	return ((((c5*z + c4)*z + c3)*z + c2)*z + c1)*z + c0;
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
