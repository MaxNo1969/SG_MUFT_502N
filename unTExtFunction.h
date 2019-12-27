// ---------------------------------------------------------------------------

#ifndef unTExtFunctionH
#define unTExtFunctionH
// ---------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
 #include <VCLTee.Chart.hpp>
 #include <VCLTee.Series.hpp>
 #include <System.IOUtils.hpp>
#define  sizeArr 150;
// #include "workWithX502.h"
// ---------------------------------------------------------------------------
// различные вспомогательные функции
class TExtFunction {
	TExtFunction();
	~TExtFunction();

public:
	// заливка массивов  (*a)[2]
	static int FillArrayModule(AnsiString _tubeNum, int _tubeModule, int _maxZones, int _countSensors, int _arrDataModule[8][100]);
	// показ трубы
	static int ShowArrayModule(int _countSensors, int _maxZones, int _arrDataModule[8][100], TChart* _chart);
	// настраиваем чарты одноообразно, это длинно муторно, но полезно
	static void PrepareBarChart(int _countSensors, int _maxZones, TChart* _chart);
	static void PrepareFastLineChart(int _countSensors,  int _lengthChart,TChart* _chart);
	// пишем чарт (трубу) в базу по зонам с учетом каналов и типа модуля
	// _moduleType 1-толщиномер 2 - поперечник 3 - продольник 4 - группа прочности 5 - суммарный резульнат
	static int SaveChartToDB(AnsiString _serialTubeNum,AnsiString _tubeNum, int _codeTubeTypeSize, int _moduleType, int _maxZones, int _codeCustomer, int _codeOperatorU, int _codeStatusTube,
		TChart* _chart);

	// вывод в строку состояния
	static int UpdateStatusBar(TStatusBar *_StatusBar, AnsiString _strTitle, AnsiString _strText, TColor _colorFont);
	// вывод в какою-то метку
	static int UpdateLabelStatus(TLabel *_label, AnsiString _strTitle, AnsiString _strText, TColor _colorFont);
	// вывод сообщения в модальную форму
	static int ShowBigModalMessage(AnsiString _strMsg, TColor _color);
		//непонятная фигня
	static void FATAL(AnsiString _msg);
	//для просмотра графиков диагностики
	static void PrepareChartToTst(TChart *chart, int _countChLog, int _lengthChart,int _maxYChart);
	// массив для закачки и просмотра зон - ширина по максимуму на 100 зон, глубина по количеству датчиков 8 (забиваем по макимуму)
	static int arrDataThick[8][100];
	static int arrDataCross[8][100];
	static int arrDataSum[8][100];
private:
	// static int a;
	// строка для вывода сообщений
	AnsiString msgLast;
};

// массивы для хранения признаков по зонам (датчик - зона)
int TExtFunction::arrDataThick[8][100];
int TExtFunction::arrDataCross[8][100];
int TExtFunction::arrDataSum[8][100];
// int TExtFunction::a;
// int TExtFunction::a=0;
#endif
