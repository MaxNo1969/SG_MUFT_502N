// ---------------------------------------------------------------------------

#ifndef MainH
#define MainH
// ---------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <vcl.h>
#include <dir.h>
#include <AppEvnts.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
// ---------------
// #include <PlatformDefaultStyleActnCtrls.hpp>

 #include <Vcl.Dialogs.hpp>
 #include <Vcl.AppEvnts.hpp>
 #include <System.ImageList.hpp>
 #include <Vcl.Menus.hpp>
 #include <Vcl.ImgList.hpp>
 #include <Vcl.ToolWin.hpp>
 #include <Vcl.ComCtrls.hpp>
 #include <VclTee.TeeGDIPlus.hpp>
 #include <VCLTee.Chart.hpp>
 #include <VCLTee.TeEngine.hpp>
 #include <VCLTee.TeeProcs.hpp>
 #include <VCLTee.TeCanvas.hpp>
 #include <VCLTee.Series.hpp>
 #include <System.IOUtils.hpp>
 #include <Vcl.ImgList.hpp>
 #include <IOUtils.hpp>
 #include <Dialogs.hpp>
 #include <AppEvnts.hpp>
 #include <Menus.hpp>
 #include <ImgList.hpp>
 #include <ToolWin.hpp>
 #include <ComCtrls.hpp>
 //#include <ImageList.hpp>
// -----------
// -----------------------
// #include <PlatformDefaultStyleActnCtrls.hpp>

#include "TGlobalSettings.h"
#include "TLogCh502Params.h"
#include "unSQLDbModule.h"
#include "ThreadWork.h"
#include "TLCardData.h"
#include "unEditEtalon.h"
#include "TypeSizeFrequencies.h"
#include "TGSPF052.h"
#include "unFmTypeSizes.h"
//-------------------
 #include "TLCard502.h"

// ---------------------------------------------------------------------------
class TMainForm : public TForm {
__published: // IDE-managed Components

	TStatusBar *StatusBar;
	TMainMenu *MainMenu;
	TMenuItem *N3;
	TMenuItem *menuSettings;
	TMenuItem *menuSGSett;
	TMenuItem *N6;
	TMenuItem *menuProtocol;
	TMenuItem *N9;
	TMenuItem *menuSave;
	TMenuItem *menuOpen;
	TMenuItem *N10;
	TMenuItem *menuAbout;
	TPanel *BottomPanel;
	TLabel *lMinScrollbar;
	TLabel *lMaxScrollbar;
	TScrollBar *scbChartDragger;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TMenuItem *menuColorSett;
	TApplicationEvents *ApplicationEvents;
	TMenuItem *menuTypeSize;
	TMenuItem *mnuCheckGen;
	TMenuItem *mnuCheck1730;
	TMenuItem *menuEtalons;
	TADOQuery *queryEtalon;
	TADOCommand *cmdEtalonVal;
	TPanel *PanelChartTop;
	TChart *SignalChart;
	TFastLineSeries *Series1;
	TFastLineSeries *Series2;
	TFastLineSeries *Series3;
	TPanel *PanelChartBottom;
	TChart *EtalonChart;
	TFastLineSeries *FastLineSeries1;
	TFastLineSeries *FastLineSeries2;
	TFastLineSeries *FastLineSeries3;
	TSplitter *SplitterMid;
	TPanel *PanelTop;
	TComboBox *cbTypeSize;
	TComboBox *cbSGGost;
	TButton *bStart;
	TButton *bCancel;
	TGroupBox *GroupBoxNGr;
	TBitBtn *bbtCreateEtalon;
	TComboBox *cbxSG;
	TPanel *PanelSG;
	TSplitter *SplitterRes;
	TMenuItem *menuExtSet;
	TTimer *timerCheck1730;
	TMenuItem *N1;
	TButton *btnExit;
	TMenuItem *mnAbaut;
	TMenuItem *menuGosts;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall menuSaveClick(TObject *Sender);
	void __fastcall menuOpenClick(TObject *Sender); // открывает муфту
	void __fastcall SignalChartClick(TObject *Sender);
	void __fastcall SignalChartScroll(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall bStartClick(TObject *Sender);
	void __fastcall bCancelClick(TObject *Sender);
	void __fastcall menuColorSettClick(TObject *Sender);
	void __fastcall scbChartDraggerChange(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall menuSettingsClick(TObject *Sender);
	void __fastcall menuTypeSizeClick(TObject *Sender);
	void __fastcall menuSGSettClick(TObject *Sender);
	void __fastcall PanelSQClick(TObject *Sender);
	void __fastcall PanelONClick(TObject *Sender);
	void __fastcall mnuCheckGenClick(TObject *Sender);
	void __fastcall mnuCheck1730Click(TObject *Sender);
	void __fastcall menuEtalonsClick(TObject *Sender);
	void __fastcall cbTypeSizeSelect(TObject *Sender);
	void __fastcall bbtCreateEtalonClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall cbSGGostSelect(TObject *Sender);
	void __fastcall SplitterMidMoved(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SplitterResMoved(TObject *Sender);
	void __fastcall cbTypeSizeChange(TObject *Sender);
	void __fastcall menuExtSetClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall mnAbautClick(TObject *Sender);
	void __fastcall menuGostsClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
    bool options;
	// общие настройки программы
	TGlobalSettings mainGlobalSettings;
	// LCard502 - указатель на карту
	TLCard502 *lСard502;
	// указатель на массив данных
	TLCardData* lCardData;
    AnsiString lastMsg;
	// vector<TEdit*> eThresholds; // Поля для отображения порогов
	public:
	void ClearCharts(void); // очищает график
    private:
	void DrawOnChart(); // рисует на чарте
	void DrawThresholds(); // рисует пороги на чарте
	void UpdateStatus(AnsiString _text1, AnsiString _text2);

	// vector<TLineSeries*> lsThresholds; // массив серий с порогами

	void SaveToFile(UnicodeString FileName); // сохраняет трубу

	long curPos;

	UINT set_msg;
	//группа прочности
	CSG csg;

	void __fastcall WmDropFiles(TWMDropFiles& Message);
	void __fastcall ReadFile(AnsiString FileName);
	BEGIN_MESSAGE_MAP MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WmDropFiles)
		END_MESSAGE_MAP(TForm);

	// TIniFile* ini;
	// vector<IU> SGSignal;
	// vector<IU> lSGSignal;
	// SGCoords* sgc;
	// vector<double>local_th;

	bool inWork; // установка в работе
	ThreadWork *threadWork;
	int thresholdCount;

	void ChangeColor();

	TColor ActiveIn;
	TColor NotActiveIn;
	//Частоты текущего типоразмера
	TSFrequencies *TSFreqs;
	//плата генератора сигнала
   TGSPF052* gen;

	//запуск рабочего цикла
	void Start();
	//перезапуск рабочего цикла
	void ReStart();
	//остановка рабочего цикла
	void Stop();
	//Перерисовываем графики
	void Redraw();
   private:
	//блокируем кнопки
	void SetAbleButtons(bool _enable);
	//код последней ошибки
    void EnableWigits(bool b);
	int lastError;
public: // User declarations

	__fastcall TMainForm(TComponent* Owner);
	void LoadFromFile(UnicodeString FileName);

};

// ---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// ---------------------------------------------------------------------------
#endif
