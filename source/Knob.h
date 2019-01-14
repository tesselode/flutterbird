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
		const float v = mAngleMin + ((float)mValue * (mAngleMax - mAngleMin));
		const float cx = mRECT.MW(), cy = mRECT.MH();
		const float radius = (mRECT.W() / 2.75f);
		float originAngle;
		switch (origin)
		{
		case KnobOrigin::Left:
			originAngle = mAngleMin;
			break;
		case KnobOrigin::Center:
			originAngle = mAngleMin + (mAngleMax - mAngleMin) / 2;
			break;
		case KnobOrigin::Right:
			originAngle = mAngleMax;
			break;
		}
		float arcAngleA = originAngle < v ? originAngle : v;
		float arcAngleB = arcAngleA == originAngle ? v : originAngle;
		g.DrawArc(darkColor, cx, cy, radius, mAngleMin, mAngleMax, 0, 12.f);
		g.DrawArc(accentColor, cx, cy, radius, arcAngleA, arcAngleB, 0, 12.f);
		g.FillCircle(lightColor, cx, cy, radius);
		g.FillCircle(mediumColor, cx, cy, radius * .8f);
		if (mMouseIsOver)
			g.FillCircle(IColor(25, 0, 0, 0), cx, cy, radius * 0.8f);
		g.DrawRadialLine(accentColor, cx, cy, v, 0.5f * radius, .9f * radius, 0, 3.f);
		if (mLabelBounds.H())
			g.DrawText(mLabelText, mLabel.Get(), mLabelBounds);
		if (mDisplayParamValue)
		{
			WDL_String str;
			GetParam()->GetDisplayForHost(str);
			if (mShowParamLabel)
			{
				str.Append(" ");
				str.Append(GetParam()->GetLabelForHost());
			}
			g.DrawText(mValueText, str.Get(), mValueBounds);
		}
	}

private:
	KnobOrigin origin;
};