//---------------------------------------------------------------------------

#ifndef CalcSGPointsH
#define CalcSGPointsH

#include <vector>
using namespace std;
#include "uCRListT.h"
#include "SGPars.h"
#include "IU.h"


//---------------------------------------------------------------------------

class CalcSGPoints
{
private:
	int* points;
	double* coords;
	CRListT<int> L;
	bool ByU;
	vector <IU> iu;
	int Start;
	int Stop;
	int periodMin;
	int periodMax;

public:
	CalcSGPoints(vector <IU> _iu, vector <int> _treshP, SGPars _sgpars, AnsiString _sop);

private:
	bool GetNextPeriodI(int _start, int _size);
	bool GetNextPeriodU(int _start, int _size);
	int GetNextSizeI(int _start);
	int GetNextSizeU(int _start);

public:
	inline int* GetPoints()
	{
		return (points);
	}
	inline double* GetCoords()
	{
		return (coords);
	}
};
#endif
