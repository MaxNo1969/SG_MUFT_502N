#ifndef ThreadWorkH
#define ThreadWorkH
// #include <IniFiles.hpp>
#include <Graphics.hpp>
#include "TSG.h"
#include <SyncObjs.hpp>
#include "TGlobalSettings.h"
#include "TGSPF052.h"
#include "TLCardData.h"

class ThreadWork : public TThread {
protected:
	void __fastcall Execute();
	  bool exitLoop;
public:
	// изменено
	// __fastcall ThreadWork(TIniFile* _ini, AnsiString _SGFix, TLCardData* _lCardData);
	__fastcall ThreadWork(bool _createSuspended, TLCardData* _lCardData,TGlobalSettings* _globalSettings, TGSPF052* _gen);
	__fastcall ~ThreadWork(void);
	static const WPARAM REDRAW = 0;
	static const WPARAM COMPUTE = 1;
	static const WPARAM UPDATE_STATUS = 3;
	static const WPARAM COMPLETE = 5;
	static const WPARAM NEXT_MUFT = 6;
    bool TestExitLoop();
	AnsiString GetStext1(void);
	AnsiString GetStext2(void);
	// Установить указанный результат расчета //todo а нужно ли?
	void SetCalc(); // (bool _IsBrak);
	bool BoolExitLoop();
	// Возвращает текущую группу прочности
	CSG GetSG(void);
	// ---------------
private:
	int pauseWorkSpeed;
	int pauseStop;
    bool createSuspended;
	bool stopThread; // запрос на останов (устанавливается из основного потока либо ставится при ошибке
	// ! текст для надписи в статусбаре в панели 1
	AnsiString stext1;
	// ! Текст для надписи в статусбаре в панели 2
	AnsiString stext2;
	int delay;
	bool Collect;
	TCriticalSection* cs;
	// Класс обсчета группы прочности
	TSG* solidGroup;
	//настройки
	TGlobalSettings* thGlobalSettings;
	//данные измерений
	TLCardData* lCardData;
	// Плата генератора сигнала
	TGSPF052* GSPF;
	bool gspfStart;
	//параметры канала
//	TLogCh502Params* lCard_parameters;
	void SetStext1(AnsiString _s);
	void SetStext2(AnsiString _s);
	TEvent* calc_event;
	// запись в протокол
	void pr(AnsiString _msg);
	// Запись данных по муфте в БД для статистики
	void SaveMuftToDB();
	inline int ThreadRun(AnsiString &_msgErr);
	// подгруппа прочности с цветом
	CSG csg;
	// Установить указанную группу прочности
	void SetSG(CSG _csg);
	// ! Поток обработки всей кучи информации
	bool OnlineCycle(void);
	// ! Выставляем исходное положение модулей перед работой
	UnicodeString PrepareForWork();
	// проверка наличия муфты. Возвращает true если за указанное время статус изменился на ожидаемый
	bool CheckMufta(bool _waitStatus, int _waitTime);
	// ! Финальные штуки (отключение сигналов и т.д.)
	void Finally();
	void ErrFinally(AnsiString _msg, bool* _Collect, bool* _result);
	void Post(WPARAM _w, LPARAM _l = 0);
    void __fastcall MainRedraw();

};
// ---------------------------------------------------------------------------

#endif
