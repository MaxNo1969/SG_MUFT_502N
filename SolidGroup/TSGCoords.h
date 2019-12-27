// ---------------------------------------------------------------------------
#ifndef TSGCoordsH
#define TSGCoordsH
#include <System.hpp>
#include <vector>

// #include <IniFiles.hpp>
#include "IU.h"
// ---------------------------------------------------------------------------
using namespace std;

// ---------------------------------------------------------------------------
class TSGCoords {

public:
	//TSGCoords(TIniFile* _ini);
	TSGCoords();
	~TSGCoords(void);
	// ! вектор из N пороговых значений
	vector<double>thresholds;
	// -------------
	vector<double>coordsFromSignal(vector<vector<double> >& _sourceSignals);
	void Save(void);

	// [порог][точка]
	vector<vector<SGPoint> >GetPoints(vector<IU>& _SignalIU);
	vector<double>GetCoords(vector<IU>& _SignalIU);
	vector<IU>Convert(vector<vector<double> >& _sourceSignals);
	vector<double>GetCoords(vector<vector<SGPoint> >& _sgPoints);

private:
	// TIniFile* ini;

	void Load(void);
	// void Save(void);

	bool GetNextPeriodI(vector<IU>& _SignalIU, int* _start, int* _size);
	int GetNextSizeI(vector<IU>& _SignalIU, int* _start);

	bool GetNextPeriodU(vector<IU>& _SignalIU, int* _start, int* _size);
	int GetNextSizeU(vector<IU>& _SignalIU, int* _start);

	int periodMin;
	int periodMax;

	vector<int>thresh;

	void SaveToProtocol(AnsiString _msg);

	bool ByU;

	int thresholdCount;
};
#endif
