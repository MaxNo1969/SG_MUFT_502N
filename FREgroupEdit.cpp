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
    int tsId = SqlDBModule->GetIntFromSql("select rec_id as F1 from TypeSizes where TSName='"+groupName+"'");
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

	SqlDBModule->FillComboBoxFromSql(
		"select distinct 1 as rec_id,case when Diameter>100 then substring(TSName,11,10) else substring(TSName,10,9) end as F1 from TypeSizes",
		cbName);
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

	cbThreadType->Text = parseList->Strings[3];
	cbCustomer->Text = parseList->Strings[4];
	cbChampferType->Text = parseList->Strings[5];

	int checkMuftaLevel = SqlDBModule->GetIntFromSql("select checkMuftaLevel as F1 from checkMuftaLevel where rec_id="+IntToStr(tsId));
    edCheckMuftaLevel->Text = IntToStr(checkMuftaLevel);
/*
	SqlDBModule->FillComboBoxFromSql("select distinct 1 as rec_id,ThreadType as [F1] from egroups",cbThreadType);
	cbThreadType->ItemIndex = -1;
	AnsiString curThreadType = SqlDBModule->GetStrFromSql("select ThreadType as [F1] from egroups where rec_id='"+IntToStr(currGroup)+"'");
	for (int i = 0; i < cbThreadType->Items->Count; i++)
	{
		if (cbThreadType->Items->Strings[i] == curThreadType)
		{
			cbThreadType->ItemIndex = i;
			break;
		}
	}

	SqlDBModule->FillComboBoxFromSql("select distinct 1 as rec_id,ChampferType as [F1] from egroups",cbChampferType);
	cbChampferType->ItemIndex = -1;
	AnsiString curChampferType = SqlDBModule->GetStrFromSql("select ChampferType as [F1] from egroups where rec_id='"+IntToStr(currGroup)+"'");
	for (int i = 0; i < cbChampferType->Items->Count; i++)
	{
		if (cbChampferType->Items->Strings[i] == curChampferType)
		{
			cbChampferType->ItemIndex = i;
			break;
		}
	}
*/

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
	sql = "insert into checkMuftaLevel (rec_id,checkMuftaLevel)";
	sql += " values("+IntToStr(newRecId)+","+edCheckMuftaLevel->Text+")";
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TEgroupEditFrm::btnSaveClick(TObject *Sender)
{
	int ts = (int)cbTypeSizes->Items->Objects[cbTypeSizes->ItemIndex];
	UnicodeString groupName = edName->Text;
	UnicodeString sql = "update TypeSizes set TSName='"+groupName;
	sql += "',Diameter="+cbTypeSizes->Text;
	sql += " where rec_id = "+IntToStr(ts);
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	sql = "update checkMuftaLevel set checkMuftaLevel="+edCheckMuftaLevel->Text;
	sql += " where rec_id = "+IntToStr(ts);
	OutputDebugString(sql.c_str());
	SqlDBModule->ExecStrSql(sql);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TEgroupEditFrm::onElementChange(TObject *Sender)
{
	AnsiString newName = cbGost->Text+"-"+cbTypeSizes->Text+"-"+cbName->Text+"-"+cbThreadType->Text+"-"+cbCustomer->Text+"-"+cbChampferType->Text;
	edName->Text = newName;
}
//---------------------------------------------------------------------------

