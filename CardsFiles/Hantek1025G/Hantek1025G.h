// ---------------------------------------------------------------------------

#ifndef Hantek1025GH
#define Hantek1025GH
#include <Windows.h>
#define BUF_SIZE	4096
#define MAX_VOLT	3.5f
#define MEA_FREQ	0
#define MEA_COUNT	1

typedef int (CALLBACK *LPDDSDownload)(int index, unsigned short* buf, int number);
typedef int (CALLBACK *LPDDSResetCounter)(int index);
typedef int (CALLBACK *LPDDSSetFrequency)(int index, double frequency, int* wavePointNum, int* TNum);

class Hantek1025G
{
	HINSTANCE hDLL;
	LPDDSDownload DDSDownload;
	LPDDSResetCounter DDSResetCounter;
	LPDDSSetFrequency DDSSetFrequency;
public:
	double m_frequency;
	float m_volt;

	int m_iDevice; // the index of device
	int m_nWavePointNum; // the point number of waveform to download
	int m_nWavePeriodNum; // the period number of waveform to download
	unsigned short buffer[BUF_SIZE]; // the buffer of waveform to download
	float m_iMeasure;

	Hantek1025G();
	~Hantek1025G();
	void Start();
	void Stop();
	void CreateWave();
	void FormSignal(int _valueFrec, double _valueAmpl);
};
// ---------------------------------------------------------------------------
#endif
