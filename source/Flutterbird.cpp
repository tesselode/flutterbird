#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#if IPLUG_DSP
void Flutterbird::InitParameters()
{
	GetParam((int)Parameters::Osc1Waveform)->InitEnum("Oscillator 1 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam((int)Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam((int)Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam((int)Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam((int)Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam((int)Parameters::Osc1Frequency)->InitDouble("Oscillator 1 frequency", .5, .01, 10.0, .01, "hz", 0, "", new IParam::ShapePowCurve(2.0));
	GetParam((int)Parameters::Osc1ToPitch)->InitDouble("Oscillator 1 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc1ToVolume)->InitDouble("Oscillator 1 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc1ToPanning)->InitDouble("Oscillator 1 to panning", 0.0, -twoPi / 4, twoPi / 4, .01);
	
	GetParam((int)Parameters::Osc2Waveform)->InitEnum("Oscillator 2 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam((int)Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam((int)Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam((int)Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam((int)Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam((int)Parameters::Osc2Frequency)->InitDouble("Oscillator 2 frequency", 2.5, .01, 10.0, .01, "hz", 0, "", new IParam::ShapePowCurve(2.0));
	GetParam((int)Parameters::Osc2ToPitch)->InitDouble("Oscillator 2 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc2ToVolume)->InitDouble("Oscillator 2 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc2ToPanning)->InitDouble("Oscillator 2 to panning", 0.0, -twoPi / 4, twoPi / 4, .01);

	GetParam((int)Parameters::Osc3Waveform)->InitEnum("Oscillator 3 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam((int)Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam((int)Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam((int)Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam((int)Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam((int)Parameters::Osc3Frequency)->InitDouble("Oscillator 3 frequency", 5.0, .01, 10.0, .01, "hz", 0, "", new IParam::ShapePowCurve(2.0));
	GetParam((int)Parameters::Osc3ToPitch)->InitDouble("Oscillator 3 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc3ToVolume)->InitDouble("Oscillator 3 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc3ToPanning)->InitDouble("Oscillator 3 to panning", 0.0, -twoPi / 4, twoPi / 4, .01);

	GetParam((int)Parameters::Osc4Waveform)->InitEnum("Oscillator 4 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam((int)Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam((int)Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam((int)Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam((int)Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam((int)Parameters::Osc4Frequency)->InitDouble("Oscillator 4 frequency", 7.5, .01, 10.0, .01, "hz", 0, "", new IParam::ShapePowCurve(2.0));
	GetParam((int)Parameters::Osc4ToPitch)->InitDouble("Oscillator 4 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc4ToVolume)->InitDouble("Oscillator 4 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc4ToPanning)->InitDouble("Oscillator 4 to panning", 0.0, -twoPi / 4, twoPi / 4, .01);

	GetParam((int)Parameters::GlobalToPitch)->InitDouble("Pitch modulation amount", .1, 0.0, 1.0, .01, "", 0, "", new IParam::ShapePowCurve(2.0));
	GetParam((int)Parameters::GlobalToVolume)->InitDouble("Volume modulation amount", .5, 0.0, 1.0, .01);
	GetParam((int)Parameters::GlobalToPanning)->InitDouble("Panning modulation amount", .5, 0.0, 1.0, .01);
	GetParam((int)Parameters::InfinitePanning)->InitBool("Allow infinite panning", false);
	GetParam((int)Parameters::Mix)->InitDouble("Dry/wet mix", 1.0, 0.0, 1.0, .01);
	GetParam((int)Parameters::TestTone)->InitBool("Play test tone", false);
}
#endif

#if IPLUG_EDITOR
void Flutterbird::InitGraphics()
{
	mMakeGraphicsFunc = [&]() {
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};

	mLayoutFunc = [&](IGraphics* pGraphics) {
		auto waveformsSvg = pGraphics->LoadSVG(SVG_WAVEFORMS_FN);
		auto bannerShading = pGraphics->LoadSVG(BANNER_SHADING_FN);
		pGraphics->LoadFont(CAVEAT_FN);
		pGraphics->LoadFont(RALEWAY_FN);
		const IText handwritingText{ 60, themeColorWhite, "Caveat-Bold", IText::kStyleNormal, IText::kAlignNear, IText::kVAlignMiddle };
		const IText labelText{ 20, themeColorWhite, "Raleway-Semibold", IText::kStyleNormal, IText::kAlignCenter, IText::kVAlignMiddle };

		pGraphics->HandleMouseOver(true);
		pGraphics->AttachCornerResizer(kUIResizerScale, false);
		pGraphics->AttachPanelBackground(IColor(255, 50, 50, 50));

		auto rows = 5;
		auto columns = 6;
		auto scale = .85;
		auto switchScale = .75;

		// top bar
		auto topBar = IRECT(0, 0, PLUG_WIDTH, PLUG_GUI_BASE_UNIT * 1.5);
		pGraphics->AttachControl(new IPanelControl(*this, topBar, themeColorAccent));
		pGraphics->AttachControl(new ISVGControl(*this, topBar, bannerShading));
		pGraphics->AttachControl(new ITextControl(*this, topBar.GetHPadded(-16.f),
			"Flutterbird", handwritingText));
		pGraphics->AttachControl(new Knob(*this, topBar.GetGridCell(0, columns - 1, 1, columns).GetScaledAboutCentre(scale).GetVShifted(PLUG_GUI_BASE_UNIT * -.1),
			KnobOrigin::Left, (int)Parameters::Mix));
		pGraphics->AttachControl(new ITextControl(*this, topBar.GetGridCell(0, columns - 1, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .4),
			"Mix", labelText));

		// labels
		auto labelsRow = IRECT(0, topBar.B, PLUG_WIDTH, topBar.B + PLUG_GUI_BASE_UNIT * .5);
		pGraphics->AttachControl(new ITextControl(*this, labelsRow.GetGridCell(0, 1, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Wave", labelText));
		pGraphics->AttachControl(new ITextControl(*this, labelsRow.GetGridCell(0, 2, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Speed", labelText));
		pGraphics->AttachControl(new ITextControl(*this, labelsRow.GetGridCell(0, 3, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Pitch", labelText));
		pGraphics->AttachControl(new ITextControl(*this, labelsRow.GetGridCell(0, 4, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Volume", labelText));
		pGraphics->AttachControl(new ITextControl(*this, labelsRow.GetGridCell(0, 5, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Pan", labelText));

		// main controls
		auto mainSection = IRECT(0, labelsRow.B, PLUG_WIDTH, PLUG_HEIGHT);

		// osc 1
		pGraphics->AttachControl(new ITextControl(*this, mainSection.GetGridCell(0, 0, rows, columns).GetHPadded(-16.f),
			"1", handwritingText));
		pGraphics->AttachControl(new WaveformSwitch(*this, mainSection.GetGridCell(0, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc1Waveform));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(0, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc1Frequency));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(0, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToPitch));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(0, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToVolume));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(0, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToPanning));

		pGraphics->AttachControl(new ITextControl(*this, mainSection.GetGridCell(1, 0, rows, columns).GetHPadded(-16.f),
			"2", handwritingText));
		pGraphics->AttachControl(new WaveformSwitch(*this, mainSection.GetGridCell(1, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc2Waveform));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(1, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc2Frequency));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(1, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToPitch));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(1, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToVolume));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(1, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToPanning));

		pGraphics->AttachControl(new ITextControl(*this, mainSection.GetGridCell(2, 0, rows, columns).GetHPadded(-16.f),
			"3", handwritingText));
		pGraphics->AttachControl(new WaveformSwitch(*this, mainSection.GetGridCell(2, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc3Waveform));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(2, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc3Frequency));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(2, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToPitch));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(2, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToVolume));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(2, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToPanning));

		pGraphics->AttachControl(new ITextControl(*this, mainSection.GetGridCell(3, 0, rows, columns).GetHPadded(-16.f),
			"4", handwritingText));
		pGraphics->AttachControl(new WaveformSwitch(*this, mainSection.GetGridCell(3, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc4Waveform));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(3, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc4Frequency));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(3, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToPitch));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(3, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToVolume));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(3, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToPanning));

		pGraphics->AttachControl(new ITextControl(*this, mainSection.GetGridCell(4, 0, rows, 2).GetHPadded(-16.f),
			"Total", handwritingText));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(4, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::GlobalToPitch));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(4, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::GlobalToVolume));
		pGraphics->AttachControl(new Knob(*this, mainSection.GetGridCell(4, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::GlobalToPanning));
	};
}
#endif

Flutterbird::Flutterbird(IPlugInstanceInfo instanceInfo)
: IPLUG_CTOR((int)Parameters::NumParameters, 1, instanceInfo)
{
#if IPLUG_DSP
	InitParameters();
#endif

#if IPLUG_EDITOR
	InitGraphics();
#endif
}

#if IPLUG_DSP
void Flutterbird::UpdateOscillators()
{
	auto osc1ToPitch = GetParam((int)Parameters::Osc1ToPitch)->Value();
	auto osc2ToPitch = GetParam((int)Parameters::Osc2ToPitch)->Value();
	auto osc3ToPitch = GetParam((int)Parameters::Osc3ToPitch)->Value();
	auto osc4ToPitch = GetParam((int)Parameters::Osc4ToPitch)->Value();
	auto osc1ToVolume = GetParam((int)Parameters::Osc1ToVolume)->Value();
	auto osc2ToVolume = GetParam((int)Parameters::Osc2ToVolume)->Value();
	auto osc3ToVolume = GetParam((int)Parameters::Osc3ToVolume)->Value();
	auto osc4ToVolume = GetParam((int)Parameters::Osc4ToVolume)->Value();
	auto osc1ToPanning = GetParam((int)Parameters::Osc1ToPanning)->Value();
	auto osc2ToPanning = GetParam((int)Parameters::Osc2ToPanning)->Value();
	auto osc3ToPanning = GetParam((int)Parameters::Osc3ToPanning)->Value();
	auto osc4ToPanning = GetParam((int)Parameters::Osc4ToPanning)->Value();

	if (osc1ToPitch != 0.0 || osc1ToVolume != 0.0 || osc1ToPanning != 0.0)
		osc1Value = osc1.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc1Waveform)->Value(), GetParam((int)Parameters::Osc1Frequency)->Value());
	if (osc2ToPitch != 0.0 || osc2ToVolume != 0.0 || osc2ToPanning != 0.0)
		osc2Value = osc2.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc2Waveform)->Value(), GetParam((int)Parameters::Osc2Frequency)->Value());
	if (osc3ToPitch != 0.0 || osc3ToVolume != 0.0 || osc3ToPanning != 0.0)
		osc3Value = osc3.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc3Waveform)->Value(), GetParam((int)Parameters::Osc3Frequency)->Value());
	if (osc4ToPitch != 0.0 || osc4ToVolume != 0.0 || osc4ToPanning != 0.0)
		osc4Value = osc4.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc4Waveform)->Value(), GetParam((int)Parameters::Osc4Frequency)->Value());
}

