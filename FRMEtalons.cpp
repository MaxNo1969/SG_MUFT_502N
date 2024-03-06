//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Win.ComObj.hpp>
#pragma hdrstop

#include "FRMEtalons.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFREtalons *FREtalons;

//---------------------------------------------------------------------------
//typedef void __fastcall (__closure *TDataSetNotifyEvent)(TDataSet* DataSet);
void __fastcall TFREtalons::beforeInsert(TDataSet* DataSet)
{
	//OutputDebugString(L"TFREtalons::beforeInsert(TDataSet* DataSet)");
    Abort();
}
__fastcall TFREtalons::TFREtalons(TComponent* Owner)
	: TForm(Owner)
{
	if((SqlDBModule->ADOConnectionDB != NULL) && SqlDBModule->ADOConnectionDB->Connected)
	{
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		qry->SQL->Add(
		"SELECT e.rec_id as [Id], e.[fenable] as [Использовать],e.[frequency] as [Частота], e.[address_file] as [Имя файла], \
			ts.TSName as [Типоразмер],sg.SGName as [Группа прочности] \
		 FROM [GP_MUFT_502].[dbo].[Etalons] e \
		 left join TypeSizes ts on e.ts_id=ts.rec_id \
		 left join SolidGroups sg on e.sg_id=sg.rec_id \
		 left join GOST g on g.rec_id = sg.Gost_id \
		 order by sg.SGName"
		 );
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
__fastcall TFREtalons::~TFREtalons()
{
	OutputDebugString(L"TFRSprGost destructor");
}
void __fastcall TFREtalons::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFREtalons::bButtonClick(TObject *Sender)
{
		TSpeedButton* btn = (TSpeedButton*)Sender;
	TDataSet *ds = grid->DataSource->DataSet;
	try {
		 if(btn->Name == "bFirst")ds->First();
		 if(btn->Name == "bNext")ds->Next();
		 if(btn->Name == "bPrev")ds->Prior();
		 if(btn->Name == "bEnd")ds->Last();
		 if(btn->Name == "bAdd")addEtalon();
		 if(btn->Name == "bDel")deleteEtalon();
		 if(btn->Name == "bCopy")copyEtalon();
	}
	catch(Exception& ex)
	{
			AnsiString err = "Ошибка БД:" + ex.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFREtalons::deleteEtalon()
{
	bool ret = false;
	try
	{
		TDataSet *ds = grid->DataSource->DataSet;
		int rec_id = ds->FieldByName("Id")->AsInteger;
		TADOCommand *cmd = new TADOCommand(this);
		cmd->Connection = SqlDBModule->ADOConnectionDB;
		char cmdText[256];
		cmd->Connection->BeginTrans();
		sprintf(cmdText,"delete from %s where %s=%d","EtalonValues","etalon_id",rec_id);
		cmd->CommandText = cmdText;
		cmd->Execute();
		sprintf(cmdText,"delete from %s where %s=%d","Etalons","rec_id",rec_id);
		cmd->CommandText = cmdText;
		cmd->Execute();
		cmd->Connection->CommitTrans();
		delete cmd;
		ds->Close();
		ds->Open();
        grid->Refresh();
		return true;
	}
	catch(Exception& ex)
	{
			SqlDBModule->ADOConnectionDB->RollbackTrans();
			AnsiString err = "Ошибка deleteEtalon:" + ex.ToString();
			TProtocol::ProtocolSave(err);
			TExtFunction::ShowBigModalMessage(err, clRed);
			return false;
	}
}

bool __fastcall TFREtalons::addEtalon()
{
	bool ret = false;
	TDataSet *ds = grid->DataSource->DataSet;
	int rec_id = ds->FieldByName("Id")->AsInteger;
	return ret;
}

bool __fastcall TFREtalons::copyEtalon()
{
	bool ret = false;
	TDataSet *ds = grid->DataSource->DataSet;
	int rec_id = ds->FieldByName("Id")->AsInteger;
	return ret;
}
