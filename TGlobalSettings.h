// ---------------------------------------------------------------------------

#ifndef TGlobalSettingsH
#define TGlobalSettingsH
// ---------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
// -----------
// #include <Controls.hpp>
// #include <Classes.hpp>
// #include <ExtCtrls.hpp>
// #include <StdCtrls.hpp>
// ---------

// ----------------
class TGlobalSettings {
public:
	TGlobalSettings();
	~TGlobalSettings(void);
	// ------------
	bool isFilter;
	int filterCurrentType;
	int filterCurrentSubType;
	int filterOrder;
	double filterCutoffFrequency;
	double filterCenterFrequency;
	double filterWidthFrequency;
	double filterRippleDb;
	double filterRolloff;
	double filterSampleRate;
	// ----------
	AnsiString applPath;
	AnsiString currentTypeSize;
	AnsiString nameCurrentTypeSize;
	int indexCurrentTypeSize; //индекс текущего типоразмера
	int indexCurrentSGGost; //индекс текущего ГОСТа ГП
	int protocolInterval;
	int protocolToFile;
	int protocolVisible;
	int zeroTransitionChannel; //канал для синхронизации по переходу через 0
	int checkMuftaLevel; //уровень сигнала наличия муфты
	int checkMuftaChannel; //канал сигнала наличия муфты
	int calcSGMode; //режим расчета вероятности ГП

	int workStatus; // статус состояния модуля
	// <0 останов по ошибке
	// 0 режим ожидания
	// 1 режим измерений
	// 3 завершение полного цикла
	unsigned int thresholdMaxCount; //максимальное число порогов
//	unsigned int CurrThresholdCount; //текущее число порогов
	unsigned int SinusFrequenciesMaxCount; //максимальное число частот
//	unsigned int CurrSinusFrequenciesCount; //текущее число частот
	// ------------------- функции
	int LoadPRGSettings(AnsiString _fullPathNameUDL);
	// -----------
	//частота дискретизации генератора
	int discrFrecGSPF;
	//текущий типоразмер
	int currTypeSize;
	//номер сообщения о готовности тестовых данных
	unsigned int WM_MsgReadyTstData;
	//сообщения потока
	unsigned int WM_MsgThread;
	// указатель на экземпляр класса обработчика данных
	// TWorkData* gsWorkData;
	// int countLOGchX502; // число лог используемых каналов АЦП
	// цветов
	enum LinesColor {
		Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8, LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12,
		LightMagenta = 13, Yellow = 14, White = 15
	};
	//главное окошко и сообщения потока
	UINT threadMsg;
	HWND mainHandle;
	AnsiString SaveEtalonPath;
	AnsiString SaveResultPath;
	bool isWork;

	//Флаг эмуляции L502
	bool bL502Emul;
private:
	//
	};
#endif
