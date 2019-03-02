#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

#if IPLUG_DSP
IParam* Flutterbird::GetParam(Parameters parameter)
{
	return IEditorDelegate::GetParam((int)parameter);
}

void Flutterbird::InitParameters()
{
	auto frequencyDisplayFunc = IParam::DisplayFunc([](double value, WDL_String &out) {
		std::ostringstream s;
		s << std::fixed << std::setprecision(2) << value << "Hz";
		out = WDL_String(s.str().c_str());
	});

	auto percentageDisplayFunc = IParam::DisplayFunc([](double value, WDL_String &out) {
		std::ostringstream s;
		s << std::fixed << std::setprecision(0) << value * 100.0 << "%";
		out = WDL_String(s.str().c_str());
	});

	auto panningDisplayFunc = IParam::DisplayFunc([](double value, WDL_String &out) {
		std::ostringstream s;
		s << std::fixed << std::setprecision(0) << value / (twoPi / 4) * 100.0 << "%";
		out = WDL_String(s.str().c_str());
	});

	GetParam(Parameters::Osc1Waveform)->InitEnum("Osc 1 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam(Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam(Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam(Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam(Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam(Parameters::Osc1Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam(Parameters::Osc1Frequency)->InitDouble("Osc 1 frequency", .5, .01, 20.0, .01, "", 0, "", IParam::ShapePowCurve(2.0), IParam::EParamUnit::kUnitCustom, frequencyDisplayFunc);
	GetParam(Parameters::Osc1TempoSync)->InitEnum("Osc 1 tempo sync", (int)TempoSyncValues::Off, (int)TempoSyncValues::NumTempoSyncValues);
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Off, "Off");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::EightBars, "8 bars");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::SixBars, "6 bars");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::FourBars, "4 bars");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::ThreeBars, "3 bars");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::TwoBars, "2 bars");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::DottedWhole, "6 beats");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Whole, "4 beats");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::DottedHalf, "3 beats");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Half, "2 beats");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::TripletHalf, "Triplet half");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::DottedQuarter, "Dotted quarter");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Quarter, "Quarter");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::TripletQuarter, "Triplet quarter");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::DottedEighth, "Dotted eighth");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Eighth, "Eighth");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::TripletEighth, "Triplet eighth");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::DottedSixteenth, "Dotted sixteenth");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::Sixteenth, "Sixteenth");
	GetParam(Parameters::Osc1TempoSync)->SetDisplayText((int)TempoSyncValues::TripletSixteenth, "Triplet sixteenth");
	GetParam(Parameters::Osc1ToPitch)->InitDouble("Osc 1 -> pitch", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc1ToVolume)->InitDouble("Osc 1 -> volume", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc1ToPanning)->InitDouble("Osc 1 -> panning", 0.0, -twoPi / 4, twoPi / 4, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, panningDisplayFunc);
	
	GetParam(Parameters::Osc2Waveform)->InitEnum("Osc 2 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam(Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam(Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam(Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam(Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam(Parameters::Osc2Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam(Parameters::Osc2Frequency)->InitDouble("Osc 2 frequency", 2.5, .01, 20.0, .01, "", 0, "", IParam::ShapePowCurve(2.0), IParam::EParamUnit::kUnitCustom, frequencyDisplayFunc);
	GetParam(Parameters::Osc2TempoSync)->InitEnum("Osc 2 tempo sync", (int)TempoSyncValues::Off, (int)TempoSyncValues::NumTempoSyncValues);
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Off, "Off");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::EightBars, "8 bars");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::SixBars, "6 bars");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::FourBars, "4 bars");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::ThreeBars, "3 bars");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::TwoBars, "2 bars");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::DottedWhole, "6 beats");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Whole, "4 beats");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::DottedHalf, "3 beats");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Half, "2 beats");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::TripletHalf, "Triplet half");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::DottedQuarter, "Dotted quarter");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Quarter, "Quarter");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::TripletQuarter, "Triplet quarter");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::DottedEighth, "Dotted eighth");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Eighth, "Eighth");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::TripletEighth, "Triplet eighth");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::DottedSixteenth, "Dotted sixteenth");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::Sixteenth, "Sixteenth");
	GetParam(Parameters::Osc2TempoSync)->SetDisplayText((int)TempoSyncValues::TripletSixteenth, "Triplet sixteenth");
	GetParam(Parameters::Osc2ToPitch)->InitDouble("Osc 2 -> pitch", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc2ToVolume)->InitDouble("Osc 2 -> volume", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc2ToPanning)->InitDouble("Osc 2 -> panning", 0.0, -twoPi / 4, twoPi / 4, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, panningDisplayFunc);

	GetParam(Parameters::Osc3Waveform)->InitEnum("Osc 3 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam(Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam(Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam(Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam(Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam(Parameters::Osc3Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam(Parameters::Osc3Frequency)->InitDouble("Osc 3 frequency", 5.0, .01, 20.0, .01, "", 0, "", IParam::ShapePowCurve(2.0), IParam::EParamUnit::kUnitCustom, frequencyDisplayFunc);
	GetParam(Parameters::Osc3TempoSync)->InitEnum("Osc 3 tempo sync", (int)TempoSyncValues::Off, (int)TempoSyncValues::NumTempoSyncValues);
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Off, "Off");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::EightBars, "8 bars");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::SixBars, "6 bars");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::FourBars, "4 bars");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::ThreeBars, "3 bars");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::TwoBars, "2 bars");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::DottedWhole, "6 beats");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Whole, "4 beats");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::DottedHalf, "3 beats");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Half, "2 beats");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::TripletHalf, "Triplet half");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::DottedQuarter, "Dotted quarter");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Quarter, "Quarter");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::TripletQuarter, "Triplet quarter");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::DottedEighth, "Dotted eighth");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Eighth, "Eighth");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::TripletEighth, "Triplet eighth");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::DottedSixteenth, "Dotted sixteenth");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::Sixteenth, "Sixteenth");
	GetParam(Parameters::Osc3TempoSync)->SetDisplayText((int)TempoSyncValues::TripletSixteenth, "Triplet sixteenth");
	GetParam(Parameters::Osc3ToPitch)->InitDouble("Osc 3 -> pitch", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc3ToVolume)->InitDouble("Osc 3 -> volume", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc3ToPanning)->InitDouble("Osc 3 -> panning", 0.0, -twoPi / 4, twoPi / 4, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, panningDisplayFunc);

	GetParam(Parameters::Osc4Waveform)->InitEnum("Osc 4 waveform", (int)Waveforms::Sine, (int)Waveforms::NumWaveforms);
	GetParam(Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Sine, "Sine");
	GetParam(Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Triangle, "Triangle");
	GetParam(Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Saw, "Saw");
	GetParam(Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Square, "Square");
	GetParam(Parameters::Osc4Waveform)->SetDisplayText((int)Waveforms::Drift, "Drift");
	GetParam(Parameters::Osc4Frequency)->InitDouble("Osc 4 frequency", 7.5, .01, 20.0, .01, "", 0, "", IParam::ShapePowCurve(2.0), IParam::EParamUnit::kUnitCustom, frequencyDisplayFunc);
	GetParam(Parameters::Osc4TempoSync)->InitEnum("Osc 4 tempo sync", (int)TempoSyncValues::Off, (int)TempoSyncValues::NumTempoSyncValues);
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Off, "Off");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::EightBars, "8 bars");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::SixBars, "6 bars");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::FourBars, "4 bars");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::ThreeBars, "3 bars");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::TwoBars, "2 bars");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::DottedWhole, "6 beats");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Whole, "4 beats");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::DottedHalf, "3 beats");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Half, "2 beats");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::TripletHalf, "Triplet half");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::DottedQuarter, "Dotted quarter");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Quarter, "Quarter");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::TripletQuarter, "Triplet quarter");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::DottedEighth, "Dotted eighth");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Eighth, "Eighth");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::TripletEighth, "Triplet eighth");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::DottedSixteenth, "Dotted sixteenth");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::Sixteenth, "Sixteenth");
	GetParam(Parameters::Osc4TempoSync)->SetDisplayText((int)TempoSyncValues::TripletSixteenth, "Triplet sixteenth");
	GetParam(Parameters::Osc4ToPitch)->InitDouble("Osc 4 -> pitch", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc4ToVolume)->InitDouble("Osc 4 -> volume", 0.0, -1.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Osc4ToPanning)->InitDouble("Osc 4 -> panning", 0.0, -twoPi / 4, twoPi / 4, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, panningDisplayFunc);

	GetParam(Parameters::GlobalToPitch)->InitDouble("Total -> pitch", .1, 0.0, 1.0, .01, "", 0, "", IParam::ShapePowCurve(2.0), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::GlobalToVolume)->InitDouble("Total -> volume", .5, 0.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::GlobalToPanning)->InitDouble("Total -> panning", .5, 0.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::Mix)->InitDouble("Wet mix", 1.0, 0.0, 1.0, .01, "", 0, "", IParam::ShapeLinear(), IParam::EParamUnit::kUnitCustom, percentageDisplayFunc);
	GetParam(Parameters::TestTone)->InitBool("Test tone", false);
}
#endif

