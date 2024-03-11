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
		qry->SQL->Add("select * from egroups");
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
			AnsiString err = "Îøèáêà ÁÄ:" + e.ToString();
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
		 //if(btn->Name == "bPost")
		 //if(btn->Name == "bFirst")ds->First();
	}
	catch (EADOError& e) {
			AnsiString err = "Îøèáêà ÁÄ:" + e.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
	}
}

void __fastcall TFRGroups::AddNewGroup(void)
{
	TEgroupEditFrm *frm = new TEgroupEditFrm(this);
	frm->ShowModal();
    delete frm;
}
