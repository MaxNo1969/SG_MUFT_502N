//---------------------------------------------------------------------------

#ifndef unFmSignalsShowH
#define unFmSignalsShowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
#ifndef TVIRTLCARD502
 #include "TWorkX502.h"
#else
 #include "TVirtualX502.h"
#endif
#include "unTGlobalSettings.h"

//#include "Main.h"
//#include "UnDataMod.h"
// ---------------------------------------------------------------------------
// #define xApplPath  ExtractFilePath(Application->ExeName)
class TfmSignalsShow : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelRight;
	TStringGrid *StringGridDIO;
	TStatusBar *StatusBarSignalsState;
	TTimer *timerCheckSignals;
	TStatusBar *StatusBar1;
	TPanel *PanelBottom;
	TButton *ButtonStart;
	TButton *ButtonStop;
	TStringGrid *StringGridADC;
	TPanel *PanelTop;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall StringGridDIODrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall timerCheckSignalsTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
 bool isError;
 TStatusBar* ssStatusBar;
 TLabel* ssStatusLabel;
 TGlobalSettings* ssProgramSettings;
public:		// User declarations
	__fastcall TfmSignalsShow(TComponent* Owner,TStatusBar* _mainStatusBar,TLabel* _mainStatusLabel,TGlobalSettings* _programSettings);
   int	CheckSignals(void);
   //
#ifndef TVIRTLCARD502
 TWorkX502* sshWorkX502;
#else
 TVirtualX502* sshWorkX502;
#endif

       //строка для вывода сообщений
	AnsiString msgLast;
};
//---------------------------------------------------------------------------
extern PACKAGE TfmSignalsShow *fmSignalsShow;
//---------------------------------------------------------------------------
#endif
