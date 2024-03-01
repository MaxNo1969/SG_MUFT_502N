#pragma hdrstop
#include "TMeasuresData.h"

TMeasuresData::TMeasuresData(int _chLogCount) {
	// создаем вектор датчиков
	vecSensorsData.reserve(_chLogCount);
	// цепляем датчики
	for (int s = 0; s < _chLogCount; s++) {
		vector<double> vecTMP;
		vecSensorsData.push_back(vecTMP);
	}
}

TMeasuresData::~TMeasuresData(void) {
	// чистим вектора
	int sz = vecSensorsData.size();
	for (int s = 0; s < sz; s++) {
		vecSensorsData[s].clear();
	}
	vecSensorsData.clear();
}

int TMeasuresData::ClearData(void) {
	int sz = vecSensorsData.size();
	for (int s = 0; s < sz; s++)
	{
		vecSensorsData[s].clear();
	}
}
