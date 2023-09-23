// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uFSignalsState.h"
#include "uFRSigPanel.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFSignalsState *FSignalsState;

// ---------------------------------------------------------------------------
//__fastcall TFSignalsState::TFSignalsState(TComponent* Owner,TIniFile* _ini,SignalList* _SL) : TForm(Owner)
__fastcall TFSignalsState::TFSignalsState(TComponent* Owner,  TGlobalSettings* _mainGlobalSettings, SignalList* _SL): TForm(Owner)
{
	//ini = _ini;
	SL=_SL;
}
// ---------------------------------------------------------------------------
//#pragma argused
void __fastcall TFSignalsState::FormShow(TObject *Sender)
{
	InOutTimer->Enabled = true;
    //Caption = this->ClassName();
}
// ---------------------------------------------------------------------------

void __fastcall TFSignalsState::InOutTimerTimer(TObject *Sender)
{
	TTimer* t = (TTimer*)Sender;
	t->Enabled = false;
	CheckSignals();
	t->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TFSignalsState::FormClose(TObject *Sender,
	TCloseAction &Action)
{
	InOutTimer->Enabled = false;
	Action=caFree;
}
// ---------------------------------------------------------------------------

void TFSignalsState::CheckSignals(void)
{
	for (int i = 0; i < ControlCount; i++)
	{
		TControl* p = Controls[i];
		if (p->ClassName() != "TFRSigPanel")
			continue;
		TFRSigPanel* pp = (TFRSigPanel*)p;
		pp->CheckSignal();
	}
}

void __fastcall TFSignalsState::FormHide(TObject *Sender)
{
	InOutTimer->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall TFSignalsState::FormCreate(TObject *Sender)
{
	int space = 5;
	int ltop0 = space;
	int ltop1 = space;
	int lwidth;
	for (int i = 0; i < SL->SignalCount(); i++)
	{
		CSignal* sig = SL->GetSignal(i);
		TFRSigPanel *p = new TFRSigPanel(this, sig);
		p->Parent = this;
		lwidth = p->Width;
		if (sig->IsInput())
		{
			AnsiString a = "In"+IntToStr(i);
			p->Name = a;
			p->Top = ltop0;
			p->Left = space;
			ltop0 += p->Height + space;
		}
		else
		{
			AnsiString a = "Out"+IntToStr(i);
			p->Name = a;
			p->Top = ltop1;
			p->Left = space + lwidth + space;
			ltop1 += p->Height + space;
		}
	}
	Width = space + lwidth + space + lwidth + space + (Width - ClientWidth);
	if (ltop0 < ltop1)
		ltop0 = ltop1;
	ClientHeight = ltop0;// + (Height - ClientHeight);
}
// ---------------------------------------------------------------------------

void __fastcall TFSignalsState::FormDestroy(TObject *Sender)
{
	//SaveFormPos(this, ini);
}
// ---------------------------------------------------------------------------
