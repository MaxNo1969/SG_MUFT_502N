// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <vector>
#include "Main.h"
#include "TProtocol.h"
#include "ColorSettings.h"
#include "Filters.h"
// ---------------------------------------------------------------------------
#include "unFmMessage.h"
#include "unTExtFunction.h"
#include "unDiagnost.h"
#include "unFmEditSettings.h"
#include "uFSignalsState.h"
#include "SignalListDef.h"
#include "ADCSettings.h"
#include "SGSettings.h"
#include "EtalonDatas.h"
#include "unExtSettings.h"
#include "InOutBits.h"
#include "unPasswordForm.h"
#include "FRGosts.h"
#include "About.h"
#include "FRMEtalons.h"
#include "FREgroupEdit.h"
#include "FRMGroups.h"
#include "FRCheckMufta.h"
// -----------------------------------

#pragma resource "*.dfm"
TMainForm *MainForm;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {

	AnsiString applPath = ExtractFilePath(Application->ExeName);
	mainGlobalSettings.applPath = applPath;
	applPath += "connectSQL.udl";
	//�������� ������� �����
	if(!FileExists(applPath,False))
	{
		AnsiString err = "��� ����� ���������� � ��: " + applPath;
		throw Exception(err);
	}
	mainGlobalSettings.LoadPRGSettings(applPath);
	mainGlobalSettings.threadMsg = RegisterWindowMessage(L"Thread");
	mainGlobalSettings.mainHandle = this->Handle;
	if (mainGlobalSettings.threadMsg == 0)
	{
		throw Exception("TMainForm::TMainForm �� ���� ���������������� ���������");
	}

    FillGroupsCb();


	l�ard502 = new TLCard502(&mainGlobalSettings);
	TSFreqs = new TSFrequencies(mainGlobalSettings.indexCurrentTypeSize);
	int freqCount = TSFreqs->Frequency.size();
	lCardData = new TLCardData(l�ard502, freqCount, 3, &mainGlobalSettings); // todo �������� 1 �������
	SLD = new SignalListDef();
#ifndef _LCARDEMUL
	SLD->dev = new InOutBits(l�ard502);
#else
	SLD->dev = new InOutBitsEmul(l�ard502);
	SLD->iCC->Set(true);
#endif
	SGFilter = new Filters("SG");
	SGFilter->setSettingsFromDB();
}

void __fastcall TMainForm::FillGroupsCb()
{
	// �������� ������ ����� ��������
	SqlDBModule->FillComboBoxFromSql(
	"\
		select ts.rec_id, ts.TSName as F1\
		from TypeSizes ts\
		order by ts.Diameter,ts.TSName\
	", cbEtalonGroup);
	cbEtalonGroup->ItemIndex = 0;
	for(int i = 0; i < cbEtalonGroup->Items->Count; i++)
	{
		if(mainGlobalSettings.indexCurrentTypeSize == (int)cbEtalonGroup->Items->Objects[i])
		{
			cbEtalonGroup->ItemIndex = i;
			break;
		}
	}
}


// ---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender) {
	PanelSG->Width = 350;

	/*
	// ����� �����
	SqlDBModule->FillComboBox("GOST", "Name", cbSGGost);
	for (int i = 0; i < cbSGGost->Items->Count; i++) {
		if ((int)cbSGGost->Items->Objects[i] == mainGlobalSettings.indexCurrentSGGost) {
			cbSGGost->ItemIndex = i;
			break;
		}
		else {
			cbSGGost->ItemIndex = -1;
		}
	}
	// ����� �����������
	SqlDBModule->FillComboBox("TypeSizes", "TSName", cbTypeSize);
	for (int i = 0; i < cbTypeSize->Items->Count; i++) {
		if ((int)cbTypeSize->Items->Objects[i] == mainGlobalSettings.indexCurrentTypeSize) {
			cbTypeSize->ItemIndex = i;
			break;
		}
		else {
			cbTypeSize->ItemIndex = -1;
		}
	}
	*/
	//queryEtalon->Connection = SqlDBModule->ADOConnectionDB;

	TExtFunction::PrepareChartToTst(SignalChart, 3, 600, 2000);
	SignalChart->Series[0]->Title += " ������";
	SignalChart->Series[1]->Title += " ����������";
	SignalChart->Series[2]->Title += " ���";

	ChangeColor();
	TExtFunction::PrepareChartToTst(EtalonChart, 3, 10, 2000);
	EnableWigits(false);
	SignalChart->Visible = false;
    PanelChartBottom->Visible = true;
}

// ------------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject * Sender) {
	if (threadWork) {
		threadWork->Terminate();
		threadWork->WaitFor();
		//threadWork->TestExitLoop();
		threadWork = NULL;
	}

	if (lCardData) {
		delete lCardData;
		lCardData = NULL;
	}

	if (SLD) {
		SLD->oSENSORON->Set(false);
		SLD->oSENSLOWPOW->Set(false);
		delete SLD;
        SLD = NULL;
	}

