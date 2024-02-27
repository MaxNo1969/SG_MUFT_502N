#include <vcl.h>
#pragma hdrstop
#include "uTFProtocol.h"
#include<System.IOUtils.hpp>
#pragma package(smart_init)
#pragma resource "*.dfm"
TFProtocol *FProtocol;

// ---------------------------------------------------------------------------
__fastcall TFProtocol::TFProtocol(TComponent* Owner, TCriticalSection* _cs): TForm(Owner)
{
	critSect = _cs;
}
// ---------------------------------------------------------------------------

void __fastcall TFProtocol::FormCreate(TObject *Sender)
{
	strList = new TStringList();
	Timer1->Interval=400;
	cbProtocolToFile->Checked=SqlDBModule->GetBoolParam("ProtocolToFile");
	AnsiString dir = SqlDBModule->GetStringParam("ProtocolDir");
	AnsiString fn = dir + "\\" + FormatDateTime("yyyy_mm_dd", Now()) + ".txt";
	//AnsiString FileName = pGlobalSettings->applPath+ "Protocols\\"+DateToStr(Date()) + ".txt";
	file = fopen(fn.c_str(), "a");
	if (file == NULL)
	{
		TDirectory::CreateDirectory(dir.c_str());
		file = fopen(fn.c_str(), "a");
	}
	strList->Add("Открыли протокол: " + TimeToStr(Time()));
	Visible = SqlDBModule->GetBoolParam("ProtocolVisible");
	Timer1->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TFProtocol::FormDestroy(TObject *Sender)
{
	Timer1->Enabled = false;
	fclose(file);
	delete strList;
}
void TFProtocol::Save(void)
{
	//TIniFile *ini = new TIniFile("..\\..\\Settings\\SettingsDefectoscope.ini");
	//ini->WriteBool("Default", "ProtocolToFile", cbProtocolToFile->Checked);
	SqlDBModule->UpdIntSql("SettingsGlobal","ProtocolToFile",(int)cbProtocolToFile->Checked,NULL);
	//SaveFormPos(this, ini);
	//ini->WriteBool("OtherSettings", "ProtocolVisible", Visible);
	SqlDBModule->UpdIntSql("SettingsGlobal","ProtocolVisible",Visible,NULL);
	//delete ini;

}


// ---------------------------------------------------------------------------
void TFProtocol::Add(AnsiString _msg)
{
	strList->Add(_msg);
}

void __fastcall TFProtocol::Timer1Timer(TObject *Sender)
{
	TTimer* tM = (TTimer*)Sender;
	tM->Enabled = false;
	critSect->Enter();
	{

		for (int i = 0; i < strList->Count; i++)
		{
			AnsiString a = strList->Strings[i];
			if (Visible)
				mProtocol->Lines->Add(a);
			if (cbProtocolToFile->Checked)
			{
				fprintf(file, a.c_str());
				fprintf(file, "\n");
			}
		}
		if (cbProtocolToFile->Checked && strList->Count > 0)
			fflush(file);
		strList->Clear();
	} critSect->Leave();
	tM->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TFProtocol::FormResize(TObject *Sender)
{
	critSect->Enter();
	{
		mProtocol->Width = ClientWidth - mProtocol->Left * 2;
		mProtocol->Height = ClientHeight - mProtocol->Top - mProtocol->Left;
	} critSect->Leave();
}
// ---------------------------------------------------------------------------
void __fastcall TFProtocol::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key!=27)
		return;
	critSect->Enter();
	{
		Close();
	} critSect->Leave();
}
//---------------------------------------------------------------------------

void __fastcall TFProtocol::cbProtocolToFileClick(TObject *Sender)
{
int p=(int)cbProtocolToFile->Checked;
SqlDBModule->UpdIntSql("SettingsGlobal","ProtocolToFile",p,NULL);
}
//---------------------------------------------------------------------------

