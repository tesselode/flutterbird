#ifndef __FLUTTERBIRD__
#define __FLUTTERBIRD__

#include <cmath>
#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include "Parameters.h"
#include <string>
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
	void InitParmeters();
	void InitBuffer();
	double GetReadPosition();
	double GetSample(std::vector<double> &buffer, double position);

	double dt = 0.0;
	std::vector<double> bufferL;
	std::vector<double> bufferR;
	Oscillator osc1;
	Oscillator osc2;
	Oscillator osc3;
	Oscillator osc4;
	int writePosition = 0;
	double readPosition = 0.0;

	ITextControl* debugText;
};

#endif
