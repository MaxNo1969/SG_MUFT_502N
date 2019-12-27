//---------------------------------------------------------------------------

#ifndef unFmMessageH
#define unFmMessageH
//---------------------------------------------------------------------------
//#include <System.Classes.hpp>
//#include <Vcl.Controls.hpp>
//#include <Vcl.StdCtrls.hpp>
//#include <Vcl.Forms.hpp>
//#include <Vcl.ExtCtrls.hpp>
//#include <Vcl.Buttons.hpp>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfmMessage : public TForm
{
__published:	// IDE-managed Components
	TPanel *panelBottom;
	TLabel *labelMsg;
	TSpeedButton *speedButtonOk;
	void __fastcall speedButtonOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmMessage(TComponent* Owner,AnsiString _msg,TColor _color);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMessage *fmMessage;
//---------------------------------------------------------------------------
#endif
