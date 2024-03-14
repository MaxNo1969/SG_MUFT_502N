// ---------------------------------------------------------------------------

#ifndef unDiagnostH
#define unDiagnostH
// ---------------------------------------------------------------------------

//------
#include "TGSPF052.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "unSQLDbModule.h"
#include "unEditEtalon.h"


  #include <System.Classes.hpp>
  #include <Vcl.Controls.hpp>
  #include <Vcl.StdCtrls.hpp>
  #include <Vcl.Forms.hpp>
  #include <Vcl.ExtCtrls.hpp>
  #include <Vcl.Buttons.hpp>
  #include <VclTee.TeeGDIPlus.hpp>
  #include <VCLTee.Chart.hpp>
  #include <VCLTee.TeEngine.hpp>
  #include <VCLTee.TeeProcs.hpp>
  #include <VCLTee.TeCanvas.hpp>
  #include <VCLTee.Series.hpp>
  #include <System.IOUtils.hpp>
//------------------
 #include "TLCard502.h"
//---------------------
#include "TThreadDiag.h"
#include "SignalList.h"
#include "TLCardData.h"
#include "TypeSizeFrequencies.h"
#include "TSG.h"

#define colorSer2[7]={clBlue,clRed,clGreen,clFuchsia,clYellow,clWhite,clBlack};
// ---------------------------------------------------------------------------
class TfmDiagnost : public TForm {
__published: // IDE-managed Components
	TPanel *PanelBottom;
	TBitBtn *btnStopGen;
	TBitBtn *btnStartGen;
	TLabeledEdit *lbeFrecSignalGSPF052;
	TLabeledEdit *lbeVoltageGSPF052;
	TLabeledEdit *lbeFrecDiscrGSPF052;
	TBitBtn *btnStartSer;
	TPanel *PanelGraph;
	TChart *ChartGPSF052;
	TPanel *BottomPanel;
	TLabel *lMinScrollbar;
	TLabel *lMaxScrollbar;
	TScrollBar *scbChartDraggerDiag;
	TStatusBar *StatusBarDiag;
	TBitBtn *btnReCalc;
	TGroupBox *GroupBoxNGr;
	TComboBox *cbxSGD;
	TBitBtn *bbtCreateEtalon;
	TADOQuery *queryEtalon;
	TButton *Button1;
	TADOCommand *cmdEtalonVal;
	TPanel *PanelSG;
	TLineSeries *Series1;

	void __fastcall btnStartGenClick(TObject *Sender);
	void __fastcall btnStopGenClick(TObject *Sender);
	void __fastcall btnStartSerClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall scbChartDraggerDiagChange(TObject *Sender);
	void __fastcall ChartGPSF052Scroll(TObject *Sender);
	void __fastcall btnReCalcClick(TObject *Sender);
	void __fastcall bbtCreateEtalonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private: // User declarations
	TGlobalSettings* pGlobalSettings;
	TGSPF052* gen;
	//����� ������
	TColor colorSer[7];//={clBlue,clRed,clGreen,clFuchsia,clYellow,clWhite,clBlack};
	void __fastcall UserWndProc(Messages::TMessage &_msg);
		// LCard502 - ��������� �� �����
	TLCard502* diagL�ard502;
	//������ � �����
	TLCardData* lCardData;
	//��� ������
	 int err;
	 int step;
	 //������ �������� �����������
	 //int currTypeSize;
	 //���������� ������������ �������
	 int chCount;
	 //����� ���������
	 int genTime;
	 //������� �����������
	 TSFrequencies* TSFreqs;
	 //������ ��������� �����
	 TThDiag* thDiag;
	 //���������� ��������� � �����
	 int chartLength;
	 //������� ��������
	 long curPos;
	 //���������� ������� �������� �����
	 bool timeFlag;
     bool enableF;
	 //���������� ��������� ����������
	 void BlockControl(bool ToTest);
	 AnsiString fileName;
	 //��������� ��
	 CSG csg;
public: // User declarations
	__fastcall TfmDiagnost(TComponent* Owner,TGlobalSettings* _pGlobalSettings,TLCard502* _L�ard502,TLCardData* _lCardData);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfmDiagnost *fmDiagnost;
// ---------------------------------------------------------------------------
#endif
