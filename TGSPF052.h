//---------------------------------------------------------------------------

#ifndef TGSPF052H
#define TGSPF052H
//---------------------------------------------------------------------------
#undef DEF_TGSPF052
#if DEF_TGSPF052
//#include <RshApi.h>

//#ifdef RSH_MSWINDOWS
//	#include <conio.h>
//#endif
//#include <iomanip>
#include <System.hpp>
#include "TGlobalSettings.h"
#include <RshApi.h>
#include "unTUtils.h"
#include "unTExtFunction.h"

//#include <RshApi.cpp>
//#include "Rsh.h"
//#include "RshTypes.h"
//#include "RshMacro.h"
//#include "RshConsts.h"
//#include "RshStatusCodes.h"
//#include "IRshFactory.h"
//#include "IRshDevice.h"
//#include "RshDllClient.h"
//#include "RshError.h"
//#include "RshEventManager.h"


//#include <IniFiles.hpp>
//================================Настройки==================================
class TGSPF052
{
public:
	// Инициализация платы
	//GSPF052(TIniFile* _ini);
	TGSPF052(TGlobalSettings* _globalSettings,int &_err);
    ~TGSPF052(void);
	// Формирование сигнала
	int FormSignal(int _valueFrec,double _valueAmpl);
	// Запускаем генерацию сигнала
	int StartGSPF052();
	// Ждем прерывания
	int WaitInterrupt();
	// Останавливаем генерацию сигнала
	int StopGSPF052();
	// Закрытие платы
	int CloseCard(AnsiString desc);
	bool isStartedGSPF052;
	// Вывод сообщения в протокол
	void toProtocol(AnsiString _msg);
	// Класс для загрузки библиотеки абстракции.
	RshDllClient* rshClient;
	// Обновление частоты дискретизации
	void SetSampleFreq(double _SampleFreq);
private:
	// Частота генерируемого синуса в Герцах
	double SignalFreq;
	// Амплитуда генерируемого синуса в вольтах
	double SignalAmplitude;
		// Частота дискретизации
	double SampleFreq;
	// Файл с настройками
	TGlobalSettings* gspfGlobalSettings;
	// Структура инициализации
	RshInitGSPF gspfPar;
	// Служебное имя устройства, с которым будет работать программа.
	char* BoardName;
	// Номер устройства. Если в системе установлено несколько одинаковых устройств, можно выбрать, к какому из них подключаться. Нумерация начинается с 1.
	U32 DeviceID;
	// Язык вывода ошибок. (В случае проблем с кодировкой выбирайте английский язык)
	RSH_LANGUAGE ErrorLanguage;
	//const RSH_LANGUAGE ErrorLanguage = RSH_LANGUAGE_ENGLISH;
	// 1МОм согласованная нагрузка. L Данная константа используется при расчете выходного напряжения генератора.
	double OutR;

	//Указатель на объект с интерфейсом IRshDevice, который используется для доступа к устройству.
	IRshDevice* rshDevice;
	// Максимальная амплитуда
	double DACMaxAmp;


//	static const AnsiString StringDelimiter = "----------";
//	static const AnsiString StringSuccess = "SUCCESS!";

};
//char* BoardName = "GSPF052PCI";
//double GSPF052::SampleFreq = 10000000.0;
//double GSPF052::SignalFreq = 1000.0;
//double GSPF052::SignalAmplitude = 1.0;
//double GSPF052::OutR = 1000000.0f;
#else
#include "Hantek1025G.h"
typedef Hantek1025G TGSPF052;
#endif
#endif
