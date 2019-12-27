// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unEditEtalon.h"
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
		TLog::ErrFullSaveLog(ex);
		err = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::gridEtalonEditButtonClick(TObject *Sender) {
	//MessageDlg("gridEtalonEditButtonClick", mtError,TMsgDlgButtons() << mbOK, NULL);
	// ShowMessage(DBGrid1.SelectedField.FieldName);
}

// ---------------------------------------------------------------------------
int TfmEditEtalon::InsertEtalon(int _frequency, int _fenable,
	AnsiString _address_file, int sg_id) {
	int err = -99;
	try {

		err = 0;
	}
	catch (Exception *ex) {
		TLog::ErrFullSaveLog(ex);
		err = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

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
	SqlDBModule->FillComboBox("TypeSizes", "TSName", cbTypeSize);
	for (int i = 0; i < cbTypeSize->Items->Count; i++) {
		if ((int)cbTypeSize->Items->Objects[i]
			== pGlobalSettings->indexCurrentTypeSize) {
			cbTypeSize->ItemIndex = i;
			break;
		}
		else {
			cbTypeSize->ItemIndex = -1;
		}
	}
	cbSGGost->ItemIndex = pGlobalSettings->indexCurrentSGGost;
	queryEtalonVal->Close();
	queryEtalon->Close();
	queryTSz->Close();
	queryEtalon->CursorLocation = clUseServer;
	// queryEtalonVal->CursorLocation = clUseServer;
	// queryTSz->CursorLocation = clUseServer;
	FillGrids(pGlobalSettings->indexCurrentTypeSize,
		pGlobalSettings->indexCurrentSGGost);
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
		strSQL =
			"SELECT T1.rec_id,T1.frequency,T1.address_file,T2.SGName,T1.fenable FROM Etalons T1";
		strSQL += " join SolidGroups T2 on (T1.sg_id=T2.rec_ID)";
		strSQL +=
			// T1.fenable=1 and
			" where T1.ts_id=:pts_id and T2.Gost_id=:pgost_id order by T1.frequency ASC, T1.rec_id ASC";
		queryEtalon->SQL->Text = strSQL;
		queryEtalon->Parameters->ParamByName("pts_id")->Value = _indTsz;
		queryEtalon->Parameters->ParamByName("pgost_id")->Value = _indGost;
		queryEtalon->Open();

		queryEtalonVal->Close();
		// AnsiString where = "rec_id=" + IntToStr(_indTsz);
		// ledTipeSize->Text = SqlDBModule->GetStrFieldSQL("TypeSizes","TSName",where,"NONE!",err);
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
		// специально вставляю, чтобы ошибки в лог валились - он создается каждые сутки
		// если будешь вставлять try { catch - получишь лог ошибок
		TLog::ErrFullSaveLog(ex);
		err = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::cbTypeSizeSelect(TObject *Sender) {
	int ind = cbTypeSize->ItemIndex;
	FillGrids((int)cbTypeSize->Items->Objects[ind], cbSGGost->ItemIndex);
}

// ---------------------------------------------------------------------------
void __fastcall TfmEditEtalon::cbSGGostSelect(TObject *Sender) {
	int ind = cbTypeSize->ItemIndex;
	FillGrids((int)cbTypeSize->Items->Objects[ind], cbSGGost->ItemIndex);
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
		TLog::ErrFullSaveLog(ex);
		err = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
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
		TLog::ErrFullSaveLog(ex);
		err = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
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
