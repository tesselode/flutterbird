#pragma once

// https://stackoverflow.com/a/707426
inline int wrap(int kX, int const kLowerBound, int const kUpperBound)
{
	int range_size = kUpperBound - kLowerBound + 1;

	if (kX < kLowerBound)
		kX += range_size * ((kLowerBound - kX) / range_size + 1);

	return kLowerBound + (kX - kLowerBound) % range_size;
}

/*
	Given 4 samples and a point from 0-1 between y1 and y2, returns an
	approximation of what the sample would be.
*/
inline float interpolate(float x, float y0, float y1, float y2, float y3)
{
	/*
	interpolation code from Polynomial Interpolators for
	High-Quality Resampling of Oversampled Audio by Olli Niemitalo (p. 48)
	http://yehar.com/blog/wp-content/uploads/2009/08/deip.pdf
	*/

	// 4-point, 2nd-order Watte tri-linear (x-form)
	float ym1py2 = y0 + y3;
	float c0 = y1;
	float c1 = (3 / 2.0) * y2 - (1 / 2.0) * (y1 + ym1py2);
	float c2 = 1 / 2.0 * (ym1py2 - y1 - y2);
	return (c2 * x + c1) * x + c0;
}