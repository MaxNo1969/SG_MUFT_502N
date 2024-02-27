// ---------------------------------------------------------------------------

#pragma hdrstop

#include "ThreadWork.h"
#include <IOUtils.hpp>
#include <math.h>
// #include "TLCard502.h"
// #include "TLogCh502Params.h"
// #include "GSPF052.h"
#include "TSG.h"
#include "TProtocol.h"
#include <ctime.h>
#include "unTExtFunction.h"
#include "SignalListDef.h"
#include "unSQLDbModule.h"
#include "TypeSizeFrequencies.h"
#include "Main.h"
// #include <boost\ratio\ratio.hpp>
// #include <chrono.hpp>
// ---------------------------------------------------------------------------

// ----����������� - ��������� ������� ���������� �� ����������---------------
__fastcall ThreadWork::ThreadWork(bool _createSuspended, TLCardData* _lCardData,
	TGlobalSettings* _globalSettings, TGSPF052* _gen) {
	thGlobalSettings = _globalSettings;
	lCardData = _lCardData;
	int err = -101;
	GSPF = _gen; // new TGSPF052(thGlobalSettings,err);
	solidGroup = new TSG(thGlobalSettings, lCardData);
	Collect = true;
	cs = new TCriticalSection();
	calc_event = new TEvent(NULL, false, false, "calc_event", true);
}

// ---------------------------------------------------------------------------
__fastcall ThreadWork::~ThreadWork(void) {
	Terminate();
	WaitFor();

	// if (GSPF) {
	// delete GSPF;
	// GSPF = NULL;
	// }
	if (gspfStart)
		GSPF->Stop();
	if (solidGroup) {
		delete solidGroup;
		solidGroup = NULL;
	}

	delete calc_event;
	delete cs;
}

// -----������ ������ ������--------------------------------------------------
void __fastcall ThreadWork::Execute() {

	SetStext1("����� \"������\"");
	SetStext2("������� � ��������� ���������");
	TProtocol::ProtocolSave("-----------");
	TProtocol::ProtocolSave(stext1);
	Post(UPDATE_STATUS);

	UnicodeString prepare_result = PrepareForWork();
	if (prepare_result != "ok") {
		SetStext1("����� \"������\" �� ��������!");
		SetStext2(prepare_result);
		TProtocol::ProtocolSave("������: " + stext2);
		Post(UPDATE_STATUS);
		Finally();
		Post(COMPLETE, 0);
		return;
	}

	TProtocol::ProtocolSave("������: ���������� ������ �������");
	bool ret = OnlineCycle();
	if (Terminated) {
		SetStext1("����� \"������\" �� ��������!");
		TProtocol::ProtocolSave("����� \"������\" �� ��������!");
		Post(UPDATE_STATUS);
		Finally();
		return;
	}

	Post(COMPUTE);
	TProtocol::ProtocolSave("���� ����������� �� Main");
	calc_event->WaitFor(INFINITE);
	calc_event->ResetEvent();
	if (Terminated) {
		Post(COMPLETE, 0);
		return;
	}

	TProtocol::ProtocolSave("�������� ����������");
	if (!ret) {
		SetStext1("����� \"������\" �� ��������!");
		TProtocol::ProtocolSave("����� \"������\" �� ��������!");
		Post(UPDATE_STATUS);
		Finally();
		Post(COMPLETE, 0);
		return;
	}
	Sleep(500);

	Post(COMPLETE, (LPARAM)1);
}

// ---------------------------------------------------------------------------
void ThreadWork::Post(WPARAM _w, LPARAM _l) {
	if (PostMessage(Application->Handle, thGlobalSettings->threadMsg, _w,
		_l) == 0)
		TExtFunction::FATAL("ThreadOnLine::Post: �� ���� ������� ���������");
	AnsiString a = "ThreadOnLine::Post: ������� ";
	a += _w;
	a += " ";
	a += _l;
	TProtocol::ProtocolSave(a);
}

// ---------------------------------------------------------------------------
// -----���������� � ������
UnicodeString ThreadWork::PrepareForWork() {
	SetStext2("��������� ������");
	Post(UPDATE_STATUS);

	Post(NEXT_MUFT);
	return "ok";
}

// -------------------------------------------------------------------------------
// ----������ ����, ���������� ���������� � ����������� ��� �������---------------
struct ExitLoop {
	bool &exitLoop;
	TGSPF052 *gen;

