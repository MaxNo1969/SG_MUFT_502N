//---------------------------------------------------------------------------


#pragma hdrstop

#include "TypeSizeFrequencies.h"
#include "unSQLDbModule.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

TSFrequencies::TSFrequencies(int _TS_id)
{
	SqlDBModule->ADOQueryDB->Close();
	AnsiString sql = "SELECT frequency_value,amplValue";
	sql += " FROM TypeSizeFrequencies WHERE TS_id = "+IntToStr(_TS_id);
	sql += " ORDER BY frequency_value ASC";
	SqlDBModule->ADOQueryDB->SQL->Text = sql;
	SqlDBModule->ADOQueryDB->Open();
	while (!SqlDBModule->ADOQueryDB->Eof) {
		//частота сигнала
		Frequency.push_back(SqlDBModule->ADOQueryDB->
			FieldByName("frequency_value")->AsInteger);
		//амплитуда сигнала
		float t = SqlDBModule->ADOQueryDB->FieldByName("amplValue")->AsFloat;
		Amplitude.push_back(t);
		SqlDBModule->ADOQueryDB->Next();
	}
	SqlDBModule->ADOQueryDB->Close();
}
TSFrequencies::~TSFrequencies()
{
	Frequency.clear();
    Amplitude.clear();
}

