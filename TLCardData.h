#ifndef TLCardDataH
#define TLCardDataH
#include <vector>
// #include <IniFiles.hpp>
//------------------
 #include "TLCard502.h"
//---------------------
#include "TLogCh502Params.h"
#include "TMeasuresData.h"
using namespace std;

// ---------------------------------------------------------------------------
class TLCardData {
private:
	// измерение
	// vector<vector<double> >LZone;
	// vector<vector<double> >CZone;
//	vector<vector<double> >GZone;
	//количество измерений
	int countMeasures;
	// bool IsCrossStarted;
	// bool IsLineStarted;
	bool IsSGStarted;

	TLCard502* dtLcard502;
	// Время сбора по одной частоте
	double BufTime;
	//Массив коэффициентов усиления. Не используется больше
//	vector<double>GVoltPercent;
	//vector<TLogCh502Params> veсLogChannelsParams;
	//TLogCh502Params* TLogCh502Params;

	//Номер текущей частоты
	int freqNum;
	//поиск точки перехода через 0 по указанному каналу
	int SearchOfZeroTransition(int _sensNum);
	//поиск периода точки перехода через 0 по указанному каналу
	int SearchOfZeroTransitionPeriod(int _sensNum);
	//отфильтрованный вектор указанного канала
	vector<double> vecZeroTransition;
	//Настройки для фильтров и т.п.
	TGlobalSettings *pSettings;
public:
	TLCardData(TLCard502* _lcard502,int _countFrequencies, int _chLogCount, TGlobalSettings* _pGSettings);
	~TLCardData(void);

	AnsiString lastError;

	//вектор измерений
	vector<double> vecMeasure;
	vector<TMeasuresData> vecMeasuresData;
	void StartSGM(int _freqNum);
	void StopSGM(void);
	void ClearSGM(void);

//	inline vector<vector<double> > * GetPointSG() {
//		return (&GZone);
//	}

//	inline vector<vector<double> >* GetPointSG(int _num) {
//		return (&vecMeasuresData[_num].vecSensorsData);
//	}

	double GetValueAvg5ByChName(AnsiString _name);
	inline double GetBufTime()
	{
		return BufTime;
	}
	bool Read(int _freqNum);
	//перессчитываем измерения и разделяем на датчики
	int ReCalcMeasuresToChannels();
	//проверяем наличие муфты
	int CheckMufta(int _sensNum);
	//получаем значения Баркгаузена на порогах
	vector<double> GetBarkValues(vector<int> &_Thresholds);
	//Расчет коррелляции
	double GetCorrelation(vector<double> &_XCoords,vector<double> &_YCoords);
	//Расчет квадратичного отклонения
	double GetSquareDeviation(vector<double> &_XCoords,vector<double> &_YCoords);
	//Возвращает текущий номер частоты
	inline int getFreqNum()
	{
		return freqNum;
	}
	//Устанавливает текущий номер частоты
	inline void setFreqNum(int _freqNum)
	{
		freqNum = _freqNum;
	}
	//передает указатель на плату
	inline TLCard502* GetLCard502()
	{
		return dtLcard502;
	}
};
// ---------------------------------------------------------------------------
#endif
