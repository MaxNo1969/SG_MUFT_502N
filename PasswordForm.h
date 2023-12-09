//---------------------------------------------------------------------------

#ifndef PasswordFormH
#define PasswordFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TPassworfForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *edit;
	TButton *okBtn;
	TButton *cancelBtn;
private:	// User declarations
public:		// User declarations
	__fastcall TPassworfForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPassworfForm *PassworfForm;
//---------------------------------------------------------------------------
#endif
