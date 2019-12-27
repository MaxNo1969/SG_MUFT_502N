// ---------------------------------------------------------------------------

#ifndef TMeasuresDataH
#define TMeasuresDataH
// ---------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <vector>
#include <iterator>
using namespace std;
// ---------------------------------------------------------------------------

//#pragma package(smart_init)

class TMeasuresData {
public:
	TMeasuresData(int _chLogCount);
	~TMeasuresData(void);
//	// переменные
//	int realSensorSize;
//	int fullSensorSize;
	// вектор данных по датчикам  [канал] - [данные] по датчику
	vector<vector<double> >vecSensorsData;
	//вектор наименований каналов - если понадобится
	vector<AnsiString> namesChannels;
	//функции
	int ClearData(void);
private:

};
#endif
