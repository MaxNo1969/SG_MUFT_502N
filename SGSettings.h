// ---------------------------------------------------------------------------

#ifndef SGSettingsH
#define SGSettingsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//#include "IniFiles.hpp"
#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <vector>
#include <Registry.hpp>
#include "unSQLDbModule.h"
#include "unTUtils.h"
#include "TGlobalSettings.h"


// ---------------------------------------------------------------------------
class TSGSettForm : public TForm
{
__published: // IDE-managed Components
	TPanel *pBottom;
	TButton *bSave;
	TButton *bExit;
	TGroupBox *gbSinusFrequencies;
	TComboBox *cbTypeSize;
	TGroupBox *gbSolidGroup;
	TComboBox *cbSolidGroup;
	TButton *bNewSG;
	TGroupBox *gbSGThreshold;
	TADOQuery *queryFrec;
	TDBGrid *gridFrec;
	TDataSource *sourseFrec;
	TDataSource *sourseTSz;
	TPanel *Panel1;
	TADOQuery *queryTSz;
	TDBNavigator *navFrec;
	TDBNavigator *navTS;
	TDBGrid *gridTSz;
	TADOCommand *commandFrec;
	TRadioGroup *rgCalcAlgo;
	TApplicationEvents *ApplicationEvents;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall bSaveClick(TObject *Sender);
	void __fastcall bExitClick(TObject *Sender);
	void __fastcall eThresholdResistKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall cbTypeSizeSelect(TObject *Sender);
	void __fastcall queryFrecAfterInsert(TDataSet *DataSet);
	void __fastcall queryTSzBeforePost(TDataSet *DataSet);

private:
	// User declarations
	TGlobalSettings *pGlobalSettings;
	bool fl;
	void BlockControls(bool _fl);
	void LoadSolidGroup();
	void SaveSolidGroup();
	AnsiString solidGroupCur;
	AnsiString strSQLTsz;
	AnsiString strSQLFrec;
	void __fastcall UserWndProc(Messages::TMessage &_msg);

public: // User declarations
	__fastcall TSGSettForm(TComponent* Owner,TGlobalSettings *_pGlobalSettingsp);
	bool need_redraw;

};

// ---------------------------------------------------------------------------
extern PACKAGE TSGSettForm *SGSettForm;
// ---------------------------------------------------------------------------
#endif
