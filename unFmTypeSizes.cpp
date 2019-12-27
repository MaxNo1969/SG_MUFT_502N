// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFmTypeSizes.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmTypeSizes *fmTypeSizes;

// ---------------------------------------------------------------------------
__fastcall TfmTypeSizes::TfmTypeSizes(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TfmTypeSizes::FormCreate(TObject *Sender) {
	blockControls = true;
	KeyPreview = true;
	bool RHKret = RegisterHotKey(Handle,
		// Handle окна, которому отправлять сообщения WM_HOTKEY
		0x00F, // УСЛОВНЫЙ идентификатор горячего ключа
		MOD_ALT + MOD_CONTROL, // модификаторы
		VK_RETURN // код клавиши
		);
	queryTypeSizes->Close();
	queryTypeSizes->SQL->Text = "SELECT rec_id,TSName as 'Наименование',Diameter as 'Диаметр' FROM TypeSizes order by TSName";
	queryTypeSizes->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TfmTypeSizes::FormClose(TObject *Sender, TCloseAction &Action) {
	queryTypeSizes->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfmTypeSizes::ApplicationEventsTsMessage(tagMSG &Msg, bool &Handled) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // сообщение наше
	{
		if (Msg.wParam == 0x00F) // идентификатор наш
		{
			Handled = true;
			blockControls = !blockControls;
			gridTypeSizes->ReadOnly = blockControls;
			if (blockControls) {
			   gridTypeSizes->Color=clInfoBk;
			} else{
			gridTypeSizes->Color=clActiveCaption;
			}
			navTypeSizes->Enabled = !blockControls;
		}
	}
}
// ---------------------------------------------------------------------------
