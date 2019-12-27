// ------	---------------------------------------------------------------------
#pragma hdrstop
#include "TSGCoords.h"
#include "TProtocol.h"
#include <algorithm>
#include <Math.hpp>

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
//TSGCoords::TSGCoords(TIniFile* _ini)
TSGCoords::TSGCoords()
{
	//ini = _ini;
	Load();
	for (unsigned int i = 0; i < thresholds.size(); i++)
		TProtocol::ProtocolSave(AnsiString("thresholds=") + thresholds[i]);
	/*
	 std::sort(thresholds.begin(),thresholds.end(),);
	 for(int i=0;i<thresholds.size();i++)
	 TPr::pr(AnsiString("thresholds=")+thresholds[i]);
	 */
}
TSGCoords::~TSGCoords(void)
{
//
}
// ---------------------------------------------------------------------------
void TSGCoords::Load(void)
{
	//todo ну блииин! брать из БД
	thresholds.resize(0);
	//thresholdCount = ini->ReadInteger("default","ThresholdCount",8);
	thresholdCount=8;
	//AnsiString sect = "Type_" + ini->ReadString("Default", "TypeSize", "1");
	AnsiString sect ="1";
	for (int i = 0; i < thresholdCount; i++){
		//thresholds.push_back(ini->ReadFloat(sect, "Threshold_" + String(i), 2.5));
		thresholds.push_back(2.5);
    }
	//int SGI_period = ini->ReadInteger("OtherSettings", "SGI_period", 100);
	int SGI_period = 100;
	//int SGI_period_dif = ini->ReadInteger("OtherSettings", "SGI_period_dif", 10);
	int SGI_period_dif = 10;
	//ByU=ini->ReadBool("OtherSettings", "SGI_by_U", false);
	ByU=false;
	periodMin = SGI_period - SGI_period_dif;
	periodMax = SGI_period + SGI_period_dif;
	thresh.resize(thresholds.size());
	for (unsigned int i = 0; i < thresholds.size(); i++)
	{
		double v = SGI_period;
		v /= 100;
		v *= thresholds[i];
		thresh[i] = (int)v;
		AnsiString a="thresh[";
		a+=i;
		a+="]=";
		a+=thresh[i];
		TProtocol::ProtocolSave(a);
	}
}

// ---------------------------------------------------------------------------
void TSGCoords::Save(void)
{
	//todo переделать для БД!
	//AnsiString sect = "Type_" + ini->ReadString("Default", "TypeSize", "1");
	AnsiString sect="1";
//	for (int i = 0; i < thresholdCount; i++)
//		ini->WriteFloat(sect, "Threshold_" + String(i), thresholds[i]);
}

// ---------------------------------------------------------------------------
vector<double>TSGCoords::coordsFromSignal(vector<vector<double> >& _sourceSignals)
{
	vector<double>ret_coords;
	vector<double>_coords;
	vector<int>quantity;

	if (_sourceSignals.size() != 5)
	{
		TProtocol::ProtocolSave("Ошибка: Собрали не 5 массивов данных!");
		return (ret_coords);
	}
	if (_sourceSignals[0].size() < 100)
	{
		TProtocol::ProtocolSave("Размер массива по ГП <100");
		return (ret_coords);
	}
	const int threshold = 30;
	TProtocol::ProtocolSave("Размер массива по ГП: " + IntToStr((int)_sourceSignals[0].size()));

	for (int step = 0; step < thresholdCount; ++step)
	{
		_coords.push_back(0.0);
		quantity.push_back(0);
	}

	// ! вектор из N векторов, характеризующих все точки данного порога магнитного сигнала
	vector<vector<double> >parameters;
	parameters.resize(thresholdCount);
	// проверяем на принадлежность к только нужному (текущему) порогу
	int th = 0;
	for (unsigned int i = 0; i < _sourceSignals[0].size() - 1; i++)
	{
		double magnetic = _sourceSignals[1][i];
		double current = _sourceSignals[0][i];
		double next_cur = _sourceSignals[0][i + 1];

		if (current >= thresholds[th] && next_cur < thresholds[th] && magnetic < 0) // фильтр!
		{ // здесь все правильно!! работает! не изменять - руки оторву!
			// в условии можно менять только ЗНАК у magnetiс - если надо считывать нижнюю полуплоскоть сигнала
			parameters[th].push_back(magnetic);
			th++;
		}
		if (th == thresholdCount)
			th = 0;
	}

	// выделяем из выбранных значений только нужные - отсекаем 1/8 с начала и с конца
	int trash = parameters[0].size() / 8;
	TProtocol::ProtocolSave("Размер параметров по ГП: " + IntToStr((int)parameters[0].size()));
	TProtocol::ProtocolSave("Размер отсеченного: " + IntToStr((int)trash));
	if (parameters[0].size())
	{
		for (unsigned int i = 0; i < parameters.size(); i++)
		{
			for (unsigned int j = trash; j < parameters[i].size() - trash; j++)
			{
				_coords[i] += parameters[i][j];
				quantity[i]++;
			}
		}
		for (int i = 0; i < thresholdCount; i++)
			ret_coords.push_back((double)(_coords[i] / quantity[i]));
	}
	else
	{
		for (int i = 0; i < thresholdCount; i++)
			ret_coords.push_back((double)1.5);
	}
	for (unsigned int i = 0; i < ret_coords.size(); i++)
	{
		if (IsNan(ret_coords[i]))
			ret_coords[i] = 0;
	}
	return ret_coords;
}

