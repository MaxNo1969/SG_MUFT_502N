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

void __fastcall TFRSprGost::beforeInsert(TDataSet* DataSet)
{
	//OutputDebugString(L"TFREtalons::beforeInsert(TDataSet* DataSet)");
	Abort();
}

//---------------------------------------------------------------------------
__fastcall TFRSprGost::TFRSprGost(TComponent* Owner)
	: TForm(Owner)
{
	if((SqlDBModule->ADOConnectionDB != NULL) && SqlDBModule->ADOConnectionDB->Connected)
	{
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		qry->SQL->Add("select * from GOST order by rec_id");
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
			AnsiString err = "������ ��:" + e.ToString();
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
			AnsiString err = "������ ��:" + e.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
	}
}



