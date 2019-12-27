//---------------------------------------------------------------------------

#ifndef unFmTypeSizesH
#define unFmTypeSizesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "unSQLDbModule.h"
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TfmTypeSizes : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *queryTypeSizes;
	TDBGrid *gridTypeSizes;
	TDBNavigator *navTypeSizes;
	TDataSource *dsTypeSizes;
	TApplicationEvents *ApplicationEventsTs;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ApplicationEventsTsMessage(tagMSG &Msg, bool &Handled);
private:	// User declarations
bool blockControls;
public:		// User declarations
	__fastcall TfmTypeSizes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmTypeSizes *fmTypeSizes;
//---------------------------------------------------------------------------
#endif
