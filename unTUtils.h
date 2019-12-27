// ---------------------------------------------------------------------------

#ifndef unTUtilsH
#define unTUtilsH

// ---------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include<IniFiles.hpp>
//#include "workWithX502.h"
// #include "UnDataMod.h"
//#include <System.Classes.hpp>
 #include <VCLTee.Chart.hpp>
 #include <Vcl.Controls.hpp>
#include <vector>
#include <iterator>
#include "TLCardData.h"
using namespace std;
 //общий класс вспомогательных и сервисных функций - статических
// класс для записи о ошибках и прочем  в логи
class TLog {
public:
	TLog();
	~TLog(void);
	//запись строки в предопределенный лог ошибок
	//путь к приложению\LOGs\errLog_" + текущие год_месяц_день + ".log";
	static int SaveStrMsgLog(AnsiString _Msg);
	//запись в текстовый файл с указанием полного пути
	static int SaveStrTxtFile(AnsiString _fullNameFile,AnsiString _Msg);
	//запись смеси текста и бинарного кода с указанием полного пути
    static int SaveTxtArrDoubleFile(AnsiString _fullFileName,AnsiString _str,double *_arr,int _arrSize);
	//разберем ошибку и запишем в предопределенный лог ошибок
	static int ErrFullSaveLog(Exception *_ex);
	//запись в текстовый файл
	static int SaveTxtVectDoubleFile(AnsiString _fullFileName,   vector<double>& _vectorData , int _vectSize);
	//запись в текствой файл в столбцы с разделителями по количеству каналов
	static int SaveChTxtDoubleFile(AnsiString _fullFileName, double *_data,int _dataSize,int _countCh);
	static int Save123TxtVectDoubleFile(AnsiString _fullFileName, vector<double> &_vectorData);
	static int SaveNEWTxtVectDoubleFile(AnsiString _fullFileName, vector<double> &_vectorData, int _vectSize);
	static int LoadTxtChDoubleFile(AnsiString _fullFileName, TLCardData *_lCardData, int _frec,int _countCh);
	// загрузить из бинарника с метками
	int LoadTubeFromFileBin(AnsiString _fullFileName,int _countZonesAll,int _wdFirstSensorsThick,int _wdCountSensorsThick,
	  int _wdFirstSensorsCross,int _wdCountSensorsCross,int _wdFullSensorSize,int _wdCountLOGchX502);
private:
	ofstream Log;
};

// для сохранения и загрузки настроек из INI
//не используется, заготовка
class TSettingsINI {
public:

	TSettingsINI();
	~TSettingsINI();
	bool loadSettingsINI();
	bool saveSettingsINI();

private:
	AnsiString applPath;
	TIniFile *Ini;
};

#endif
