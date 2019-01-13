#pragma once

#include "IControls.h"

class WaveformSwitch : public IVSwitchControl
{
public:
	WaveformSwitch(IGEditorDelegate& dlg, IRECT bounds, ISVG svg, int paramIdx = kNoParameter)
		: IVSwitchControl(dlg, bounds, paramIdx),
		switchContents(svg)
	{}

	void Draw(IGraphics& g) override
	{
		g.DrawSVG(switchContents, mRECT);
	}

private:
	ISVG switchContents;
};
