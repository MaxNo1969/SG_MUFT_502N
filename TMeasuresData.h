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
	// ������ ������ �� ��������  [�����] - [������] �� �������
	vector<vector<double> >vecSensorsData;
	//�������
	int ClearData(void);
private:

};
#endif
