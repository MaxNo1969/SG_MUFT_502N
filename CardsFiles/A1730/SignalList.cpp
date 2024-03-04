#pragma hdrstop
#include "SignalList.h"
#include "TProtocol.h"
#include "unSQLDbModule.h"
#include "unTExtFunction.h"
#pragma package(smart_init)

SignalList::SignalList() {
	dev = NULL;
	cs = new TCriticalSection();
	int err;
	period = SqlDBModule->GetIntFieldSQL("PCIE1730Params", "SignalListTimeout", NULL, 50, err);
	SqlDBModule->ADOQueryDB->Close();
	AnsiString sql = "select rec_id,SignalListTimeout,Devnum,fName,fchNum,fIsIn,fHint,";
	sql += "(CASE fIsIzol WHEN 1 THEN fchNum+16  ELSE fchNum+0 END) as realChNum";
	sql += "  FROM PCIE1730Params order by Devnum,fIsIn desc,realChNum";
	SqlDBModule->ADOQueryDB->SQL->Text = sql;
	SqlDBModule->ADOQueryDB->Open();
	while (!SqlDBModule->ADOQueryDB->Eof) {
		// наименование сигнала
		AnsiString name = SqlDBModule->ADOQueryDB->FieldByName("fName")->AsString;
		// AnsiString h = SqlDBModule->ADOQueryDB->FieldByName("fHint")->AsString;
		// вход или выход
		bool isIn = (bool)SqlDBModule->ADOQueryDB->FieldByName("fIsIn")->AsInteger;
		// bool d = (bool)SqlDBModule->ADOQueryDB->FieldByName("fDigital")->AsInteger;
		// номер канала
		int chNum = SqlDBModule->ADOQueryDB->FieldByName("fchNum")->AsInteger;
		// номер канала реальный с учетом типа канала изолированный или ТТЛ
		int realChNum = SqlDBModule->ADOQueryDB->FieldByName("realChNum")->AsInteger;
		listSignal.Add(new CSignal(name, isIn, realChNum, WriteSignals, cs, Wait));
		SqlDBModule->ADOQueryDB->Next();
	}
	SqlDBModule->ADOQueryDB->Close();
	IsAlarm = false;
	wasAlarm = false;
	AlarmList = new TStringList();
}

__fastcall SignalList::~SignalList(void) {
	if (!this->Terminated) {
		Terminate();
		WaitFor();
	}
	else {
		//
	}
	delete dev;
	delete cs;
	delete AlarmList;

}

void SignalList::FlushSignals(DWORD _buf, DWORD _tick) {
	for (int i = 0; i < listSignal.Count(); i++) {
		CSignal* p = listSignal[i];
		if (!p->in)
			continue;
		bool value = (_buf & (((DWORD)1) << p->index)) != 0;
		p->value_prev = p->value;
		if (value != p->value) {
			p->value = value;
			p->last_changed = _tick;
		}
	}
}

void _fastcall SignalList::Execute() {
	while (true) {
		if (Terminated)
			break;
		cs->Enter(); {
			DWORD v = dev ?dev->Read():0;
			DWORD tick = GetTickCount();
			FlushSignals(v, tick);
			if (IsAlarm) {
				if (!wasAlarm) {
					if (CheckAlarm())
						LatchesTerminate0();
				}
			}
			CheckFront(tick);
			CheckWait(tick);
			if (!blockDrop)
				Drop();
		} cs->Leave();
		Sleep(period);
		if (Terminated)
			break;
	}
}

bool SignalList::Wait(bool _value, CSignal* _signal, DWORD _tm) {
	TEvent* event = new TEvent(true);
	Latch* lp = new Latch(_value, _signal, event);
	cs->Enter(); {
		listLatch.Add(lp);
	} cs->Leave();
	bool ret = event->WaitFor(_tm) == wrSignaled;
	delete event;
	cs->Enter(); {
		if (lp->terminate)
			ret = false;
		listLatch.Remove(lp);
	} cs->Leave();
	return (ret);
}

