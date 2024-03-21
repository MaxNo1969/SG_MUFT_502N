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
	// ���������
	// vector<vector<double> >LZone;
	// vector<vector<double> >CZone;
//	vector<vector<double> >GZone;
	//���������� ���������
	int countMeasures;
	// bool IsCrossStarted;
	// bool IsLineStarted;
	bool IsSGStarted;

	TLCard502* dtLcard502;
	// ����� ����� �� ����� �������
	double BufTime;
	//������ ������������� ��������. �� ������������ ������
//	vector<double>GVoltPercent;
	//vector<TLogCh502Params> ve�LogChannelsParams;
	//TLogCh502Params* TLogCh502Params;

	//����� ������� �������
	int freqNum;
	//����� ����� �������� ����� 0 �� ���������� ������
	int SearchOfZeroTransition(int _sensNum);
	//����� ������� ����� �������� ����� 0 �� ���������� ������
	int SearchOfZeroTransitionPeriod(int _sensNum);
	//��������������� ������ ���������� ������
	vector<double> vecZeroTransition;
	//��������� ��� �������� � �.�.
	TGlobalSettings *pSettings;
public:
	TLCardData(TLCard502* _lcard502,int _countFrequencies, int _chLogCount, TGlobalSettings* _pGSettings);
	~TLCardData(void);

	AnsiString lastError;

	//������ ���������
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
	//�������������� ��������� � ��������� �� �������
	int ReCalcMeasuresToChannels();
	//��������� ������� �����
	int CheckMufta(int _sensNum);
	//�������� �������� ����������� �� �������
	vector<double> GetBarkValues(vector<int> &_Thresholds);
	//������ �����������
	double GetCorrelation(vector<double> &_XCoords,vector<double> &_YCoords);
	//������ ������������� ����������
	double GetSquareDeviation(vector<double> &_XCoords,vector<double> &_YCoords);
	//���������� ������� ����� �������
	inline int getFreqNum()
	{
		return freqNum;
	}
	//������������� ������� ����� �������
	inline void setFreqNum(int _freqNum)
	{
		freqNum = _freqNum;
	}
	//�������� ��������� �� �����
	inline TLCard502* GetLCard502()
	{
		return dtLcard502;
	}
};
// ---------------------------------------------------------------------------
#endif
