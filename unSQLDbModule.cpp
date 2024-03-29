// ---------------------------------------------------------------------------

#pragma hdrstop

#include "unSQLDbModule.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
// ---------------------------------------------------------------------------
// #pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TSqlDBModule *SqlDBModule;

// ---------------------------------------------------------------------------
__fastcall TSqlDBModule::TSqlDBModule(TComponent* Owner) : TDataModule(Owner) {
	ADOConnectionDB->Close();
	applPath = ExtractFilePath(Application->ExeName);
	pathUDL = ExtractFilePath(Application->ExeName) + "connectSQL.udl";
	ADOConnectionDB->ConnectionString = "FILE NAME=" + pathUDL;
}

bool TSqlDBModule::GetBoolParam(AnsiString _paramName)
{
	bool result = false;
	AnsiString val;
	try
	{
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "select paramValueInt from extSettingsGlobal where paramName='" + _paramName+"'";
		ADOQueryDB->Open();
		val = ADOQueryDB->FieldByName("paramValueBool")->AsInteger;
		result = (val==1);
		ADOQueryDB->Close();
		return result;
	}
	catch (Exception *ex) {
		AnsiString errStr = "TSqlDBModule::GetBoolParam:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
		result = false;
	}
	return result;
}

AnsiString TSqlDBModule::GetStringParam(AnsiString _paramName)
{
	AnsiString result;
	try
	{
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "select paramValueStr from extSettingsGlobal where paramName='" + _paramName+"'";
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("paramValueStr")->AsAnsiString;
		return result;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		AnsiString errStr = "TSqlDBModule::GetStringParam:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
		result = "";
	}
	return result;
}

int TSqlDBModule::GetIntParam(AnsiString _paramName)
{
	int result;
	try
	{
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "select paramValueStr from extSettingsGlobal where paramName='" + _paramName+"'";
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("paramValueStr")->AsInteger;
		return result;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		AnsiString errStr = "TSqlDBModule::GetStringParam:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
		result = 0;
	}
	return result;
}

float TSqlDBModule::GetFloatParam(AnsiString _paramName)
{
	float result;
	try
	{
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "select paramValueFloat from extSettingsGlobal where paramName='" + _paramName+"'";
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("paramValueFloat")->AsFloat;
		return result;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		AnsiString errStr = "TSqlDBModule::GetStringParam:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
		result = 0;
	}
	return result;
}


// ---------------------------------------------------------------------------
// ������� ��� ������ ����� �� ��
// ---------------------------------------------------------------------------
int TSqlDBModule::GetIntFieldSQL(AnsiString _tableName, AnsiString _fieldName, AnsiString _where, int _default, int &err) {
	int result = _default;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName;
		}
		else {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName + " where " + _where;
		}

		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName(_fieldName)->AsInteger;
		ADOQueryDB->Close();
		err = 0;
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		result = _default;
		err = -1;
	}
	return result;
}

bool TSqlDBModule::GetBoolFieldSQL(AnsiString _tableName, AnsiString _fieldName, AnsiString _where, bool _default, int &err) {
	bool result = _default;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName;
		}
		else {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName + " where " + _where;
		}

		ADOQueryDB->Open();
		result = (bool)ADOQueryDB->FieldByName(_fieldName)->AsInteger;
		ADOQueryDB->Close();
		err = 0;
		// return result;
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		result = _default;
		err = -1;
	}
	return result;
}

AnsiString TSqlDBModule::GetStrFieldSQL(AnsiString _tableName, AnsiString _fieldName, AnsiString _where, AnsiString _default, int &err) {
	AnsiString result = _default;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName;
		}
		else {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName + " where " + _where;
		}

		ADOQueryDB->Open();
		// err = ADOQueryDB->RecordCount;
		result = ADOQueryDB->FieldByName(_fieldName)->AsString;
		ADOQueryDB->Close();
		err = 0;
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		result = _default;
		err = -1;
	}
	return result;
}

double TSqlDBModule::GetFloatFieldSQL(AnsiString _tableName, AnsiString _fieldName, AnsiString _where, double _default, int &err) {
	double result = _default;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName;
		}
		else {
			ADOQueryDB->SQL->Text = "select " + _fieldName + " from " + _tableName + " where " + _where;
		}

		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName(_fieldName)->AsFloat; ;
		ADOQueryDB->Close();
		err = 0;
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		result = _default;
		err = -1;
	}
	return result;
}

