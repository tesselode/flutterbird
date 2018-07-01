#ifndef __FLUTTERBIRD__
#define __FLUTTERBIRD__

#include "IPlug_include_in_plug_hdr.h"
#include "Parameters.h"

class Flutterbird : public IPlug
{
public:
	Flutterbird(IPlugInstanceInfo instanceInfo);
	~Flutterbird();

	void Reset();
	void OnParamChange(int paramIdx);
	void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
};

#endif
