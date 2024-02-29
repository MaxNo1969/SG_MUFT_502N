// ---------------------------------------------------------------------------
#pragma hdrstop

   #include <VCLTee.Chart.hpp>
   #include <VCLTee.Series.hpp>


#include "Filters.h"
#include "TProtocol.h"
#include "unSQLDbModule.h"
#include "unTExtFunction.h"

// ------------------------------------------------------------------------------
Filters *SGFilter;

Filters::Filters(AnsiString _type) {
	try {
		type = _type;
		dllInstance = LoadLibrary(L"filters.dll");

		if (!dllInstance) {
			String strError = L"Не удалось загрузить библиотеку фильтров";
			TExtFunction::FATAL("Не удалось загрузить библиотеку фильтров");
		}
		else {
			filter_chebyshev = (_ChebyshevI) GetProcAddress(dllInstance,
				"ChebyshevI");
			filter_butterworth = (_Butterworth) GetProcAddress(dllInstance,
				"Butterworth");
			filter_elliptic = (_Elliptic) GetProcAddress(dllInstance,
				"Elliptic");
			setSettingsFromDB();
		}
	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave("Filters::Filters: "+ex->Message);
		TExtFunction::FATAL(ex->Message);
	}
}

void Filters::toFilter(double *data, int N) {
	switch (settings.CurrentType) {
	case 0: {
			filter_butterworth(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.CurrentSubType);
			break;
		}
	case 1: {
			filter_chebyshev(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.rippleDb,
				settings.CurrentSubType);
			break;
		}
	case 2: {
			filter_elliptic(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.rippleDb, settings.rolloff,
				settings.CurrentSubType);
			break;
		}
	}
}

void Filters::setSettingsFromDB() {
	SqlDBModule->ADOQueryDB->Close();
	AnsiString sql =
		"SELECT filterCurrentType,filterCurrentSubType,filterOrder,filterCutoffFrequency,filterWidthFrequency,";
	sql += " filterCenterFrequency,filterRippleDb,filterRolloff,filterSampleRate,isFilter FROM SettingsGlobal";
	SqlDBModule->ADOQueryDB->SQL->Text = sql;
	SqlDBModule->ADOQueryDB->Open();
	settings.CurrentType = (filterTypes)SqlDBModule->ADOQueryDB->FieldByName("filterCurrentType")->AsInteger;
	settings.CurrentSubType =(filterSubTypes)SqlDBModule->ADOQueryDB->FieldByName("filterCurrentSubType")->AsInteger;
	settings.order = SqlDBModule->ADOQueryDB->FieldByName("filterOrder")
		->AsInteger;
	settings.cutoffFrequency = SqlDBModule->ADOQueryDB->FieldByName
		("filterCutoffFrequency")->AsFloat;
	settings.widthFrequency = SqlDBModule->ADOQueryDB->FieldByName
		("filterWidthFrequency")->AsFloat;
	settings.centerFrequency = SqlDBModule->ADOQueryDB->FieldByName
		("filterCenterFrequency")->AsFloat;
	settings.rippleDb = SqlDBModule->ADOQueryDB->FieldByName("filterRippleDb")
		->AsFloat;
	settings.rolloff = SqlDBModule->ADOQueryDB->FieldByName("filterRolloff")
		->AsFloat;
	settings.sampleRate = SqlDBModule->ADOQueryDB->FieldByName("filterSampleRate")
		->AsFloat;
	SqlDBModule->ADOQueryDB->Close();
}

#pragma package(smart_init)
