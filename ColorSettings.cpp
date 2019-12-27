// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ColorSettings.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormColor *FormColor;

// ---------------------------------------------------------------------------
__fastcall TFormColor::TFormColor(TComponent* Owner) : TForm(Owner)
{
}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::FormCreate(TObject *Sender)
{
	AnsiString str = "";
    ADOQuery1->Active = false;
	ADOQuery1->Connection = SqlDBModule->ADOConnectionDB;
	str = "SELECT rec_id, SGName, Color, Gost_id FROM SolidGroups";
	str += " ORDER BY rec_id ASC";
	ADOQuery1->SQL->Text = str;
	ADOQuery1->ExecSQL();
	ADOQuery1->Active = true;
	for(int i = 0; i< DBGrid1->Columns->Count; i++)
	{
		DBGrid1->Columns->operator [](i)->Width = 64;
    }
//	ini = new TIniFile("..\\..\\Settings\\SettingsMuftaSG.ini");
//	PanelNetU->Color = (TColor)ini->ReadInteger(L"Color", L"NetU", 255);
//	PanelSignalSG->Color = (TColor)ini->ReadInteger(L"Color", L"SignalSG",16711680);
//	PanelSynchroDetector->Color = (TColor)ini->ReadInteger(L"Color", L"SynchroDetector", 41984);
//	PanelInductionSignal->Color = (TColor)ini->ReadInteger(L"Color", L"InductionSignal",16711680 );
//	PanelSynchroSignal->Color = (TColor)ini->ReadInteger(L"Color", L"SynchroSignal", 10066329 );

//	ActiveIn->Color = (TColor)ini->ReadInteger(L"Color", L"ActiveIn", 1503543);
//	ActiveOut->Color = (TColor)ini->ReadInteger(L"Color", L"ActiveOut", 465649);
//	NotActiveOut->Color = (TColor)ini->ReadInteger(L"Color", L"NotActiveOut", 8421504);
//	NotActiveIn->Color = (TColor)ini->ReadInteger(L"Color", L"NotActiveIn", 12425481);

//	sgD->Color = SolidGroup_D = (TColor)ini->ReadInteger(L"Color", L"sgD",65535);
//	sgK->Color = SolidGroup_K = (TColor)ini->ReadInteger(L"Color", L"sgK",65280);
//	sgE->Color = SolidGroup_E = (TColor)ini->ReadInteger(L"Color", L"sgE",16711680);

}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::PanelSignalSGClick(TObject *Sender)
{
	TPanel* Pan = dynamic_cast<TPanel*>(Sender);
	if (ColorDialog->Execute())
		Pan->Color = ColorDialog->Color;
}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::BCloseClick(TObject *Sender)
{
	FormColor->Close();
}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::BSaveClick(TObject *Sender)
{
//	ini->WriteInteger(L"Color", L"NetU", PanelNetU->Color);
//	ini->WriteInteger(L"Color", L"SignalSG", PanelSignalSG->Color);
//	ini->WriteInteger(L"Color", L"SynchroDetector", PanelSynchroDetector->Color);
//	ini->WriteInteger(L"Color", L"InductionSignal", PanelInductionSignal->Color);
//	ini->WriteInteger(L"Color", L"SynchroSignal", PanelSynchroSignal->Color);

//	ini->WriteInteger(L"Color", L"ActiveIn", ActiveIn->Color);
//	ini->WriteInteger(L"Color", L"NotActiveIn", NotActiveIn->Color);
//	ini->WriteInteger(L"Color", L"ActiveOut", ActiveOut->Color);
//	ini->WriteInteger(L"Color", L"NotActiveOut", NotActiveOut->Color);

//	ini->WriteInteger(L"Color", L"sgD", sgD->Color);
//	SolidGroup_D = sgD->Color;
//	ini->WriteInteger(L"Color", L"sgK", sgK->Color);
//	SolidGroup_K = sgK->Color;
//	ini->WriteInteger(L"Color", L"sgE", sgE->Color);
//	SolidGroup_E = sgE->Color;
}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		FormColor->Close();
}
// ---------------------------------------------------------------------------
void __fastcall TFormColor::DBGrid1DblClick(TObject *Sender)
{
	int rec_id = ADOQuery1->FieldByName("rec_id")->AsInteger;
	if(rec_id)
	{
		ColorDialog->Color = (TColor)ADOQuery1->FieldByName("Color")->AsInteger;
		if (ColorDialog->Execute())
		{
			ADOQuery1->Active = false;
			SqlDBModule->UpdIntSql("SolidGroups","Color",(int)ColorDialog->Color
				,"rec_id = "+IntToStr(rec_id));
			ADOQuery1->ExecSQL();
			ADOQuery1->Active = true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormColor::FormClose(TObject *Sender, TCloseAction &Action)
{
	ADOQuery1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormColor::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, TGridDrawState State)
{
	if(DataCol==2) //если это ячейка с цветом, то закрасим ее
		DBGrid1->Canvas->Brush->Color
			= (TColor)DBGrid1->DataSource->DataSet->FieldByName("Color")->AsInteger;
	DBGrid1->Canvas->FillRect(Rect);
	//включим прорисовку грида
	DBGrid1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

