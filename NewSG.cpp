//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewSG.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewSGForm *NewSGForm;
//---------------------------------------------------------------------------
__fastcall TNewSGForm::TNewSGForm(AnsiString _TypeSize)
	: TForm(Owner)
{
	TypeSize = _TypeSize;
	eNewSGName->Text = "";
	NewSGName = "";
}
//---------------------------------------------------------------------------
void __fastcall TNewSGForm::bOKClick(TObject *Sender)
{
//	if(eNewSGName->Text != "")
//	{
//		//Проверим что такой еще не было для этого типоразмера
//		AnsiString SQL = "";
//		SQL = "SELECT * FROM SolidGroups as a ";
//		SQL += "WHERE a.TypeSize=" + TypeSize + " ";
//		SQL += "AND a.SolidGroup=" + eNewSGName->Text;
//		CSelect SGSett(SQL);
//		if(SGSett.Count()!=0)
//		{
//			Application->MessageBoxW(L"Такая ГП уже есть - попробуйте другое название"
//				, L"Ошибка"	, MB_ICONERROR | MB_OK);
//			return;
//		}
//		NewSGName = eNewSGName->Text;
//		Close();
//	}
}
//---------------------------------------------------------------------------
