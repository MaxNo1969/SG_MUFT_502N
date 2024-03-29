//---------------------------------------------------------------------------

#ifndef FRGostsH
#define FRGostsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TFRSprGost : public TForm
{
__published:	// IDE-managed Components
	TToolBar *tb;
	TDBGrid *grid;
	TSpeedButton *bPrev;
	TSpeedButton *bFirst;
	TSpeedButton *bNext;
	TSpeedButton *bEnd;
	TSpeedButton *bAdd;
	TSpeedButton *bPost;
	TSpeedButton *bDel;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tbButtonClick(TObject *Sender);
    void __fastcall beforeInsert(TDataSet* DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TFRSprGost(TComponent* Owner);
	__fastcall ~TFRSprGost();
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSprGost *FRSprGost;
#endif