if (l�ard502) {
  	delete l�ard502;
	l�ard502 = NULL;
}
if (gen) {
	delete gen;
	gen =  NULL;
}
	if (TSFreqs) {
		delete TSFreqs;
		TSFreqs = NULL;
	}
}

// ---------------------------------------------------------------------------
void TMainForm::LoadFromFile(UnicodeString FileName) {
	try {
		TLog::LoadTxtChDoubleFile(AnsiString(FileName).c_str(), lCardData, 0,3); //serg
		TSG* solidGroup = new TSG(&mainGlobalSettings, lCardData);
		csg = solidGroup->Get1FrecSG();
		delete solidGroup;
		Redraw();
	}
	catch (Exception *ex) {
		AnsiString err;
		const TVarRec args[] = {FileName,ex->ToString()};
		err.Format("������ �������� ����� \"%s\": %s",args,2);
		TProtocol::ProtocolSave(err);
		TExtFunction::ShowBigModalMessage(err, clRed);
	}
}

// ---------------------------------------------------------------------------
void TMainForm::SaveToFile(UnicodeString FileName) {
	try {
		// ���������� � ����
		int arrSize = lCardData->vecMeasure.size();
		TLog::SaveChTxtDoubleFile(FileName, &(lCardData->vecMeasure[0]), arrSize, 3); //serg
	}
	catch (Exception *ex) {
		AnsiString err;
		const TVarRec args[] = {FileName,ex->ToString()};
		err.Format("������ ���������� ����� \"%s\": %s",args,2);
		TProtocol::ProtocolSave(err);
		TExtFunction::ShowBigModalMessage(err, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuSaveClick(TObject * Sender) {
	int arrS = SignalChart->Series[0]->Count();
	if (arrS > 0)
	{
		if (SaveDialog->Execute())SaveToFile(SaveDialog->FileName);
	}
	else
	{
		AnsiString err = "��� ������ ��� ����������";
		TProtocol::ProtocolSave(err);
		TExtFunction::ShowBigModalMessage(err, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuOpenClick(TObject * Sender) {
	if (OpenDialog->Execute())
		LoadFromFile(OpenDialog->FileName);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::WmDropFiles(TWMDropFiles & Message) {
	//HDROP drop_handle = (HDROP)Message.Drop;
	//wchar_t fName[MAXPATH];
	//int filenum = DragQueryFile(drop_handle, -1, NULL, NULL);
	// for (int i = 0; i < filenum; i++)
	// {
	// DragQueryFile(drop_handle, i, fName, MAXPATH);
	// ReadFile(fName);
	// }
	// DragFinish(drop_handle);
}

// ---------------------------------------------------------------------------------
// ����� ��������������, ��������� ���������� � ��������� ���� -----
void __fastcall TMainForm::ReadFile(AnsiString FileName) {
	// AnsiString str = ExtractFileExt(FileName);
	// if (str == ".sg")
	// MainForm->LoadFromFile(FileName);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::SignalChartClick(TObject * Sender) {
	// SignalChart->SetFocus();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::SignalChartScroll(TObject * Sender) {
	lMinScrollbar->Caption = "" + IntToStr((int) SignalChart->BottomAxis->Minimum);
	lMaxScrollbar->Caption = "" + IntToStr((int) SignalChart->BottomAxis->Maximum);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::scbChartDraggerChange(TObject * Sender) {
	double length = 200;
	for (int i = 0; i < SignalChart->SeriesCount(); ++i) {
		if (length < SignalChart->Series[i]->MaxXValue()) {
			length = SignalChart->Series[i]->MaxXValue();
		}
	}
	double max = SignalChart->BottomAxis->Maximum;
	double min = SignalChart->BottomAxis->Minimum;
	double step = (double)(max - min) / 100.0;
	if (length > 0)
		scbChartDragger->Max = (int)ceil((double)length * 100.0 / (double)(max - min));
	else
		scbChartDragger->Max = (int)ceil((double)100.0 * 100.0 / (double)(max - min));
	// curPos = max/step;
	long change = scbChartDragger->Position - curPos;
	if (change > 0) {
		SignalChart->BottomAxis->Maximum = change * step + max;
		SignalChart->BottomAxis->Minimum = change * step + min;
	}
	else {
		SignalChart->BottomAxis->Minimum = change * step + min;
		SignalChart->BottomAxis->Maximum = change * step + max;
	}

	SignalChart->Refresh();
	curPos = scbChartDragger->Position;
	SignalChartScroll(Sender);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ApplicationEventsMessage(tagMSG & Msg, bool &Handled) {
	if (Msg.message == WM_HOTKEY) { // ��������� ����
		if (Msg.wParam == 0x00E) // ������������� ���
		{
			WinExec("hh ..\\..\\help\\Help.chm", SW_RESTORE);
			Handled = true;
		}
	}
	if (Msg.message == mainGlobalSettings.threadMsg) { // Handled = true;
		switch (Msg.wParam) {
		case ThreadWork::REDRAW: {
				if(NULL == threadWork) break;
				TProtocol::ProtocolSave("���������: ������������");
				csg = threadWork->GetSG();
				Redraw();
				break;
			}
		case ThreadWork::COMPUTE: {
				if(NULL == threadWork) break;
				AnsiString a = "���������: ������ �����, ���: ";
				a += Msg.lParam;
				TProtocol::ProtocolSave(a);
				if (threadWork != NULL)
					threadWork->SetCalc();
				break;
			}
		case ThreadWork::COMPLETE: { {
		        if(NULL == threadWork) break;
					AnsiString a = "���������: ���������� �����, ���: ";
					a += Msg.lParam;
					TProtocol::ProtocolSave(a);
				} threadWork->Terminate();
				SLD->LatchesTerminate();
				SLD->SetAlarm(false);
				threadWork->WaitFor();
				//threadWork->TestExitLoop();
				delete threadWork;
				threadWork = NULL;
				SetAbleButtons(true);

				if (Msg.lParam == 1 && !SLD->iCC->WasConst(false, 100)) {
					// ���� ���� ��������� ������ ��������� - ��������
					Start();
				}
				else {
					if (SLD->iCC->WasConst(false, 100))
						TProtocol::ProtocolSave("������� ���� ����������");
					// ���� ���� ��������� ������ � ������� - ���������
					TProtocol::ProtocolSave("_return_code==false");
					// bWork->Caption = "������";
					// bCancelWork->Enabled = false;
				}
				break;
			}
		case ThreadWork::UPDATE_STATUS: {
				if (threadWork != NULL)
					UpdateStatus(threadWork->GetStext1(), threadWork->GetStext2());
				break;
			}
		}
	}
}

// ---------------------------------------------------------------------------
void TMainForm::UpdateStatus(AnsiString _text1, AnsiString _text2) {
	StatusBar->Panels->Items[0]->Text = _text1;
	StatusBar->Panels->Items[1]->Text = _text2;
	StatusBar->Font->Size = 20;
	// StatusBar->Font->Color=clRed;
	StatusBar->Refresh();
}

// ---------------------------------------------------------------------------
void TMainForm::ClearCharts(void) {
	 int count = SignalChart->SeriesCount();
	 for(int i = 0; i < count; ++i)
	 {
		  SignalChart->Series[i]->Clear();
	 }
	 PanelSG->Caption = "����";
	 PanelSG->Color = clBtnFace;
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::bStartClick(TObject * Sender) {
	mainGlobalSettings.isWork=true;
	if (threadWork == NULL)
		Start();
	else
		ReStart();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::bCancelClick(TObject * Sender) {
	mainGlobalSettings.isWork=false;
	Stop();
}

// ---------------------------------------------------------------------------
void TMainForm::Start() {
	try
	{
#ifndef _LCARDEMUL
	  if(!l�ard502 || !l�ard502->handle)
	  {
		 TExtFunction::ShowBigModalMessage("����� LCard502 �� ������� !", clRed);
		 return;
	  }
#endif
		// �� ������ ������ ������� ������� ��� ���������
		SLD->oSENSORON->Set(false);
		if (SLD->iCC->Get())// ��������� ���� ����������
		{
			SetAbleButtons(false);
			if (threadWork != NULL)
			{
				TProtocol::ProtocolSave("TMainForm::Start: ������ ��� ��������");
				return;
			}
			inWork = true;
			// ������� ����������
			SLD->oSENSLOWPOW->Set(true);
			//SLD->oSENSORON->Set(true);//��� 12�
			if (threadWork != NULL)
			{
				threadWork->Terminate();
				threadWork->WaitFor();
				//threadWork->TestExitLoop();
				ThreadWork *x = threadWork;
				threadWork = NULL;
				delete x;
			}
#ifndef _LCARDEMUL
			if (!gen)
			{
			   gen = new TGSPF052();
			   if(NULL == gen->hDLL)
				{
					delete gen;
					gen = NULL;
					SetAbleButtons(true);
					inWork = false;
					SLD->oSENSORON->Set(false);
					SLD->LatchesTerminate();
					TProtocol::ProtocolSave("������: �� ������� ��������� ���������");
					TExtFunction::ShowBigModalMessage("������: �� ������� ��������� ���������", clBlue);
					return;
				}
			}
#endif
			TSFrequencies TSFreqs = TSFrequencies(mainGlobalSettings.indexCurrentTypeSize);
			if (TSFreqs.Frequency.size() <= 0)
			{
				TProtocol::ProtocolSave("������: ������ ��� ����� ����������� ��� � ���� ������");
				TExtFunction::ShowBigModalMessage("������: ������ ��� ����� ����������� ��� � ���� ������", clBlue);
				return;
			}
			int f = TSFreqs.Frequency[0];
			double a = TSFreqs.Amplitude[0];
			if(gen)gen->FormSignal(f, a);
            TProtocol::ProtocolSave("��������� ������");
			threadWork = new ThreadWork(true, lCardData, &mainGlobalSettings, gen);
			SLD->SetAlarm(true);
		}
		else {
			AnsiString msg = "��� ������� ����� ����������!!! \n";
			TExtFunction::ShowBigModalMessage(msg, clRed);
			SetAbleButtons(true);
			return;
		}

	}
	catch (Exception *ex) {
		AnsiString errStr = "TMainForm::Start:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void TMainForm::ReStart() {
	// ������������ ������ ��� �������� ��� ���������, ������� � ��� ���
	if (threadWork == NULL) {
		//TProtocol::ProtocolSave("TMainForm::ReStart: ������ �� ��������");
		return;
	}
	threadWork->SetCalc();
}

// ---------------------------------------------------------------------------
void TMainForm::Stop() {
	if (threadWork != NULL)
	{
		// ������ �����
		threadWork->Terminate();
		threadWork->WaitFor();
		//threadWork->TestExitLoop();
		ThreadWork *x = threadWork;
		threadWork = NULL;
		Sleep(1000);
		delete x;
	}

	// �������� ���������
  //	if (gen) {
  //		delete gen;
   //		gen = NULL;
   //	}
	// MainMenu->Items->Visible = true;
	// GroupBoxNGr->Visible = true;
	// bStart->Enabled = true;
	SetAbleButtons(true);
	inWork = false;
	SLD->oSENSORON->Set(false);
	SLD->LatchesTerminate();
	UpdateStatus("�������� ������", "������ \"������\"");
	TProtocol::ProtocolSave("User: �������� ������ ������");
}

// ---------------------------------------------------------------------------
void TMainForm::Redraw() {
	// ������� ��� ���������� ������
	// int MeasCount = lCardData->vecMeasuresData.size();
	// TExtFunction::PrepareFastLineChart
	// (MeasCount * l�ard502->countLogCh, 2500, SignalChart);
	// for (int k = 0; k < MeasCount; k++) {
	// for (int i = 0; i < l�ard502->countLogCh; i++) {
	// int sz =
	// lCardData->vecMeasuresData[k].vecSensorsData[0].size();
	// double* arr = new double[sz];
	// for (int j = 0; j < sz; j++) {
	// arr[j] =
	// lCardData->vecMeasuresData[k].vecSensorsData
	// [i][j] - k * 10.0; // ������ �����
	// }
	// SignalChart->Series[k * l�ard502->countLogCh + i]
	// ->AddArray(arr, sz);
	// }
	// }

	// ��������� ����� ��������
	int chCount = 3;
	if(lCardData->vecMeasuresData.size()>0)
		chCount = lCardData->vecMeasuresData[0].vecSensorsData.size();
	TExtFunction::PrepareChartToTst(SignalChart, chCount, 0, 0);
	SignalChart->Title->Text->Clear();
	SignalChart->Title->Text->Add("������� ��������");

	ChangeColor();
	SignalChart->Series[0]->Title += " ������";
	SignalChart->Series[1]->Title += " ����������";
	SignalChart->Series[2]->Title += " ���";
	// ������� �� ����� �������
	int arrSize;
	for (int i = 0; i < chCount; i++) {
		arrSize = 0;
		if(lCardData->vecMeasuresData.size()>0)
			arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
		if(arrSize>0)
		{
			double* tmpArray = new double[arrSize];
			for (int j = 0; j < arrSize; j++) {
				tmpArray[j] = lCardData->vecMeasuresData[0].vecSensorsData[i][j];
			}
			SignalChart->Series[i]->AddArray(tmpArray, arrSize - 1);
		}
	}
	// ��������� �������� �� �������
	vector<int>Thresholds;
	int res;
	// ��������� ������ �� ����������  �����������
	TADOQuery *queryEtalon = new TADOQuery(NULL);
	queryEtalon->Connection = SqlDBModule->ADOConnectionDB;
	AnsiString strSQL = "select threshold_value from TypeSizeThresholds where TS_id=:pTS_id order by threshold_value";
	queryEtalon->SQL->Text = strSQL;
	queryEtalon->Parameters->ParamByName("pTS_id")->Value = mainGlobalSettings.indexCurrentTypeSize;
	queryEtalon->Open();
	queryEtalon->First();
	int tst = queryEtalon->RecordCount;
	if (tst == 0)
	{
		if(threadWork && threadWork->Started)
		{
			TProtocol::ProtocolSave("�� ������� �������� ������� ��� ������ "+cbEtalonGroup->Text+"! ��������� ������� ��������.");
			return;
		}
		else
		{
			MessageDlg("�� ������� �������� �������! ��������� ������� ��������.", mtWarning, TMsgDlgButtons() << mbOK, NULL);
			TProtocol::ProtocolSave("�� ������� �������� ������� ��� ������ "+cbEtalonGroup->Text+"! ��������� ������� ��������.");
			return;
		}
	}
	while (!queryEtalon->Eof)
	{
		res = queryEtalon->FieldByName("threshold_value")->AsInteger;
		Thresholds.push_back(res);
		queryEtalon->Next();
	}
	queryEtalon->Close();
	delete queryEtalon;
	// ��������� ���� �������
	vector<double> BarkValues;
	if(lCardData->vecMeasuresData.size()>0 && lCardData->vecMeasuresData[0].vecSensorsData[0].size()>0)
	{
		BarkValues = lCardData->GetBarkValues(Thresholds);
	}
	else
	{
		for (unsigned int i = 0; i < Thresholds.size(); i++)
		{
			double x =0.0;
			BarkValues.push_back(x);
		}
	}
	// ������� ����������� �����
	TFastLineSeries* series = new TFastLineSeries(SignalChart);
	// series->ColorEachPoint = true;
	series->Marks->Visible = false;
	series->LinePen->Width = 3;
	series->Color = clBlack;
	series->ShowInLegend = false;
	SignalChart->AddSeries(series);
	double PeriodProc = arrSize / 300.0;
	for (unsigned int i = 0; i < Thresholds.size(); i++) {
		res = (int)(Thresholds[i] * PeriodProc);
		SignalChart->Series[SignalChart->SeriesCount() - 1]->AddXY(res, BarkValues[i], "", clBlack);
	}
	// //������ ����� ��� ��������
	// TColor colorSer[7];
	// colorSer[0] = clBlack;
	// colorSer[1] = clBlue;
	// colorSer[2] = clRed;
	// colorSer[3] = clGreen;
	// colorSer[4] = clFuchsia;
	// colorSer[5] = clYellow;
	// colorSer[6] = clWhite;
	// ������ � ��
	PanelSG->Width = 180;
	PanelSG->Caption = csg.group; // + " " + IntToStr((int)(csg.probability * 100)) + "%";
	PanelSG->Width *= 2;
	// if(csg.group_id < 7)
	PanelSG->Color = csg.color; // colorSer[csg.group_id]; //todo ���������!
	PanelSG->Font->Color = (TColor)(16777215 - (int)csg.color);
	// else PanelSG->Color = clLime;
	// ������� �� ����� �������
	if(SignalChart->Visible)
	{
	// �������� ���� ������������������� ������� ��������
	EtalonDatas EDatas = EtalonDatas(mainGlobalSettings.indexCurrentTypeSize);
	TExtFunction::PrepareChartToTst(EtalonChart, EDatas.Etalons.size(), 0, 0);
	// ������� �� ����� �������
	if(EDatas.Etalons.size()>0)
	{
		arrSize = EDatas.Etalons[0].BarkValues.size();
		for (int i = 0; i < EDatas.Etalons.size(); i++)
		{
		// arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
			double* tmpArray = new double[arrSize];
			for (int j = 0; j < arrSize; j++)
			{
				tmpArray[j] = EDatas.Etalons[i].BarkValues[j];
			}
		// int sg_id = EDatas.Etalons[i].SG_id;
		// if(sg_id < 0)
		// sg_id = 0;
		EtalonChart->Series[i]->Title = EDatas.Etalons[i].SG_name;
		// if(sg_id < 7)
		EtalonChart->Series[i]->Color = EDatas.Etalons[i].Color; // colorSer[sg_id];
		// else EtalonChart->Series[i]->Color = clLime;
		EtalonChart->Series[i]->AddArray(tmpArray, arrSize - 1);
		}
	}
	// �� ���� ��������� - ��� � ��� �� ���� ������ ��� ����
	// series = new TFastLineSeries(EtalonChart);
	////	series->ColorEachPoint = true;
	// series->Marks->Visible = false;
	// series->LinePen->Width = 3;
	// series->Color = clBlack;
	// series->ShowInLegend = true;
	// EtalonChart->AddSeries(series);
	}
	else
		TExtFunction::PrepareChartToTst(EtalonChart, 1, 0, 0);
	EtalonChart->Series[EtalonChart->SeriesCount() - 1]->ShowInLegend = true;
	EtalonChart->Series[EtalonChart->SeriesCount() - 1]->Title = "����� ������";
	// EtalonChart->Series[SignalChart->SeriesCount()-1]->LinePen->Width = 3;
	for (int i = 0; i < Thresholds.size(); i++)
	{
		EtalonChart->Series[EtalonChart->SeriesCount() - 1]->AddY(BarkValues[i], "", clBlack);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuColorSettClick(TObject * Sender) {
	FormColor = new TFormColor(this);
	FormColor->Show();
	// delete FormColor;
	// FormColor->ShowModal();
	// ChangeColor();
}

// ---------------------------------------------------------------------------
void TMainForm::ChangeColor() {
	// ����� �����
	SignalChart->Series[0]->Color = clBlue; // ����������
	SignalChart->Series[1]->Color = clRed; // ����������
	SignalChart->Series[2]->Color = clGreen; // ���
	SignalChart->Series[3]->Color = clBlack; // DotsMeasure2
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuSettingsClick(TObject * Sender) {
	ADCSettForm = new TADCSettForm(this, l�ard502);
	ADCSettForm->ShowModal();
	delete ADCSettForm;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuTypeSizeClick(TObject * Sender) {
	// SettingsForm->ShowModal();
	fmTypeSizes = new TfmTypeSizes(this);
	fmTypeSizes->ShowModal();
	delete fmTypeSizes;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuSGSettClick(TObject * Sender) {

	SGSettForm = new TSGSettForm(this, &mainGlobalSettings);
	SGSettForm->ShowModal();
	SGSettForm->Close();
	delete SGSettForm;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::PanelSQClick(TObject * Sender) {
	// PanelTop->FullRepaint();
	// ToolBarTop->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::PanelONClick(TObject * Sender) {
	// PanelTop->FullRepaint();
	// ToolBarTop->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::mnuCheckGenClick(TObject * Sender) {
	/*
	if(!l�ard502 || !l�ard502->handle)
	{
		 TExtFunction::ShowBigModalMessage("����� LCard502 �� ������� !", clRed);
		 return;
	}
	*/
	fmDiagnost = new TfmDiagnost(this, &mainGlobalSettings, l�ard502, lCardData);
	// fmDiagnost->Show();
	fmDiagnost->ShowModal();
	fmDiagnost->Close();
	fmDiagnost = NULL;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::mnuCheck1730Click(TObject * Sender) {
	/*
	if(!l�ard502 || !l�ard502->handle)
	{
		 TExtFunction::ShowBigModalMessage("����� LCard502 �� ������� !", clRed);
		 return;
	}
	*/
	FSignalsState = new TFSignalsState(this, &mainGlobalSettings, SLD);
	FSignalsState->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::menuEtalonsClick(TObject *Sender) {
	fmEditEtalon = new TfmEditEtalon(this, &mainGlobalSettings, lCardData);
	fmEditEtalon->ShowModal();
	fmEditEtalon = NULL;
	//TFREtalons* frm = new TFREtalons(this);
	//frm->Show();
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::CreateEtalon(int _tsId,int _sgId, TLCardData *_lcd)
{
	TADOQuery *qry = NULL;
	TADOCommand *cmd = NULL;
	try	{
	try	{
		qry = new TADOQuery(NULL);
		qry->Connection = SqlDBModule->ADOConnectionDB;
		cmd = new TADOCommand(NULL);
		cmd->Connection = SqlDBModule->ADOConnectionDB;

		AnsiString tsName = SqlDBModule->GetStrFromSql("select TSName as F1 from TypeSizes where rec_id="+IntToStr(_tsId));
		AnsiString sgName = SqlDBModule->GetStrFromSql("select SGName as F1 from SolidGroups where rec_id="+IntToStr(_sgId));
		int freq = SqlDBModule->GetIntFromSql("select max(frequency_value) as F1 from TypeSizeFrequencies where ts_id="+IntToStr(_tsId));

		AnsiString fileName = mainGlobalSettings.SaveEtalonPath+"\\";
		fileName += tsName;
		fileName += "_SG_";
		fileName += sgName;
		fileName += FormatDateTime("_yyyymmddhhmmss", Now());
		fileName += ".csv";

		SaveDialog->InitialDir = mainGlobalSettings.SaveEtalonPath;
		SaveDialog->FileName = fileName;
		if(!SaveDialog->Execute(this->Handle))
			return;
		else
			fileName = SaveDialog->FileName;

		//����� ���� �� ��������� ��� ���� �������� ������� ��� ����� �����������
		//���� ��� �� ������ ���������
		int treshCount = SqlDBModule->GetIntFromSql("select count(*) as F1 from TypeSizeThresholds where TS_id="+IntToStr(_tsId));
		if(treshCount == 0) {
			if(MessageDlg(UnicodeString("�� ������� �������� ��� ������ ")+tsName+". ���������?", mtConfirmation , TMsgDlgButtons() << mbOK<<mbCancel, NULL) == mbCancel)
				return;
			else{
				SGSettForm = new TSGSettForm(this, &mainGlobalSettings);
				SGSettForm->ShowModal();
				//SGSettForm->Close();
				delete SGSettForm;
			}
		}

		// ���������� �������� � ����
		UnicodeString strSQL = "";
		strSQL = "INSERT INTO Etalons(ts_id,fenable,frequency,address_file,sg_id) VALUES( ";
		strSQL += IntToStr(_tsId);
		strSQL += ",";
		strSQL += IntToStr(1);
		strSQL += ",";
		strSQL += IntToStr(freq);
		strSQL += ",'";
		strSQL += fileName;
		strSQL += "',";
		strSQL += IntToStr(_sgId);
		strSQL += ");\n";
		strSQL += "SELECT @@IDENTITY AS 'LAST_ID';";

		qry->Close();
		qry->SQL->Text = strSQL;
		qry->Open();
		int etId = qry->FieldByName("LAST_ID")->AsInteger;
		qry->Close();

		strSQL = "INSERT INTO EtalonValues Select ";
		strSQL += IntToStr(etId);
		strSQL +=",threshold_value, 123 from TypeSizeThresholds where TS_id=";
		strSQL += IntToStr(mainGlobalSettings.indexCurrentTypeSize);
		strSQL += " order by threshold_value";
		qry->SQL->Text = strSQL;
		qry->ExecSQL();
		qry->Close();
		// ��������� �������� �� �������
		vector<int>Thresholds;
		// ��������� ������ �� ����������  �����������
		strSQL = "select threshold_value from TypeSizeThresholds where TS_id=:pTS_id order by threshold_value";
		qry->SQL->Text = strSQL;
		qry->Parameters->ParamByName("pTS_id")->Value = _tsId;
		qry->Open();
		qry->First();
		while (!qry->Eof) {
			int res = qry->FieldByName("threshold_value")->AsInteger;
				Thresholds.push_back(res);
				qry->Next();
		}
		qry->Close();

		strSQL = "SELECT rec_id as vrec_id, etalon_id,thres_val,barkgausen_val FROM EtalonValues \
				  where etalon_id = :petalon_id order by thres_val";
		qry->SQL->Text = strSQL;
		qry->Parameters->ParamByName("petalon_id")->Value = etId;
			// ��������� ���� �������
		vector<double>BarkValues;
		BarkValues = _lcd->GetBarkValues(Thresholds);
		// ������� � ����
		qry->Open();
		qry->First();
		int ii = 0;
		UnicodeString strCmdSql;
		for (unsigned int i = 0; i < Thresholds.size(); i++) {
			strCmdSql =	"UPDATE EtalonValues SET barkgausen_val = :pbarkgausen_val";
			strCmdSql += " WHERE rec_id=" + IntToStr(qry->FieldByName("vrec_id")->AsInteger);
			cmd->CommandText = strCmdSql;
			cmd->Parameters->ParamByName("pbarkgausen_val")->Value = BarkValues[i];
			cmd->Execute();
			qry->Next();
		}
		qry->Close();
		int freqNum = _lcd->getFreqNum();
		int arrSize = _lcd->vecMeasuresData[freqNum].vecSensorsData[0].size() * 3;
		vector<double>forSave;
		for (unsigned int i = 0; i < _lcd->vecMeasuresData[0].vecSensorsData[0].size(); i++) {
			forSave.push_back(_lcd->vecMeasuresData[freqNum].vecSensorsData[0][i]);
			forSave.push_back(_lcd->vecMeasuresData[freqNum].vecSensorsData[1][i]);
			forSave.push_back(_lcd->vecMeasuresData[freqNum].vecSensorsData[2][i]);
		}
		TLog::SaveChTxtDoubleFile(fileName, &(forSave[0]), arrSize, 3);
		MessageDlg("������� ��������", mtConfirmation, TMsgDlgButtons() << mbOK, NULL);
		}
		catch (Exception *ex) {
			AnsiString errStr = "TMainForm::bbtCreateEtalonClick:" + ex->Message;
			TProtocol::ProtocolSave(errStr);
			TExtFunction::ShowBigModalMessage(errStr, clRed);
		}
	}
	__finally {
		delete qry;
		delete cmd;
	}
}

void __fastcall TMainForm::bbtCreateEtalonClick(TObject *Sender) {
	if (cbEtalonGroup->ItemIndex == -1) {
		MessageDlg("�������� ������ ��������", mtError,
			TMsgDlgButtons() << mbOK, NULL);
		return;
	}
	if (cbxSG->ItemIndex == -1) {
		MessageDlg("�������� ������ ���������", mtError,
			TMsgDlgButtons() << mbOK, NULL);
		return;
	}
	int arrS = SignalChart->Series[0]->Count();
	int freqN = lCardData->getFreqNum();
	if (arrS <= 0) {
		MessageDlg("�������� ������!!!", mtError,
		TMsgDlgButtons() << mbOK, NULL);
		return;
	}
	int tsId = (int)cbEtalonGroup->Items->Objects[cbEtalonGroup->ItemIndex];
	int sgId = (int)cbxSG->Items->Objects[cbxSG->ItemIndex];
	CreateEtalon(tsId, sgId, lCardData);
}


void __fastcall TMainForm::FormResize(TObject *Sender) {
	// Panel1->Height=Panel2->Top-Panel1->Top;
	// SignalChart->Height=Panel1->Height-SignalChart->MarginBottom-SignalChart->MarginTop;
}

// ---------------------------------------------------------------------------
// ��������� ������
void TMainForm::SetAbleButtons(bool _enable) {
	MainMenu->Items->Find("���������")->Enabled = _enable;
	MainMenu->Items->Find("�����������")->Enabled = _enable;
	MainMenu->Items->Find("���������")->Enabled = _enable;
	MainMenu->Items->Find("������")->Enabled = _enable;
 //	GroupBoxNGr->Visible = _enable;
	bStart->Enabled = _enable;
	cbEtalonGroup->Enabled = _enable;
	cbxSG->Enabled = _enable;
    bbtCreateEtalon->Enabled = _enable;
	//cbSGGost->Enabled = _enable;
}

void __fastcall TMainForm::SplitterMidMoved(TObject *Sender) {
	PanelChartTop->Height = SplitterMid->Top;
	PanelChartBottom->Top = SplitterMid->Top + SplitterMid->Height;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject *Sender) {

	// if(lastError<0){
	// this->Close();
	// return;
	// }else{
	// //
	// }
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::SplitterResMoved(TObject *Sender) {
	// PanelSG->Width=SplitterRes->Left+SplitterRes->Width;
	PanelSG->Left = SplitterRes->Left + SplitterRes->Width;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::menuExtSetClick(TObject *Sender)
{
	fmExtSettings=new TfmExtSettings(this,&mainGlobalSettings);
	fmExtSettings->ShowModal();
	delete fmExtSettings;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 	if (mainGlobalSettings.isWork) {
		lastMsg = "������� ������� ������!!!";
		TExtFunction::ShowBigModalMessage(lastMsg, clRed);
        CanClose=false;
		return;
	}
	else {
		if (threadWork != NULL) {
				threadWork->Terminate();
				threadWork->WaitFor();
				//threadWork->TestExitLoop();
				ThreadWork *x = threadWork;
				threadWork = NULL;
				delete x;
		}
		if(NULL != gen )
		{
			gen->Stop();
			TGSPF052* x = gen;
			gen = NULL;
			Sleep(1000);
			delete x;
			Sleep(1000);
		}
	}
}
void TMainForm::EnableWigits(bool b)
{
	GroupBoxNGr->Visible = b;
	//PanelChartBottom->Visible = b;
	SignalChart->Visible = b;
	menuSettings->Visible = b;
	menuSGSett->Visible = b;
	menuColorSett->Visible = b;
	menuTypeSize->Visible = b;
	menuEtalons->Visible = b;
	menuExtSet->Visible = b;
	menuGosts->Visible = b;
	btnAddGroupEtalons->Visible = b;
    menuEgroupsEdit->Visible = b;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N1Click(TObject *Sender)
{
	  if(!GroupBoxNGr->Visible)
	  {
		TPasswordForm *f = new TPasswordForm(this);
		f->ShowModal();
		if(f->result)
		{
		   EnableWigits(true);
		   SignalChart->Visible = true;
		   PanelChartBottom->Visible = true;
		}
	  }
	  else
	  {
		   EnableWigits(false);
		   SignalChart->Visible = false;
		   PanelChartBottom->Visible = true;
	  }
	  Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnExitClick(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mnAbautClick(TObject *Sender)
{
   TAboutBox *a = new TAboutBox((TComponent *)Sender);
   a->ShowModal();
   a->Free();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuGostsClick(TObject *Sender)
{
	TFRSprGost *spr = new TFRSprGost(this);
	spr->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
		Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbEtalonGroupChange(TObject *Sender)
{
	TComboBox *cb = (TComboBox*)Sender;
	int ind = cb->ItemIndex;
	if(ind < 0)return;
	mainGlobalSettings.indexCurrentTypeSize = (int)cbEtalonGroup->Items->Objects[ind];
	SqlDBModule->UpdIntSql("SettingsGlobal","indexCurrentTypeSize",mainGlobalSettings.indexCurrentTypeSize,NULL);
	//�53366-73-N80Q-NU-UNG-F0-3� (����,  �������, ������ N80Q, ��� ������, ��������, ��� ����� F0, ��������� �������� 3)
	AnsiString groupName = cb->Text;
	TStringList *lst = new TStringList();
	lst->Delimiter = '-';
	lst->DelimitedText = groupName;
	int gostId = SqlDBModule->GetIntFromSql(
		   "select rec_id as F1 from GOST where ShortName='"+cbEtalonGroup->Text.SubString(0,5)+"'");
	//��������� ������ ����� ��������� - �� ������� �� ����-�
	SqlDBModule->FillComboBoxFromSql("select rec_id, SGName as F1 from SolidGroups where Gost_id=" + IntToStr(gostId), cbxSG);
	//������ �� �������
	cbxSG->ItemIndex = -1;
	//�� ���� ���� ��������� ��� �� �����
    Redraw();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::btnAddGroupEtalonsClick(TObject *Sender)
{
	TEgroupEditFrm *frm = new TEgroupEditFrm(cbEtalonGroup->Text);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::menuEgroupsEditClick(TObject *Sender)
{
	TFRGroups *frm = new TFRGroups(this);
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbxSGChange(TObject *Sender)
{
	int ind = cbxSG->ItemIndex;
	if(ind>=0)
	{
		int sg = (int)cbxSG->Items->Objects[cbxSG->ItemIndex];
		mainGlobalSettings.currSG = sg;
		//SqlDBModule->UpdIntSql("SettingsGlobal", "indexCurrentSolidGroup", mainGlobalSettings.currSG, NULL);
		SqlDBModule->SavePar("indexCurrentSolidGroup",IntToStr(mainGlobalSettings.currSG));
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbEtalonGroupKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	TComboBox *cb = (TComboBox*)Sender;
	if(Key == VK_RETURN)
	{
		for(int i=0; i < cb->Items->Count; i++)
		if(cb->Text==cb->Items->Strings[i])
		{
			Key = 0;
			return;
		}
		//cb->Items->Add(cb->Text);
		MessageDlg("����� ������ �� �������!!!", mtError, TMsgDlgButtons() << mbOK, NULL);
        Key = 0;
		return;
	}
/*
	if(Key == VK_DELETE)
	{
		for(int i=0; i < cb->Items->Count; i++)
		if(cb->Text==cb->Items->Strings[i])
		{
			cb->Items->Delete(i);
			return;
		}
	}
 */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::miCheckMuftaClick(TObject *Sender)
{
	TFRMMuftaLevel *frm = new TFRMMuftaLevel(this);
	frm->ShowModal();
    delete frm;
}
//---------------------------------------------------------------------------

