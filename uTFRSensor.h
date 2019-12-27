//---------------------------------------------------------------------------

#ifndef uTFRSensorH
#define uTFRSensorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//#include "RChannel_parameters.h"
#include "TLogCh502Params.h"
#include "unSQLDbModule.h"
#include "cspin.h"
//---------------------------------------------------------------------------
class TFRSensor : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LName;
	TComboBox *CBRange;
	TCSpinEdit *SEChannel;
	TComboBox *CBMode;
private:	// User declarations
	//TIniFile* ini;
	int GetRange(void);
	int GetChannel(void);
	int GetMode(void);
	TLogCh502Params* ch_par;
public:		// User declarations
	__fastcall TFRSensor(TComponent* Owner,TLogCh502Params* _ch_par,AnsiString _title);
	void SetEnabledR(bool _v);
	void SaveSettings(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSensor *FRSensor;
//---------------------------------------------------------------------------
#endif
