#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Flutterbird::Flutterbird(const InstanceInfo& info)
: Plugin(info, MakeConfig(0, 1))
{
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
	mMakeGraphicsFunc = [&]()
	{
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};
	
	mLayoutFunc = [&](IGraphics* pGraphics)
	{
		pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
		pGraphics->AttachPanelBackground(COLOR_GRAY);
	};
#endif
}

#if IPLUG_DSP
void Flutterbird::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	for (int sample = 0; sample < nFrames; sample++)
	{
		for (int channel = 0; channel < NOutChansConnected(); channel++)
		{
			outputs[channel][sample] = inputs[channel][sample];
		}
	}
}
#endif
