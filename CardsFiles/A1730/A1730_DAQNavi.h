//---------------------------------------------------------------------------
#ifndef A1730_DAQNaviH
#define A1730_DAQNaviH
#undef A1730_DAQNaviR
#ifdef A1730_DAQNaviR
//---------------------------------------------------------------------------
#include "A1730.h"
#pragma warn -8060
#include "c:/Advantech/DAQNavi/Inc/bdaqctrl.h"
#pragma warn .8060
#include<SyncObjs.hpp>
using namespace Automation::BDaq;

//---------------------------------------------------------------------------
class A1730_DAQNavi:public A1730
{
private:
	InstantDiCtrl* instantDiCtrl;
	InstantDoCtrl* instantDoCtrl;
	int CheckA1730();
public:
	A1730_DAQNavi(int &_DevNum,int &_codeErr);
	~A1730_DAQNavi(void);
	//--------
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	void WriteSignals(void);
	void ReadSignals(void);
};
//---------------------------------------------------------------------------
#endif
#endif


