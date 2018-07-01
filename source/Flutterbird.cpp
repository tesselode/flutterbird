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

void Flutterbird::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		bufferL[writePosition] = inputs[0][s];
		bufferR[writePosition] = inputs[1][s];
		writePosition++;
		if (writePosition == std::size(bufferL))
			writePosition = 0;

		outputs[0][s] = bufferL[readPosition];
		outputs[1][s] = bufferR[readPosition];
		readPosition++;
		if (readPosition == std::size(bufferL))
			readPosition = 0;
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
