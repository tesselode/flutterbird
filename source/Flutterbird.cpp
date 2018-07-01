#include "Flutterbird.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

Flutterbird::Flutterbird(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR((int)Parameters::numParameters, 128, instanceInfo)
{
	TRACE;

	IGraphics* pGraphics = MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT);
	pGraphics->AttachPanelBackground(&COLOR_GRAY);

	IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, 60);

	AttachGraphics(pGraphics);

	MakeDefaultPreset((char *) "-", 128);
}

Flutterbird::~Flutterbird() {}

double Flutterbird::GetReadPosition()
{
	return writePosition + .001 * GetSampleRate() * (cos(counter * .001) - 1.0);
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
		counter++;

		bufferL[writePosition] = inputs[0][s];
		bufferR[writePosition] = inputs[1][s];
		
		auto readPosition = GetReadPosition();
		outputs[0][s] = GetSample(bufferL, readPosition);
		outputs[1][s] = GetSample(bufferR, readPosition);

		writePosition++;
		if (writePosition == std::size(bufferL))
			writePosition = 0;
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
}

void Flutterbird::Reset()
{
	TRACE;
	IMutexLock lock(this);

	InitBuffer();
}

void Flutterbird::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);
}
