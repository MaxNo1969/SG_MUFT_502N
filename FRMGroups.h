//---------------------------------------------------------------------------

#ifndef FRMGroupsH
#define FRMGroupsH
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
class TFRGroups : public TForm
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
	void __fastcall tbButtonClick(TObject *Sender);
    void __fastcall beforeInsert(TDataSet* DataSet);
private:	// User declarations
	void __fastcall AddNewGroup(void);
public:		// User declarations
	__fastcall TFRGroups(TComponent* Owner);
	__fastcall ~TFRGroups();
};
//---------------------------------------------------------------------------
extern PACKAGE TFRGroups *FRGroups;
//---------------------------------------------------------------------------
#endif
