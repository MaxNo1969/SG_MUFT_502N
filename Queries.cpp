//---------------------------------------------------------------------------

#pragma hdrstop

#include "Queries.h"
#include "unSqlDBModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
std::list<UnicodeString>GetGost()
{
	SqlDBModule->ADOQueryDB->Close();
	SqlDBModule->ADOQueryDB->SQL->Text = "select id, Name from GOST ORDER BY id";

	SqlDBModule->ADOQueryDB->Open();
	std::list<UnicodeString>l;
	while (!SqlDBModule->ADOQueryDB->Eof)
	{
	//SqlDBModule->ADOQueryDB->FieldByName("filterRolloff")
		UnicodeString s = SqlDBModule->ADOQueryDB->FieldByName("Name")->AsWideString;
		l.push_back(s);
        SqlDBModule->ADOQueryDB->Next();
	}
	SqlDBModule->ADOQueryDB->Close();
    return l;
}

