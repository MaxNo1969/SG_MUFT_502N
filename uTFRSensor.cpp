// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSensor.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
//#include "TLogCh502Params.h"
#include "unTExtFunction.h"
TFRSensor *FRSensor;

// ---------------------------------------------------------------------------
__fastcall TFRSensor::TFRSensor(TComponent* Owner,TLogCh502Params* _ch_par,AnsiString _title) : TFrame(Owner)
{   if (!_ch_par) {
	  TExtFunction::ShowBigModalMessage("Канал "+_title+" не найден!!!",clRed);
	  return;
	}else{

    }
	ch_par=_ch_par;
	LName->Caption=_title;
	//±10 ±5 ±2.5 ±1.25 ±0.625 ±0.3125
	CBRange->ItemIndex=ch_par->adcRangeIndex;
	SEChannel->Value=ch_par->logicalChannel;
	CBMode->ItemIndex=ch_par->collectedMode;
	SetEnabledR(false);
}

// ---------------------------------------------------------------------------
void TFRSensor::SetEnabledR(bool _v)
{
	SEChannel->Enabled = _v;
	CBRange->Enabled = _v;
	CBMode->Enabled = _v;
}

// ---------------------------------------------------------------------------
void TFRSensor::SaveSettings(void)
{   //выдираем параметры из фреймов бред какой-то
AnsiString strWhere="";
	ch_par->logicalChannel=SEChannel->Value;
	//strWhere="numLogCh="+IntToStr((int)ch_par->logicalChannel);
	strWhere = "chName='" + ch_par->chName + "'";
	SqlDBModule->UpdIntSql("L502ChParams","numLogCh",ch_par->logicalChannel,strWhere);
	ch_par->adcRangeIndex=CBRange->ItemIndex;
	SqlDBModule->UpdIntSql("L502ChParams","adcRangeIndex",ch_par->adcRangeIndex,strWhere);
	ch_par->collectedMode=CBMode->ItemIndex;
	SqlDBModule->UpdIntSql("L502ChParams","collectedMode",ch_par->collectedMode,strWhere);
}
// ---------------------------------------------------------------------------




