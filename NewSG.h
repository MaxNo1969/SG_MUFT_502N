//---------------------------------------------------------------------------

#ifndef NewSGH
#define NewSGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNewSGForm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *eNewSGName;
	TButton *bOK;
	void __fastcall bOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNewSGForm(AnsiString _TypeSize);
	AnsiString NewSGName;
    AnsiString TypeSize;
};
//---------------------------------------------------------------------------
extern PACKAGE TNewSGForm *NewSGForm;
//---------------------------------------------------------------------------
#endif