#if IPLUG_EDITOR
void Flutterbird::InitGraphics()
{
	mMakeGraphicsFunc = [&]() {
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};

	mLayoutFunc = [&](IGraphics* pGraphics) {
		auto waveformsSvg = pGraphics->LoadSVG(WAVEFORMS_SVG_FN);
		auto bannerShadingSvg = pGraphics->LoadSVG(BANNER_SHADING_SVG_FN);
		auto toggleSvg = pGraphics->LoadSVG(TOGGLE_SVG_FN);
		pGraphics->LoadFont(HANDWRITING_FONT_FN);
		pGraphics->LoadFont(MONOSPACE_FONT_FN);
		const IText handwritingText{ 60, themeColorWhite, "Caveat-Bold", IText::kStyleNormal, IText::kAlignNear, IText::kVAlignMiddle };
		const IText labelText{ 18, themeColorWhite, "CourierPrimeSans-Italic", IText::kStyleNormal, IText::kAlignCenter, IText::kVAlignMiddle };
		const IText infoText{ 18, themeColorWhite, "CourierPrimeSans-Italic", IText::kStyleNormal, IText::kAlignNear, IText::kVAlignMiddle };

		pGraphics->HandleMouseOver(true);
		pGraphics->AttachCornerResizer(kUIResizerScale, false);
		pGraphics->AttachPanelBackground(IColor(255, 50, 50, 50));

		auto rows = 5;
		auto columns = 7;
		auto scale = .85;
		auto switchScale = .75;

		// top bar
		auto topBar = IRECT(0, 0, PLUG_WIDTH, PLUG_GUI_BASE_UNIT * 1.5);
		pGraphics->AttachControl(new IPanelControl(topBar, themeColorAccent));
		pGraphics->AttachControl(new ISVGControl(topBar, bannerShadingSvg));
		pGraphics->AttachControl(new ITextControl(topBar.GetHPadded(-16.f).GetVShifted(-20.f),
			"Flutterbird", handwritingText));
		parameterNameLabel = new ITextControl(topBar.GetHPadded(-16.f).GetVShifted(16.f),
			"v2.0 alpha 1", infoText);
		pGraphics->AttachControl(parameterNameLabel);
		parameterValueLabel = new ITextControl(topBar.GetHPadded(-16.f).GetVShifted(36.f),
			"", infoText);
		pGraphics->AttachControl(parameterValueLabel);
		pGraphics->AttachControl(new SvgSwitchControl(topBar.GetGridCell(0, columns - 2, 1, columns)
				.GetCentredInside(PLUG_GUI_BASE_UNIT * scale * switchScale, PLUG_GUI_BASE_UNIT * scale * switchScale)
				.GetVShifted(PLUG_GUI_BASE_UNIT * -.1),
			toggleSvg, (int)Parameters::TestTone));
		pGraphics->AttachControl(new ITextControl(topBar.GetGridCell(0, columns - 2, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .4),
			"Test", labelText));
		pGraphics->AttachControl(new Knob(topBar.GetGridCell(0, columns - 1, 1, columns).GetScaledAboutCentre(scale).GetVShifted(PLUG_GUI_BASE_UNIT * -.1),
			KnobOrigin::Left, (int)Parameters::Mix));
		pGraphics->AttachControl(new ITextControl(topBar.GetGridCell(0, columns - 1, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .4),
			"Mix", labelText));

		// labels
		auto labelsRow = IRECT(0, topBar.B, PLUG_WIDTH, topBar.B + PLUG_GUI_BASE_UNIT * .5);
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 1, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Wave", labelText));
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 2, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Speed", labelText));
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 3, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Sync", labelText));
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 4, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Pitch", labelText));
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 5, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Volume", labelText));
		pGraphics->AttachControl(new ITextControl(labelsRow.GetGridCell(0, 6, 1, columns).GetVShifted(PLUG_GUI_BASE_UNIT * .1),
			"Pan", labelText));

		// main controls
		auto mainSection = IRECT(0, labelsRow.B, PLUG_WIDTH, PLUG_HEIGHT);

		// osc 1
		pGraphics->AttachControl(new ITextControl(mainSection.GetGridCell(0, 0, rows, columns).GetHPadded(-16.f),
			"1", handwritingText));
		pGraphics->AttachControl(new SvgSwitchControl(mainSection.GetGridCell(0, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc1Waveform));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(0, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc1Frequency));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(0, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc1TempoSync));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(0, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToPitch));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(0, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToVolume));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(0, 6, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc1ToPanning));

		// osc 2
		pGraphics->AttachControl(new ITextControl(mainSection.GetGridCell(1, 0, rows, columns).GetHPadded(-16.f),
			"2", handwritingText));
		pGraphics->AttachControl(new SvgSwitchControl(mainSection.GetGridCell(1, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc2Waveform));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(1, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc2Frequency));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(1, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc2TempoSync));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(1, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToPitch));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(1, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToVolume));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(1, 6, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc2ToPanning));

		// osc 3
		pGraphics->AttachControl(new ITextControl(mainSection.GetGridCell(2, 0, rows, columns).GetHPadded(-16.f),
			"3", handwritingText));
		pGraphics->AttachControl(new SvgSwitchControl(mainSection.GetGridCell(2, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc3Waveform));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(2, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc3Frequency));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(2, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc3TempoSync));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(2, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToPitch));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(2, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToVolume));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(2, 6, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc3ToPanning));

		// osc 4
		pGraphics->AttachControl(new ITextControl(mainSection.GetGridCell(3, 0, rows, columns).GetHPadded(-16.f),
			"4", handwritingText));
		pGraphics->AttachControl(new SvgSwitchControl(mainSection.GetGridCell(3, 1, rows, columns).GetScaledAboutCentre(scale * switchScale),
			waveformsSvg, (int)Parameters::Osc4Waveform));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(3, 2, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc4Frequency));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(3, 3, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::Osc4TempoSync));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(3, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToPitch));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(3, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToVolume));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(3, 6, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Center, (int)Parameters::Osc4ToPanning));

		// global amounts
		pGraphics->AttachControl(new ITextControl(mainSection.GetGridCell(4, 0, rows, 1).GetHPadded(-16.f),
			"Total amount", handwritingText));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(4, 4, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::GlobalToPitch));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(4, 5, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::GlobalToVolume));
		pGraphics->AttachControl(new Knob(mainSection.GetGridCell(4, 6, rows, columns).GetScaledAboutCentre(scale),
			KnobOrigin::Left, (int)Parameters::GlobalToPanning));
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
bool Flutterbird::SerializeState(IByteChunk & chunk) const
{
	TRACE;
	chunk.PutStr("Flutterbird v2.0 alpha 1");
	return SerializeParams(chunk);
}

