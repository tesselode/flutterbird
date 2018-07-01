#ifndef __FLUTTERBIRD__
#define __FLUTTERBIRD__

#include <cmath>
#include "IPlug_include_in_plug_hdr.h"
#include "Parameters.h"
#include "Util.h"
#include <vector>

const int bufferLength = 10;

class Flutterbird : public IPlug
{
public:
	Flutterbird(IPlugInstanceInfo instanceInfo);
	~Flutterbird();

	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
	void InitBuffer();
	double GetReadPosition();
	double GetSample(std::vector<double> &buffer, double position);

	std::vector<double> bufferL;
	std::vector<double> bufferR;
	int writePosition = 0;

	int counter = 0;
};

#endif
