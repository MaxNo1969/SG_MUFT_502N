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
	EtalonDatas(int _TS_id, int _SGGost_id);
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

//Массив образцов
class EtalonArray
{
private:
public:
	//Название массива
	AnsiString name;
	//Типоразмер
	int ts_id;
	//ГОСТ
	int gost_id;
	vector<Etalon> Etalons;

	EtalonArray(AnsiString _name,int _TS_id, int _SGGost_id):
		name(name),ts_id(_TS_id),gost_id(_SGGost_id){};
	~EtalonArray(){Etalons.clear();};

};


#endif