int Flutterbird::UnserializeState(const IByteChunk & chunk, int startPos)
{
	TRACE;
	WDL_String versionString;
	startPos = chunk.GetStr(versionString, startPos);
	return UnserializeParams(chunk, startPos);
}

double Flutterbird::TempoSyncToFrequency(TempoSyncValues value)
{
	/*
		the default value of 1 is a placeholder just in case none of
		these cases are touched, somehow, but that should never happen
	*/
	double numberOfBeats = 1;
	switch (value)
	{
	case TempoSyncValues::EightBars:
		numberOfBeats = 32;
		break;
	case TempoSyncValues::SixBars:
		numberOfBeats = 24;
		break;
	case TempoSyncValues::FourBars:
		numberOfBeats = 16;
		break;
	case TempoSyncValues::ThreeBars:
		numberOfBeats = 12;
		break;
	case TempoSyncValues::TwoBars:
		numberOfBeats = 8;
		break;
	case TempoSyncValues::DottedWhole:
		numberOfBeats = 6;
		break;
	case TempoSyncValues::Whole:
		numberOfBeats = 4;
		break;
	case TempoSyncValues::DottedHalf:
		numberOfBeats = 3;
		break;
	case TempoSyncValues::Half:
		numberOfBeats = 2;
		break;
	case TempoSyncValues::TripletHalf:
		numberOfBeats = 4.0/3.0;
		break;
	case TempoSyncValues::DottedQuarter:
		numberOfBeats = 3.0/2.0;
		break;
	case TempoSyncValues::Quarter:
		numberOfBeats = 1;
		break;
	case TempoSyncValues::TripletQuarter:
		numberOfBeats = 2.0/3.0;
		break;
	case TempoSyncValues::DottedEighth:
		numberOfBeats = 3.0/4.0;
		break;
	case TempoSyncValues::Eighth:
		numberOfBeats = 1.0/2.0;
		break;
	case TempoSyncValues::TripletEighth:
		numberOfBeats = 1.0/3.0;
		break;
	case TempoSyncValues::DottedSixteenth:
		numberOfBeats = 3.0/8.0;
		break;
	case TempoSyncValues::Sixteenth:
		numberOfBeats = 1.0/4.0;
		break;
	case TempoSyncValues::TripletSixteenth:
		numberOfBeats = 1.0/6.0;
		break;
	}
	return GetTempo() / (60.0 * numberOfBeats);
}

