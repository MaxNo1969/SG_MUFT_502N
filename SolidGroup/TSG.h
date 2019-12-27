//---------------------------------------------------------------------------
#ifndef TSGH
#define TSGH
#include<system.hpp>
//#include <IniFiles.hpp>
#include <vector>
#include <Graphics.hpp>
#include "CSG.h"
#include "IU.h"
//
#include "TGlobalSettings.h"
#include "TLCardData.h"
#include "unTUtils.h"
using namespace std;
//---------------------------------------------------------------------------
class TSG
{
public:
	//класс для группы прочности -  обсчет и вывод результата
	TSG(TGlobalSettings* _mainGlobalSettings,TLCardData* _sgLCardData);
	~TSG(void);
	int Exec(int _freqNum);
	CSG csg;
	// считаем ГП по всем частотам
	CSG GetSG();
    // считаем ГП по первой частоте
	CSG Get1FrecSG();
	inline void ResetState(void){
		state=0;
	}
private:
	int state;
	int freqNum;   //номер текущей частоты генератора

	void pr(AnsiString _msg);
	void pr0(AnsiString _msg);

	AnsiString SGroupFix;
	TColor conv_color(int _col);
	DWORD startTime;
	//--------
	TGlobalSettings* sgGlobalSettings;
	TLCardData* sgLCardData;
};
//---------------------------------------------------------------------------
#endif
