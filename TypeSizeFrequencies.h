//---------------------------------------------------------------------------

#ifndef TypeSizeFrequenciesH
#define TypeSizeFrequenciesH
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class TSFrequencies //класс хранящий настройки ГСПФ для типоразмера
{
public:
	TSFrequencies(int _TS_id);
	~TSFrequencies();
	//частота
	vector <int> Frequency;
	//амплитуда
	vector <double> Amplitude;
};
#endif
