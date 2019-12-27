// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unExtSettings.h"

// ---------------------------------------------------------------------------

// -------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// -----------

TfmExtSettings *fmExtSettings;

// ---------------------------------------------------------------------------
__fastcall TfmExtSettings::TfmExtSettings(TComponent* Owner, TGlobalSettings* _pGlobalSettings) : TForm(Owner) {
	pGlobalSettings = _pGlobalSettings;
}

// ---------------------------------------------------------------------------
void __fastcall TfmExtSettings::apEvExtSetMessage(tagMSG &Msg, bool &Handled) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // сообщение наше
	{
		if (Msg.wParam == 0x00F) // идентификатор наш
		{
			Handled = true;
			blockControls = !blockControls;
			gridExtSet->ReadOnly = blockControls;
			if (blockControls) {
				gridExtSet->Color = clInfoBk;
			}
			else {
				gridExtSet->Color = clActiveCaption;
			}
			navExtSet->Enabled = !blockControls;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmExtSettings::FormCreate(TObject *Sender) {
	blockControls = true;
	KeyPreview = true;
	bool RHKret = RegisterHotKey(Handle,
		// Handle окна, которому отправлять сообщения WM_HOTKEY
		0x00F, // УСЛОВНЫЙ идентификатор горячего ключа
		MOD_ALT + MOD_CONTROL, // модификаторы
		VK_RETURN // код клавиши
		);
	queryExtSet->Close();
	AnsiString strSQL = "SELECT paramRusName as 'Наименование параметра', paramValueStr as 'Строковое значение',paramValueFloat as 'Численное значение'";
	strSQL += " FROM extSettingsGlobal where isActive=1 order by paramName ";
	queryExtSet->SQL->Text = strSQL;
	queryExtSet->Open();
	gridExtSet->Columns->Items[0]->Width = 250;
}

// ---------------------------------------------------------------------------
void __fastcall TfmExtSettings::queryExtSetBeforePost(TDataSet *DataSet) {
	pGlobalSettings->SaveEtalonPath = SqlDBModule->GetStrFieldSQL("extSettingsGlobal", "paramValueStr", "UPPER(paramName)=UPPER('SavedEtalonsPath')", 0,
		lastErrr);
	pGlobalSettings->SaveResultPath = SqlDBModule->GetStrFieldSQL("extSettingsGlobal", "paramValueStr", "UPPER(paramName)=UPPER('SavedResultsPath')", 0,
		lastErrr);
}
// ---------------------------------------------------------------------------

void __fastcall TfmExtSettings::gridExtSetDblClick(TObject *Sender) {
	UnicodeString dir = "C:\\";
	if (queryExtSet->RecNo < 0 || gridExtSet->ReadOnly ) {

		return;
	}
	else {
		//if (SelectDirectory("Выберите папку", "Desktop", dir, TSelectDirExtOpts() << sdNewUI << sdValidateDir << sdShowEdit << sdNewFolder, 0)) {
        if (SelectDirectory("Выберите папку", "Desktop", dir, TSelectDirExtOpts() << sdNewUI << sdValidateDir, 0)) {
			//Application->MessageBoxW(L"Папка выбрана", L"Сообщение", MB_ICONERROR);
			MessageDlg("Папка выбрана", mtInformation, TMsgDlgButtons() << mbOK, NULL);
		}
		else {
			//Application->MessageBoxW(L"Отмена выбора", L"Сообщение", MB_ICONERROR);
			MessageDlg("Отмена выбора", mtInformation, TMsgDlgButtons() << mbOK, NULL);
		}
	}

}
// ---------------------------------------------------------------------------
