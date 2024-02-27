#pragma hdrstop
#include "TLCardData.h"
#include "TProtocol.h"
#include "unSQLDbModule.h"
#include "Filters.h"
#include "unTUtils.h"
#include "unTExtFunction.h"
#ifdef BERLIN_10
//
#else
 #pragma package(smart_init)
#endif


TLCardData* lCardData = NULL;

// ---------------------------------------------------------------------------
TLCardData::TLCardData(TLCard502* _lCard502,int _countFrequencies, int _chLogCount, TGlobalSettings* _pGSettings)
{
	dtLcard502=_lCard502;
	pSettings = _pGSettings;
	if(!pSettings)
	{
		AnsiString err = "TLCardData::TLCardData: Ќе удалось получить доступ к параметрам";
		throw Exception(err);
	}
	//общее количество измерений по муфте
	countMeasures = _countFrequencies;
//	vecMeasuresData.reserve(_countMeasures);
	for (int i = 0; i < _countFrequencies; i++) {
		TMeasuresData* mData = new TMeasuresData(_chLogCount);
		vecMeasuresData.push_back(*mData);
		delete mData;
	}
	IsSGStarted = false;
	int err;
	BufTime = SqlDBModule->GetFloatFieldSQL("SettingsGlobal","ReadBufTime",NULL, 1.0,err);
	freqNum = 0;
}

