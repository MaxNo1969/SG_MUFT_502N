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
	TLabel *Label7;
	TComboBox *cbName;
	TLabel *Label8;
	TEdit *edCheckMuftaLevelMax;
	TEdit *edCheckMuftaLevelMin;
	TLabeledEdit *lbeFreqSignal;
	TLabeledEdit *lbeVoltage;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall cbKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnAddClick(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall onElementChange(TObject *Sender);


private:	// User declarations
    int tsId; //Запомним rec_id для типоразмера на случай если поменяется имя и т.п.
	AnsiString groupName;
public:		// User declarations
	__fastcall TEgroupEditFrm(AnsiString _groupName);
};
//---------------------------------------------------------------------------
extern PACKAGE TEgroupEditFrm *EgroupEditFrm;
//---------------------------------------------------------------------------
#endif
