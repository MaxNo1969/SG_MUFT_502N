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
		"SELECT e.rec_id as [Id], e.egroup as [Группа образцов],e.[fenable] as [Использовать],e.[frequency] as [Частота], e.[address_file] as [Имя файла], \
			ts.TSName as [Типоразмер],sg.SGName as [Группа прочности] \
		 FROM [GP_MUFT_502].[dbo].[Etalons] e \
		 left join TypeSizes ts on e.ts_id=ts.rec_id \
		 left join SolidGroups sg on e.sg_id=sg.rec_id \
		 left join GOST g on g.rec_id = sg.Gost_id \
		 order by egroup,sg.SGName"
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
		 if(btn->Name == "bAdd")return;
		 if(btn->Name == "bDel")ds->Delete();
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
