#pragma once

#include "IControls.h"
#include "ThemeColors.h"

class SmallSwitchControl : public IVSwitchControl
{
public:
	SmallSwitchControl(IRECT bounds, int paramIdx)
		: IVSwitchControl(bounds, paramIdx)
	{}

	void Draw(IGraphics& g) override
	{
		IColor color;
		if (GetParam()->Value() > 0)
			color = GetMouseIsOver() ? themeColorAccentGrayed : themeColorAccent;
		else
			color = GetMouseIsOver() ? themeColorDarkGrayed : themeColorDark;
		g.FillCircle(color, (mRECT.L + mRECT.R) / 2, (mRECT.T + mRECT.B) / 2, mRECT.W() / 2);
	}
};