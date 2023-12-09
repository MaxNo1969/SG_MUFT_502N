//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <string>
#include "unPasswordForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPasswordForm *PasswordForm;
//---------------------------------------------------------------------------
__fastcall TPasswordForm::TPasswordForm(TComponent* Owner)
	: TForm(Owner)
{
    result = false;
}
//---------------------------------------------------------------------------
void __fastcall TPasswordForm::okBtnClick(TObject *Sender)
{
	std::wfstream f(L"./password.txt");
	if(f)
	{
		std::wstring s;
		getline(f,s);
		result = 0 == UnicodeString(s.c_str()).Compare(edit->Text);
		f.close();
	}
	else
	{
		result = "p@ssw0rd" == edit->Text;
	}
	if(result)Close();
}
//---------------------------------------------------------------------------
void __fastcall TPasswordForm::cancelBtnClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
