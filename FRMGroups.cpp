//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FRMGroups.h"
#include "Main.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#include "FREgroupEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRGroups *FRGroups;

void __fastcall TFRGroups::beforeInsert(TDataSet* DataSet)
{
	//OutputDebugString(L"TFREtalons::beforeInsert(TDataSet* DataSet)");
	Abort();
}

//---------------------------------------------------------------------------
__fastcall TFRGroups::TFRGroups(TComponent* Owner)
	: TForm(Owner)
{
	if((SqlDBModule->ADOConnectionDB != NULL) && SqlDBModule->ADOConnectionDB->Connected)
	{
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		//qry->SQL->Add("select * from TypeSizes");
		qry->SQL->Add("\
		select ts.rec_id, ts.TSName [Группа], ts.Diameter [Диаметр],isnull(c.cnt,0) [Количество образцов]\
		from TypeSizes ts\
		left join (select ts_id,count(*) cnt from Etalons group by ts_id) c on c.ts_id=ts.rec_id\
		");

		try
		{
			qry->Open();
			qry->First();
			TDataSource *ds = new TDataSource(this);
			ds->DataSet = qry;
			ds->DataSet->BeforeInsert = (TDataSetNotifyEvent)&beforeInsert;
			ds->Enabled = true;
			grid->DataSource = ds;
		}
		catch (EADOError& e)
		{
			AnsiString err = "Ошибка БД:" + e.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TFRGroups::~TFRGroups()
{
	OutputDebugString(L"TFRSprGost destructor");
}
//---------------------------------------------------------------------------
void __fastcall TFRGroups::FormClose(TObject*, TCloseAction &Action)
{
	Action = caFree;
}

void __fastcall TFRGroups::tbButtonClick(TObject *Sender)
{
	TSpeedButton* btn = (TSpeedButton*)Sender;
	TDataSet *ds = grid->DataSource->DataSet;
	try {
		 if(btn->Name == "bFirst")ds->First();
		 if(btn->Name == "bNext")ds->Next();
		 if(btn->Name == "bPrev")ds->Prior();
		 if(btn->Name == "bEnd")ds->Last();
		 if(btn->Name == "bAdd")AddNewGroup();
		 if(btn->Name == "bDel")ds->Delete();
		 if(btn->Name == "bEdit")EditGroup();
	}
	catch (EADOError& e) {
			AnsiString err = "Ошибка БД:" + e.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
	}
}

void __fastcall TFRGroups::AddNewGroup(void)
{
	AnsiString tsName = grid->DataSource->DataSet->FieldByName("Группа")->AsString;
	TEgroupEditFrm *frm = new TEgroupEditFrm(tsName);
	frm->ShowModal();
	delete frm;
	MainForm->FillGroupsCb();
	grid->DataSource->DataSet->Close();
	grid->DataSource->DataSet->Open();
	grid->Refresh();
}

void __fastcall TFRGroups::EditGroup(void)
{
	AnsiString tsName = grid->DataSource->DataSet->FieldByName("Группа")->AsString;
	TEgroupEditFrm *frm = new TEgroupEditFrm(tsName);
	frm->ShowModal();
	delete frm;
	MainForm->FillGroupsCb();
	grid->DataSource->DataSet->Close();
	grid->DataSource->DataSet->Open();
	grid->Refresh();
}
void __fastcall TFRGroups::gridCellClick(TColumn *Column)
{
	MainForm->getGlobalSettings()->indexCurrentTypeSize = grid->DataSource->DataSet->FieldByName("rec_id")->AsInteger;
    MainForm->menuEtalonsClick(this);
}
//---------------------------------------------------------------------------

