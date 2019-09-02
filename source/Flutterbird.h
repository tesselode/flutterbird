#pragma once

#include "IPlug_include_in_plug_hdr.h"

using namespace iplug;
using namespace igraphics;

class Flutterbird : public Plugin
{
public:
	Flutterbird(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif
};
