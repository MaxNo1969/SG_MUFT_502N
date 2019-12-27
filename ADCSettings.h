// ---------------------------------------------------------------------------

#ifndef ADCSettingsH
#define ADCSettingsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//#include "IniFiles.hpp"
#include <AppEvnts.hpp>
#include "Filters.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "uTFilterSettings.h"
#include "uTFRSensor.h"
#include <vector>
#include <Registry.hpp>
#include "uCRListT.h"
//------------------
 #include "TLCard502.h"
//---------------------
//#include "RLCard_parameters.h"


// ---------------------------------------------------------------------------
class TADCSettForm : public TForm
{
__published: // IDE-managed Components

	TApplicationEvents *ApplicationEvents;
	TPanel *pBottom;
	TButton *bSave;
	TButton *bExit;
	TPageControl *PageControl;
	TTabSheet *ppPage;
	TLabel *Label2;
	TEdit *readRate;
	TGroupBox *gbSG;
	TEdit *sendRate;
	TLabel *Label1;
	TFilterSettings *FSSG;
	TTrackBar *tbCheckMuftaLevel;
	TLabel *lCheckMuftaLevelCaption;
	TEdit *edLevelMut;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall bSaveClick(TObject *Sender);
	void __fastcall bExitClick(TObject *Sender);
	void __fastcall eThresholdResistKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall tbCheckMuftaLevelChange(TObject *Sender);
	void __fastcall edLevelMutEnter(TObject *Sender);
	void __fastcall edLevelMutExit(TObject *Sender);
	void __fastcall edLevelMutKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:
	// User declarations
	//фреймы параметров
	CRListT<TFRSensor> listSens;
	TLCard502 *sLСard502;

	void block();

	bool flag; //активна ли блокировка

	void FillAllControls();
	//RLCard_parameters* Par;

public: // User declarations
	__fastcall TADCSettForm(TComponent* Owner,TLCard502 *_lСard502);
	bool need_redraw;

};

// ---------------------------------------------------------------------------
extern PACKAGE TADCSettForm *ADCSettForm;
// ---------------------------------------------------------------------------
#endif
