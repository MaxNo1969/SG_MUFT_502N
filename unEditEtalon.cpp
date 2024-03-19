// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "unEditEtalon.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEditEtalon *fmEditEtalon;

// ---------------------------------------------------------------------------
__fastcall TfmEditEtalon::TfmEditEtalon(TComponent* Owner,
	TGlobalSettings *_pGlobalSettings, TLCardData* _lCardData) : TForm(Owner) {
	int err = -99;
	try {
		pGlobalSettings = _pGlobalSettings;
		plCardData = _lCardData;
		// WindowProc = UserWndProc;
		err = 0;
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmEditEtalon::TfmEditEtalon:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::UserWndProc(Messages::TMessage &_msg) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (_msg.Msg == WM_HOTKEY) // сообщение наше
	{
		if (_msg.WParam == 0x00F) // идентификатор наш
		{
			// Handled = true;
			isEnable = !isEnable;
			BlockControls(isEnable);
			_msg.Result = 0;
		}
		else {
			//
		}
	}
	else {
		WndProc(_msg);
	}
}

void TfmEditEtalon::BlockControls(bool _isEnable) {

	// GroupBox1->Enabled = _isEnable;
	// GroupBox2->Enabled = _isEnable;
	navEtalon->Enabled = _isEnable;
	navEtalonVal->Enabled = _isEnable;
	navTS->Enabled = _isEnable;

	gridEtalon->ReadOnly = !_isEnable;
	gridEtalonVal->ReadOnly = !_isEnable;
	gridTSz->ReadOnly = !_isEnable;
	if (!isEnable) {
		gridEtalon->Color = clInfoBk;
		gridEtalonVal->Color = clInfoBk;
		gridTSz->Color = clInfoBk;
	}
	else {
		// gridFrec->Color=clWindow;
		gridEtalon->Color = clSkyBlue;
		gridEtalonVal->Color = clSkyBlue;
		gridTSz->Color = clSkyBlue;
	}
}

void __fastcall TfmEditEtalon::FormCreate(TObject *Sender) {
	// blockControls(false);   //todo временно
	KeyPreview = true;
	TMainForm *main = (TMainForm*)Owner;
	SqlDBModule->FillComboBoxFromSql("select rec_id, TSName as F1 from TypeSizes",cbTypeSize);
	for (int i = 0; i < cbTypeSize->Items->Count; i++) {
		int typeId = (int)cbTypeSize->Items->Objects[i];
		if ((int)cbTypeSize->Items->Objects[i] == pGlobalSettings->indexCurrentTypeSize)
		{
			cbTypeSize->ItemIndex = i;
			break;
		}
		else {
			cbTypeSize->ItemIndex = -1;
		}
	}
	int idGost = 0;
	//Заполняем список групп прочности - он зависит от ГОСТ-а
	if(cbTypeSize->ItemIndex>=0)
	{
		AnsiString gostName = cbTypeSize->Items->Strings[cbTypeSize->ItemIndex].SubString(0,5);
		idGost = SqlDBModule->GetIntFromSql("select rec_id as F1 from GOST where ShortName='"+gostName+"'");
		SqlDBModule->FillComboBoxFromSql("select rec_id, SGName as F1 from SolidGroups where Gost_id=" +IntToStr(idGost),cbSGGost);
		cbSGGost->ItemIndex=-1;
	}
	queryEtalonVal->Close();
	queryEtalon->Close();
	queryTSz->Close();
	queryEtalon->CursorLocation = clUseServer;
	// queryEtalonVal->CursorLocation = clUseServer;
	// queryTSz->CursorLocation = clUseServer;
/*
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		qry->SQL->Add("select rec_id,SGName from SolidGroups where gost_id="+IntToStr(idGost));
		qry->Open();
		sgPopup->Items->Clear();
		while(!qry->Eof)
		{
			TMenuItem *item = new TMenuItem(this);
			item->Caption = qry->FieldByName("SGName")->AsAnsiString;
			item->Tag = qry->FieldByName("rec_id")->AsInteger;
			sgPopup->Items->Add(item);
			qry->Next();
		}
		qry->Close();
		qry->SQL->Clear();
		qry->SQL->Add("select rec_id,TSName from TypeSizes");
		qry->Open();
		tsPopup->Items->Clear();
		while(!qry->Eof)
		{
			TMenuItem *item = new TMenuItem(this);
			item->Caption = qry->FieldByName("TSName")->AsAnsiString;
			item->Tag = qry->FieldByName("rec_id")->AsInteger;
			tsPopup->Items->Add(item);
			qry->Next();
		}
		qry->Close();
		delete qry;
  */
	FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex],cbSGGost->ItemIndex);
	bool RHKret = RegisterHotKey(this->Handle, 0x00F,
		// УСЛОВНЫЙ идентификатор горячего ключа
		MOD_ALT + MOD_CONTROL, // модификаторы
		VK_RETURN // код клавиши
		);
	BlockControls(false);
}