int TSqlDBModule::GetBackupDB(AnsiString _bdName, AnsiString& _msg) {
	int err = -99;
	_msg = "Empty";
	AnsiString strSql = "";
	if (!ADOConnectionDB->Connected) {
		ADOConnectionDB->Open();
	}
	else {
		//
	};
	strSql = "BACKUP DATABASE [MobileDef] TO  DISK = N'" + applPath + "\\DB_BKP\\" + _bdName;
	strSql +=
		" WITH NOFORMAT, NOINIT,  NAME = N'MobileDef-������ ���� ������ ��������� �����������', SKIP, NOREWIND, NOUNLOAD,  STATS = 10 GO";
	ADOQueryDB->SQL->Text = strSql;

	ADOQueryDB->ExecSQL();
	_msg = "Good!";
	ADOQueryDB->Close();
	err = 0;
	return err;
}

int TSqlDBModule::ExecStrSql(AnsiString _strSql) {
	int err = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = _strSql;
		ADOQueryDB->ExecSQL();
		err = ADOQueryDB->RowsAffected;
		// result = ADOQueryDB->FieldByName("F1")->AsInteger;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		err = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return err;
}

int TSqlDBModule::SelectStrSql(AnsiString _strSql, int &_err) {
	_err = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = _strSql;
		ADOQueryDB->Open();
		_err = ADOQueryDB->RecordCount;
		// result = ADOQueryDB->FieldByName("F1")->AsInteger;
		// ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		_err = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return _err;
}

AnsiString TSqlDBModule::GetStrFromSql(AnsiString _strSql) {
	AnsiString result = "";
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			result = -3;
		};
		if (ADOQueryDB->Active) {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = _strSql;
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("F1")->AsString;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		result = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return result;
}

int TSqlDBModule::GetIntFromSql(AnsiString _strSql) {
	int result = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			result = -3;
		};
		if (ADOQueryDB->Active) {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = _strSql;
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("F1")->AsInteger;
		// result = ADOQueryDB->RecordCount;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		result = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return result;
}

double TSqlDBModule::GetFloatFromSql(AnsiString _strSql) {
	double result = 0;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			result = -3;
		};
		if (ADOQueryDB->Active) {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = _strSql;
		ADOQueryDB->Open();
		result = ADOQueryDB->FieldByName("F1")->AsFloat;
		// result = ADOQueryDB->RecordCount;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		result = 0;
		TProtocol::ProtocolSave(ex->Message);
	}
	return result;
}




int TSqlDBModule::FillComboBox(AnsiString _tableName, AnsiString _fieldName, TComboBox* _comboBox) {
	int result = 0;
	int rec_id = -1;
	AnsiString str = "";
	if (!ADOConnectionDB->Connected) {
		ADOConnectionDB->Open();
	}
	else {
		result = -3;
	};
	if (ADOQueryDB->Active) {
		ADOQueryDB->Close();
	}
	ADOQueryDB->SQL->Text = "select rec_id," + _fieldName + " from " +
		// _tableName + " order by rec_id";
		_tableName + " order by " + _fieldName;
	ADOQueryDB->Open();
	result = ADOQueryDB->RecordCount;
	_comboBox->Clear();
	while (!ADOQueryDB->Eof) {
		// _strings->Add(ADOQueryDB->FieldByName(_fieldName)->AsString);
		rec_id = ADOQueryDB->FieldByName("rec_id")->AsInteger;
		str = ADOQueryDB->FieldByName(_fieldName)->AsString;
		// ������ ������� ������� ����� ������
		_comboBox->AddItem(str, (TObject*)rec_id);
		ADOQueryDB->Next();
	}
	ADOQueryDB->Close();
	return result;
}

int TSqlDBModule::FillComboBoxFromSql(AnsiString _strSQL, TComboBox* _comboBox) {
	int result = 0;
	int rec_id = -1;
	if (!ADOConnectionDB->Connected) {
		ADOConnectionDB->Open();
	}
	else {
		result = -3;
	};
	if (ADOQueryDB->Active) {
		ADOQueryDB->Close();
	}
	ADOQueryDB->SQL->Text = _strSQL;
	ADOQueryDB->Open();
	result = ADOQueryDB->RecordCount;
	_comboBox->Clear();
	while (!ADOQueryDB->Eof) {
		rec_id = ADOQueryDB->FieldByName("rec_id")->AsInteger;
		_comboBox->AddItem(ADOQueryDB->FieldByName("F1")->AsString, (TObject*)rec_id);
		ADOQueryDB->Next();
	}
	ADOQueryDB->Close();
	return result;
}

void __fastcall TSqlDBModule::ADOQueryDBAfterClose(TDataSet *DataSet) { // ����������� ���������� ������ �� ������ ������
	static_cast<TADOQuery*>(DataSet)->CursorLocation = clUseClient;
}

// �������� �������� ����
int TSqlDBModule::UpdIntSql(AnsiString _tableName, AnsiString _fieldName, int _fieldValue, AnsiString _where) {
	int err = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		};
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " = " + IntToStr(_fieldValue);
		}
		else {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " = " + IntToStr(_fieldValue) + " WHERE " + _where;
		}
		ADOQueryDB->ExecSQL();
		err = ADOQueryDB->RowsAffected;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		err = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return err;
}

