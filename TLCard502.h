// ---------------------------------------------------------------------------
#ifndef TLCard502H
#define TLCard502H
//#include "RLCard_parameters.h"
#include "TLogCh502Params.h"
#include "x502api.h"
#include <E502api.h>
#include "TGlobalSettings.h"
#include <vector>
#pragma comment(lib, "l502api.lib")
#define LCard502_INIT_SIZE 2000
#define LCard502_ADD_PERCENT 50
using namespace std;
// ---------------------------------------------------------------------------
class TLCard502
{
private:
	// ! Хендл платы
	t_x502_hnd handle;
	int raw_size;
	unsigned int* rawi;
	double* raw;
	double* rawc;
	bool IsStarted;
	// ! ТаймАут для сбора (с каким периодом будем скидывать данные из ацп в большой буфер,мс)
//	int RECV_TOUT;
//	int MainSensors;
//	int OtherSensors;
	t_x502_serial_list listCards;
	void SetRawSize(int _size);
	void LFATAL(AnsiString _msg, int _err);
	bool CheckError(int _err);
//	void LoadMainSettings();

//	RLCard_parameters* Parameters;

public:
	//текст ошибки
	AnsiString LastError;

	//Конструктор и открытие платы
	TLCard502(TGlobalSettings* _mainGlobalSettings,int &_codeErr);
	//Деструктор и закрытие платы
	~TLCard502(void);
	//Старт платы
	void Start(void);
	//Остановка платы
	void Stop(void);
	//Читаем данные с платы
	double* Read(int* _size);
	//Получить значение с канала
	double GetValue(int _ch);

	// Читает настройки и вбивает в плату
	void LoadAndSetSettings(vector<TLogCh502Params>& _logChannels);

	inline double* GetRawC(void)
	{
		return(rawc);
	}


	//-----------------------------------------

	// ! ТаймАут для сбора (с каким периодом будем скидывать данные из ацп в большой буфер,мс)
	int RECV_TOUT;
	// ! @brief Режим синхронизации
	// ! @li 0 Внутренний сигнал
	// ! @li 1 От внешнего мастера по разъему синхронизации
	// ! @li 2 По фронту сигнала DI_SYN1
	// ! @li 3 По фронту сигнала DI_SYN2
	// ! @li 6 По спаду сигнала DI_SYN1
	// ! @li 7 По спаду сигнала DI_SYN2
	uint32_t syncMode;
	// ! Источник запуска синхронного ввода/вывода см. режимы @link syncMode
	uint32_t syncStartMode;
	// ! Частота на канал (Гц.)
	double frequencyPerChannel_Hz;
	//количество задействованых каналов
	int	countLogCh;
	//указатель на настройки
	TGlobalSettings* globalSettings;

	// ! Возвращает кол-во используемых каналов
	int getCountChannels()
	{
		return vecLogChannels.size();// + others.size();
	}

	// ! Индивидуальные настройки для каждого канала
	vector<TLogCh502Params> vecLogChannels;
	// ! @brief Дополнительные каналы
	// ! @li 0 - Ток продольный соленоид
	// ! @li 1 - Напряжение продольный соленоид
	// ! @li 2 - Ток поперечный соленоид
	// ! @li 3 - Напряжение поперечный соленоид
	// ! @li 4 - Ток группы прочности
	// ! @li 5 - Напряжение группы прочности
	// ! @li 6 - Разделение по зонам
//	vector<TLogCh502Params> others;

//	int LSensors;
//	int CSensors;
//	int GSensors;
//	int OSensors;

//	void LoadSettings(void);
//	void SaveSettings(void);

	TLogCh502Params* FindChByName(AnsiString _name);
	int FindPosByName(AnsiString _name);
};
#endif
