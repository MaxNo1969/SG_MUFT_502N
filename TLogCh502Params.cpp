#pragma hdrstop
#include "TLogCh502Params.h"
#include "TProtocol.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
TLogCh502Params::TLogCh502Params()
{
	chName="";
	logicalChannel=0;
	collectedMode=0;
	adcRangeIndex=0;
	//adcRange=0;
	chGain=1;
}
TLogCh502Params::~TLogCh502Params(void)
{
//
}
// ---------------------------------------------------------------------------
AnsiString TLogCh502Params::ToString(void)
{
	AnsiString ret=chName;
	ret+=":  ch=";
	ret+=UIntToStr(logicalChannel);
	ret+=",mode=";
	ret+=UIntToStr(collectedMode);
	ret+=",range=";
	ret+=IntToStr(adcRangeIndex);
	return(ret);
}
// ---------------------------------------------------------------------------