// ---------------------------------------------------------------------------
int TfmEditEtalon::FillGrids(int _indTsz, int _indGost) {
	int err = -99;
	AnsiString strSQL = "";
	try {
		queryEtalon->Close();
		if(_indGost >=0)
		{
		strSQL =
			"SELECT e.rec_id,e.frequency,ts.TSName,e.address_file,sg.SGName,e.fenable FROM Etalons e";
		strSQL += " join SolidGroups sg on (e.sg_id=sg.rec_ID)";
		strSQL += " join TypeSizes ts on ts.rec_id=e.ts_id";
		strSQL += " where e.ts_id=:pts_id and sg.rec_id=:pgost_id order by e.frequency ASC, e.rec_id ASC";
		queryEtalon->SQL->Text = strSQL;
		queryEtalon->Parameters->ParamByName("pts_id")->Value = _indTsz;
		queryEtalon->Parameters->ParamByName("pgost_id")->Value = _indGost;
		}
		else
		{
		strSQL =
			"SELECT e.rec_id,e.frequency,ts.TSName,e.address_file,sg.SGName,e.fenable FROM Etalons e";
		strSQL += " join SolidGroups sg on (e.sg_id=sg.rec_ID)";
		strSQL += " join TypeSizes ts on ts.rec_id=e.ts_id";
		strSQL += " where e.ts_id=:pts_id order by e.frequency ASC, e.rec_id ASC";
		queryEtalon->SQL->Text = strSQL;
		queryEtalon->Parameters->ParamByName("pts_id")->Value = _indTsz;
		}

		queryEtalon->Open();
		if(cbTypeSize->ItemIndex>=0)
		{
			AnsiString gostName = cbTypeSize->Items->Strings[cbTypeSize->ItemIndex].SubString(0,5);
			int idGost = SqlDBModule->GetIntFromSql("select rec_id as F1 from GOST where ShortName='"+gostName+"'");
			SqlDBModule->FillComboBoxFromSql("select rec_id, SGName as F1 from SolidGroups where Gost_id=" +IntToStr(idGost),cbSGGost);
			cbSGGost->ItemIndex=0;

			TADOQuery *qry = new TADOQuery(this);
			qry->Connection = SqlDBModule->ADOConnectionDB;
			qry->SQL->Add("select rec_id,SGName from SolidGroups where gost_id="+IntToStr(idGost));
			qry->Open();
			sgPopup->Items->Clear();
			while(!qry->Eof)
			{
				TMenuItem *item = new TMenuItem(this);
				item->Caption = qry->FieldByName("SGName")->AsAnsiString;
				item->Tag = qry->FieldByName("rec_id")->AsInteger;
				item->OnClick = sgPopupClick;
				sgPopup->Items->Add(item);
				qry->Next();
			}
			qry->Close();
			qry->SQL->Clear();
			qry->SQL->Add("select rec_id,TSName from TypeSizes");
			qry->Open();
			tsPopup->Items->Clear();
			while(!qry->Eof)
			{
				TMenuItem *item = new TMenuItem(this);
				item->Caption = qry->FieldByName("TSName")->AsAnsiString;
				item->Tag = qry->FieldByName("rec_id")->AsInteger;
				item->OnClick = tsPopupClockClick;
				tsPopup->Items->Add(item);
				qry->Next();
			}
			qry->Close();
			delete qry;
		}


		queryEtalonVal->Close();
		strSQL =
			"SELECT rec_id as vrec_id, etalon_id,thres_val,barkgausen_val FROM EtalonValues where etalon_id = :rec_id order by thres_val";
		queryEtalonVal->SQL->Text = strSQL;
		queryEtalonVal->Open();

		queryTSz->Close();
		// queryTSz->Connection = SqlDBModule->ADOConnectionDB;
		strSQL = "SELECT threshold_value,rec_id,TS_id FROM TypeSizeThresholds";
		strSQL += " WHERE TS_id=:pTypeSize";
		strSQL += " ORDER BY threshold_value ASC";
		queryTSz->SQL->Text = strSQL;
		// перед инсертом и делитом ключевое поле править уже не надо - это прямая правка таблицы типоразмеров
		// как бы так
		queryTSz->Parameters->ParamByName("pTypeSize")->Value = _indTsz;
		// (int)cbTypeSize->Items->Objects[ind];
		queryTSz->Open();
		err = 0;
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmEditEtalon::FillGrids:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
	return err;
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::cbTypeSizeSelect(TObject *Sender) {
	int indTsz = cbTypeSize->ItemIndex;
	if(indTsz < 0)indTsz = 0;
	//Заполняем список групп прочности - он зависит от ГОСТ-а
	if(cbTypeSize->ItemIndex>=0)
	{
		AnsiString gostName = cbTypeSize->Items->Strings[cbTypeSize->ItemIndex].SubString(0,5);
		int idGost = SqlDBModule->GetIntFromSql("select rec_id as F1 from GOST where ShortName='"+gostName+"'");
		SqlDBModule->FillComboBoxFromSql("select rec_id, SGName as F1 from SolidGroups where Gost_id=" +IntToStr(idGost),cbSGGost);
		cbSGGost->ItemIndex=-1;
		/*
		TADOQuery *qry = new TADOQuery(this);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		qry->SQL->Add("select rec_id,SGName from SolidGroups where gost_id="+IntToStr(idGost));
		qry->Open();
		sgPopup->Items->Clear();
		while(!qry->Eof)
		{
			TMenuItem *item = new TMenuItem(this);
			item->Caption = qry->FieldByName("SGName")->AsAnsiString;
			item->Tag = qry->FieldByName("rec_id")->AsInteger;
			item->OnClick = sgPopupClick;
			sgPopup->Items->Add(item);
			qry->Next();
		}
		qry->Close();
		qry->SQL->Clear();
		qry->SQL->Add("select rec_id,TSName from TypeSizes");
		qry->Open();
		tsPopup->Items->Clear();
		while(!qry->Eof)
		{
			TMenuItem *item = new TMenuItem(this);
			item->Caption = qry->FieldByName("TSName")->AsAnsiString;
			item->Tag = qry->FieldByName("rec_id")->AsInteger;
			item->OnClick = tsPopupClockClick;
			tsPopup->Items->Add(item);
			qry->Next();
		}
		qry->Close();
		delete qry;
        */
	}

	int indSG = cbSGGost->ItemIndex;
	if(indSG < 0)
		FillGrids((int)cbTypeSize->Items->Objects[indTsz], -1);
	else
		FillGrids((int)cbTypeSize->Items->Objects[indTsz], (int)cbSGGost->Items->Objects[indSG]);
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::cbSGGostSelect(TObject *Sender) {
	int indTsz = cbTypeSize->ItemIndex;
	if(indTsz < 0)indTsz = 0;
	int indSG = cbSGGost->ItemIndex;
	if(indSG < 0)
		FillGrids((int)cbTypeSize->Items->Objects[indTsz], -1);
	else
		FillGrids((int)cbTypeSize->Items->Objects[indTsz], (int)cbSGGost->Items->Objects[indSG]);
}
// ---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::bbtShowEtClick(TObject *Sender) { //
	int err = 0;
	try {

		AnsiString fn;
		int frec = plCardData->getFreqNum();
		fn = queryEtalon->FieldByName("address_file")->AsString;
		TLog::LoadTxtChDoubleFile(fn, plCardData, frec,3);
		// TMeasuresData* _measuresData
		// todo вроде и так из файла?
		vector<int>ThresVal;
		vector<double>BarkVal;
		queryEtalonVal->First();
		while (!queryEtalonVal->Eof) {
			ThresVal.push_back(queryEtalonVal->FieldByName("thres_val")
				->AsInteger);
			BarkVal.push_back(queryEtalonVal->FieldByName("barkgausen_val")
				->AsFloat);
			queryEtalonVal->Next();
		}
		TMeasuresData* pMeasuresData = &plCardData->vecMeasuresData[frec];
		fmViewMeasure = new TfmViewMeasure(this, pMeasuresData, pGlobalSettings,
			ThresVal, BarkVal);
		// fmViewMeasure->PrepareChartToShow()
		fmViewMeasure->ShowModal();
		fmViewMeasure->Close();
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmEditEtalon::bbtShowEtClick:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::bbtRecalcClick(TObject *Sender) {
	int err = 0;
	try {
		AnsiString strCmdSql = "";

		vector<int>Thresholds;
		double res = 0;
		// читаем эталон из файла
		AnsiString fn;
		int frec = plCardData->getFreqNum();
		fn = queryEtalon->FieldByName("address_file")->AsString;
		TLog::LoadTxtChDoubleFile(fn, plCardData, frec,3);
		queryTSz->First();
		// загружаем пороги по выбранному
		while (!queryTSz->Eof) {
			res = queryTSz->FieldByName("threshold_value")->AsInteger;
			Thresholds.push_back(res);
			queryTSz->Next();
		}
		vector<double>BarkValues;
		queryEtalonVal->First();
		BarkValues = plCardData->GetBarkValues(Thresholds);
		// удаляем старые значения
		strCmdSql = "DELETE FROM EtalonValues WHERE etalon_id=" +
			IntToStr(queryEtalon->FieldByName("rec_id")->AsInteger);
		cmdEtalonVal->CommandText = strCmdSql;
		cmdEtalonVal->Execute();
		// Вводим новые
		for (int i = 0; i < Thresholds.size(); i++) {
			strCmdSql =
				"INSERT INTO EtalonValues (etalon_id,thres_val,barkgausen_val ) VALUES (";
			strCmdSql +=
				IntToStr(queryEtalon->FieldByName("rec_id")->AsInteger);
			strCmdSql += "," + IntToStr(Thresholds[i]);
			strCmdSql += ", :pbarkgausen_val )";
			double xxx = BarkValues[i];
			cmdEtalonVal->CommandText = strCmdSql;
			cmdEtalonVal->Parameters->ParamByName("pbarkgausen_val")
				->Value = xxx; // (*BarkValues)[i];
			cmdEtalonVal->Execute();
			queryEtalonVal->Next();
		}
		queryEtalonVal->Close();
		queryEtalonVal->Open();
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmEditEtalon::bbtRecalcClick:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
	// delete BarkValues;
}
// ---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::FormClose(TObject *Sender, TCloseAction &Action)
{
	queryEtalonVal->Close();
	queryEtalon->Close();
	queryTSz->Close();
	queryEtalon->CursorLocation = clUseClient;
	// queryEtalonVal->CursorLocation = clUseClient;
	// queryTSz->CursorLocation = clUseClient;
}
// ---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::bbtRecalcAllClick(TObject *Sender) {
	AnsiString strCmdSql = "";

	vector<int>Thresholds;
	double res = 0;
	// загружаем пороги по выбранному
	queryTSz->First();
	while (!queryTSz->Eof) {
		res = queryTSz->FieldByName("threshold_value")->AsInteger;
		Thresholds.push_back(res);
		queryTSz->Next();
	}
	queryEtalon->First();
	while (!queryEtalon->Eof) {
		// читаем эталон из файла
		AnsiString fn;
		int frec = plCardData->getFreqNum();
		fn = queryEtalon->FieldByName("address_file")->AsString;
		TLog::LoadTxtChDoubleFile(fn, plCardData, frec,3);//serg
		// получаем новые значения Баркгаузена
		vector<double>BarkValues;
		BarkValues = plCardData->GetBarkValues(Thresholds);
		// удаляем старые значения
		strCmdSql = "DELETE FROM EtalonValues WHERE etalon_id=" +
			IntToStr(queryEtalon->FieldByName("rec_id")->AsInteger);
		cmdEtalonVal->CommandText = strCmdSql;
		cmdEtalonVal->Execute();
		// Вводим новые
		for (int i = 0; i < Thresholds.size(); i++) {
			strCmdSql =
				"INSERT INTO EtalonValues (etalon_id,thres_val,barkgausen_val ) VALUES (";
			strCmdSql +=
				IntToStr(queryEtalon->FieldByName("rec_id")->AsInteger);
			strCmdSql += "," + IntToStr(Thresholds[i]);
			strCmdSql += ", :pbarkgausen_val )";
			double xxx = BarkValues[i];
			cmdEtalonVal->CommandText = strCmdSql;
			cmdEtalonVal->Parameters->ParamByName("pbarkgausen_val")
				->Value = xxx; // (*BarkValues)[i];
			cmdEtalonVal->Execute();
			queryEtalonVal->Next();
		}
		queryEtalon->Next();
	}
	queryEtalonVal->Close();
	queryEtalonVal->Open();
}

// ---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::queryTSzBeforePost(TDataSet *DataSet) {
	// необходимо проверить режим датасета

	int ind = cbTypeSize->ItemIndex;
	if (DataSet->State == dsInsert) {
		DataSet->FieldByName("TS_id")->AsInteger =
			(int)cbTypeSize->Items->Objects[ind];
	}
	else {
		//
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::ApplicationEventsMessage(tagMSG &Msg,
	bool &Handled) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // сообщение наше
	{
		if (Msg.wParam == 0x00F) // идентификатор наш
		{
			Handled = true;
			if (isEnable)
				isEnable = false;
			else
				isEnable = true;
			BlockControls(isEnable);
		}
	}
}




void __fastcall TfmEditEtalon::sgPopupClick(TObject *Sender)
{
	TMenuItem *item = (TMenuItem*)Sender;
	int sgId = item->Tag;
	UnicodeString Msg = "Будет заменена группа прочности образца.\n";
	Msg += queryEtalon->FieldByName("SGName")->AsString + " => " + item->Caption + "\n";
	Msg += "Заменить?";
	if(MessageDlg(Msg,TMsgDlgType::mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,NULL) == mrYes)
	{
	   int rec_id = queryEtalon->FieldByName("rec_id")->AsInteger;
	   TADOCommand *cmd = new TADOCommand(this);
	   cmd->Connection = SqlDBModule->ADOConnectionDB;
	   cmd->CommandText = "update Etalons set sg_id="+IntToStr(sgId)+" where rec_id="+IntToStr(rec_id);
	   cmd->Execute();
	   FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex],cbSGGost->ItemIndex);
	   cbSGGost->ItemIndex = -1;
  	   cbSGGost->Text = "";
	   FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex],cbSGGost->ItemIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::miFNameClick(TObject *Sender)
{
	  ofdEtalonFile->FileName = queryEtalon->FieldByName("address_file")->AsString;
	  if(ofdEtalonFile->Execute())
	  {
		UnicodeString Msg = "Будет заменен файл образца для группы.\n";
		Msg += queryEtalon->FieldByName("address_file")->AsString + " => " + ofdEtalonFile->FileName + "\n";
		Msg += "Не забудте пересчитать пороги.\nЗаменить?";
		if(MessageDlg(Msg,TMsgDlgType::mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,NULL) == mrYes)
		{
			int rec_id = queryEtalon->FieldByName("rec_id")->AsInteger;
			String fName = ofdEtalonFile->FileName;
			TADOCommand *cmd = new TADOCommand(this);
			cmd->Connection = SqlDBModule->ADOConnectionDB;
			cmd->CommandText = "update Etalons set address_file='"+fName+"' where rec_id="+IntToStr(rec_id);
			cmd->Execute();
			cbSGGost->ItemIndex = -1;
			cbSGGost->Text = "";
			FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex],cbSGGost->ItemIndex);
		}
	  }
}
//---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::tsPopupClockClick(TObject *Sender)
{
	TMenuItem* item = (TMenuItem*)Sender;
	int tsId = item->Tag;
	UnicodeString Msg = "Будет изменена группа образца.\n";
	Msg += queryEtalon->FieldByName("TSName")->AsString + " => " + item->Caption + "\n";
	Msg += "Не забудте пересчитать пороги.\nЗаменить?";
	if(MessageDlg(Msg, TMsgDlgType::mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,NULL) == mrYes)
	{
			int rec_id = queryEtalon->FieldByName("rec_id")->AsInteger;
			TADOCommand *cmd = new TADOCommand(this);
			cmd->Connection = SqlDBModule->ADOConnectionDB;
			cmd->CommandText = "update Etalons set ts_id="+IntToStr(tsId)+" where rec_id="+IntToStr(rec_id);
			cmd->Execute();
			cbSGGost->ItemIndex = -1;
			cbSGGost->Text = "";
			FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex],cbSGGost->ItemIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmEditEtalon::cbSGGostKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	TComboBox *cb = (TComboBox*)Sender;
	if(Key == VK_DELETE)
	{
		cb->Text = "";
		cb->ItemIndex = -1;
		FillGrids((int)cbTypeSize->Items->Objects[cbTypeSize->ItemIndex], -1);
	}

}
//---------------------------------------------------------------------------