void SignalList::WriteSignals(void) {
	DWORD buf = dev?dev->ReadOut():0;
	CSignal* p;
	for (int i = 0; i < listSignal.Count(); i++) {
		p = listSignal[i];
		if (p->in)
		{
			buf = dev?dev->Read():0;
			if (p->value)
				buf |= ((DWORD)1) << p->index;
			else
				buf &= ~(((DWORD)1) << p->index);
            if(dev)dev->WriteIn(buf);
			continue;
		}
		if (p->value)
			buf |= ((DWORD)1) << p->index;
		else
			buf &= ~(((DWORD)1) << p->index);
	}
	if(dev)dev->Write(buf);
}

CSignal* SignalList::Find(AnsiString _name, bool _in) {
	for (int i = 0; i < listSignal.Count(); i++) { // временно для отладки
		AnsiString a = listSignal[i]->name;
		bool in = listSignal[i]->in;
		//
		if (listSignal[i]->name == _name && listSignal[i]->in == _in) {
			return (listSignal[i]);
		}
		else {
			a = "Не угадал";
		}
	}
	AnsiString a = "Signals::Find: сигнал ";
	a += _name;
	a += " не найден";
	TExtFunction::FATAL(a);
}

void SignalList::SetPeriod(int _period) {
	cs->Enter(); {
		period = _period;
	} cs->Leave();
}

bool SignalList::CheckAlarm(void) {
	return (false);
}

void SignalList::LatchesTerminate0(void) {
	for (int i = 0; i < listLatch.Count(); i++) {
		Latch* lp = listLatch[i];
		lp->terminate = true;
		lp->event->SetEvent();
	}
}

Front* SignalList::SetFront(CSignal* _signal, bool _value, OnFrontDef _OnFront) {
	Front* front;
	cs->Enter(); {
		front = listFront.Add(new Front(_signal, _value, _OnFront));
	} cs->Leave();
	return (front);
}

void SignalList::ClearFront(Front* _front) {
	cs->Enter(); {
		listFront.Remove(_front);
	} cs->Leave();
}

void SignalList::ClearFronts(void) {
	cs->Enter(); {
		listFront.Clear();
	} cs->Leave();
}

void SignalList::CheckFront(DWORD _tick) {
	for (int i = 0; i < listFront.Count(); i++) {
		Front* f = listFront[i];
		if (f->signal->value == f->value && f->signal->value_prev != f->value)
			f->OnFront(_tick);
	}
}

void SignalList::CheckWait(DWORD _tick) {
	Latch* lp;
	for (int i = 0; i < listLatch.Count(); i++) {
		Latch* lp = listLatch[i];
		if (lp->signal->value == lp->value)
			lp->event->SetEvent();
	}
}

void SignalList::LatchesTerminate(void) {
	cs->Enter(); {
		LatchesTerminate0();
	} cs->Leave();
}

void SignalList::SetAlarm0(bool _on) {
	cs->Enter(); {
		IsAlarm = _on;
		wasAlarm = false;
		AlarmList->Clear();
	} cs->Leave();
}

bool SignalList::WasAlarm(void) {
	bool ret;
	cs->Enter(); {
		ret = wasAlarm;
	} cs->Leave();
	return (ret);
}

void SignalList::GetAlarmList(TStringList* _alarmList) {
	cs->Enter(); {
		_alarmList->Clear();
		for (int i = 0; i < AlarmList->Count; i++)
			_alarmList->Add(AlarmList->Strings[i]);
	} cs->Leave();
}

void SignalList::prAlarm(void) {
	for (int i = 0; i < AlarmList->Count; i++)
		pr(AlarmList->Strings[i]);
}

void SignalList::pr(AnsiString _msg) {
	TProtocol::ProtocolSave(_msg);
}

void SignalList::BlockDrop(bool _val) {
	cs->Enter(); {
		blockDrop = _val;
	} cs->Leave();
}
