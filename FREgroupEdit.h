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
	TButton *btnSave;
	TButton *btnCancel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall cbKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
	TGlobalSettings *gs;
public:		// User declarations
	__fastcall TEgroupEditFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEgroupEditFrm *EgroupEditFrm;
//---------------------------------------------------------------------------
#endif
