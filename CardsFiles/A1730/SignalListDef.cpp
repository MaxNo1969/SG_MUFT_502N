#pragma hdrstop
#include "SignalListDef.h"
#pragma package(smart_init)
SignalListDef* SLD = NULL;

//SignalListDef::SignalListDef(TIniFile* _ini) : SignalList(_ini)
//������ �������� �� 1730
SignalListDef::SignalListDef() : SignalList()
{

	iCC = Find("���� ����������", true);
	iPOW12 = Find("������� 12�", true);

	oSENSORON = Find("��� �������", false);
	oSENSLOWPOW = Find("��� �������", false);
//	oRESERV1 = Find("������ 1", false);
	oRESERV2 = Find("������ 2", false);

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