// ---------------------------------------------------------------------------
TLCardData::~TLCardData(void) {
	for (int i = 0; i < countMeasures; i++) {
		//delete measuresData[i];
	}
	vecMeasuresData.clear();
}
// ---------------------------------------------------------------------------
void TLCardData::ClearSGM(void) {
	int m = vecMeasuresData.size();
	for (int i = 0; i < vecMeasuresData.size(); i++)
		vecMeasuresData[i].ClearData();
}
// ---------------------------------------------------------------------------
void TLCardData::StartSGM(int _freqNum) {
	IsSGStarted = true;
	freqNum = _freqNum;
	if(freqNum == 0)
		ClearSGM();
	vecMeasure.clear();
	if(dtLcard502)dtLcard502->Start();
//	dtLcard502->StartRead();

}
// ---------------------------------------------------------------------------
void TLCardData::StopSGM(void) {
//	dtLcard502->StopRead();
	if(dtLcard502)dtLcard502->Stop();
	if (IsSGStarted)
		ReCalcMeasuresToChannels();
	IsSGStarted = false;
}
// ---------------------------------------------------------------------------
bool TLCardData::Read(int _freqNum) {
	freqNum = _freqNum;
	int size;
	//читаем размером ??? -> size
	double* buf;
	if(dtLcard502)
	{
		buf = dtLcard502->Read(&size);
		// double* raw_buf=lcard502->GetRawC();
		if (size < 0)
		{
			lastError = dtLcard502->LastError;
			return (false);
		}
		//int packet_size = /* CZone.size() + LZone.size()+ */ GZone.size();
		//размер кадра - количество лог каналов
		//	int kadrSize = vecMeasuresData[_freqNum].vecSensorsData.size(); //GZone.size();
		//	int kadrs = size / kadrSize;

		if (IsSGStarted)
		{
			// for (int i = 0; i < size; i++) {
			// vecMeasure.push_back(buf[i]);
			// }
			// serg - скорректируем как бы до 14 разр€дов
			for (int i = 0; i < size; i++)
			{
				// serg
				double dtmp = buf[i] / 730;
				vecMeasure.push_back(buf[i] / 730);
			}

		}
// «акоментированный кусок
/*
		unsigned int size_new = GZone[0].size() + packets;
		if (GZone[0].capacity() < size_new)
		{
			 size_new *= (1 + LCard502_ADD_PERCENT / 100);
			 for (unsigned int s = 0; s < GZone.size(); s++)
			   GZone[s].reserve(size_new);
		}
		for (int p = 0; p < packets; p++)
		{
			double* pbuf = buf + p * packet_size;
			for (unsigned int s = 0; s < GZone.size(); s++)
				GZone[s].push_back(pbuf[s]*GVoltPercent[s]*10);
		}
*/

		//----- ўукин: отложим разбитие по каналам до полного сбора
/*
		unsigned int size_new = vecMeasuresData[_freqNum].vecSensorsData[0].size()+ kadrs;
		if (vecMeasuresData[_freqNum].vecSensorsData[0].capacity() < size_new)
		{
			size_new *= (1 + LCard502_ADD_PERCENT / 100);
			for (unsigned int s = 0; s < vecMeasuresData[_freqNum].vecSensorsData.size(); s++)
				vecMeasuresData[_freqNum].vecSensorsData[s].reserve(size_new);
		}
		for (int p = 0; p < kadrs; p++)
		{
			double* pbuf = buf + p * kadrSize;
			for (unsigned int s = 0; s < vecMeasuresData[_freqNum].vecSensorsData.size(); s++)
				vecMeasuresData[_freqNum].vecSensorsData[s].push_back(pbuf[s] // GVoltPercent[s]*10 ); //todo
		}
*/
	}
	return (true);
}
// ---------------------------------------------------------------------------
double TLCardData::GetValueAvg5ByChName(AnsiString _ch_name) {
	// среднее арифметическое по 5-ти
	int err = -100;
	double ret = 0;
	if(dtLcard502)
	{
		TLogCh502Params* Ch = dtLcard502->FindChByName(_ch_name);//, err);
		for (int i = 0; i < 5; i++)
		{
			// ret += lcard502->GetValue(lcard502->FindNumChByName(_ch_name));
			// GetValueByChannel
		ret += dtLcard502->GetValue(Ch->logicalChannel);
		}
	}
	return (ret / 5);
}
// ---------------------------------------------------------------------------
int TLCardData::SearchOfZeroTransition(int _sensNum)
{
//	//количество каналов
//	int channelsQuantity = vecMeasuresData[freqNum].vecSensorsData.size();
//	//точка перехода
//	int step = 0;
//	//мы добрались до отрицательного участка Ќапр€жени€
//	bool flag = false;
//	//количество кадров
//	int kadrsQuantity = vecMeasure.size() / channelsQuantity;
//	for(int i = 0; i < kadrsQuantity; i++)
//	{
//		if(!flag && vecMeasure[i*channelsQuantity+_sensNum] < 0)
//			flag = true; //нашли отрицательный участок
//		if(flag && vecMeasure[i*channelsQuantity+_sensNum] >= 0)
//		{
//			step = i*channelsQuantity;
//			break;
//		}
//	}
//	return step;

	//точка перехода
	int step = 0;
	//мы добрались до отрицательного участка Ќапр€жени€
	bool flag = false;
	//количество кадров
	int kadrsQuantity = vecZeroTransition.size();
	for(int i = 0; i < kadrsQuantity; i++)
	{
		if(!flag && vecZeroTransition[i] < 0)
			flag = true; //нашли отрицательный участок
		if(flag && vecZeroTransition[i] >= 0)
		{
			step = i;
			break;
		}
	}
	return step;
}
// ---------------------------------------------------------------------------
int TLCardData::SearchOfZeroTransitionPeriod(int _sensNum)
{
//	//количество каналов
//	int channelsQuantity = vecMeasuresData[freqNum].vecSensorsData.size();
//	//точки перехода
//	int step1 = 0;
//	int step2 = 0;
//	//мы добрались до отрицательного участка сигнала
//	bool flag = false;
//	//количество кадров
//	int kadrsQuantity = vecMeasure.size() / channelsQuantity;
//	for(int i = 0; i < kadrsQuantity; i++)
//	{
//		if(!flag && vecMeasure[i*channelsQuantity+_sensNum] < 0)
//			flag = true; //нашли отрицательный участок
//		if(flag && (step1 == 0) && vecMeasure[i*channelsQuantity+_sensNum] >= 0)
//		{
//			step1 = i*channelsQuantity;
//			flag = false;
//		}
//		if(flag && (step1 != 0) && vecMeasure[i*channelsQuantity+_sensNum] >= 0)
//		{
//			step2 = i*channelsQuantity - step1;
//			return step2;
//		}
//	}
//	return step2;

	//точки перехода
	int step1 = 0;
	int step2 = 0;
	//мы добрались до отрицательного участка сигнала
	bool flag = false;
	//количество кадров
	int kadrsQuantity = vecZeroTransition.size();
	for(int i = 0; i < kadrsQuantity; i++)
	{
		if(!flag && vecZeroTransition[i] < 0)
			flag = true; //нашли отрицательный участок
		if(flag && (step1 == 0) && vecZeroTransition[i] >= 0)
		{
			step1 = i;
			flag = false;
		}
		if(flag && (step1 != 0) && vecZeroTransition[i] >= 0)
		{
			step2 = i - step1;
			return step2;
		}
	}
	return step2;
}
// ---------------------------------------------------------------------------
bool TLCardData::CheckMufta(int _sensNum)
{
	//мы нашли превышение уровн€
	int count = 0;
	int const maxCounts = 3;
	//количество кадров
	int kadrsQuantity = vecMeasuresData[freqNum].vecSensorsData[0].size();
	//отфильтруем
	SGFilter->toFilter(&(vecMeasuresData[freqNum].vecSensorsData[_sensNum][0])
		,vecMeasuresData[freqNum].vecSensorsData[_sensNum].size());
	double thresVal = dtLcard502->globalSettings->checkMuftaLevel;
	for(int i = 0; i < kadrsQuantity; i++)
	{
		double val = vecMeasuresData[freqNum].vecSensorsData[_sensNum][i];
		if(val > thresVal)
		{
			if(++count > maxCounts)
			{
				return true;
			}
		}
	}
	return false;
}
// ---------------------------------------------------------------------------
vector<double> TLCardData::GetBarkValues(vector<int> &_Thresholds)
{   //очень хреново, что вектор создаетс€ здесь, а удал€ть его необходимо выше
//лучше передать BarkValues как параметр, как _Thresholds
	vector<double> BarkValues;// = new vector<double>;
	//в файле хран€тс€ три периода
	int Period = vecMeasuresData[freqNum].vecSensorsData[0].size() / 3;
	for(int i = 0; i < _Thresholds.size(); i++)
	{
		int x = _Thresholds[i] * Period / 100;
		if (x >= vecMeasuresData[freqNum].vecSensorsData[0].size())
			x = vecMeasuresData[freqNum].vecSensorsData[0].size()-1;
		BarkValues.push_back(vecMeasuresData[freqNum].vecSensorsData[0][x]);
	}
	return BarkValues;
}
// ---------------------------------------------------------------------------
double TLCardData::GetCorrelation(vector<double> &_XCoords,vector<double> &_YCoords)
{
	double XSum = 0;
	double YSum = 0;
	double XYSum = 0;
	double X2Sum = 0;
	double Y2Sum = 0;
	double Corr = 0;

	if (_XCoords.size() != _YCoords.size())
	{
		return 0; //не считать при не совпадении размеров
	}
	int vecSize = _XCoords.size();
	for (int i = 0; i < vecSize; i++)
	{
//		TProtocol::ProtocolSave("_XCoords["+IntToStr(i)+"]: "+FloatToStr(_XCoords[i]));
//		TProtocol::ProtocolSave("_YCoords["+IntToStr(i)+"]: "+FloatToStr(_YCoords[i]));
		XSum += _XCoords[i];
		YSum += _YCoords[i];
		XYSum += _XCoords[i] * _YCoords[i];
		X2Sum += _XCoords[i] * _XCoords[i];
		Y2Sum += _YCoords[i] * _YCoords[i];
	}
	Corr = (vecSize * XYSum - XSum * YSum)
		/ (sqrt(vecSize * X2Sum - XSum * XSum)
		* sqrt(vecSize * Y2Sum - YSum * YSum));
	TProtocol::ProtocolSave("Corr = "+FloatToStr(Corr));
	return Corr;
}
// ---------------------------------------------------------------------------
double TLCardData::GetSquareDeviation(vector<double> &_XCoords,vector<double> &_YCoords)
{
	double Corr = 0;
	double Diff = 0;
	if (_XCoords.size() != _YCoords.size())
	{
		return 0; //не считать при не совпадении размеров
	}
	int vecSize = _XCoords.size();
	for (int i = 0; i < vecSize; i++)
	{
//		TProtocol::ProtocolSave("_XCoords["+IntToStr(i)+"]: "+FloatToStr(_XCoords[i]));
//		TProtocol::ProtocolSave("_YCoords["+IntToStr(i)+"]: "+FloatToStr(_YCoords[i]));
		Diff = _XCoords[i] - _YCoords[i];
		Corr += Diff * Diff;
	}
	TProtocol::ProtocolSave("Corr = "+FloatToStr(Corr));
	return Corr;  	//¬озвращает большое значение, почти всегда больше 1.
//	return 1.0/(1+Corr);  	//„ем меньше отклонение, тем веро€тнее √ѕ
}
// ---------------------------------------------------------------------------

