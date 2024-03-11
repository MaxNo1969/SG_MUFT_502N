//---------------------------------------------------------------------------


#pragma hdrstop

#include "EtalonDatas.h"
#include "unSQLDbModule.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

EtalonDatas::EtalonDatas(int _TS_id, int _SGGost_id)
{
	SqlDBModule->ADOQueryDB->Close();
	AnsiString strSQL;
	strSQL = "SELECT T1.rec_id as rec,T1.frequency,T1.sg_id, T2.SGName, T2.Color";
	strSQL += " FROM Etalons T1 join SolidGroups T2 on (T1.sg_id=T2.rec_ID)";
	strSQL += " where T1.fenable=1 and T1.ts_id=";
	strSQL += IntToStr(_TS_id);
	strSQL += " and T2.Gost_id=";
	strSQL += IntToStr(_SGGost_id);
	strSQL += " order by T1.frequency ASC, T1.rec_id ASC";
	SqlDBModule->ADOQueryDB->SQL->Text = strSQL;
	SqlDBModule->ADOQueryDB->Open();
	while (!SqlDBModule->ADOQueryDB->Eof)
	{
		Etalon CurrEta = Etalon();
		CurrEta.Etalon_id = SqlDBModule->ADOQueryDB->
			FieldByName("rec")->AsInteger;
		CurrEta.SG_id = SqlDBModule->ADOQueryDB->
			FieldByName("sg_id")->AsInteger;
		CurrEta.SG_name = SqlDBModule->ADOQueryDB->
			FieldByName("SGName")->AsString;
		CurrEta.Frequency = SqlDBModule->ADOQueryDB->
			FieldByName("frequency")->AsInteger;
		CurrEta.Color = (TColor)SqlDBModule->ADOQueryDB->
			FieldByName("Color")->AsInteger;
		Etalons.push_back(CurrEta);
		SqlDBModule->ADOQueryDB->Next();
	}
	SqlDBModule->ADOQueryDB->Close();

	for(int i = 0; i < Etalons.size(); i++)
	{   //по всем полученным эталонам читаем параметры
		strSQL = "SELECT etalon_id,thres_val,barkgausen_val";
		strSQL += " FROM EtalonValues where etalon_id = ";
		strSQL += IntToStr(Etalons[i].Etalon_id);
		strSQL += " order by thres_val ASC";
		SqlDBModule->ADOQueryDB->SQL->Text = strSQL;
		SqlDBModule->ADOQueryDB->Open();

		while (!SqlDBModule->ADOQueryDB->Eof) {
			//Забиваем параметры
			Etalons[i].Thresholds.push_back(SqlDBModule->ADOQueryDB->
				FieldByName("thres_val")->AsInteger);
			Etalons[i].BarkValues.push_back(SqlDBModule->ADOQueryDB->
				FieldByName("barkgausen_val")->AsFloat);
			SqlDBModule->ADOQueryDB->Next();
		}
		SqlDBModule->ADOQueryDB->Close();
	}
}

//---------------------------------------------------------------------------
EtalonDatas::~EtalonDatas()
{
//	for(int i = 0; i < Etalons.size();i++)
//		delete &Etalons[i];
	Etalons.clear();
}
//---------------------------------------------------------------------------
Etalon::Etalon()
{
	Etalon_id = 0;
	Frequency = 0;
	SG_id = 0;
	Color = clYellow;
//	Thresholds = new vector<int>;
//	ThresValues = new vector<double>;
}
//---------------------------------------------------------------------------
Etalon::~Etalon()
{
//	delete &Thresholds;
//	delete &BarkValues;
}
//---------------------------------------------------------------------------
TSThresholds::TSThresholds(int _TS_id)
{
	// загружаем пороги по выбранному  типоразмеру
	SqlDBModule->ADOQueryDB->Close();
	AnsiString strSQL = "select threshold_value from TypeSizeThresholds where TS_id=";
	strSQL += IntToStr(_TS_id);
	strSQL += " order by threshold_value";
	SqlDBModule->ADOQueryDB->SQL->Text = strSQL;
	SqlDBModule->ADOQueryDB->Open();
	SqlDBModule->ADOQueryDB->First();
	while (!SqlDBModule->ADOQueryDB->Eof) {
		int res = SqlDBModule->ADOQueryDB->FieldByName("threshold_value")->AsInteger;
		Thresholds.push_back(res);
		SqlDBModule->ADOQueryDB->Next();
	}
}
//---------------------------------------------------------------------------
TSThresholds::~TSThresholds()
{
	Thresholds.clear();
}
