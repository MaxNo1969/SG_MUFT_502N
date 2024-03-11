//---------------------------------------------------------------------------

#ifndef FREgroupEditH
#define FREgroupEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "TGlobalSettings.h"
#include "Main.h"

class TEgroupEditFrm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbGost;
	TLabel *Label1;
	TComboBox *cbTypeSizes;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edName;
	TLabel *Label4;
	TComboBox *cbCustomer;
	TComboBox *cbThreadType;
	TLabel *Label5;
	TComboBox *cbChampferType;
	TLabel *Label6;
	TButton *btnAdd;
	TButton *btnCancel;
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall cbKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);


private:	// User declarations
	TGlobalSettings *gs;
    TMainForm *main;
public:		// User declarations
	__fastcall TEgroupEditFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEgroupEditFrm *EgroupEditFrm;
//---------------------------------------------------------------------------
#endif
