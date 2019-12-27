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
		// Handle ����, �������� ���������� ��������� WM_HOTKEY
		0x00F, // �������� ������������� �������� �����
		MOD_ALT + MOD_CONTROL, // ������������
		VK_RETURN // ��� �������
		);
	queryTypeSizes->Close();
	queryTypeSizes->SQL->Text = "SELECT rec_id,TSName as '������������',Diameter as '�������' FROM TypeSizes order by TSName";
	queryTypeSizes->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TfmTypeSizes::FormClose(TObject *Sender, TCloseAction &Action) {
	queryTypeSizes->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfmTypeSizes::ApplicationEventsTsMessage(tagMSG &Msg, bool &Handled) {
	// ��������� �� ������� ��������� ������ Ctrl+Alt+Enter
	if (Msg.message == WM_HOTKEY) // ��������� ����
	{
		if (Msg.wParam == 0x00F) // ������������� ���
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
