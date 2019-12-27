//---------------------------------------------------------------------------

#ifndef unFmEditSettingsH
#define unFmEditSettingsH
#include <ADODB.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#ifdef BERLIN_10
  #include <System.Classes.hpp>
  #include <Vcl.Controls.hpp>
  #include <Vcl.StdCtrls.hpp>
  #include <Vcl.Forms.hpp>
  #include <Data.DB.hpp>
  #include <Vcl.DBCtrls.hpp>
  #include <Vcl.DBGrids.hpp>
  #include <Vcl.ExtCtrls.hpp>
  #include <Vcl.Grids.hpp>
  #include <Vcl.Mask.hpp>
  #include <Data.Win.ADODB.hpp>
#else
  #include <Classes.hpp>
  #include <Controls.hpp>
  #include <DB.hpp>
  #include <DBCtrls.hpp>
  #include <DBGrids.hpp>
  #include <ExtCtrls.hpp>
  #include <Grids.hpp>
#endif

//---------------------------------------------------------------------------

//#include "UnDataMod.h"

//---------------------------------------------------------------------------
class TfmSettings : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSourceSettings;
	TDBGrid *DBGridSettings;
	TDBNavigator *DBNavigatorSettings;
	TADOQuery *getHintsADOQuery;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress_old(TObject *Sender, System::WideChar &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfmSettings(TComponent* Owner,TADOQuery* _setADOQueryDB, bool _gridUse);
    TADOQuery *setADOQueryDB;
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSettings *fmSettings;
//---------------------------------------------------------------------------
#endif