double Flutterbird::GetReadPosition()
{
	auto osc1ToPitch = GetParam((int)Parameters::Osc1ToPitch)->Value() * GetParam((int)Parameters::GlobalToPitch)->Value();
	auto osc2ToPitch = GetParam((int)Parameters::Osc2ToPitch)->Value() * GetParam((int)Parameters::GlobalToPitch)->Value();
	auto osc3ToPitch = GetParam((int)Parameters::Osc3ToPitch)->Value() * GetParam((int)Parameters::GlobalToPitch)->Value();
	auto osc4ToPitch = GetParam((int)Parameters::Osc4ToPitch)->Value() * GetParam((int)Parameters::GlobalToPitch)->Value();
	auto totalToPitch = osc1ToPitch + osc2ToPitch + osc3ToPitch + osc4ToPitch;

	auto target = 0.0;
	if (osc1ToPitch != 0.0)
	{
		auto oscValue = osc1Value;
		if (osc1ToPitch < 0.0)
		{
			osc1ToPitch *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target += osc1ToPitch * oscValue;
	}
	if (osc2ToPitch != 0.0)
	{
		auto oscValue = osc2Value;
		if (osc2ToPitch < 0.0)
		{
			osc2ToPitch *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target += osc2ToPitch * oscValue;
	}
	if (osc3ToPitch != 0.0)
	{
		auto oscValue = osc3Value;
		if (osc3ToPitch < 0.0)
		{
			osc3ToPitch *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target += osc3ToPitch * oscValue;
	}
	if (osc4ToPitch != 0.0)
	{
		auto oscValue = osc4Value;
		if (osc4ToPitch < 0.0)
		{
			osc4ToPitch *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target += osc4ToPitch * oscValue;
	}

	auto followSpeed = totalToPitch == 0.0 ? 10.0 : 1.0;
	readPosition += (target - readPosition) * followSpeed * dt;
	return writePosition - readPosition * GetSampleRate();
}

void Flutterbird::UpdateVolume()
{
	auto osc1ToVolume = GetParam((int)Parameters::Osc1ToVolume)->Value() * GetParam((int)Parameters::GlobalToVolume)->Value();
	auto osc2ToVolume = GetParam((int)Parameters::Osc2ToVolume)->Value() * GetParam((int)Parameters::GlobalToVolume)->Value();
	auto osc3ToVolume = GetParam((int)Parameters::Osc3ToVolume)->Value() * GetParam((int)Parameters::GlobalToVolume)->Value();
	auto osc4ToVolume = GetParam((int)Parameters::Osc4ToVolume)->Value() * GetParam((int)Parameters::GlobalToVolume)->Value();

	double target = 1.0;

	if (osc1ToVolume != 0.0)
	{
		auto oscValue = osc1Value;
		if (osc1ToVolume < 0.0)
		{
			osc1ToVolume *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target -= osc1ToVolume * oscValue;
	}
	if (osc2ToVolume != 0.0)
	{
		auto oscValue = osc2Value;
		if (osc2ToVolume < 0.0)
		{
			osc2ToVolume *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target -= osc2ToVolume * oscValue;
	}
	if (osc3ToVolume != 0.0)
	{
		auto oscValue = osc3Value;
		if (osc3ToVolume < 0.0)
		{
			osc3ToVolume *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target -= osc3ToVolume * oscValue;
	}
	if (osc4ToVolume != 0.0)
	{
		auto oscValue = osc4Value;
		if (osc4ToVolume < 0.0)
		{
			osc4ToVolume *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		target -= osc4ToVolume * oscValue;
	}

	target = target < 0.0 ? 0.0 : target;
	volume += (target - volume) * 100.0 * dt;
}

void Flutterbird::UpdatePanning()
{
	auto osc1ToPanning = GetParam((int)Parameters::Osc1ToPanning)->Value() * GetParam((int)Parameters::GlobalToPanning)->Value();
	auto osc2ToPanning = GetParam((int)Parameters::Osc2ToPanning)->Value() * GetParam((int)Parameters::GlobalToPanning)->Value();
	auto osc3ToPanning = GetParam((int)Parameters::Osc3ToPanning)->Value() * GetParam((int)Parameters::GlobalToPanning)->Value();
	auto osc4ToPanning = GetParam((int)Parameters::Osc4ToPanning)->Value() * GetParam((int)Parameters::GlobalToPanning)->Value();

	double target = 0.0;

	if (osc1ToPanning != 0.0)
	{
		auto oscValue = osc1Value;
		if (osc1ToPanning < 0.0)
		{
			osc1ToPanning *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		oscValue = -1.0 + 2.0 * oscValue;
		target -= osc1ToPanning * oscValue;
	}
	if (osc2ToPanning != 0.0)
	{
		auto oscValue = osc2Value;
		if (osc2ToPanning < 0.0)
		{
			osc2ToPanning *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		oscValue = -1.0 + 2.0 * oscValue;
		target -= osc2ToPanning * oscValue;
	}
	if (osc3ToPanning != 0.0)
	{
		auto oscValue = osc3Value;
		if (osc3ToPanning < 0.0)
		{
			osc3ToPanning *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		oscValue = -1.0 + 2.0 * oscValue;
		target -= osc3ToPanning * oscValue;
	}
	if (osc4ToPanning != 0.0)
	{
		auto oscValue = osc4Value;
		if (osc4ToPanning < 0.0)
		{
			osc4ToPanning *= -1.0;
			oscValue = 1.0 - oscValue;
		}
		oscValue = -1.0 + 2.0 * oscValue;
		target -= osc4ToPanning * oscValue;
	}
	
	if (!GetParam((int)Parameters::InfinitePanning)->Value())
		target = target < -twoPi / 8 ? -twoPi / 8 : target > twoPi / 8 ? twoPi / 8 : target;
	panning += (target - panning) * 100.0 * dt;
}

double Flutterbird::GetSample(std::vector<double> &buffer, double position)
{
	int p0 = wrap(floor(position) - 1, 0, std::size(buffer) - 1);
	int p1 = wrap(floor(position), 0, std::size(buffer) - 1);
	int p2 = wrap(ceil(position), 0, std::size(buffer) - 1);
	int p3 = wrap(ceil(position) + 1, 0, std::size(buffer) - 1);

	auto x = position - floor(position);
	auto y0 = buffer[p0];
	auto y1 = buffer[p1];
	auto y2 = buffer[p2];
	auto y3 = buffer[p3];

	return interpolate(x, y0, y1, y2, y3);
}

void Flutterbird::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		// update oscillators
		UpdateOscillators();

		// do calculations
		auto readPosition = GetReadPosition();
		UpdateVolume();
		UpdatePanning();
		auto mix = GetParam((int)Parameters::Mix)->Value();
		auto dryVolume = sqrt(1.0 - mix);
		auto wetVolume = sqrt(mix);

		// write to the buffer
		auto inL = inputs[0][s];
		auto inR = inputs[1][s];
		if (GetParam((int)Parameters::TestTone)->Value())
		{
			testTonePhase += 440.0 * dt;
			while (testTonePhase >= 1.0) testTonePhase -= 1.0;
			inL = inR = .25 * sin(testTonePhase * twoPi);
		}
		bufferL[writePosition] = inL;
		bufferR[writePosition] = inR;

		// send wobbly audio to the output
		auto outL = GetSample(bufferL, readPosition) * volume;
		auto outR = GetSample(bufferR, readPosition) * volume;
		adjustPanning(outL, outR, panning, outL, outR);
		outputs[0][s] = inL * dryVolume + outL * wetVolume;
		outputs[1][s] = inR * dryVolume + outR * wetVolume;

		// update write position
		writePosition++;
		if (writePosition == bufferLength) writePosition = 0;
	}
}

void Flutterbird::InitBuffer()
{
	bufferL.clear();
	bufferR.clear();
	bufferLength = tapeLength * GetSampleRate();
	for (int sample = 0; sample < bufferLength; sample++)
	{
		bufferL.push_back(0.0);
		bufferR.push_back(0.0);
	}
	writePosition = 0;
}

void Flutterbird::OnReset()
{
	dt = 1.0 / GetSampleRate();
	InitBuffer();
}
#endif
