//---------------------------------------------------------------------------

#ifndef unPasswordFormH
#define unPasswordFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TPasswordForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *edit;
	TButton *okBtn;
	TButton *cancelBtn;
	void __fastcall okBtnClick(TObject *Sender);
	void __fastcall cancelBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    bool result;
	__fastcall TPasswordForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPasswordForm *PasswordForm;
//---------------------------------------------------------------------------
#endif
