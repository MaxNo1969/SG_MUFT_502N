// ---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ABOUT_NTC_NK_URAN.h"
#include "IOUtils.hpp"
// ---------------------------------------------------------------------
#pragma resource "*.dfm"
TfmAboutBox *fmAboutBox;

// ---------------------------------------------------------------------
__fastcall TfmAboutBox::TfmAboutBox(TComponent* AOwner) : TForm(AOwner) {
}
// ---------------------------------------------------------------------

void __fastcall TfmAboutBox::FormShow(TObject *Sender) {
	TFile *f = new TFile();
	lCreationDate->Caption = "Дата сборки: " + f->GetLastWriteTime(Application->ExeName);
	delete f;
}
// ---------------------------------------------------------------------------
void __fastcall TfmAboutBox::LabelSendClick(TObject *Sender)
{
	try {
		// Application->MessageBoxW(L"Ругаться вредно!", L"Сообщение!",MB_ICONINFORMATION);
		ShellExecute(Handle, L"open", L"mailto:help.uran@gmail.com", NULL, NULL, SW_SHOWDEFAULT);
		// ShellExecute(Handle, L"open", L"http://uran-ndt.ru/", NULL, NULL, SW_SHOWDEFAULT);
	}
	catch (Exception *ex) {
		Application->MessageBoxW(ex->Message.c_str(), L"Ошибка!", MB_ICONERROR);
		// TDateTime currentDT;
		// AnsiString strCurrentDT = FormatDateTime("yyyy.mm.dd hh:mm:ss",currentDT.CurrentDateTime());
		// TPr::prWrite(strCurrentDT+AnsiString("PA: ") + ex->Message)
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmAboutBox::LabelSendMouseEnter(TObject *Sender)
{
	// сменим шрифт
	LabelSend->Font->Color = clBlue;
	LabelSend->Font->Style = TFontStyles() << fsUnderline;
}
//---------------------------------------------------------------------------

void __fastcall TfmAboutBox::LabelSendMouseLeave(TObject *Sender)
{
	// сменим шрифт
	LabelSend->Font->Color = clBlack;
	LabelSend->Font->Style = TFontStyles();
}
//---------------------------------------------------------------------------

void __fastcall TfmAboutBox::LabelOpenSiteDblClick(TObject *Sender)
{
	try {
		ShellExecute(Handle, L"open", L"http://uran-ndt.ru/", NULL, NULL, SW_SHOWDEFAULT);
	}
	catch (Exception *ex) {
		Application->MessageBoxW(ex->Message.c_str(), L"Ошибка!", MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmAboutBox::LabelOpenSiteMouseEnter(TObject *Sender)
{
	// сменим шрифт
	LabelOpenSite->Font->Color = clBlue;
	LabelOpenSite->Font->Style = TFontStyles() << fsUnderline;
}
//---------------------------------------------------------------------------

void __fastcall TfmAboutBox::LabelOpenSiteMouseLeave(TObject *Sender)
{
	// сменим шрифт
	LabelOpenSite->Font->Color = clBlack;
	LabelOpenSite->Font->Style = TFontStyles();
}
//---------------------------------------------------------------------------