	ExitLoop(bool &val, TGSPF052 *g) : exitLoop(val) {
		gen = g;
		exitLoop = true;
	}

	~ExitLoop() {
		gen->Stop();
		exitLoop = false;
	}
};

bool ThreadWork::TestExitLoop() {
	while (exitLoop)
		Sleep(1000);
	return true;
}

bool ThreadWork::OnlineCycle() {
	ExitLoop _exitLoop(exitLoop, GSPF);
	TProtocol::ProtocolSave("������: ����� ������");
	bool result = true; // ����� ��������� ���������� �����
	AnsiString msg = "";
	// ���� �����
	bool timeFlag;
	gspfStart = false;
	timeFlag = CheckMufta(false, 60000 * 5);
	if (!timeFlag) // ���� ��������� ����� ��������, �� �������
	{
		// ��������� ������� ����� �������
		if (SLD->iCC->WasConst(false, 50))
			msg = "������: ������ ������ ���� ����������";
		else
			msg = "������: �� ��������� ���� ������ �����";
		SetStext2(msg);
		Post(UPDATE_STATUS);
		// TExtFunction::ShowBigModalMessage(msg,clBlue);
		TProtocol::ProtocolSave(msg);
		return false;
	}

	 timeFlag = CheckMufta(true, 60000 * 5);
	 if (!timeFlag) // ���� ��������� ����� ��������, �� �������
	 {
	 // ��������� ������� ����� �������
	 if (SLD->iCC->WasConst(false, 50))
	 msg = "������: ������ ������ ���� ����������";
	 else
	 msg = "������: �� ��������� ���� �������� �����";
	 SetStext2(msg);
	 Post(UPDATE_STATUS);
	 // TExtFunction::ShowBigModalMessage(msg,clBlue);
	 TProtocol::ProtocolSave(msg);
	 return false;
	 }

	// gen = new TGSPF052(dGlobalSettings,err);
	if (solidGroup != NULL) {
		delete solidGroup;
	}
	lCardData->ClearSGM();

	solidGroup = new TSG(thGlobalSettings, lCardData);
	Sleep(500); // �������� �� �������� �����
	DWORD LastTime = GetTickCount();
	SetStext2("�������� ����");
	Post(UPDATE_STATUS);
	// �������� ������� �������
	SLD->oSENSORON->Set(true);
	// �������� ����
	gspfStart = true;
	GSPF->Start();
	Sleep(500);
	// ������ �����
	while (true) {
		if (solidGroup->Exec(0) == 2) {
			break;
		}
	}
	// ���������� ��������� �� � ������������� ����
	solidGroup->ResetState();
	GSPF->Stop();

	// ��������� ������� �������
	SLD->oSENSORON->Set(false);
	// SLD->oSENSLOWPOW->Set(false);
	SetStext2("��������� ����");
	Post(UPDATE_STATUS);
	// ������������ ��
	int err = 0;
	csg = solidGroup->Get1FrecSG();
	csg.group = SqlDBModule->GetStrFieldSQL("SolidGroups", "SGName",
		"rec_id=" + IntToStr(csg.group_id), "X", err);
	csg.color = (TColor)SqlDBModule->GetIntFieldSQL("SolidGroups", "Color",
		"rec_id=" + IntToStr(csg.group_id), 65535, err);
	// PanelSG->Caption = csg.group+" "+IntToStr((int)(csg.probability*100))+"%";
	// PanelSG->Color = csg.color;
	// ������� �� ����� �������
	Post(REDRAW);
	// ------
	if (Terminated) // ���� ��������
	{
		Collect = false;
		result = false;
		TProtocol::ProtocolSave("������: ����� � Terminated");
		Finally();
	}
	TProtocol::ProtocolSave("OnlineCycle ��������");
	return result;
}

void ThreadWork::Finally() {
	// ������������� LCard
	if (lCardData != NULL) {
		lCardData->StopSGM();
	}
	else {
		//
	}
	// ��������� ������� �������
	SLD->oSENSORON->Set(false);
}

void ThreadWork::ErrFinally(AnsiString _msg, bool* _Collect, bool* _result) {
	Finally();
	*_Collect = false;
	*_result = false;
	TProtocol::ProtocolSave(_msg);
	SetStext2(_msg);
	Post(UPDATE_STATUS);
}

