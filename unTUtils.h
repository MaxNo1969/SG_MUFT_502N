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
	static int SaveChTxtDoubleFile(AnsiString _fullFileName, double *_data,int _dataSize,int _countCh);
	static int LoadTxtChDoubleFile(AnsiString _fullFileName, TLCardData *_lCardData, int _frec,int _countCh);
private:
	ofstream Log;
};
#endif
