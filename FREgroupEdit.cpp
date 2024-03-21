//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FREgroupEdit.h"
#include "FRMGroups.h"
#include "Main.h"
#include "TProtocol.h"
#include "unSQLDbModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEgroupEditFrm *EgroupEditFrm;
//---------------------------------------------------------------------------
__fastcall TEgroupEditFrm::TEgroupEditFrm(AnsiString _groupName)
	: TForm(Owner),groupName(_groupName)
{
}
//---------------------------------------------------------------------------
void __fastcall TEgroupEditFrm::FormCreate(TObject *Sender)
{
	//Заполняем значения полей
	//Текущая группа если выбрана
	//int currGroup = gs->indexCurrentTypeSize;
	//AnsiString groupName = main->cbEtalonGroup->Text;
	//«53366-73-N80Q-NU-UNG-F0-3» (ГОСТ,  диаметр, группа N80Q, тип резьбы, заказчик, тип фаски F0, подмассив образцов 3)
	tsId = SqlDBModule->GetIntFromSql("select rec_id as F1 from TypeSizes where TSName='"+groupName+"'");
	edName->Text = groupName;
	TStringList *parseList = new TStringList();
	parseList->Delimiter = '-';
	parseList->DelimitedText = groupName;
	SqlDBModule->FillComboBoxFromSql("select rec_id,ltrim(rtrim(ShortName)) as [F1] from GOST",cbGost);
	cbGost->ItemIndex = -1;
	for (int i = 0; i < cbGost->Items->Count; i++)
	{
		if (cbGost->Items->Strings[i] == parseList->Strings[0])
		{
			cbGost->ItemIndex = i;
			break;
		}
	}
	SqlDBModule->FillComboBoxFromSql("select distinct 1 as rec_id, Diameter as [F1] from TypeSizes",cbTypeSizes);
	cbTypeSizes->ItemIndex = -1;
	for (int i = 0; i < cbTypeSizes->Items->Count; i++)
	{
		if (cbTypeSizes->Items->Strings[i] == parseList->Strings[1])
		{
			cbTypeSizes->ItemIndex = i;
			break;
		}
	}

	TADOQuery* qry = new TADOQuery(NULL);
	TStringList* tsNames = new TStringList();
	qry->Connection = SqlDBModule->ADOConnectionDB;
	qry->SQL->Add("select rec_id, TSName from Typesizes");
	qry->Open();
	while(!qry->Eof)
	{
		String tsName = qry->FieldByName("TSName")->AsString;
		int tsId = qry->FieldByName("rec_id")->AsInteger;
		tsNames->AddObject(tsName,(TObject*)tsId);
		qry->Next();
	}
	qry->Close();
	delete qry;

	for(int i = 0; i < tsNames->Count; i++)
	{
		TStringList *parseList = new TStringList();
		parseList->Delimiter = '-';
		parseList->DelimitedText = tsNames->Strings[i];
		if(parseList->Count > 2 && cbName->Items->IndexOf(parseList->Strings[2]) < 0)
			cbName->Items->Add(parseList->Strings[2]);
		if(parseList->Count > 3 && cbThreadType->Items->IndexOf(parseList->Strings[3]) < 0)
			cbThreadType->Items->Add(parseList->Strings[3]);
		if(parseList->Count > 4 && cbCustomer->Items->IndexOf(parseList->Strings[4]) < 0)
			cbCustomer->Items->Add(parseList->Strings[4]);
		if(parseList->Count > 5 && cbChampferType->Items->IndexOf(parseList->Strings[5]) < 0)
			cbChampferType->Items->Add(parseList->Strings[5]);
	}

	//SqlDBModule->FillComboBoxFromSql(
	//	"select distinct 1 as rec_id,case when Diameter>100 then substring(TSName,11,3) else substring(TSName,10,3) end as F1 from TypeSizes",
	//	cbName);
	cbName->ItemIndex = -1;
	AnsiString curName = parseList->Strings[2];
	for (int i = 0; i < cbName->Items->Count; i++)
	{
		AnsiString strCb = cbName->Items->Strings[i];
		if (cbName->Items->Strings[i] == curName)
		{
			cbName->ItemIndex = i;
			break;
		}
	}

    cbName->Text = parseList->Strings[2];
	cbThreadType->Text = parseList->Strings[3];
	cbCustomer->Text = parseList->Strings[4];
	cbChampferType->Text = parseList->Strings[5];

	int checkMuftaLevelMax = SqlDBModule->GetIntFromSql("select checkMuftaLevel as F1 from checkMuftaLevel where rec_id="+IntToStr(tsId));
	edCheckMuftaLevelMax->Text = IntToStr(checkMuftaLevelMax);
	int checkMuftaLevelMin = SqlDBModule->GetIntFromSql("select minMuftaLevel as F1 from checkMuftaLevel where rec_id="+IntToStr(tsId));
	edCheckMuftaLevelMin->Text = IntToStr(checkMuftaLevelMin);
	int freqSignal = SqlDBModule->GetIntFromSql("select frequency_value as F1 from TypeSizeFrequencies where TS_id="+IntToStr(tsId));
	int freqDefault = 195000;
	double voltageDefault = 3.0;
	if(freqSignal == 0)
	{
		//Записываем частоту и напряжение
        String sql;
		sql = "insert into TypeSizeFrequencies (TS_id, frequency_value, amplValue)";
		sql += " values("+IntToStr(tsId)+","+IntToStr(freqDefault)+","+FloatToStr(voltageDefault)+")";
		OutputDebugString(sql.c_str());
		SqlDBModule->ExecStrSql(sql);
	}
	lbeFreqSignal->Text = IntToStr(freqDefault);
	double voltage = SqlDBModule->GetFloatFromSql("select amplValue as F1 from TypeSizeFrequencies where TS_id="+IntToStr(tsId));
	if(voltage == 0)voltage = voltageDefault;
	lbeVoltage->Text = FloatToStr(voltage);
}
//---------------------------------------------------------------------------
void __fastcall TEgroupEditFrm::btnCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TEgroupEditFrm::cbKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TComboBox *cb = (TComboBox*)Sender;
	if(Key == VK_RETURN)
	{
		for(int i=0; i < cb->Items->Count; i++)
		if(cb->Text==cb->Items->Strings[i])
		{
			Key = 0;
			return;
		}
		cb->Items->Add(cb->Text);
	}
	if(Key == VK_DELETE)
	{
		for(int i=0; i < cb->Items->Count; i++)
		if(cb->Text==cb->Items->Strings[i])
		{
			cb->Items->Delete(i);
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TEgroupEditFrm::btnAddClick(TObject *Sender)
{
	//int ts = (int)cbTypeSizes->Items->Objects[cbTypeSizes->ItemIndex];
	//int gost = (int)cbGost->Items->Objects[cbGost->ItemIndex];
	UnicodeString sql = "insert into TypeSizes (TSName,Diameter)";
	sql += " values('"+edName->Text+"',"+cbTypeSizes->Text+")";
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	int newRecId = SqlDBModule->GetIntFromSql("select @@identity as F1");
	//Записываем порог определения муфты
	//TODO: проверить корректность
	sql = "insert into checkMuftaLevel (rec_id,checkMuftaLevel,minMuftaLevel)";
	sql += " values("+IntToStr(newRecId)+","+edCheckMuftaLevelMax->Text+","+edCheckMuftaLevelMin->Text+")";
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	//Записываем частоту и напряжение
	sql = "insert into TypeSizeFrequencies (TS_id, frequency_value, amplValue)";
	sql += " values("+IntToStr(newRecId)+","+lbeFreqSignal->Text+","+lbeVoltage->Text+")";
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);

	MainForm->FillGroupsCb();
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TEgroupEditFrm::btnSaveClick(TObject *Sender)
{
	UnicodeString groupName = edName->Text;
	UnicodeString sql = "update TypeSizes set TSName='"+groupName;
	sql += "',Diameter="+cbTypeSizes->Text;
	sql += " where rec_id = "+IntToStr(tsId);
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	sql = "update checkMuftaLevel set checkMuftaLevel="+edCheckMuftaLevelMax->Text;
	sql += ", minMuftaLevel=" + edCheckMuftaLevelMin->Text;
	sql += " where rec_id = "+IntToStr(tsId);
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);

	sql = "update TypeSizeFrequencies set frequency_value="+lbeFreqSignal->Text;
	sql += ", amplValue=" + lbeVoltage->Text;
	sql += " where TS_id = "+IntToStr(tsId);
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);

	MainForm->FillGroupsCb();
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TEgroupEditFrm::onElementChange(TObject *Sender)
{
	AnsiString newName = cbGost->Text+"-"+cbTypeSizes->Text+"-"+cbName->Text+"-"+cbThreadType->Text+"-"+cbCustomer->Text+"-"+cbChampferType->Text;
	edName->Text = newName;
}
//---------------------------------------------------------------------------

