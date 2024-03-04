#pragma hdrstop
#include "SignalListDef.h"
#pragma package(smart_init)
SignalListDef* SLD = NULL;

//SignalListDef::SignalListDef(TIniFile* _ini) : SignalList(_ini)
//ñïèñîê ñèãíàëîâ îò 1730
SignalListDef::SignalListDef() : SignalList()
{

	iCC = Find("ÖÅÏÈ ÓÏÐÀÂËÅÍÈß", true);
	iPOW12 = Find("ÏÈÒÀÍÈÅ 12Â", true);

	oSENSORON = Find("ÂÊË ÑÈËÎÂÎÅ", false);
	oSENSLOWPOW = Find("ÂÊË ÏÈÒÀÍÈÅ", false);
//	oRESERV1 = Find("ÐÅÇÅÐÂ 1", false);
	oRESERV2 = Find("ÐÅÇÅÐÂ 2", false);

}


bool SignalListDef::CheckAlarm(void)
{
	return (wasAlarm);
}

void SignalListDef::SetAlarm(bool _on)
{
	SetAlarm0(_on);
	cs->Enter();
	{
	} cs->Leave();
}

void SignalListDef::Drop(void)
{
//
}
