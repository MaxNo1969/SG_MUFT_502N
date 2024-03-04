// ---------------------------------------------------------------------------
#ifndef SignalListH
#define SignalListH
#include<SyncObjs.hpp>
#include "TSignal.h"
#include "uCRListT.h"
#include "Latch.h"
#include "A1730.h"
#include "Front.h"
//#include "A1730_DAQNavi.h"
//#include <IniFiles.hpp>
class SignalList : private TThread
{
private:
	void __fastcall Execute();
	CRListT <CSignal> listSignal;
	CRListT <Latch> listLatch;
	CRListT <Front> listFront;
	void WriteSignals(void);
	void FlushSignals(DWORD _buf,DWORD _tick);
	bool Wait(bool _value,CSignal* _signal,DWORD _tm);
public:
	A1730* dev;
private:
	//A1730_DAQNavi* dev;
	int period;
	void LatchesTerminate0(void);
	void CheckFront(DWORD _tick);
	void CheckWait(DWORD _tick);
	bool IsAlarm;
protected:
	CSignal* Find(AnsiString _name,bool _in);
	virtual bool CheckAlarm(void);
public:
	TCriticalSection* cs;
protected:
	bool wasAlarm;
	TStringList* AlarmList;
	void prAlarm(void);
	void pr(AnsiString _msg);
	void SetAlarm0(bool _on);
	virtual void Drop(void)=0;
	bool blockDrop;
public:
	SignalList();
	virtual __fastcall ~SignalList(void);
	void SetPeriod(int _period);
	inline int SignalCount(void)
	{
		return (listSignal.Count());
	}
	inline CSignal* GetSignal(int _index)
	{
		return (listSignal[_index]);
	}
	void LatchesTerminate(void);
	Front* SetFront(CSignal* _signal,bool _value,OnFrontDef _OnFront);
	void ClearFront(Front* _front);
	void ClearFronts(void);
	bool WasAlarm(void);
	void GetAlarmList(TStringList* _alarmList);
	void BlockDrop(bool _val);
};
#endif
