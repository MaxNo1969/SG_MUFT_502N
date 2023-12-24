//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Hantek1025G.h"
//#include "HTDDSDll.h"
#include <System.hpp>
//#pragma comment(lib, "HTDDSDll.lib")
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
DLL_API int WINAPI DDSSearch();
DLL_API BOOL WINAPI DDSSetFrequency(int index, double frequency, int* wavePointNum, int* TNum);
DLL_API BOOL WINAPI DDSGetMeasure(int index, BOOL bFreq, double* measure);
DLL_API BOOL WINAPI DDSSetSingleWave(int index, BOOL bSingle);
DLL_API BOOL WINAPI DDSResetCounter(int index);
DLL_API BOOL WINAPI DDSSetTrigger(int index, BOOL bInter, BOOL bEdge);
DLL_API BOOL WINAPI DDSGetDigitalIn(int index, unsigned short* In);
DLL_API BOOL WINAPI DDSSetDigitalOut(int index, unsigned short Out);
DLL_API BOOL WINAPI DDSDownload(int index, unsigned short* buf, int number);
DLL_API BOOL WINAPI DDSSetDIOMode(int index, BOOL mode);
DLL_API BOOL WINAPI DDSCheck(int index);
DLL_API BOOL WINAPI DDSSetPowerOnOutput(int index, BOOL bOpen);
*/
#ifndef TestHantek
Hantek1025G::Hantek1025G()
{
	m_frequency = 1000.0;
	m_volt = 2.0f;
	m_nWavePointNum = 4096;
	m_nWavePeriodNum = 1;
	m_iDevice = 0;
	hDLL = LoadLibraryA("HTDDSDll.dll");
	if (hDLL != NULL)
	{
		DDSSearch        = (LPDDSSearch)GetProcAddress(hDLL, "DDSSearch");
		DDSDownload      = (LPDDSDownload)GetProcAddress(hDLL, "DDSDownload");
		DDSResetCounter  = (LPDDSResetCounter)GetProcAddress(hDLL, "DDSResetCounter");
		DDSSetFrequency  = (LPDDSSetFrequency)GetProcAddress(hDLL, "DDSSetFrequency");
		DDSCheck         = (LPDDSCheck)GetProcAddress(hDLL, "DDSCheck");
		DDSSetPowerOnOutput = (LPDDSSetPowerOnOutput)GetProcAddress(hDLL, "DDSSetPowerOnOutput");
		DDSSetSingleWave = (LPDDSSetSingleWave)GetProcAddress(hDLL, "DDSSetSingleWave");
		if(!(DDSSearch() && DDSCheck(m_iDevice)))
		{
			 FreeLibrary(hDLL);
			 hDLL = NULL;
			 MessageDlg("Генератор не инициализировался", mtError, TMsgDlgButtons() << mbOK, NULL);
			 return;
		}
		DDSSetPowerOnOutput(m_iDevice, 0);
	}
	else
	{
		MessageDlg("Нет библиотеки \"HTDDSDll.dll\"", mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}
Hantek1025G::~Hantek1025G()
{
	if(NULL == hDLL) return;
	Stop();
    Sleep(1000);
	FreeLibrary(hDLL);
}
void Hantek1025G::Start()
{
	if(NULL == hDLL) return;
	DDSDownload(m_iDevice, buffer, m_nWavePointNum);
	DDSSetSingleWave(m_iDevice, 0);
}

void Hantek1025G::Stop()
{
	if(NULL == hDLL) return;
	DDSSetSingleWave(m_iDevice, 1);
}

void Hantek1025G::CreateWave()
{
	for (int i = 0; i < m_nWavePointNum; i++)
	{
		float tmp=m_volt/MAX_VOLT*Sin((i*1.0/m_nWavePointNum)*2*3.14159f*m_nWavePeriodNum);
		tmp = 2048-2047*tmp;
		if (tmp > 4095)
			tmp = 4095;
		else if (tmp < 0)
			tmp = 0;
		buffer[i] = (unsigned short)tmp;
	}
}
void Hantek1025G::FormSignal(int _valueFrec,double _valueAmpl)
{
	if(NULL == hDLL) return;
	m_frequency = _valueFrec;
	m_volt = _valueAmpl;
	DDSSetFrequency(m_iDevice, m_frequency, &m_nWavePointNum, &m_nWavePeriodNum);
	CreateWave();
}
#endif


