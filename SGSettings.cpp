// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SGSettings.h"
// #include "LCardData.h"
// #include "uCDBS.h"
// #include "uCExecSQL.h"
// #include "uCSelect.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"
TSGSettForm *SGSettForm;

// ---------------------------------------------------------------------------
__fastcall TSGSettForm::TSGSettForm(TComponent* Owner, TGlobalSettings *_pGlobalSettingsp) : TForm(Owner) {
	pGlobalSettings = _pGlobalSettingsp;
	// WindowProc = UserWndProc;
	// частоты
	queryFrec->Connection = SqlDBModule->ADOConnectionDB;
	strSQLFrec =
		"SELECT T2.TS_id,T2.frequency_value,T2.amplValue FROM TypeSizes as T1 JOIN TypeSizeFrequencies as T2 ON T1.rec_id = T2.TS_ID";
	strSQLFrec += " WHERE T1.rec_id=:pTypeSize";
	strSQLFrec += " ORDER BY T1.rec_id,T2.frequency_value ASC";
	commandFrec->Connection = SqlDBModule->ADOConnectionDB;
	queryFrec->SQL->Text = strSQLFrec;
	// пороги
	queryTSz->Connection = SqlDBModule->ADOConnectionDB;
	strSQLTsz = "SELECT threshold_value,rec_id,TS_id FROM TypeSizeThresholds";
	strSQLTsz += " WHERE TS_id=:pTypeSize";
	strSQLTsz += " ORDER BY threshold_value ASC";
	queryTSz->SQL->Text = strSQLTsz;
	KeyPreview = true;
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::FormCreate(TObject *Sender) {
	int err = -99;
	int ind = 0;
	try {
		queryTSz->Close();
		SqlDBModule->FillComboBox("TypeSizes", "TSName", cbTypeSize);
		for (int i = 0; i < cbTypeSize->Items->Count; i++) {
			if ((int)cbTypeSize->Items->Objects[i] == pGlobalSettings->indexCurrentTypeSize) {
				cbTypeSize->ItemIndex = i;
				break;
			}
			else {
				cbTypeSize->ItemIndex = 0;
			}
		}
		ind = cbTypeSize->ItemIndex;
		SqlDBModule->FillComboBox("SolidGroups", "SGName", cbSolidGroup);
		cbSolidGroup->ItemIndex = 0;
		// Пороги
		//pGlobalSettings->ThresholdMaxCount = 12;
		queryTSz->Close();
		queryTSz->Parameters->ParamByName("pTypeSize")->Value = (int)cbTypeSize->Items->Objects[ind];
		queryTSz->Open();
		queryFrec->Close();
		queryFrec->Parameters->ParamByName("pTypeSize")->Value = (int)cbTypeSize->Items->Objects[ind];
		queryFrec->Open();
		// Алгоритм
		rgCalcAlgo->ItemIndex = pGlobalSettings->calcSGMode;
		bool RHKret = RegisterHotKey(Handle,
			// Handle окна, которому отправлять сообщения WM_HOTKEY
			0x00F, // УСЛОВНЫЙ идентификатор горячего ключа
			MOD_ALT + MOD_CONTROL, // модификаторы
			VK_RETURN // код клавиши
			);
		BlockControls(false); // todo
	}
	catch (Exception *ex) {
		TLog::ErrFullSaveLog(ex);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::FormDestroy(TObject *Sender) {

	// SaveFormPos(this, ini);
}
// ---------------------------------------------------------------------------

void TSGSettForm::BlockControls(bool _fl) {
	bSave->Enabled = _fl; // !bSave->Enabled;
	gridFrec->ReadOnly = !_fl;
	gridFrec->Enabled = _fl;
	gridTSz->ReadOnly = !_fl;
	gridTSz->Enabled = _fl;
	navFrec->Enabled = _fl;
	navTS->Enabled = _fl;
	rgCalcAlgo->Enabled = _fl;
	if (_fl) {
		gridFrec->FixedColor = clYellow;
		gridTSz->FixedColor = clYellow;
	}
	else {
		// gridFrec->Color=clWindow;
		gridFrec->FixedColor = clSkyBlue;
		gridTSz->FixedColor = clSkyBlue;
	}
	this->Refresh();
}

// ------------------------------------------------------------------------------
void __fastcall TSGSettForm::ApplicationEventsMessage(tagMSG &Msg, bool &Handled) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // сообщение наше
	{
		if (Msg.wParam == 0x00F) // идентификатор наш
		{
			Handled = true;
			fl = !fl;
			BlockControls(fl);
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::bSaveClick(TObject *Sender) {
	pGlobalSettings->calcSGMode = rgCalcAlgo->ItemIndex;
	if (queryFrec->State == dsInsert || queryFrec->State == dsEdit) {
		queryFrec->Post();
	}
	else {
		//
	}
	if (queryTSz->State == dsInsert || queryTSz->State == dsEdit) {
		queryTSz->Post();
	}
	else {
		//
	}
	queryFrec->Refresh();
	queryTSz->Refresh();
	SqlDBModule->UpdIntSql("SettingsGLobal", "calcSGMode", rgCalcAlgo->ItemIndex, NULL);
	//ModalResult = mrOk;
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::bExitClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::eThresholdResistKeyPress(TObject *Sender, wchar_t &Key) {
	if (!((Key >= '0' && Key <= '9') || (Key == VK_BACK) || (Key == ',')))
		Key = 0x00;
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::cbTypeSizeSelect(TObject *Sender) {
	int ind = cbTypeSize->ItemIndex;
	queryTSz->Close();
	queryTSz->Parameters->ParamByName("pTypeSize")->Value = (int)cbTypeSize->Items->Objects[ind];
	queryTSz->Open();
	queryFrec->Close();
	queryFrec->Parameters->ParamByName("pTypeSize")->Value = (int)cbTypeSize->Items->Objects[ind];
	queryFrec->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::queryFrecAfterInsert(TDataSet *DataSet) {
	int ind = cbTypeSize->ItemIndex;
	queryFrec->FieldByName("TS_id")->AsInteger = (int)cbTypeSize->Items->Objects[ind];
	// queryFrec->FieldByName("frequency_nu")->AsInteger=queryFrec->RecordCount+1;
	queryFrec->FieldByName("amplValue")->AsFloat = 5.0;
	AnsiString insertStr = queryFrec->SQL->Text;
}

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::UserWndProc(Messages::TMessage &_msg) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (_msg.Msg == WM_HOTKEY) // сообщение наше
	{
		if (_msg.WParam == 0x00F) // идентификатор наш
		{
			// Handled = true;

			fl = !fl;
			BlockControls(fl);
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

// ---------------------------------------------------------------------------
void __fastcall TSGSettForm::queryTSzBeforePost(TDataSet *DataSet) {
	// необходимо проверить режим датасета

	int ind = cbTypeSize->ItemIndex;
	if (DataSet->State == dsInsert) {
		DataSet->FieldByName("TS_id")->AsInteger = (int)cbTypeSize->Items->Objects[ind];
	}
	else {
		//
	}

}
// ---------------------------------------------------------------------------
