//---------------------------------------------------------------------------

#ifndef FRMEtalonsH
#define FRMEtalonsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class TFREtalons : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *grid;
	TToolBar *tb;
	TSpeedButton *bFirst;
	TSpeedButton *bPrev;
	TSpeedButton *bNext;
	TSpeedButton *bEnd;
	TSpeedButton *bAdd;
	TSpeedButton *bDel;
	TSpeedButton *bPost;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall bButtonClick(TObject *Sender);
	void __fastcall beforeInsert(TDataSet* DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TFREtalons(TComponent* Owner);
    __fastcall ~TFREtalons();
};
//---------------------------------------------------------------------------
extern PACKAGE TFREtalons *FREtalons;
//---------------------------------------------------------------------------
#endif
