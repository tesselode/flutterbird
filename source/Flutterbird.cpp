#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

Flutterbird::Flutterbird(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR(0, 1, instanceInfo)
{
#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
	mMakeGraphicsFunc = [&]() {
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};
	
	mLayoutFunc = [&](IGraphics* pGraphics) {
		pGraphics->AttachCornerResizer(kUIResizerScale, false);
		pGraphics->AttachPanelBackground(COLOR_GRAY);
	};
#endif
}

#if IPLUG_DSP
void Flutterbird::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		for (int c = 0; c < NOutChansConnected(); c++)
		{
			outputs[c][s] = 0.0;
		}
	}
}
#endif