int TSqlDBModule::UpdStrSql(AnsiString _tableName, AnsiString _fieldName, AnsiString _fieldValue, AnsiString _where) {
	int err = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		};
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " = '" + _fieldValue;
		}
		else {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " = '" + _fieldValue + "' WHERE " + _where;
		}

		ADOQueryDB->ExecSQL();
		err = ADOQueryDB->RowsAffected;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		err = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return err;
}

int TSqlDBModule::UpdFloatSql(AnsiString _tableName, AnsiString _fieldName, double _fieldValue, AnsiString _where) {
	int err = -1;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		};
		if (_where == NULL) {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " =:pfieldValue ";
		}
		else {
			ADOQueryDB->SQL->Text = "UPDATE " + _tableName + " SET " + _fieldName + " =:pfieldValue  WHERE " + _where;

		}
		ADOQueryDB->Parameters->ParamByName("pfieldValue")->Value = _fieldValue;
		ADOQueryDB->ExecSQL();
		err = ADOQueryDB->RowsAffected;
		ADOQueryDB->Close();
	}
	catch (Exception *ex) {
		err = -2;
		TProtocol::ProtocolSave(ex->Message);
	}
	return err;
}

void __fastcall TSqlDBModule::ADOConnectionDBBeforeConnect(TObject *Sender) {
	if (FileExists(pathUDL)) {
		//
	}
	else {
		ADOConnectionDB->Cancel();
		ADOConnectionDB->Close();
		AnsiString msg = "���� ���������� � �� �� ������!!!";
	}
}

// ---------------------------------------------------------------------------
double TSqlDBModule::GetFloatExtFieldSQL(TADOQuery *_query, AnsiString _tableName, AnsiString _fieldName, AnsiString _where,
	double _default, int &err) {
	double result = _default;
	try {
		AnsiString applPath = ExtractFilePath(Application->ExeName);
		AnsiString pathUDL = ExtractFilePath(Application->ExeName) + "connectSQLVirt.udl";
		_query->Close();
		_query->ConnectionString = "FILE NAME=" + pathUDL;
		if (_where == NULL) {
			_query->SQL->Text = "select " + _fieldName + " from " + _tableName;
		}
		else {
			_query->SQL->Text = "select " + _fieldName + " from " + _tableName + " where " + _where;
		}

		_query->Open();
		result = _query->FieldByName(_fieldName)->AsFloat; ;
		_query->Close();
		err = 0;
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		result = _default;
		err = -1;
	}
	return result;
}

bool TSqlDBModule::SavePar(AnsiString _name, AnsiString _value)
{
	bool res = false;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "update extSettingsGlobal set paramValueStr='"+_value+"' where paramName='"+_name+"'";
		ADOQueryDB->ExecSQL();
		res = (ADOQueryDB->RowsAffected == 0);
		ADOQueryDB->Close();
		if(res)
		{
			ADOQueryDB->SQL->Text = "insert into extSettingsGlobal (paramName,paramValueStr) values ('"+_name+"','"+_value+"')";
			ADOQueryDB->ExecSQL();
			ADOQueryDB->Close();
		}
		res = true;
	}
	catch (Exception *ex) {
		res = false;
		TProtocol::ProtocolSave(ex->Message);
	}
	return res;
}
bool TSqlDBModule::SavePar(AnsiString _name, int _value)
{
	bool res = false;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "update extSettingsGlobal set paramValueStr='"+IntToStr(_value)+"' where paramName='"+_name+"'";
		ADOQueryDB->ExecSQL();
		res = (ADOQueryDB->RowsAffected == 0);
		ADOQueryDB->Close();
		if(res)
		{
			ADOQueryDB->SQL->Text = "insert into extSettingsGlobal (paramName,paramValueInt) values ('"+_name+"',"+IntToStr(_value)+")";
			ADOQueryDB->ExecSQL();
			ADOQueryDB->Close();
		}
		res = true;
	}
	catch (Exception *ex) {
		res = false;
		TProtocol::ProtocolSave(ex->Message);
	}
	return res;
}

int TSqlDBModule::getLastId(AnsiString _tableName)
{
	int res = 0;
	try {
		if (!ADOConnectionDB->Connected) {
			ADOConnectionDB->Open();
		}
		else {
			res = 0;
		};
		if (ADOQueryDB->Active) {
			ADOQueryDB->Close();
		}
		ADOQueryDB->SQL->Text = "select max(rec_id) as [F1] from "+_tableName;
		ADOQueryDB->Open();
		res = ADOQueryDB->FieldByName("F1")->AsInteger;
		ADOQueryDB->Close();
		return res;
	}
	catch (Exception *ex) {
		res = 0;
		TProtocol::ProtocolSave(ex->Message);
	}
	return res;
}