int TLCardData::ReCalcMeasuresToChannels()
{
	int arrSize = vecMeasure.size();
	if (arrSize == 0)
	{
		AnsiString msg = "Ќе собрали данных!!! \n";
		TProtocol::ProtocolSave("ReCalcMeasuresToChannels "+msg);
		TLog::SaveStrMsgLog(msg);
//		TExtFunction::ShowBigModalMessage(msg, clRed);
		return -1;
	}
	int ChanCount = vecMeasuresData[freqNum].vecSensorsData.size();
	vecZeroTransition.clear();
	int zeroTransitionChannel = dtLcard502->globalSettings->zeroTransitionChannel;
	int j = zeroTransitionChannel;
	while(j < arrSize)
	{
		vecZeroTransition.push_back(vecMeasure[j]);
		j += ChanCount;
	}
	if (pSettings->isFilter) {
	  SGFilter->toFilter(&(vecZeroTransition[0]),vecZeroTransition.size());
	}else{
	 //
	}

	//изменим поиск перехода на отфильтрованный сигнал
	int p = SearchOfZeroTransition(zeroTransitionChannel)*ChanCount;
	int ThreePeriods = SearchOfZeroTransitionPeriod(zeroTransitionChannel) * ChanCount * 3;
	if(ThreePeriods < arrSize - p)
		arrSize = ThreePeriods + p;
	vecZeroTransition.clear();
	if (ThreePeriods == 0)
	{
		AnsiString msg = "Ќулевой период у сигнала!!! \n";
		TProtocol::ProtocolSave("ReCalcMeasuresToChannels "+msg);
		TLog::SaveStrMsgLog(msg);
//		TExtFunction::ShowBigModalMessage(msg, clRed);
//		return -2;
	}
	//создадим временные вектора
	vector< vector<double> > UncuttedData;
//	int ChanCount = vecMeasuresData[freqNum].vecSensorsData.size();
	for (int i = 0; i < ChanCount; i++)
	{
		vector<double> ChanVec;
		UncuttedData.push_back(ChanVec);
	}
	//а теперь заполним данные
	int sens = 0;
	for (int i = 0; i < vecMeasure.size(); i++)
	{
		UncuttedData[sens].push_back(vecMeasure[i]);
		sens++;
		if(sens == ChanCount)
			sens = 0;
	}
	//отфильтруем Ѕаркгаузена
	if(pSettings->isFilter)
	{
		for (int i = 0;i < UncuttedData.size(); i++)
		{
			SGFilter->toFilter(&(UncuttedData[i][0]),UncuttedData[i].size());
		}
	}
	//сначала очистим данные
	for(int i = 0; i < vecMeasuresData[freqNum].vecSensorsData.size(); i++)
		vecMeasuresData[freqNum].vecSensorsData[i].clear();
	//а теперь заполним данные
	sens = 0;
	for (; p/ChanCount < arrSize/ChanCount; p++)
	{
		vecMeasuresData[freqNum].vecSensorsData[sens].push_back(UncuttedData[sens][p/ChanCount]); 
		sens++;
		if(sens == ChanCount)
			sens = 0;
	}
	return 0;
}
// ---------------------------------------------------------------------------
