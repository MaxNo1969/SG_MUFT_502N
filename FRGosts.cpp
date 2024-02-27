//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "TProtocol.h"
#include "FRGosts.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSprGost *FRSprGost;
//---------------------------------------------------------------------------
__fastcall TFRSprGost::TFRSprGost(TComponent* Owner)
	: TForm(Owner)
{
	if((SqlDBModule->ADOConnectionDB != NULL) && SqlDBModule->ADOConnectionDB->Connected)
	{
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		qry->SQL->Add("select rec_id,Name from GOST order by rec_id");
		try
		{
			qry->Open();
			qry->First();
			TDataSource *ds = new TDataSource(this);
			ds->DataSet = qry;
			Helper helper;
			ds->DataSet->OnNewRecord = &helper.OnNewRecordAdded;
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

__fastcall TFRSprGost::~TFRSprGost()
{
	OutputDebugString(L"TFRSprGost destructor");
}
//---------------------------------------------------------------------------
void __fastcall TFRSprGost::FormClose(TObject*, TCloseAction &Action)
{
	Action = caFree;
}

void __fastcall TFRSprGost::tbButtonClick(TObject *Sender)
{
	TSpeedButton* btn = (TSpeedButton*)Sender;
	TDataSet *ds = grid->DataSource->DataSet;
	try {
		 if(btn->Name == "bFirst")ds->First();
		 if(btn->Name == "bNext")ds->Next();
		 if(btn->Name == "bPrev")ds->Prior();
		 if(btn->Name == "bEnd")ds->Last();
		 if(btn->Name == "bAdd")ds->Append();
		 if(btn->Name == "bDel")ds->Delete();
		 //if(btn->Name == "bPost")
		 if(btn->Name == "bFirst")ds->First();
	}
	catch (EADOError& e) {
			AnsiString err = "Ошибка БД:" + e.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
	}
}

void __fastcall Helper::OnNewRecordAdded(TDataSet *ds)
{
	// ... do stuff
	ds->FieldByName("rec_id")->AsInteger = getNewId();
	ds->FieldByName("Name")->AsString = "Новая запись";
	return;
}
int Helper::getNewId()
{
	int res = -1;
	TADOQuery *qry = new TADOQuery(NULL);
	qry->Connection = SqlDBModule->ADOConnectionDB;
	qry->SQL->Add("select max(rec_id) as maxId from GOST");
	try
	{
		qry->Open();
		qry->First();
		res = qry->FieldByName("maxId")->AsInteger+1;
	}
	catch (EADOError& e)
	{
		AnsiString err = "Ошибка добавления записи:" + e.ToString();
		TProtocol::ProtocolSave(err);
		TExtFunction::ShowBigModalMessage(err, clRed);
		return res;
	}
	delete qry;
	return res;
}


