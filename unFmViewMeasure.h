// ---------------------------------------------------------------------------

#ifndef unFmViewMeasureH
#define unFmViewMeasureH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
// #include "Chart.hpp"
// #include "TeEngine.hpp"
// #include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
// #include <ADODB.hpp>
// #include <DB.hpp>
// ---------------------
#include <vector>
// --------------------
#include "TGlobalSettings.h"
#include "unTUtils.h"
#include "TMeasuresData.h"
// форма для просмотра зон
// ---------------------------------------------------------------------------
class TfmViewMeasure : public TForm {
__published: // IDE-managed Components
	TPopupMenu *popupMenuChartZone;
	TMenuItem *ZoomUp;
	TMenuItem *ZoomDown;
	TMenuItem *mnuZoomReset;
	TChart *chartView;
	TFastLineSeries *Series1;
	TFastLineSeries *Series2;
	TFastLineSeries *Series3;

	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ChartViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ZoomUpClick(TObject *Sender);
	void __fastcall mnuZoomResetClick(TObject *Sender);
	void __fastcall ZoomDownClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations
			// переменные
	AnsiString title;
	double start;
	double zone_size;
	int curr_zone;
	int curr_sens;
	int DevidMeas1;
	int DevidMeas2;
	bool IsLinear;
	int curr_defect;
	bool KeyUpFlag;
	double levelOut1;
	double levelOut2;
	double levelIn1;
	double levelIn2;
	bool mouse_on;
	int offsetView;
	TColor colorsSeries[];
	TGlobalSettings* pProgramSettings;
	TMeasuresData* pMeasuresData;
	vector<int> ThresVal;
	vector<double> BarkVal;
	int savedLeftAxisMaximum;
	int savedLeftAxisMinimum;
	// функции
	void SetBorder(TLineSeries* _series, double _level, TColor _color);
	// Рисует границы дефектов
	void SetBrackBorder(int _startMeas, int _finalMeas, double _Border,
		TColor _color, AnsiString _mark);

public: // User declarations
	__fastcall TfmViewMeasure(TComponent* Owner, TMeasuresData* _measuresData,
		TGlobalSettings* _programSettings, vector<int> _ThresVal, vector<double> _BarkVal);
    //_showAll=true - показываем вообще все
	int __fastcall PrepareChartToShow(TChart *_chart, TMeasuresData* _measuresData,
		int _countLogCh, int _maxY, int _maxX, AnsiString _title);
	int __fastcall TfmViewMeasure::PrepareSensor(int _selZone, int _selSensor);
	void SetCaption(AnsiString _cap);
	void Clear(void);
	void SetMetric(double _start, double _zone_size);
	void SetInner(bool _v);
	void SetCurrPoint(int _curr_zone, int _curr_sens, bool _IsLinear);
	// показывает границы поиска дефектов СОП
	void ViewEtalonCheck(void);
	// расчитывает измерение на графике в зависимости от расстояния
	int CalcMeasFromRange(int _x);

	int __fastcall ShowZone(int _selZone);
	int __fastcall ShowSensor(int _selZone, int _selDate);
};

extern PACKAGE TfmViewMeasure* fmViewMeasure;
#endif
