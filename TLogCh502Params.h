#ifndef TLogCh502ParamsH
#define TLogCh502ParamsH

#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
//#include <IniFiles.hpp>
#include <vector>
//---------------------------------------------------------------------------
//параметры одного логического канала
//бывший RChannel_parameters
class TLogCh502Params
{
private:
	//TIniFile* ini;
	//AnsiString sect;
public:
	// Конструктор параметры одного логического канала
	TLogCh502Params();
	// деструктор
	~TLogCh502Params(void);
	// ! @brief Входной диапазон
	// ! @li 0 Диапазон +/-10V
	// ! @li 1 Диапазон +/-5V
	// ! @li 2 Диапазон +/-2.5V
	// ! @li 3 Диапазон +/-1.25V
	// ! @li 4 Диапазон +/-0.625V
	// ! @li 5 Диапазон +/-0.3125V
	//unsigned int adcRange;
	int adcRangeIndex;
	// ! Номер логического канала 0-31
	unsigned int logicalChannel;
//	unsigned int fizChannel;
	// ! @brief Режим сбора
	// ! @li 0 Измерение напряжения относительно общей земли
	// ! @li 1 Дифференциальное измерение напряжения
	// ! @li 2 Измерение собственного нуля
	unsigned int collectedMode;
	double chGain;
	AnsiString chName;
	AnsiString ToString(void);
};
//---------------------------------------------------------------------------
#endif
