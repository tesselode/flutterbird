#pragma once

#include "IControls.h"
#include "ThemeColors.h"

/*
	The possible "neutral positions" for a knob. The outer arc of the knob
	will be drawn from the origin to the angle the knob is pointing at.
*/
enum class KnobOrigin {
	Left,
	Center,
	Right,
};

class Knob : public IVKnobControl {
public:
	Knob(IRECT bounds, KnobOrigin o, int paramIdx)
		: IVKnobControl(bounds, paramIdx), origin(o)
	{}

	// Changes the parameter the knob is assigned to.
	void SetParameterIndex(int index)
	{
		mParamIdx = index;
		mValue = GetParam()->GetNormalized();
		SetDirty();
	}

	void Draw(IGraphics &g) override
	{
		const float cx = mRECT.MW(), cy = mRECT.MH();
		const float angle = mAngleMin + ((float)mValue * (mAngleMax - mAngleMin));
		const float radius = (mRECT.W() / 2.75f);
		float arcStartAngle, arcEndAngle;
		GetArcStartAndEndAngles(angle, arcStartAngle, arcEndAngle);

		if (IsGrayed())
		{
			g.DrawArc(themeColorDarkGrayed, cx, cy, radius, mAngleMin, mAngleMax, 0, 12.f);
			g.DrawArc(themeColorAccentGrayed, cx, cy, radius, arcStartAngle, arcEndAngle, 0, 12.f);
			g.FillCircle(mMouseIsOver ? themeColorLightGrayed : themeColorWhiteGrayed, cx, cy, radius);
			g.DrawRadialLine(themeColorAccentGrayed, cx, cy, angle, 0.5f * radius, .9f * radius, 0, 3.f);
		}
		else
		{
			g.DrawArc(themeColorDark, cx, cy, radius, mAngleMin, mAngleMax, 0, 12.f);
			g.DrawArc(themeColorAccent, cx, cy, radius, arcStartAngle, arcEndAngle, 0, 12.f);
			g.FillCircle(mMouseIsOver ? themeColorLight : themeColorWhite, cx, cy, radius);
			g.DrawRadialLine(themeColorAccent, cx, cy, angle, 0.5f * radius, .9f * radius, 0, 3.f);
		}
		
	}

private:
	KnobOrigin origin;

	/*
		Returns the start and end angles of the knob's arc, given
		the knob's current value and origin.
	*/
	void GetArcStartAndEndAngles(float knobAngle, float &start, float &end)
	{
		float originAngle = origin == KnobOrigin::Right ? mAngleMax :
			origin == KnobOrigin::Center ? mAngleMin + (mAngleMax - mAngleMin) / 2:
			mAngleMin;
		start = originAngle < knobAngle ? originAngle : knobAngle;
		end = start == originAngle ? knobAngle : originAngle;
	}
};
