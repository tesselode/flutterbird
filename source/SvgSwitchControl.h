#pragma once

#include "IControls.h"
#include "ThemeColors.h"

/*
	A switch control that uses an SVG for its inner graphics.
	The graphic for each state should be arranged vertically in the SVG, like a framestrip.
*/
class SvgSwitchControl : public IVSwitchControl
{
public:
	SvgSwitchControl(IRECT bounds, ISVG svg, int paramIdx = kNoParameter)
		: IVSwitchControl(bounds, paramIdx),
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
};
