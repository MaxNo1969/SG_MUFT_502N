// ---------------------------------------------------------------------------
#pragma hdrstop
#include "TSG.h"
// #include "SignalListDef.h"
#include <Math.hpp>
#include <algorithm>
#include "TProtocol.h"
#include "Filters.h"
#include "TLCardData.h"
#include "TLogCh502Params.h"
#include "TSGCoords.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#include "EtalonDatas.h"
#include "TypeSizeFrequencies.h"
// ---------------------------------------------------------------------------
#ifdef BERLIN_10
//
#else
  #pragma package(smart_init)
#endif


// ---------------------------------------------------------------------------
// SG::SG(TIniFile* _ini, AnsiString _SGroupFix)
TSG::TSG(TGlobalSettings* _mainGlobalSettings,TLCardData* _sgLCardData) {
	// SGroupFix = _SGroupFix;
	sgGlobalSettings=_mainGlobalSettings;
	sgLCardData=_sgLCardData;
	state = 0;
	freqNum = 0;
}

// ---------------------------------------------------------------------------
TSG::~TSG(void) {
	// lcard->Stop();
	sgLCardData->StopSGM();
}

// ---------------------------------------------------------------------------
void TSG::pr(AnsiString _msg) {
	AnsiString a = "SG: ";
	a += _msg;
	TProtocol::ProtocolSave(a);
}

// ---------------------------------------------------------------------------
void TSG::pr0(AnsiString _msg) {
	TProtocol::ProtocolSave(_msg);
}

// ---------------------------------------------------------------------------
int TSG::Exec(int _freqNum) {
	freqNum = _freqNum;
	switch (state) {
	case 0:
	{
		startTime = GetTickCount();
		sgLCardData->StartSGM(freqNum);
		state = 1;
		break;
	}
	case 1:
	{
		if (!sgLCardData->Read(freqNum))
			TExtFunction::FATAL("SG::Exec: не смогли прочитать плату lcard");
		int x = sgLCardData->GetBufTime()*1000;
		int y = GetTickCount()-startTime;
		if((GetTickCount()-startTime) < sgLCardData->GetBufTime()*1000)
			break;
		sgLCardData->StopSGM();
		state = 2;
		break;
	}
	default:
		break;
	}
	return (state);
}
// ---------------------------------------------------------------------------
CSG TSG::GetSG()
{
	double maxCorr = 0;
	vector<int> maxCorrSG_id;
	vector<double> BarkValues;
	CSG ret;
	//найдем группу прочности
	try{
	//составим список частот текущего типоразмера и значения порогов их эталонов
	TSFrequencies TSFreqs = TSFrequencies(sgGlobalSettings->indexCurrentTypeSize);
	EtalonDatas EDatas = EtalonDatas(sgGlobalSettings->indexCurrentTypeSize,sgGlobalSettings->indexCurrentSGGost);
	TSThresholds TSThres = TSThresholds(sgGlobalSettings->indexCurrentTypeSize);
	//для каждой собранной частоты
	for(int i = 0; i < sgLCardData->vecMeasuresData.size(); i++)
	{
		sgLCardData->setFreqNum(i);
		BarkValues = sgLCardData->GetBarkValues(TSThres.Thresholds);
		int currSG_id = 0;
		//для каждого эталона с такой же частотой и типоразмером
		for(int j = 0; j < EDatas.Etalons.size(); j++)
		{
			if(TSFreqs.Frequency[i] == EDatas.Etalons[j].Frequency)
			{
				//найдем их коррелляцию
				double currCorr = sgLCardData->GetCorrelation(BarkValues,EDatas.Etalons[j].BarkValues);
				//определим наибольшую коррелляцию и посчитаем ее эталон как ГП для этой частоты
				if(currCorr > maxCorr)
				{
					maxCorr = currCorr;
					currSG_id = EDatas.Etalons[j].SG_id;
				}
			}
		}
		maxCorrSG_id.push_back(currSG_id);
	}
	//определим наиболее частую ГП по всем частотам
	int maximal = 0;
	int element = 0;
	for (int i = 0; i < maxCorrSG_id.size();i++)
	{
		int currNum = maxCorrSG_id[i];
		int currCount = std::count(maxCorrSG_id.begin(), maxCorrSG_id.end(), currNum);
		if (currCount > maximal)
		{
			maximal = currCount;
			element = currNum;
		}
		if (currCount == maximal) //если есть 2 максимума, то группа не определена
		{
			element = 0;
		}
	}

	ret.group_id = element;
	}
	catch (Exception *ex) {
		TLog::ErrFullSaveLog(ex);
		//AnsiString msg
		//programSettings.colorMSG = programSettings.colorBrak;
		//TExtFunction::UpdateStatusBar(programSettings.gsStatusBar, strStatus, _msg, programSettings.colorMSG);
		//TExtFunction::UpdateLabelStatus(programSettings.gsStatusLabel, strStatus, _msg, programSettings.colorMSG);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
		}
	return (ret);
}

