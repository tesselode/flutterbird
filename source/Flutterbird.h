#pragma once

#include "IPlug_include_in_plug_hdr.h"

class Flutterbird : public IPlug
{
public:
	Flutterbird(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif
};