void Flutterbird::UpdateOscillators()
{
	auto osc1ToPitch = GetParam(Parameters::Osc1ToPitch)->Value();
	auto osc2ToPitch = GetParam(Parameters::Osc2ToPitch)->Value();
	auto osc3ToPitch = GetParam(Parameters::Osc3ToPitch)->Value();
	auto osc4ToPitch = GetParam(Parameters::Osc4ToPitch)->Value();
	auto osc1ToVolume = GetParam(Parameters::Osc1ToVolume)->Value();
	auto osc2ToVolume = GetParam(Parameters::Osc2ToVolume)->Value();
	auto osc3ToVolume = GetParam(Parameters::Osc3ToVolume)->Value();
	auto osc4ToVolume = GetParam(Parameters::Osc4ToVolume)->Value();
	auto osc1ToPanning = GetParam(Parameters::Osc1ToPanning)->Value();
	auto osc2ToPanning = GetParam(Parameters::Osc2ToPanning)->Value();
	auto osc3ToPanning = GetParam(Parameters::Osc3ToPanning)->Value();
	auto osc4ToPanning = GetParam(Parameters::Osc4ToPanning)->Value();

	auto osc1Used = osc1ToPitch != 0.0 || osc1ToVolume != 0.0 || osc1ToPanning != 0.0;
	auto osc2Used = osc2ToPitch != 0.0 || osc2ToVolume != 0.0 || osc2ToPanning != 0.0;
	auto osc3Used = osc3ToPitch != 0.0 || osc3ToVolume != 0.0 || osc3ToPanning != 0.0;
	auto osc4Used = osc4ToPitch != 0.0 || osc4ToVolume != 0.0 || osc4ToPanning != 0.0;

	if (osc1Used)
	{
		auto osc1TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc1TempoSync)->Value();
		auto osc1Frequency = osc1TempoSync == TempoSyncValues::Off ? GetParam(Parameters::Osc1Frequency)->Value()
			: TempoSyncToFrequency(osc1TempoSync);
		osc1Value = osc1.Next(dt, (Waveforms)(int)GetParam(Parameters::Osc1Waveform)->Value(), osc1Frequency);
	}
	if (osc2Used)
	{
		auto osc2TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc2TempoSync)->Value();
		auto osc2Frequency = osc2TempoSync == TempoSyncValues::Off ? GetParam(Parameters::Osc2Frequency)->Value()
			: TempoSyncToFrequency(osc2TempoSync);
		osc2Value = osc2.Next(dt, (Waveforms)(int)GetParam(Parameters::Osc2Waveform)->Value(), osc2Frequency);
	}
	if (osc3Used)
	{
		auto osc3TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc3TempoSync)->Value();
		auto osc3Frequency = osc3TempoSync == TempoSyncValues::Off ? GetParam(Parameters::Osc3Frequency)->Value()
			: TempoSyncToFrequency(osc3TempoSync);
		osc3Value = osc3.Next(dt, (Waveforms)(int)GetParam(Parameters::Osc3Waveform)->Value(), osc3Frequency);
	}
	if (osc4Used)
	{
		auto osc4TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc4TempoSync)->Value();
		auto osc4Frequency = osc4TempoSync == TempoSyncValues::Off ? GetParam(Parameters::Osc4Frequency)->Value()
			: TempoSyncToFrequency(osc4TempoSync);
		osc4Value = osc4.Next(dt, (Waveforms)(int)GetParam(Parameters::Osc4Waveform)->Value(), osc4Frequency);
	}
}