// ---------------------------------------------------------------------------
TColor TSG::conv_color(int _col) {
	unsigned int ret;
	ret = _col >> 16 & 0xFF;
	ret |= _col & 0xFF00;
	ret |= _col << 16 & 0xFF0000;
	return ((TColor)ret);
}

// ---------------------------------------------------------------------------
CSG TSG::Get1FrecSG()
{
	//найдем группу прочности
	//составим список частот текущего типоразмера и значения порогов их эталонов
	TSFrequencies TSFreqs = TSFrequencies(sgGlobalSettings->indexCurrentTypeSize);
	EtalonDatas EDatas = EtalonDatas(sgGlobalSettings->indexCurrentTypeSize,sgGlobalSettings->indexCurrentSGGost);
	//serg
	if (EDatas.Etalons.size()==0) {
		CSG ret;
		ret.group_id = 0;
		ret.probability = 0;
		ret.group = "ХХХ";
		ret.color = clWhite;
		 TExtFunction::ShowBigModalMessage("Не найдены значения эталонов!", clRed);
		return (ret);
	}else{
	  //
    }
	TSThresholds TSThres = TSThresholds(sgGlobalSettings->indexCurrentTypeSize);
	double probability = 0;
//	vector<int> maxCorrSG_id;
	vector<double> BarkValues;
	//для каждой собранной частоты
	sgLCardData->setFreqNum(0);
	BarkValues = sgLCardData->GetBarkValues(TSThres.Thresholds);
	int currSG_id = 0;
	switch(sgGlobalSettings->calcSGMode)
	{
		case 1:
		{
			//по отклонению
			double minDev = 0;
			double maxDev = 1;
			//для каждого эталона с такой же частотой и типоразмером
			for(int j = 0; j < EDatas.Etalons.size(); j++)
			{
				if(TSFreqs.Frequency[0] == EDatas.Etalons[j].Frequency)
				{
					//найдем их отклонение
					double currDev = sgLCardData->GetSquareDeviation(BarkValues,EDatas.Etalons[j].BarkValues);
					//определим наименьшее и наибольшее отклонения и посчитаем его эталон как ГП для этой частоты
					if((currDev < minDev) || (minDev == 0))
					{
						minDev = currDev;
						currSG_id = EDatas.Etalons[j].SG_id;
					}
					if((currDev > maxDev) || (maxDev == 1))
					{
						maxDev = currDev;
//						currSG_id = EDatas.Etalons[j].SG_id;
					}
				}
			}
			probability = (maxDev-minDev)/maxDev;
			break;
		}
		case 2:
		{
			//по вероятности
//			vector<double> probValues;
//			double maxProb = 0;
//			//для каждого эталона с такой же частотой и типоразмером
//			for(int j = 0; j < EDatas.Etalons.size(); j++)
//			{
//				if(TSFreqs.Frequency[0] == EDatas.Etalons[j].Frequency)
//				{
//					//найдем их отклонение
//					double currDev = sgLCardData->GetSquareDeviation(BarkValues,EDatas.Etalons[j].BarkValues);
//					probValues.push_back(currDev);
//				}
//				else probValues.push_back(1.0);
//			}
//			//посчитаем делитель
//			double devider = 1;
//			for(int i = 0; i < probValues.size(); i++)
//				devider *= (1.0/probValues[i]);
//			//для каждого эталона с такой же частотой и типоразмером
//			for(int j = 0; j < EDatas.Etalons.size(); j++)
//			{
//				if(TSFreqs.Frequency[0] == EDatas.Etalons[j].Frequency)
//				{
//					//найдем их отклонение
//					double currProb = (1.0/probValues[j])/devider;
//					if(currProb > maxProb)
//					{
//						maxProb = currProb;
//						currSG_id = EDatas.Etalons[j].SG_id;
//					}
//				}
//			}
//			probability = maxProb;
//			break;
	}
		default:
		{
			//По корреляции
			double maxCorr = 0;
			//для каждого эталона с такой же частотой и типоразмером
			for(int j = 0; j < EDatas.Etalons.size(); j++)
			{
				if(TSFreqs.Frequency[0] == EDatas.Etalons[j].Frequency)
				{
					//найдем их коррелляцию
					double currCorr = sgLCardData->GetCorrelation(BarkValues,EDatas.Etalons[j].BarkValues);
					//определим наибольшую коррелляцию и посчитаем ее эталон как ГП для этой частоты
					if(currCorr > maxCorr)
					{
						maxCorr = currCorr;
						currSG_id = EDatas.Etalons[j].SG_id;
					}
				}
			}
			probability = maxCorr;
		}
	}
	//результат
    int err;
	CSG ret;
	ret.group_id = currSG_id;
	ret.probability = probability;
	ret.group = SqlDBModule->GetStrFieldSQL("SolidGroups","SGName"
		,"rec_id="+IntToStr(ret.group_id),"X",err);
	ret.color = (TColor)SqlDBModule->GetIntFieldSQL("SolidGroups","Color"
		,"rec_id="+IntToStr(ret.group_id),65535,err);
	return (ret);
}

