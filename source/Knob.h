#pragma once

#include "IControls.h"
#include "ThemeColors.h"

enum class KnobOrigin {
	Left,
	Center,
	Right,
};

class Knob : public IVKnobControl {
public:
	Knob(IGEditorDelegate& dlg, IRECT bounds, KnobOrigin o, int paramIdx)
		: IVKnobControl(dlg, bounds, paramIdx), origin(o)
	{}

	void Draw(IGraphics &g) override
	{
		const float cx = mRECT.MW(), cy = mRECT.MH();
		const float angle = mAngleMin + ((float)mValue * (mAngleMax - mAngleMin));
		const float radius = (mRECT.W() / 2.75f);
		float arcStartAngle, arcEndAngle;
		GetArcStartAndEndAngles(angle, arcStartAngle, arcEndAngle);

		g.DrawArc(themeColorDark, cx, cy, radius, mAngleMin, mAngleMax, 0, 12.f);
		g.DrawArc(themeColorAccent, cx, cy, radius, arcStartAngle, arcEndAngle, 0, 12.f);
		g.FillCircle(mMouseIsOver ? themeColorLight : themeColorWhite, cx, cy, radius);
		g.DrawRadialLine(themeColorAccent, cx, cy, angle, 0.5f * radius, .9f * radius, 0, 3.f);
	}

private:
	KnobOrigin origin;

	void GetArcStartAndEndAngles(float knobAngle, float &start, float &end)
	{
		float originAngle = origin == KnobOrigin::Right ? mAngleMax :
			origin == KnobOrigin::Center ? mAngleMin + (mAngleMax - mAngleMin) / 2:
			mAngleMin;
		start = originAngle < knobAngle ? originAngle : knobAngle;
		end = start == originAngle ? knobAngle : originAngle;
	}
};