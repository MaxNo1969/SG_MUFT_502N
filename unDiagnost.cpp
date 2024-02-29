// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unDiagnost.h"
#include "TGSPF052.h"
#include "unTExtFunction.h"
#include "TProtocol.h"
// #include "unSQLDbModule.h"
#include "unTUtils.h"
#include "TSG.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "Series"
#pragma resource "*.dfm"
TfmDiagnost *fmDiagnost;

// ---------------------------------------------------------------------------
__fastcall TfmDiagnost::TfmDiagnost(TComponent* Owner,
	TGlobalSettings* _pGlobalSettings, TLCard502 *_LСard502,
	TLCardData *_lCardData) : TForm(Owner) {
	pGlobalSettings = _pGlobalSettings;
	diagLСard502 = _LСard502;
	lCardData = _lCardData;
	err = -101;
	chCount = diagLСard502->countLogCh;
	genTime = 1; // переведем в секунды
	chartLength = diagLСard502->frequencyPerChannel_Hz * genTime;
	// colorSer={clBlue,clRed,clGreen,clFuchsia,clYellow,clWhite,clBlack};
	colorSer[0] = clBlue;
	colorSer[1] = clRed;
	colorSer[2] = clGreen;
	colorSer[3] = clFuchsia;
	colorSer[4] = clYellow;
	colorSer[5] = clWhite;
	colorSer[6] = clBlack;
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::btnStartGenClick(TObject *Sender) {
	AnsiString msg = "";
	TExtFunction::PrepareChartToTst(ChartGPSF052, chCount, 0, 0);
	try {
		if (SLD->iCC->Get()) // проверяем цепи управления
		{
			// блокируем элементы управления
			BlockControl(true);
			SLD->oSENSLOWPOW->Set(true); // включим слаботочку
			// TODO проверка наличия муфты
			// здесь на разовом сборе пожалуй и не надо
			// ---
			// gen = new TGSPF052(dGlobalSettings,err);
			TSG* solidGroup = new TSG(pGlobalSettings, lCardData);
			Sleep(500); // задержка на поправку муфты
			DWORD LastTime = GetTickCount();
			// включаем питание датчика
			SLD->oSENSORON->Set(true);
			for (int i = 0; i < chCount; i++) {
				ChartGPSF052->Series[i]->Color = colorSer[i];
			}
			// btnStopGen->Enabled = true;
			// Включаем ГСПФ
			//gen->SetSampleFreq(StrToInt(lbeFrecDiscrGSPF052->Text));
			int frec = StrToInt(lbeFrecSignalGSPF052->Text);
			float volt = StrToFloat(lbeVoltageGSPF052->Text);
			gen->FormSignal(frec, volt);
			gen->Start();
			Sleep(500);
			// чтение ЛКард
			while (true) {
				if (solidGroup->Exec(0) == 2) {
					break;
				}
			}
			// Сбрасываем состояние ГП и останавливаем ГСПФ
			solidGroup->ResetState();
			gen->Stop();

			// выключаем питание датчика
			SLD->oSENSORON->Set(false);
			// SLD->oSENSLOWPOW->Set(false);
			// Выводим на экран графики
			// lCardData->ReCalcMeasuresToChannels();
			int arrSize;
			//serg
			arrSize = lCardData->vecMeasuresData[0].vecSensorsData[0].size();
			if (arrSize==0) {
			  MessageDlg("Нет данных!", mtError, TMsgDlgButtons() << mbOK, NULL);
			  return;
			}else{
				//
			}
			for (int i = 0; i < chCount; i++) {
				arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
				double* tmpArray = new double[arrSize];
				for (int j = 0; j < arrSize; j++) {
					tmpArray[j] =
						lCardData->vecMeasuresData[0].vecSensorsData[i][j];
				}
				ChartGPSF052->Series[i]->AddArray(tmpArray, arrSize - 1);
			}
			// посчитаем значения на порогах
			vector<int>Thresholds;
			int res;
			// загружаем пороги по выбранному  типоразмеру
			queryEtalon->Close();
			AnsiString strSQL = "select threshold_value from TypeSizeThresholds where TS_id=:pTS_id order by threshold_value";
			queryEtalon->SQL->Text = strSQL;
			queryEtalon->Parameters->ParamByName("pTS_id")->Value = pGlobalSettings->indexCurrentTypeSize;
			queryEtalon->Open();
			queryEtalon->First();
			int tst=queryEtalon->RecordCount;
			while (!queryEtalon->Eof) {
				res = queryEtalon->FieldByName("threshold_value")->AsInteger;
				Thresholds.push_back(res);
				queryEtalon->Next();
			}
			queryEtalon->Close();
			// посчитали знач порогов
			vector<double> BarkValues;
			BarkValues = lCardData->GetBarkValues(Thresholds);
			//покажем контрольные точки
			TFastLineSeries* series = new TFastLineSeries(ChartGPSF052);
			series->ColorEachPoint = true;
			series->Marks->Visible = false;
			series->LinePen->Width = 3;
			series->Color = clBlack;
			series->ShowInLegend = false;
			ChartGPSF052->AddSeries(series);
			double PeriodProc = arrSize / 300.0;
			for (int i = 0; i < Thresholds.size(); i++) {
				ChartGPSF052->Series[ChartGPSF052->SeriesCount()-1]->AddXY(Thresholds[i]*PeriodProc,BarkValues[i], "", clBlack);
			}
			//рассчитываем ГП
			int err = 0;
			csg = solidGroup->Get1FrecSG();
//			csg.group = SqlDBModule->GetStrFieldSQL("SolidGroups","SGName"
//				,"rec_id="+IntToStr(csg.group_id),"X",err);
//			csg.color = (TColor)SqlDBModule->GetIntFieldSQL("SolidGroups","Color"
//				,"rec_id="+IntToStr(csg.group_id),65535,err);    //по умолчанию желтый
            PanelSG->Width=180;
			PanelSG->Caption = csg.group;//+" "+IntToStr((int)(csg.probability*100))+"%";
			PanelSG->Width*=2;
            //PanelChartTop->
			PanelSG->Color = csg.color;
			PanelSG->Font->Color = 16777215 - (int)csg.color;
			// ChartGPSF052->Series[chCount]->AddArray(thDiag->vecMeasure[chCount],thDiag->countMeasure-1);
//			// Сохранение в файл
//			fileName = "";
//			//fileName = "..\\..\\SavedResult\\";
			//fileName = ExtractFilePath(Application->ExeName);
			//fileName+="\\SavedResult\\";
//			fileName += FormatDateTime("yyyy_mm_dd_hh_mm_ss_", Now());
//			fileName += StrToInt(lbeFrecSignalGSPF052->Text);
//			fileName += "_";
//			fileName += IntToStr(pGlobalSettings->indexCurrentTypeSize);
//			fileName += "_SG_";
//			fileName += csg.group;
//			fileName += "_FHZ.csv";
//			TLog::Save3TxtVectDoubleFile(ExtractFilePath(Application->ExeName) +
//				fileName, lCardData->vecMeasuresData[0].vecSensorsData[0],
//				lCardData->vecMeasuresData[0].vecSensorsData[1],
//				lCardData->vecMeasuresData[0].vecSensorsData[2], arrSize);
			// s +="0";
			// TLog::Save123TxtVectDoubleFile(s, lCardData->vecMeasure);
			// Разблокируем элементы управления
			BlockControl(false);

		}
		else {
			msg = "Нет сигнала цепей управления!!! \n";
			TExtFunction::ShowBigModalMessage(msg, clRed);
			return;
		}
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmDiagnost::btnStartGenClick:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::btnStopGenClick(TObject *Sender) {
	try {
		if (thDiag) {
			// надо чарт отрисовать, пока поток не прибили
			for (int i = 0; i < chCount; i++) {
				ChartGPSF052->Series[i]->AddArray(thDiag->vecMeasure[i],
					thDiag->countMeasure - 1);
			}
			ChartGPSF052->Series[chCount]->AddArray(thDiag->vecMeasure[chCount],
				thDiag->countMeasure - 1);
			thDiag->stopThread = true;
			thDiag->WaitFor();
			delete thDiag;
			thDiag = NULL;
		}
		else {
			//
		}
		gen->Stop();
		// Закрытие платы
		// Close(onst char* desc=0);
		// gen->CloseCard("ok");
		// delete gen;
		// gen = NULL;
		// выключаем питание датчика
		SLD->oSENSORON->Set(false);
		fileName = "";
		fileName= pGlobalSettings->SaveResultPath;
		fileName += "\\SavedResult\\";
		fileName += FormatDateTime("yyyy_mm_dd_hh_mm_ss_", Now());
		fileName += StrToInt(lbeFrecSignalGSPF052->Text);
		fileName += "_";
		fileName += IntToStr(pGlobalSettings->indexCurrentTypeSize);
		fileName += "_SG_D_";
		fileName += "FHZ.csv";
		int arrSize = lCardData->vecMeasure.size();
		TLog::SaveChTxtDoubleFile(fileName, &(lCardData->vecMeasure[0]), arrSize,3);
		BlockControl(false);
	}
	catch (Exception *ex) {
		AnsiString errStr = "TfmDiagnost::btnStopGenClick:"+ex->Message;
		TProtocol::ProtocolSave(errStr);
		TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::btnStartSerClick(TObject *Sender) {
	AnsiString msg = "";
	TExtFunction::PrepareChartToTst(ChartGPSF052, chCount, 0, 0);
	try {
		if (SLD->iCC->Get()) // проверяем цепи управления
		{
			// блокируем элементы управления
			BlockControl(true);
			SLD->oSENSLOWPOW->Set(true); // включим слаботочку
			// проверка наличия муфты
			timeFlag = false;
			DWORD StartTime = GetTickCount();
			TSG* muftаSearch = new TSG(pGlobalSettings, lCardData);
			while (true) {
				while (true) {
					if (muftаSearch->Exec(0) == 2)
						break;
				}
				muftаSearch->ResetState();
				if (lCardData->CheckMufta(pGlobalSettings->checkMuftaChannel)) {
					break;
				}
				lCardData->ClearSGM();
				if (GetTickCount() - StartTime > 10000) // проверяем минуту
				{
					timeFlag = true;
					break;
				}
			}
			delete muftаSearch;
			lCardData->ClearSGM();
			if (timeFlag) // если превышено время ожидание, то выходим
			{
				// SLD->oSENSLOWPOW->Set(false);
				BlockControl(false);
				return;
			}
			// ---
			// gen = new TGSPF052(dGlobalSettings,err);
			TSG* solidGroup = new TSG(pGlobalSettings, lCardData);
			Sleep(500); // задержка на поправку муфты

			// включаем питание датчика
			SLD->oSENSORON->Set(true);
			// btnStopGen->Enabled = true;

			// Начало цикла
			for (int freqNum = 0; freqNum < TSFreqs->Frequency.size();
			freqNum++) {
				// Включаем ГСПФ
				//gen->SetSampleFreq(StrToInt(lbeFrecDiscrGSPF052->Text));
				gen->FormSignal(TSFreqs->Frequency[freqNum],
					TSFreqs->Amplitude[freqNum]);
				gen->Start();
				Sleep(100);
				// чтение ЛКард
				while (true) {
					if (solidGroup->Exec(freqNum) == 2) {
						break;
					}
				}
				// Сбрасываем состояние ГП и останавливаем ГСПФ
				solidGroup->ResetState();
				gen->Stop();
			}
			// конец цикла
			// выключаем питание датчика
			SLD->oSENSORON->Set(false);
			// SLD->oSENSLOWPOW->Set(false);

			// Выводим на экран графики
			for (int i = 0; i < chCount; i++) {
				ChartGPSF052->Series[i]->Color = colorSer[i];
			}
			int arrSize;
			for (int i = 0; i < chCount; i++) {
				arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
				double* tmpArray = new double[arrSize];
				for (int j = 0; j < arrSize; j++) {
					tmpArray[j] = lCardData->vecMeasuresData[0].vecSensorsData[i][j];
				}
				ChartGPSF052->Series[i]->AddArray(tmpArray, arrSize - 1);
			}
			// Сохранение в файл
			for (int freqNum = 0; freqNum < TSFreqs->Frequency.size();
			freqNum++) {
				AnsiString s = "";
				s=pGlobalSettings->SaveResultPath;
				s += "\\SavedResult\\";
				s += FormatDateTime("yyyy_mm_dd_hh_mm_ss_", Now());
				s += IntToStr(TSFreqs->Frequency[freqNum]);
				s += "_";
				s += IntToStr(pGlobalSettings->indexCurrentTypeSize);
				s += "_SG_D1_";
				s += "FHZ.csv";
				TLog::SaveChTxtDoubleFile(s,&(lCardData->vecMeasure[0]),lCardData->vecMeasure.size(),3);
				// s +="0";
				// TLog::Save123TxtVectDoubleFile(s, lCardData->vecMeasure);
			}
			// Разблокируем элементы управления
			BlockControl(false);

		}
		else {
			AnsiString errStr = "Нет сигнала цепей управления!!!";
			TProtocol::ProtocolSave(errStr);
			TExtFunction::ShowBigModalMessage(errStr, clRed);
			return;
		}
	}
	catch (Exception *ex) {
			AnsiString errStr = "TfmDiagnost::btnStartSerClick:"+ex->Message;
			TProtocol::ProtocolSave(errStr);
			TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::FormClose(TObject *Sender, TCloseAction &Action) {
	if (gen) {
		//gen->CloseCard("ok");
		delete gen;
		gen = NULL;
	}
	else {
		//
	}
	// Action = caFree;
	// Application->OnMessage =NULL;
}

// ---------------------------------------------------------------------------------------------------------
void __fastcall TfmDiagnost::FormCreate(TObject *Sender) {
	TExtFunction::PrepareChartToTst(ChartGPSF052, chCount, chartLength, 2000);
	ChartGPSF052->Series[0]->Title += " Сигнал";
	ChartGPSF052->Series[1]->Title += " Напряжение";
	ChartGPSF052->Series[2]->Title += " Ток";
	int firstFrec = 0;
	// Application->OnMessage = DiagnostEventsMessage;
	// serg-s временно!
//	pGlobalSettings->indexCurrentTypeSize = 1;
	// TypeSizeFrequencies
	TSFreqs = new TSFrequencies(pGlobalSettings->indexCurrentTypeSize);
	// первая запись частот по типоразмеру
	firstFrec = SqlDBModule->GetIntFromSql
		("select min(frequency_value) as F1 from TypeSizeFrequencies where TS_id=" +
		IntToStr(pGlobalSettings->indexCurrentTypeSize));
	lbeFrecSignalGSPF052->Text = IntToStr(firstFrec);
	// SqlDBModule->GetIntFieldSQL("TypeSizeFrequencies",
	// "frequency_value", "TS_id=" +
	// IntToStr(pGlobalSettings->indexCurrentTypeSize) + " and frequency_num=" +
	// IntToStr(firstFrec), 1000, err));
	lbeVoltageGSPF052->Text =
		FloatToStr(SqlDBModule->GetFloatFieldSQL("TypeSizeFrequencies",
		"amplValue", "TS_id=" + IntToStr(pGlobalSettings->indexCurrentTypeSize)
		+ " and frequency_value=" + IntToStr(firstFrec), 5, err));
	lbeFrecDiscrGSPF052->Text = IntToStr(pGlobalSettings->discrFrecGSPF);
	// lbeStepCountGSPF052->Text =IntToStr(SqlDBModule->GetIntFieldSQL("GSPF052Params","count(*) as F1","isUsed=1", 0,err));
	if (!gen) {
		gen = new TGSPF052();//(pGlobalSettings, err);
		if(NULL == gen->hDLL)
			   {
					delete gen;
					gen = NULL;
					SLD->oSENSORON->Set(false);
					SLD->LatchesTerminate();
					return;
			   }
	}
	else {
		//
	}
	//SqlDBModule->FillComboBox("SolidGroups", "SGName", cbxSG);
	SqlDBModule->FillComboBoxFromSql("select rec_id, SGName as F1 from SolidGroups where Gost_id=" + IntToStr(pGlobalSettings->indexCurrentSGGost), cbxSGD);
	cbxSGD->ItemIndex = -1;
	queryEtalon->Connection = SqlDBModule->ADOConnectionDB;
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::ApplicationEventsMessage(tagMSG &Msg,
	bool &Handled) {
	try {
		if (Msg.message == pGlobalSettings->WM_MsgReadyTstData)
		{ // тестовые данные собраны
			// double* Y = new double[thDiag->countMeasure];
			// for (int i = 0; i < thDiag->countMeasure; i++) {
			// Y[i] = thDiag->vecMeasure[0][i];
			// }
			for (int i = 0; i < chCount; i++) {
				ChartGPSF052->Series[i]->AddArray(thDiag->vecMeasure[i],
					thDiag->countMeasure - 1);
			}
			// нулевая линия
			int x = thDiag->vecMeasure.size();
			int y = ChartGPSF052->SeriesCount();
			if (x != y) {
				int z = x + y;
			}
			ChartGPSF052->Series[chCount]->AddArray(thDiag->vecMeasure[chCount],
				thDiag->countMeasure - 1);
			ChartGPSF052->Refresh();
			thDiag->Terminate();
			thDiag->WaitFor();
			delete thDiag;
			thDiag = NULL;
			// ------------------------------
			BlockControl(false);
		}
		else {

		}
	}
	catch (Exception *ex) {
			AnsiString errStr = "TfmDiagnost::ApplicationEventsMessage:"+ex->Message;
			TProtocol::ProtocolSave(errStr);
			TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
	// if (Msg.wParam == 33) { // идентификатор наш
}

void __fastcall TfmDiagnost::scbChartDraggerDiagChange(TObject *Sender) {
	double length = 2000;
	for (int i = 0; i < ChartGPSF052->SeriesCount(); ++i) {
		if (length < ChartGPSF052->Series[i]->MaxXValue()) {
			length = ChartGPSF052->Series[i]->MaxXValue();
		}
	}
	double max = ChartGPSF052->BottomAxis->Maximum;
	double min = ChartGPSF052->BottomAxis->Minimum;
	double step = (double)(max - min) / 100.0;
	if (length > 0)
		scbChartDraggerDiag->Max =
			(int)ceil((double)length * 100.0 / (double)(max - min));
	else
		scbChartDraggerDiag->Max =
			(int)ceil((double)100.0 * 100.0 / (double)(max - min));
	// curPos = max/step;
	long change = scbChartDraggerDiag->Position - curPos;
	if (change > 0) {
		ChartGPSF052->BottomAxis->Maximum = change * step + max;
		ChartGPSF052->BottomAxis->Minimum = change * step + min;
	}
	else {
		ChartGPSF052->BottomAxis->Minimum = change * step + min;
		ChartGPSF052->BottomAxis->Maximum = change * step + max;
	}

	ChartGPSF052->Refresh();
	curPos = scbChartDraggerDiag->Position;
	ChartGPSF052Scroll(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TfmDiagnost::ChartGPSF052Scroll(TObject *Sender) {
	lMinScrollbar->Caption =
		"" + IntToStr((int) ChartGPSF052->BottomAxis->Minimum);
	lMaxScrollbar->Caption =
		"" + IntToStr((int) ChartGPSF052->BottomAxis->Maximum);
}
// ---------------------------------------------------------------------------

void TfmDiagnost::BlockControl(bool ToTest) {
	lbeFrecSignalGSPF052->Enabled = !ToTest;
	lbeVoltageGSPF052->Enabled = !ToTest;
	lbeFrecDiscrGSPF052->Enabled = !ToTest;
	btnStopGen->Enabled = ToTest;
	btnStartGen->Enabled = !ToTest;
	btnStartSer->Enabled = !ToTest;
	btnReCalc->Enabled = !ToTest;
	GroupBoxNGr->Enabled = !ToTest;
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::btnReCalcClick(TObject *Sender) {
	// Выводим на экран графики
	lCardData->ReCalcMeasuresToChannels();
	int arrSize;
	for (int i = 0; i < chCount; i++) {
		arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
		double* tmpArray = new double[arrSize];
		for (int j = 0; j < arrSize; j++) {
			tmpArray[j] = lCardData->vecMeasuresData[0].vecSensorsData[i][j];
		}
		ChartGPSF052->Series[i]->Clear();
		ChartGPSF052->Series[i]->AddArray(tmpArray, arrSize - 1);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfmDiagnost::bbtCreateEtalonClick(TObject *Sender) {
	AnsiString strSQL = "";
	AnsiString strCmdSql = "";
	int ind = 0;
	int err;
	double res = 0;
	try {

		if (cbxSGD->ItemIndex == -1) {
			MessageDlg("Выберите группу прочности", mtError,
				TMsgDlgButtons() << mbOK, NULL);

		}
		else {
		// запишем в файл, как эталон под другим именем
			fileName = "";
			//fileName =  "..\\..\\SavedEtalons\\E_";
			//fileName = ExtractFilePath(Application->ExeName);
			//fileName+="\SavedEtalons\\E_";
			fileName=pGlobalSettings->SaveEtalonPath;
			fileName+="\\E_";
			fileName += FormatDateTime("yyyy_mm_dd_hh_mm_ss_", Now());
			fileName += lbeFrecSignalGSPF052->Text;
			fileName += "_TS_";
			fileName += SqlDBModule->GetStrFieldSQL("TypeSizes","TSName"
				,"rec_id = "+IntToStr(pGlobalSettings->indexCurrentTypeSize),0,err);
			fileName += "_SG_";
			fileName += cbxSGD->Text;
			fileName += "_FHZ.csv";
			// записали значения в базу
			ind = cbxSGD->ItemIndex;
			strSQL =
				"INSERT INTO Etalons(ts_id,fenable,frequency,address_file,sg_id) VALUES( ";
			strSQL += IntToStr(pGlobalSettings->indexCurrentTypeSize);
			strSQL += ",";
			strSQL += IntToStr(1);
			strSQL += ",";
			strSQL += lbeFrecSignalGSPF052->Text;
			strSQL += ",'";
			strSQL += fileName;
			strSQL += "',";
			strSQL += IntToStr((int)cbxSGD->Items->Objects[ind]);
			strSQL += ");\n";
			strSQL += "SELECT @@IDENTITY AS 'LAST_ID';";
			queryEtalon->Close();
			queryEtalon->SQL->Text = strSQL;
			queryEtalon->Open();
			int etId = queryEtalon->FieldByName("LAST_ID")->AsInteger;
			queryEtalon->Close();
			strSQL = "INSERT INTO EtalonValues Select ";
			strSQL += IntToStr(etId);
			strSQL +=
				",threshold_value, 123 from TypeSizeThresholds where TS_id=";
			strSQL += IntToStr(pGlobalSettings->indexCurrentTypeSize);
			strSQL += " order by threshold_value";
			queryEtalon->SQL->Text = strSQL;
			queryEtalon->ExecSQL();
			queryEtalon->Close();
			// fmEditEtalon = new TfmEditEtalon(this,pGlobalSettings,lCardData);
			// fmEditEtalon->ShowModal();
			// fmEditEtalon=NULL;
			// cbxSG->ItemIndex=-1;

			// посчитаем значения на порогах
			vector<int>Thresholds;

			// загружаем пороги по выбранному  типоразмеру
			queryEtalon->Close();
			strSQL =
				"select threshold_value from TypeSizeThresholds where TS_id=:pTS_id order by threshold_value";
			queryEtalon->SQL->Text = strSQL;
			queryEtalon->Parameters->ParamByName("pTS_id")->Value = pGlobalSettings->indexCurrentTypeSize;
			queryEtalon->Open();
			queryEtalon->First();
			int tst=queryEtalon->RecordCount;
			while (!queryEtalon->Eof) {
				res = queryEtalon->FieldByName("threshold_value")->AsInteger;
				Thresholds.push_back(res);
				queryEtalon->Next();
			}
			queryEtalon->Close();
			strSQL=	"SELECT rec_id as vrec_id, etalon_id,thres_val,barkgausen_val FROM EtalonValues where etalon_id = :petalon_id order by thres_val";
			queryEtalon->SQL->Text=strSQL;
			queryEtalon->Parameters->ParamByName("petalon_id")->Value = etId;
			// посчитали знач порогов
			vector<double> BarkValues;
			BarkValues = lCardData->GetBarkValues(Thresholds);
			// обновим в базе
			queryEtalon->Open();
			queryEtalon->First();
			int ii = 0;
			for (int i = 0; i < Thresholds.size(); i++) {
				strCmdSql ="UPDATE EtalonValues SET barkgausen_val = :pbarkgausen_val";
				// cmdEtalonVal->Parameters->ParamByName("pbarkgausen_val")->Value = 222;
				// double tst = BarkValues[i];
				cmdEtalonVal->Parameters->ParamByName("pbarkgausen_val")->Value = BarkValues[i];
				// strCmdSql+= FloatToStr(BarkValues[i]);
				strCmdSql += " WHERE rec_id=";
				strCmdSql +=IntToStr(queryEtalon->FieldByName("vrec_id")->AsInteger);
				cmdEtalonVal->CommandText = strCmdSql;
				// cmdEtalonVal->Parameters->ParamByName("prec_id")->Value = queryEtalonVal->FieldByName("vrec_id")->AsInteger;
				// cmdEtalonVal->Parameters->ParamByName("pbarkgausen_val")->Value = &BarkValues[i];
				cmdEtalonVal->Execute();
				queryEtalon->Next();
			}
			queryEtalon->Close();
			int frec=lCardData->getFreqNum();
			int arrSize = lCardData->vecMeasuresData[0].vecSensorsData[0].size()*3;
			//int arrSize = lCardData->vecMeasure.size();
			vector<double> forSave;
			for(int i = 0; i<lCardData->vecMeasuresData[0].vecSensorsData[0].size();i++)
			{
			   forSave.push_back(lCardData->vecMeasuresData[0].vecSensorsData[0][i]);
			   forSave.push_back(lCardData->vecMeasuresData[0].vecSensorsData[1][i]);
			   forSave.push_back(lCardData->vecMeasuresData[0].vecSensorsData[2][i]);
			}
			//TLog::SaveChTxtDoubleFile(fileName, &(lCardData->vecMeasure[0]), arrSize,3);
			TLog::SaveChTxtDoubleFile(fileName, &(forSave[0]), arrSize,3);
			MessageDlg("Образец сохранен", mtConfirmation,
				TMsgDlgButtons() << mbOK, NULL);
			err = 0;
			//
			// queryTSz->Close();
			// queryTSz->Parameters->ParamByName("pTypeSize")->Value = (int)cbTypeSize->Items->Objects[ind];
			// queryTSz->Open();

		}
	}
	catch (Exception *ex) {
			AnsiString errStr = "TfmDiagnost::bbtCreateEtalonClick:"+ex->Message;
			TProtocol::ProtocolSave(errStr);
			TExtFunction::ShowBigModalMessage(errStr, clRed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfmDiagnost::UserWndProc(Messages::TMessage &_msg) {
	// Проверяем на нажатие сочетания клавиш Ctrl+Alt+Enter
	if (_msg.Msg == WM_HOTKEY) // сообщение наше
	{
		if (_msg.WParam == 0x00F) // идентификатор наш
		{
			// Handled = true;
			enableF = !enableF;
			BlockControl(enableF);
			_msg.Result = 0;
		}
		else {
			//
		}
	}
	else {
		WndProc(_msg);
	}
}

void __fastcall TfmDiagnost::Button1Click(TObject *Sender) {
	int arrSize;                          //todo
	int frec=lCardData->getFreqNum();
	AnsiString fn="";
	TLog::LoadTxtChDoubleFile(fn, lCardData,frec,3);
	TExtFunction::PrepareChartToTst(ChartGPSF052, chCount, 0, 2000);
	for (int i = 0; i < chCount; i++) {
		arrSize = lCardData->vecMeasuresData[0].vecSensorsData[i].size();
		double* tmpArray = new double[arrSize];
		for (int j = 0; j < arrSize; j++) {
			tmpArray[j] = lCardData->vecMeasuresData[0].vecSensorsData[i][j];
		}
		ChartGPSF052->Series[i]->Clear();
		ChartGPSF052->Series[i]->AddArray(tmpArray, arrSize - 1);
	}
}
// ---------------------------------------------------------------------------