// ---------------------------------------------------------------------------
vector<vector<SGPoint> >TSGCoords::GetPoints(vector<IU>& _SignalIU)
{
	vector<vector<SGPoint> >points;
	points.resize(thresholds.size());

	int start_period = 0;
	int size_period = 0;
	for(;;)
	{
		bool ok;
		if(ByU)
			ok=GetNextPeriodU(_SignalIU, &start_period, &size_period);
		else
			ok=GetNextPeriodI(_SignalIU, &start_period, &size_period);
		if(!ok)
			break;
		AnsiString a;
		a+="start=";
		a+=start_period;
		a+=" size=";
		a+=size_period;
		TProtocol::ProtocolSave(a);
		for (unsigned int i = 0; i < points.size(); i++)
		{
			IU& iu = _SignalIU[start_period + thresh[i]];
			SGPoint sgPoint;
//			sgPoint.I = iu.I;
//			sgPoint.U = iu.U;
			sgPoint.Measure1 = iu.Measure1;
			sgPoint.Measure2 = iu.Measure2;
			sgPoint.index = start_period + thresh[i];
			points[i].push_back(sgPoint);
		}
	}
	return (points);
}

// ---------------------------------------------------------------------------
vector<double>TSGCoords::GetCoords(vector<IU>& _SignalIU)
{
	vector<vector<SGPoint> >sgPoints = GetPoints(_SignalIU);
	return (GetCoords(sgPoints));
}
// ---------------------------------------------------------------------------
vector<double>TSGCoords::GetCoords(vector<vector<SGPoint> >& _sgPoints)
{
	vector<double>coords;
	coords.resize(_sgPoints.size());
	for (unsigned int i = 0; i < coords.size(); i++)
	{
		coords[i] = 0;
		for (unsigned int j = 0; j < _sgPoints[i].size(); j++)
//			coords[i] += _sgPoints[i][j].U;
			coords[i] += _sgPoints[i][j].Measure2; //todo достаточно?
		coords[i] /= _sgPoints[i].size();
	}
	return (coords);
}
// ---------------------------------------------------------------------------
bool TSGCoords::GetNextPeriodI(vector<IU>& _SignalIU, int* _start, int* _size)
{
	*_start += *_size + 1;
	for (; *_start < (int)_SignalIU.size(); (*_start)++)
	{
//		if (_SignalIU[*_start].I < 0)
		if (_SignalIU[*_start].Measure1 < 0)       //todo этот сигнал?
		{
			int size = GetNextSizeI(_SignalIU, _start);
			if (size >= 0)
			{
				*_size = size;
				return (true);
			}
		}
	}
	return (false);
}

// ---------------------------------------------------------------------------
int TSGCoords::GetNextSizeI(vector<IU>& _SignalIU, int* _start)
{
	int size = 0;
	for (int i = *_start; i < (int)_SignalIU.size(); i++)
	{
//		if (_SignalIU[i].I < 0)
		if (_SignalIU[i].Measure1 < 0)       //todo этот сигнал?
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}

// ---------------------------------------------------------------------------
bool TSGCoords::GetNextPeriodU(vector<IU>& _SignalIU, int* _start, int* _size)
{
	*_start += *_size + 1;
	for (; *_start < (int)_SignalIU.size(); (*_start)++)
	{
//		if (_SignalIU[*_start].U > 0)
		if (_SignalIU[*_start].Measure2 > 0)
		{
			int size = GetNextSizeU(_SignalIU, _start);
			if (size >= 0)
			{
				*_size = size;
				return (true);
			}
		}
	}
	return (false);
}

// ---------------------------------------------------------------------------
int TSGCoords::GetNextSizeU(vector<IU>& _SignalIU, int* _start)
{
	int size = 0;
	for (int i = *_start; i < (int)_SignalIU.size(); i++)
	{
//		if (_SignalIU[i].U > 0)
		if (_SignalIU[i].Measure2 > 0)
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}
// ---------------------------------------------------------------------------
vector<IU>TSGCoords::Convert(vector<vector<double> >& _sourceSignals)
{
	vector<IU>ret;
	ret.resize(_sourceSignals[0].size());
	for (unsigned int i = 0; i < ret.size(); i++)
	{
//		ret[i].I = _sourceSignals[0][i];
//		ret[i].U = _sourceSignals[1][i];
		ret[i].Measure1 = _sourceSignals[0][i];
		ret[i].Measure2 = _sourceSignals[1][i];
	}
	return (ret);
}
// ---------------------------------------------------------------------------
void TSGCoords::SaveToProtocol(AnsiString _msg)
{
	TProtocol::ProtocolSave(_msg);
}
// ---------------------------------------------------------------------------

