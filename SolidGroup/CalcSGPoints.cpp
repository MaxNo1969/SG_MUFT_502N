//---------------------------------------------------------------------------


#pragma hdrstop

#include "CalcSGPoints.h"
#include <ctime.h>
#include <Math.hpp>
//---------------------------------------------------------------------------
#ifdef BERLIN_10
//
#else
  #pragma package(smart_init)
#endif

CalcSGPoints::CalcSGPoints(vector <IU> _iu, vector <int> _treshP, SGPars _sgpars, AnsiString _sop)
{
	points = NULL;
	ByU = false;
	iu = _iu;
//	if (_sop == "Мертвые зоны")
//	{
	double vv = iu.size();
	vv /= 100;
	vv *= _sgpars.GetBorderBegin();
	Start = (int)vv;
	vv = iu.size();
	vv /= 100;
	vv *= _sgpars.GetBorderEnd();
	Stop = iu.size() - (int)vv;
//	}
//	else
//	{
//		SOP sop = _sgpars.GetSOP(_sop);
//		if (sop == null)
//			FN.fatal("CalcSGPoints:CalcSGPoints: СОП не найден: " + _sop);
//		if (sop.Length <= 0)
//		{
//			Start = 0;
//			Stop = iu.Length;
//		}
//		else
//		{
//			double per_mm = iu.Length;
//			per_mm /= sop.Length;
//			double vv = sop.BeginPoint;
//			vv *= per_mm;
//			Start = Convert.ToInt32(vv);
//			vv = sop.EndPoint;
//			vv *= per_mm;
//			Stop = Convert.ToInt32(vv);
//			if (Start < 0)
//				Start = 0;
//			if (Stop < Start)
//				Stop = Start;
//			if (Stop > iu.Length - 1)
//				Stop = iu.Length - 1;
//		}
//	}
	TDateTime dt0 = Now();
	ByU = _sgpars.GetAlgorithmPoints() == "По напряжению";
	vector<int> tresh = *new vector<int>();
	int newSize = _treshP.size();
	tresh.resize(newSize);
	coords = new double[newSize];
	for (int i = 0; i < newSize; i++)
	{
		double v = _treshP[i];
		v /= 100;
		v *= _sgpars.GetHalfPeriod();
		tresh[i]=(int)v;
		coords[i] = 0;
	}
	periodMin = _sgpars.GetHalfPeriod() - _sgpars.GetHalfPeriodDif();
	if (periodMin < 0)
		periodMin = 0;
	periodMax = _sgpars.GetHalfPeriod() + _sgpars.GetHalfPeriodDif();
	L = *new CRListT<int>();
	//            L.Capacity = 200000;

	int start_period = Start;
	int size_period = 0;
	double nn = 0;
	for (; ; )
	{
		bool ok;
		if (ByU)
			ok = GetNextPeriodU(start_period, size_period);
		else
			ok = GetNextPeriodI(start_period, size_period);
		if (!ok)
			break;
		for (int i = 0; i < newSize; i++)
		{
			int *sum = L.Add();
			*sum = start_period + tresh[i];
			//L.Add(sum);
			coords[i] += iu[start_period + tresh[i]].Measure2;
		}
		nn++;
	}
	for (int i = 0; i < newSize; i++)
	{
		coords[i] /= nn;
		if (IsNan(coords[i]))
			coords[i] = 0;
	}
	points = new int[L.Count()];
	for (int i = 0; i < L.Count(); i++)
		points[i] = *L[i];
	TDateTime dt1 = Now();
	int ms = (dt1 - dt0);//.Milliseconds;
}
bool CalcSGPoints::GetNextPeriodI(int _start, int _size)    //todo вернуть новые значения
{
	_start += _size + 1;
	bool last = true;
	for (; _start < Stop; _start++)
	{
		if (iu[_start].Measure1 < 0)
		{
			if (last == false)
			{
				int size = GetNextSizeI(_start);
				if (size >= 0)
				{
					_size = size;
					return (true);
				}
			}
			last = true;
		}
		else
			last = false;
	}
	return (false);
}
bool CalcSGPoints::GetNextPeriodU(int _start, int _size)  //todo вернуть новые значения
{
	_start += _size + 1;
	bool last = true;
	for (; _start < Stop; _start++)
	{
		if (iu[_start].Measure2 > 0)
		{
			if (last == false)
			{
				int size = GetNextSizeU(_start);
				if (size >= 0)
				{
					_size = size;
					return (true);
				}
				last = true;
			}
		}
		else
			last = false;
	}
	return (false);
}
int CalcSGPoints::GetNextSizeI(int _start)
{
	int size = 0;
	for (int i = _start; i < Stop; i++)
	{
		if (iu[i].Measure1 < 0)
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}
int CalcSGPoints::GetNextSizeU(int _start)
{
	int size = 0;
	for (int i = _start; i < Stop; i++)
	{
		if (iu[i].Measure2 > 0)
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}

