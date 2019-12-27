//---------------------------------------------------------------------------

#ifndef ColorSettingsH
#define ColorSettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//#include "IniFiles.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "unSQLDbModule.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TFormColor : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *ColorSolidGroups;
	TColorDialog *ColorDialog;
	TButton *BSave;
	TButton *BClose;
	TPanel *pBottom;
	TDBGrid *DBGrid1;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	void __fastcall PanelSignalSGClick(TObject *Sender);
	void __fastcall BCloseClick(TObject *Sender);
	void __fastcall BSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:	// User declarations
//	TIniFile *ini;
public:		// User declarations

//	TColor SolidGroup_D;
//	TColor SolidGroup_E;
//	TColor SolidGroup_K;

	__fastcall TFormColor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormColor *FormColor;
//---------------------------------------------------------------------------
#endif
