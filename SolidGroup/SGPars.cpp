//---------------------------------------------------------------------------


#pragma hdrstop

#include "SGPars.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


SGPars::SGPars(AnsiString _schema)
{
	halfPeriod = 600;
	halfPeriodDif = 40;
	borderBegin = 15;
	borderEnd = 15;
	algorithmPoints = "По току";
	algorithmSG = "Корреляция";
	veracity = 75;
	tubeCount = 50; //макс число труб в базе
	schema = _schema;

	AnsiString SQL = "select * from Uran.SGPars";
//	//CSelect S(SQL);
//	if (S.IsOk()!="Ok")
//		FATAL("SGPars::SGPars: не могу получить параметры");
//	halfPeriod = S.AsInt("period");
//	halfPeriodDif = S.AsInt("period_dif");
//	borderBegin = S.AsInt("borders");
//	borderEnd = S.AsInt("borders1");
//	algorithmPoints = S.AsChar("algorithm");
//	algorithmSG = S.AsChar("pro");
//	veracity = S.AsInt("veracity");
//	tubeCount = S.AsInt("tubeCount");
}

int SGPars::GetHalfPeriod()
{
	return (halfPeriod);
}
void SGPars::SetHalfPeriod(int value)
{
	//CExecSQL("update Uran.SGPars set period="+ IntToStr(value));
	halfPeriod = value;
}

int SGPars::GetHalfPeriodDif()
{
	return (halfPeriodDif);
}
void SGPars::SetHalfPeriodDif(int value)
{
	//CExecSQL("update Uran.SGPars set period_dif="+ IntToStr(value));
	halfPeriodDif = value;
}

int SGPars::GetBorderBegin()
{
	return (borderBegin);
}
void SGPars::SetborderBegin(int value)
{
	//CExecSQL("update Uran.SGPars set borders="+ IntToStr(value));
	borderBegin = value;
}

int SGPars::GetBorderEnd()
{
	return (borderEnd);
}
void SGPars::SetBorderEnd(int value)
{
	//CExecSQL("update Uran.SGPars set borders1="+ IntToStr(value));
	borderEnd = value;
}

AnsiString SGPars::GetAlgorithmPoints()
{
	return (algorithmPoints);
}
void SGPars::SetAlgorithmPoints(AnsiString value)
{
	//CExecSQL("update Uran.SGPars set algorithm="+ value);
	algorithmPoints = value;
}

AnsiString SGPars::GetAlgorithmSG()
{
	return (algorithmSG);
}
void SGPars::SetAlgorithmSG(AnsiString value)
{
	//CExecSQL("update Uran.SGPars set pro="+ value);
	algorithmSG = value;
}

int SGPars::GetVeracity()
{
	return (veracity);
}
void SGPars::SetVeracity(int value)
{
	//CExecSQL("update Uran.SGPars set veracity="+ IntToStr(value));
	veracity = value;
}

int SGPars::GetTubeCount()
{
	return (tubeCount);
}
void SGPars::SetTubeCount(int value)
{
	//CExecSQL("update Uran.SGPars set tubeCount="+ IntToStr(value));
	tubeCount = value;
}

