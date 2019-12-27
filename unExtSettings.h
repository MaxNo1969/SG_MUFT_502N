//---------------------------------------------------------------------------

#ifndef unExtSettingsH
#define unExtSettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
#include "TGlobalSettings.h"
#include "unSQLDbModule.h"
#include "FileCtrl.hpp"
#include <System.IOUtils.hpp>
class TfmExtSettings : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *gridExtSet;
	TDataSource *dsExtSet;
	TApplicationEvents *apEvExtSet;
	TADOQuery *queryExtSet;
	TDBNavigator *navExtSet;
	TOpenDialog *openDExtSet;
	void __fastcall apEvExtSetMessage(tagMSG &Msg, bool &Handled);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall queryExtSetBeforePost(TDataSet *DataSet);
	void __fastcall gridExtSetDblClick(TObject *Sender);
private:	// User declarations
TGlobalSettings* pGlobalSettings;
int lastErrr;
bool blockControls;
public:		// User declarations
	__fastcall TfmExtSettings(TComponent* Owner,TGlobalSettings* _pGlobalSettings);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmExtSettings *fmExtSettings;
//---------------------------------------------------------------------------
#endif
