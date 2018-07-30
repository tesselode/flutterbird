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
	// Optimal 32x (6-point, 5th-order) (z-form)
	// Olli Niemitalo
	// http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
	float z = x - 1 / 2.0;
	float even1 = y3 + y2, odd1 = y3 - y2;
	float even2 = y4 + y1, odd2 = y4 - y1;
	float even3 = y5 + y0, odd3 = y5 - y0;
	float c0 = even1 * 0.42685983409379380 + even2 * 0.07238123511170030
		+ even3 * 0.00075893079450573;
	float c1 = odd1 * 0.35831772348893259 + odd2 * 0.20451644554758297
		+ odd3 * 0.00562658797241955;
	float c2 = even1 * -0.217009177221292431 + even2 * 0.20051376594086157
		+ even3 * 0.01649541128040211;
	float c3 = odd1 * -0.25112715343740988 + odd2 * 0.04223025992200458
		+ odd3 * 0.02488727472995134;
	float c4 = even1 * 0.04166946673533273 + even2 * -0.06250420114356986
		+ even3 * 0.02083473440841799;
	float c5 = odd1 * 0.08349799235675044 + odd2 * -0.04174912841630993
		+ odd3 * 0.00834987866042734;
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
