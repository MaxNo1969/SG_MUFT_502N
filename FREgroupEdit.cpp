//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FREgroupEdit.h"
#include "Main.h"
#include "TProtocol.h"
#include "unSQLDbModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEgroupEditFrm *EgroupEditFrm;
//---------------------------------------------------------------------------
__fastcall TEgroupEditFrm::TEgroupEditFrm(TComponent* Owner)
	: TForm(Owner)
{
	 gs = ((TMainForm*)Owner)->getGlobalSettings();
}
//---------------------------------------------------------------------------
void __fastcall TEgroupEditFrm::FormCreate(TObject *Sender)
{
	//Заполняем значения полей
	//Текущая группа если выбрана
	int currGroup = gs->indexCurrentEtalonGroup;
	edName->Text = SqlDBModule->GetStrFromSql("select name as [F1] from egroups where rec_id='"+IntToStr(currGroup)+"'");
	SqlDBModule->FillComboBoxFromSql("select rec_id,ShortName as [F1] from GOST",cbGost);
	cbGost->ItemIndex = -1;
	for (int i = 0; i < cbGost->Items->Count; i++)
	{
		if ((int)cbGost->Items->Objects[i] == gs->indexCurrentSGGost)
		{
			cbGost->ItemIndex = i;
			break;
		}
	}
	SqlDBModule->FillComboBoxFromSql("select rec_id,TSName as [F1] from TypeSizes",cbTypeSizes);
	cbTypeSizes->ItemIndex = -1;
	for (int i = 0; i < cbTypeSizes->Items->Count; i++)
	{
		if ((int)cbTypeSizes->Items->Objects[i] == gs->indexCurrentTypeSize)
		{
			cbTypeSizes->ItemIndex = i;
			break;
		}
	}

	SqlDBModule->FillComboBoxFromSql("select distinct 1 as rec_id,Customer as [F1] from egroups",cbCustomer);
	cbCustomer->ItemIndex = -1;
	AnsiString curCustomer = SqlDBModule->GetStrFromSql("select customer as [F1] from egroups where rec_id='"+IntToStr(currGroup)+"'");
	for (int i = 0; i < cbCustomer->Items->Count; i++)
	{
		if (cbCustomer->Items->Strings[i] == curCustomer)
		{
			cbCustomer->ItemIndex = i;
			break;
		}
	}

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

