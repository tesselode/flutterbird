#pragma once

#include "IControls.h"
#include "ThemeColors.h"

class SvgSwitch : public IVSwitchControl
{
public:
	SvgSwitch(IGEditorDelegate& dlg, IRECT bounds, ISVG svg, int paramIdx = kNoParameter)
		: IVSwitchControl(dlg, bounds, paramIdx),
		switchContents(svg)
	{}

	void Draw(IGraphics& g) override
	{
		g.FillRect(mMouseIsOver ? themeColorLight : themeColorWhite, mRECT);
		g.DrawRect(themeColorDark, mRECT, 0, 8.0f);

		auto svgY = mRECT.T - (mRECT.B - mRECT.T) * (int)GetParam()->Value();
		auto svgH = (mRECT.B - mRECT.T) * mNumStates;
		auto svgRect = IRECT(mRECT.L, svgY, mRECT.R, svgY + svgH);
		g.PathClipRegion(mRECT);
		g.DrawSVG(switchContents, svgRect);
	}

private:
	ISVG switchContents;
	ILayerPtr layer;
};
