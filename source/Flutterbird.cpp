#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

void Flutterbird::InitParmeters()
{
	GetParam((int)Parameters::Osc1Waveform)->InitEnum("Oscillator 1 waveform", (int)Waveforms::Sine, (int)Waveforms::numWaveforms);
	GetParam((int)Parameters::Osc1Frequency)->InitDouble("Oscillator 1 frequency", 1.0, .01, 10.0, .01, "", "", 2.0);
	GetParam((int)Parameters::Osc1ToPitch)->InitDouble("Oscillator 1 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc1ToVolume)->InitDouble("Oscillator 1 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc2Waveform)->InitEnum("Oscillator 2 waveform", (int)Waveforms::Sine, (int)Waveforms::numWaveforms);
	GetParam((int)Parameters::Osc2Frequency)->InitDouble("Oscillator 2 frequency", 1.0, .01, 10.0, .01, "", "", 2.0);
	GetParam((int)Parameters::Osc2ToPitch)->InitDouble("Oscillator 2 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc2ToVolume)->InitDouble("Oscillator 2 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc3Waveform)->InitEnum("Oscillator 3 waveform", (int)Waveforms::Sine, (int)Waveforms::numWaveforms);
	GetParam((int)Parameters::Osc3Frequency)->InitDouble("Oscillator 3 frequency", 1.0, .01, 10.0, .01, "", "", 2.0);
	GetParam((int)Parameters::Osc3ToPitch)->InitDouble("Oscillator 3 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc3ToVolume)->InitDouble("Oscillator 4 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc4Waveform)->InitEnum("Oscillator 4 waveform", (int)Waveforms::Sine, (int)Waveforms::numWaveforms);
	GetParam((int)Parameters::Osc4Frequency)->InitDouble("Oscillator 4 frequency", 1.0, .01, 10.0, .01, "", "", 2.0);
	GetParam((int)Parameters::Osc4ToPitch)->InitDouble("Oscillator 4 to pitch", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::Osc4ToVolume)->InitDouble("Oscillator 4 to volume", 0.0, -1.0, 1.0, .01);
	GetParam((int)Parameters::GlobalToPitch)->InitDouble("Pitch modulation amount", .5, 0.0, 1.0, .01);
	GetParam((int)Parameters::GlobalToVolume)->InitDouble("Volume modulation amount", .5, 0.0, 1.0, .01);
	GetParam((int)Parameters::Mix)->InitDouble("Dry/wet mix", 1.0, 0.0, 1.0, .01);
}

Flutterbird::Flutterbird(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR((int)Parameters::numParameters, 128, instanceInfo)
{
	TRACE;

	InitParmeters();

	IGraphics* pGraphics = MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT, 120);
	pGraphics->AttachPanelBackground(&COLOR_GRAY);

	debugText = new ITextControl(this, IRECT(0, 0, 300, 300), new IText(24), "Test");
	pGraphics->AttachControl(debugText);

	IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, 60);

	AttachGraphics(pGraphics);

	MakeDefaultPreset((char *) "-", 128);
}

Flutterbird::~Flutterbird() {}

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

	if (osc1ToPitch != 0.0 || osc1ToVolume != 0.0)
		osc1Value = osc1.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc1Waveform)->Value(), GetParam((int)Parameters::Osc1Frequency)->Value());
	if (osc2ToPitch != 0.0 || osc2ToVolume != 0.0)
		osc2Value = osc2.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc2Waveform)->Value(), GetParam((int)Parameters::Osc2Frequency)->Value());
	if (osc3ToPitch != 0.0 || osc3ToVolume != 0.0)
		osc3Value = osc3.Next(dt, (Waveforms)(int)GetParam((int)Parameters::Osc3Waveform)->Value(), GetParam((int)Parameters::Osc3Frequency)->Value());
	if (osc4ToPitch != 0.0 || osc4ToVolume != 0.0)
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

double Flutterbird::GetVolume()
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
	return volume;
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

void Flutterbird::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		UpdateOscillators();

		bufferL[writePosition] = inputs[0][s];
		bufferR[writePosition] = inputs[1][s];
		
		auto readPosition = GetReadPosition();
		auto volume = GetVolume();
		auto outL = GetSample(bufferL, readPosition) * volume;
		auto outR = GetSample(bufferR, readPosition) * volume;
		auto mix = GetParam((int)Parameters::Mix)->Value();
		outputs[0][s] = inputs[0][s] * sqrt(1.0 - mix) + outL * sqrt(mix);
		outputs[1][s] = inputs[1][s] * sqrt(1.0 - mix) + outR * sqrt(mix);

		writePosition++;
		if (writePosition == std::size(bufferL))
			writePosition = 0;

		//debugText->SetTextFromPlug(strdup(std::to_string(writePosition - readPosition).c_str()));
	}
}

void Flutterbird::InitBuffer()
{
	bufferL.clear();
	bufferR.clear();
	for (int i = 0; i < bufferLength * GetSampleRate(); i++)
		bufferL.push_back(0.0);
	for (int i = 0; i < bufferLength * GetSampleRate(); i++)
		bufferR.push_back(0.0);
	writePosition = 0;
}

void Flutterbird::Reset()
{
	TRACE;
	IMutexLock lock(this);

	dt = 1.0 / GetSampleRate();
	InitBuffer();
}

void Flutterbird::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);
}