double Flutterbird::GetReadPosition()
{
	auto osc1ToPitch = GetParam(Parameters::Osc1ToPitch)->Value() * GetParam(Parameters::GlobalToPitch)->Value();
	auto osc2ToPitch = GetParam(Parameters::Osc2ToPitch)->Value() * GetParam(Parameters::GlobalToPitch)->Value();
	auto osc3ToPitch = GetParam(Parameters::Osc3ToPitch)->Value() * GetParam(Parameters::GlobalToPitch)->Value();
	auto osc4ToPitch = GetParam(Parameters::Osc4ToPitch)->Value() * GetParam(Parameters::GlobalToPitch)->Value();
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
	relativeReadPosition += (target - relativeReadPosition) * followSpeed * dt;
	return writePosition - relativeReadPosition * GetSampleRate();
}

void Flutterbird::UpdateVolume()
{
	auto osc1ToVolume = GetParam(Parameters::Osc1ToVolume)->Value() * GetParam(Parameters::GlobalToVolume)->Value();
	auto osc2ToVolume = GetParam(Parameters::Osc2ToVolume)->Value() * GetParam(Parameters::GlobalToVolume)->Value();
	auto osc3ToVolume = GetParam(Parameters::Osc3ToVolume)->Value() * GetParam(Parameters::GlobalToVolume)->Value();
	auto osc4ToVolume = GetParam(Parameters::Osc4ToVolume)->Value() * GetParam(Parameters::GlobalToVolume)->Value();

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
	auto osc1ToPanning = GetParam(Parameters::Osc1ToPanning)->Value() * GetParam(Parameters::GlobalToPanning)->Value();
	auto osc2ToPanning = GetParam(Parameters::Osc2ToPanning)->Value() * GetParam(Parameters::GlobalToPanning)->Value();
	auto osc3ToPanning = GetParam(Parameters::Osc3ToPanning)->Value() * GetParam(Parameters::GlobalToPanning)->Value();
	auto osc4ToPanning = GetParam(Parameters::Osc4ToPanning)->Value() * GetParam(Parameters::GlobalToPanning)->Value();

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
		// reset oscillator phases on playback start
		if (mTimeInfo.mTransportIsRunning && !playingPrevious)
		{
			osc1.Reset();
			osc2.Reset();
			osc3.Reset();
			osc4.Reset();
			relativeReadPosition = 0.0;
		}
		playingPrevious = mTimeInfo.mTransportIsRunning;

		// update parameters
		testToneSwitch.Update(dt);

		// update oscillators
		UpdateOscillators();

		// do calculations
		auto readPosition = GetReadPosition();
		UpdateVolume();
		UpdatePanning();
		auto mix = GetParam(Parameters::Mix)->Value();
		auto dryVolume = sqrt(1.0 - mix);
		auto wetVolume = sqrt(mix);

		// write to the buffer
		auto inL = inputs[0][s];
		auto inR = inputs[1][s];
		if (testToneSwitch.value > 0.0)
		{
			testTonePhase += 440.0 * dt;
			while (testTonePhase >= 1.0) testTonePhase -= 1.0;
			auto testToneOut = .25 * sin(testTonePhase * twoPi);
			inL = inputs[0][s] * (1.0 - testToneSwitch.value) + testToneOut * testToneSwitch.value;
			inR = inputs[1][s] * (1.0 - testToneSwitch.value) + testToneOut * testToneSwitch.value;
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

void Flutterbird::OnParamChange(int paramIdx)
{
	switch (paramIdx)
	{
	case (int)Parameters::TestTone:
		testToneSwitch.on = (bool)GetParam(Parameters::TestTone)->Value();
		break;
	}
}

void Flutterbird::OnParamChangeUI(int paramIdx, EParamSource source)
{
	auto ui = GetUI();
	if (!ui) return;

	switch (source)
	{
	case kUI:
	{
		auto param = GetParam((Parameters)paramIdx);
		parameterNameLabel->SetStr(param->GetNameForHost());
		WDL_String valueString;
		param->GetDisplayForHost(valueString);
		parameterValueLabel->SetStr(valueString.Get());
		break;
	}
	}

	switch (paramIdx)
	{
	case (int)Parameters::Osc1TempoSync:
	{
		auto osc1TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc1TempoSync)->Value();
		ui->GetControl(18)->GrayOut(osc1TempoSync != TempoSyncValues::Off);
		break;
	}
	case (int)Parameters::Osc2TempoSync:
	{
		auto osc2TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc2TempoSync)->Value();
		ui->GetControl(25)->GrayOut(osc2TempoSync != TempoSyncValues::Off);
		break;
	}
	case (int)Parameters::Osc3TempoSync:
	{
		auto osc3TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc3TempoSync)->Value();
		ui->GetControl(32)->GrayOut(osc3TempoSync != TempoSyncValues::Off);
		break;
	}
	case (int)Parameters::Osc4TempoSync:
	{
		auto osc4TempoSync = (TempoSyncValues)(int)GetParam(Parameters::Osc4TempoSync)->Value();
		ui->GetControl(39)->GrayOut(osc4TempoSync != TempoSyncValues::Off);
		break;
	}
	case (int)Parameters::GlobalToPitch:
	{
		auto pitchModulationEnabled = (bool)GetParam(Parameters::GlobalToPitch)->Value() != 0.0;
		ui->GetControl(20)->GrayOut(!pitchModulationEnabled);
		ui->GetControl(27)->GrayOut(!pitchModulationEnabled);
		ui->GetControl(34)->GrayOut(!pitchModulationEnabled);
		ui->GetControl(41)->GrayOut(!pitchModulationEnabled);
		break;
	}
	case (int)Parameters::GlobalToVolume:
	{
		auto volumeModulationEnabled = (bool)GetParam(Parameters::GlobalToVolume)->Value() != 0.0;
		ui->GetControl(21)->GrayOut(!volumeModulationEnabled);
		ui->GetControl(28)->GrayOut(!volumeModulationEnabled);
		ui->GetControl(35)->GrayOut(!volumeModulationEnabled);
		ui->GetControl(42)->GrayOut(!volumeModulationEnabled);
		break;
	}
	case (int)Parameters::GlobalToPanning:
	{
		auto panningModulationEnabled = (bool)GetParam(Parameters::GlobalToPanning)->Value() != 0.0;
		ui->GetControl(22)->GrayOut(!panningModulationEnabled);
		ui->GetControl(29)->GrayOut(!panningModulationEnabled);
		ui->GetControl(36)->GrayOut(!panningModulationEnabled);
		ui->GetControl(43)->GrayOut(!panningModulationEnabled);
		break;
	}
	}
}

#endif
