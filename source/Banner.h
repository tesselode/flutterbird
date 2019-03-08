#pragma once

#include "config.h"
#include "IControl.h"
#include "ThemeColors.h"

class Banner : public IControl
{
public:
	Banner(IRECT bounds) : IControl(bounds.GetScaled(2), kNoParameter), mainBounds(bounds) {}

	void Draw(IGraphics& g) override
	{
		g.StartLayer(mRECT);

		g.PathRect(mainBounds);
		g.PathFill(IPattern(themeColorAccent));

		auto l = mainBounds.L;
		auto r = mainBounds.R;
		float x[] = { l + (r - l) * .45, l + (r - l) * .55, mainBounds.R, mainBounds.R };
		float y[] = { mainBounds.B, mainBounds.T, mainBounds.T, mainBounds.B };
		g.PathConvexPolygon(x, y, 4);
		g.PathFill(IPattern(IColor(64, 0, 0, 0)));

		auto layerPointer = g.EndLayer();
		//g.ApplyLayerDropShadow(layerPointer, IShadow(IPattern(IColor(255, 0, 0, 0)), 32, 0, 0, .5));
		g.DrawLayer(layerPointer);
	}

private:
	IRECT mainBounds;
};
