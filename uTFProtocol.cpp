#include <vcl.h>
#pragma hdrstop
#include "uTFProtocol.h"

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
	//TIniFile* ini = new TIniFile("..\\..\\Settings\\SettingsDefectoscope.ini");
	//Timer1->Interval = ini->ReadInteger("Default", "ProtocolPeriod", 400);
	Timer1->Interval=400;
	//LoadFormPos(this, ini);
	//cbProtocolToFile->Checked = ini->ReadBool("Default", "ProtocolToFile", 0);
	int err=0;
	cbProtocolToFile->Checked=(bool)SqlDBModule->GetIntFieldSQL("SettingsGlobal","ProtocolToFile",NULL,1,err);
	//SqlDBModule->UpdIntSql
	AnsiString FileName = "..\\..\\Protocols\\Protocol_" + FormatDateTime("yyyy_mm_dd", Now()) + ".txt";
	//AnsiString FileName = pGlobalSettings->applPath+ "Protocols\\"+DateToStr(Date()) + ".txt";
	file = fopen(FileName.c_str(), "a");
	if (file == NULL)
	{
		CreateDirectoryW(L"..\\..\\Protocols", 0);
		file = fopen(FileName.c_str(), "a");
	}
	// mProtocol->Perform(WM_VSCROLL,SB_BOTTOM,0);
	strList->Add("Открыли протокол: " + TimeToStr(Time()));
	//if (ini->ReadBool("OtherSettings", "ProtocolVisible", false))
	if ((bool)SqlDBModule->GetIntFieldSQL("SettingsGlobal","ProtocolVisible",NULL,0,err)) {
	  Show();
	} else{
		//
    }

	//delete ini;
  //	Timer1->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TFProtocol::FormDestroy(TObject *Sender)
{
  //	Timer1->Enabled = false;
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