// ---------------------------------------------------------------------------
AnsiString ThreadWork::GetStext1(void) {
	AnsiString ret;
	cs->Enter(); {
		ret = stext1;
	} cs->Leave();
	return (ret);
}

// ---------------------------------------------------------------------------
AnsiString ThreadWork::GetStext2(void) {
	AnsiString ret;
	cs->Enter(); {
		ret = stext2;
	} cs->Leave();
	return (ret);
}

// ---------------------------------------------------------------------------
void ThreadWork::SetStext1(AnsiString _s) {
	cs->Enter(); {
		stext1 = _s;
	} cs->Leave();
}

// ---------------------------------------------------------------------------
void ThreadWork::SetStext2(AnsiString _s) {
	cs->Enter(); {
		stext2 = _s;
	} cs->Leave();
}

// ---------------------------------------------------------------------------
void ThreadWork::SetCalc() // (bool _IsBrak)
{
	// IsBrak = _IsBrak;
	calc_event->SetEvent();
}

// ---------------------------------------------------------------------------
void ThreadWork::pr(AnsiString _msg) {
	TProtocol::ProtocolSave(_msg);
}

// ---------------------------------------------------------------------------
void ThreadWork::SaveMuftToDB() {
	AnsiString SQL;
	AnsiString ret;

	int TubeNum = 1; // S3.AsInt("TubeNum");
	if (TubeNum == 0 || TubeNum == 200000)
		TubeNum = 1;
	else
		TubeNum++;
}

// ----------------------------------------------------------------------------
CSG ThreadWork::GetSG(void) {
	CSG ret;
	cs->Enter(); {
		ret = csg;
	} cs->Leave();
	return (ret);
}

// ----------------------------------------------------------------------------
void ThreadWork::SetSG(CSG _csg) {
	cs->Enter(); {
		csg = _csg;
	} cs->Leave();
}

// ---------------------------------------------------------------------------
void __fastcall ThreadWork::MainRedraw()
{
	MainForm->ClearCharts();
}
// �������� ������� �����. ���������� true ���� �� ��������� ����� ������ ��������� �� ���������
bool ThreadWork::CheckMufta(bool _waitStatus, int _waitTime) {
	// ���� �����
	int const maxCount = 9;
    int counter = 0;
	bool timeFlag = false;
	DWORD StartTime = GetTickCount();
	if (_waitStatus)
	{
 		Synchronize(MainRedraw);
		SetStext2("��������� ����� � ������!");
	}
	else
		SetStext2("������� ����� �� �������!");
	Post(UPDATE_STATUS);

	TLCardData * muft�SearchData = new TLCardData(lCardData->GetLCard502(), 1,
		lCardData->GetLCard502()->countLogCh, thGlobalSettings);
	TSG* muft�Search = new TSG(thGlobalSettings, muft�SearchData);
	while (true) {
		while (true) {
			if (muft�Search->Exec(0) == 2)
				break;
		}
		muft�Search->ResetState();
		bool result = muft�SearchData->CheckMufta
			(thGlobalSettings->checkMuftaChannel);
			///////////////////////////////////////
		//if (result == _waitStatus) {
		//	break;
		//}

		if(!result && !_waitStatus)
		{
			++counter;
			if(counter >=maxCount)
			{
				break;
			}
		}
		 if(result && !_waitStatus)
		 {
			 counter = 0;
		 }
		 if(result && _waitStatus)
		 {
             break;
         }
		///////////////////////////////////////
		muft�SearchData->ClearSGM();
		if (GetTickCount() - StartTime > _waitTime) {
			timeFlag = true;
			break;
		}
		// ��������� ������� ����� �������
		if (SLD->iCC->WasConst(false, 50)) {
			TProtocol::ProtocolSave("������: ������ ������ ���� ����������");
			timeFlag = true;
			SetStext2("������: ������ ������ ���� ����������");
			Post(UPDATE_STATUS);
			break;
		}
		// �������, �� ���� �� ������
		if (Terminated) {
			TProtocol::ProtocolSave("������: ����� � Terminated");
			timeFlag = true;
			break;
		}
	}
	delete muft�Search;
	muft�SearchData->ClearSGM();
	delete muft�SearchData;
	if (timeFlag) // ���� ��������� ����� ��������, �� false
			return false;
	else // ���� ��������� ������� ������, �� true
			return true;
}
// ---------------------------------------------------------------------------
