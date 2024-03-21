//---------------------------------------------------------------------------

#ifndef FRCheckMuftaH
#define FRCheckMuftaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "FRCheckMufta.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#include "Main.h"

//---------------------------------------------------------------------------
class TFRMMuftaLevel : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *btnCheck;
	TLabel *Label2;
	TEdit *edMaxVal;
	TEdit *edMinVal;
	void __fastcall btnCheckClick(TObject *Sender);
private:	// User declarations
    TMainForm *main;
public:		// User declarations
	__fastcall TFRMMuftaLevel(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRMMuftaLevel *FRMMuftaLevel;
//---------------------------------------------------------------------------
#endif
