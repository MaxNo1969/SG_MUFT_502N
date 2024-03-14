//---------------------------------------------------------------------------

#ifndef EtalonDatasH
#define EtalonDatasH
#include <vector>
#include <Classes.hpp>
#include <Graphics.hpp>
using namespace std;

//---------------------------------------------------------------------------
class Etalon //класс хранящий эталон
{
public:
	Etalon();
	~Etalon();
	//id Эталона в базе
	int Etalon_id;
	//частота
	int Frequency;
	//группа прочности индекс
	int SG_id;
	//группа прочности имя
	AnsiString SG_name;
	//Цвет
	TColor Color;
	//пороги
	vector<int> Thresholds;
	//значения на порогах
	vector<double> BarkValues;
};
//---------------------------------------------------------------------------
class EtalonDatas //класс хранящий эталоны для типоразмера
{
public:
	EtalonDatas(int _TS_id);
	~EtalonDatas();
	//эталоны
	vector<Etalon> Etalons;
};
//---------------------------------------------------------------------------
class TSThresholds //класс хранящий пороги типоразмера
{
public:
	TSThresholds(int _TS_id);
	~TSThresholds();
	//пороги
	vector<int> Thresholds;

};

#endif
