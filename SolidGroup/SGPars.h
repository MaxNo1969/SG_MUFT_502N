//---------------------------------------------------------------------------

#ifndef SGParsH
#define SGParsH
#include<system.hpp>
//#include "uCExecSQL.h"
//class AlgorithmPointsConverter : StringConverter
//{
//	public override bool GetStandardValuesSupported(ITypeDescriptorContext context) { return true; }
//	public override bool GetStandardValuesExclusive(ITypeDescriptorContext context) { return true; }
//	public override StandardValuesCollection GetStandardValues(
//	  ITypeDescriptorContext context)
//	{
//		List<string> L = new List<string>();
//		L.Add("По току");
//		L.Add("По напряжению");
//		return (new StandardValuesCollection(L));
//	}
//}
//
//class AlgorithmSGConverter : StringConverter
//{
//	public override bool GetStandardValuesSupported(ITypeDescriptorContext context) { return true; }
//	public override bool GetStandardValuesExclusive(ITypeDescriptorContext context) { return true; }
//	public override StandardValuesCollection GetStandardValues(
//	  ITypeDescriptorContext context)
//	{
//		List<string> L = new List<string>();
//		L.Add("Корреляция");
//		L.Add("Расстояние");
//		L.Add("Вероятность");
//		return (new StandardValuesCollection(L));
//	}
//}
//---------------------------------------------------------------------------
class SGPars
{
private:
	AnsiString schema;
	int halfPeriod;
	int halfPeriodDif;
	int borderBegin;
	int borderEnd;
	AnsiString algorithmPoints;
	AnsiString algorithmSG;
	int veracity;
	int tubeCount; //макс число труб в базе
public:
	SGPars(AnsiString _schema);
	int GetHalfPeriod();
	void SetHalfPeriod(int value);
	int GetHalfPeriodDif();
	void SetHalfPeriodDif(int value);
	int GetBorderBegin();
	void SetborderBegin(int value);
	int GetBorderEnd();
	void SetBorderEnd(int value);
	AnsiString GetAlgorithmPoints();
	void SetAlgorithmPoints(AnsiString value);
	AnsiString GetAlgorithmSG();
	void SetAlgorithmSG(AnsiString value);
	int GetVeracity();
	void SetVeracity(int value);
	int GetTubeCount();
	void SetTubeCount(int value);
};

#endif
