// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFmMessage.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMessage *fmMessage;

// ---------------------------------------------------------------------------
__fastcall TfmMessage::TfmMessage(TComponent* Owner, AnsiString _msg, TColor _color) : TForm(Owner) {
	this->labelMsg->Font->Color = _color;
	this->labelMsg->Caption = _msg;
	if (_color==clRed) {
	   this->speedButtonOk->Caption="Продолжить";
	}else{
		this->speedButtonOk->Caption="Продолжить";
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmMessage::speedButtonOkClick(TObject *Sender) {
	this->ModalResult = mrOk;
}
// ---------------------------------------------------------------------------
