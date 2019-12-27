// ---------------------------------------------------------------------------

#pragma hdrstop

#include "TVirtLCard791.h"
// ---------------
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#include "unTUtils.h"
#include "unFmMessage.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
// TVirtualLCard791 *lcard;

TVirtualLCard791::TVirtualLCard791(TGlobalSettings* _mainGlobalSettings,
	int &_codeErr) {
	try {

		_codeErr = -99;
		countLogCh = 0;
		started = false;
		// заполним вектор каналов
		SqlDBModule->ADOQueryDB->Close();
		AnsiString str = "";
		str = "SELECT rec_id,adcRangeIndex,chName,numLogCh,collectedMode,chGain";
		str += " FROM L502ChParams where fEnable=1 order by numLogCh";
		SqlDBModule->ADOQueryDB->SQL->Text = str;
		SqlDBModule->ADOQueryDB->Open();
		str = SqlDBModule->ADOQueryDB->FieldByName("chName")->AsString;
		int c = SqlDBModule->ADOQueryDB->RecordCount;
		vecLogChannels.reserve(c);
		while (!SqlDBModule->ADOQueryDB->Eof) {
			TLogCh791Params* tlcp = new TLogCh791Params();
			tlcp->chName = SqlDBModule->ADOQueryDB->FieldByName("chName")
				->AsString;
			// tlcp->adcRange = SqlDBModule->ADOQueryDB->FieldByName("adcRange")
			// ->AsInteger;
			tlcp->adcRangeIndex = SqlDBModule->ADOQueryDB->FieldByName
				("adcRangeIndex")->AsInteger;
			tlcp->logicalChannel = SqlDBModule->ADOQueryDB->FieldByName
				("numLogCh")->AsInteger;
			tlcp->collectedMode = SqlDBModule->ADOQueryDB->FieldByName
				("collectedMode")->AsInteger;
			tlcp->chGain = SqlDBModule->ADOQueryDB->FieldByName("collectedMode")
				->AsInteger;
			vecLogChannels.push_back(*tlcp);
			SqlDBModule->ADOQueryDB->Next();
		}
		SqlDBModule->ADOQueryDB->Close();
		slot = 0;
		lastError = "";
		t_stop_event = CreateEvent(0, true, false, 0);
		// ------------

		// частота измерений
		// measures_frequency_kHz = 11;
		measures_frequency_kHz = SqlDBModule->GetFloatFieldSQL("L791Params",
			"measures_frequency_kHz", NULL, 11, _codeErr);
		// частота кадров (частота на канал)
		// frequencyPerChannel_Hz = 100;
		frequencyPerChannel_Hz = SqlDBModule->GetFloatFieldSQL("L791Params",
			"frequencyPerChannel_Hz", NULL, 100, _codeErr);
		RECV_TOUT = SqlDBModule->GetIntFieldSQL("L791Params", "RECV_TOUT",
			NULL, 0, _codeErr);
		syncMode = SqlDBModule->GetIntFieldSQL("L791Params", "syncMode",
			NULL, 0, _codeErr);
		syncStartMode = SqlDBModule->GetIntFieldSQL("L791Params",
			"syncStartMode", NULL, 0, _codeErr);
		sendFrequency = SqlDBModule->GetFloatFieldSQL("L791Params",
			"sendFrequency", NULL, 1000, _codeErr);
		countLogCh = SqlDBModule->GetIntFieldSQL("L791Params", "countLogCh",
			NULL, 3, _codeErr);
		szDataBuf = 1024 * countLogCh;
		data_buf = new double[szDataBuf];
		_codeErr = 0;
		LastRead = 0;
		// --------- припишем настройки в плату
		LoadAndSetSettings(vecLogChannels);
		// -----------
		// queryAsync = new TADOQuery(NULL);
		// AnsiString applPath = ExtractFilePath(Application->ExeName);
		// AnsiString pathUDL = ExtractFilePath(Application->ExeName) +"connectSQLVirt.udl";
		// queryAsync->ConnectionString = "FILE NAME=" + pathUDL;
		// queryAsync->SQL->Text = "select TOP 3600 * from valuesADC";
		// queryAsync->Open();
		// _codeErr = queryAsync->RecordCount;
		// ----------------
		sizeBuf = 3600;
		offsetBuf = 0;
		virtBuf.reserve(countLogCh + 1);
		for (int i = 0; i < countLogCh + 1; i++) {
			double* sensData = new double[sizeBuf];
			for (int k = 0; k < sizeBuf; k++) {
				sensData[k] = 0;
			}
			virtBuf.push_back(sensData);
			// delete sensData;
		}
		// заполним виртуальный буфер
		for (int i = 0; i < sizeBuf; i++) {
			int ampl = 0;
			int val = 0;
			int val0 = 0;
			// один канал (последний) оставляем для импульсов
			for (int j = 0; j < countLogCh - 1; j++) {
				int trash = random(100);
				ampl = (int)8192 / (j + 1);
				val = ampl * sin(i * (2 * 3.1415926 * (j + 1) * 4) / sizeBuf);
				// намусорим в сигнале
				if (trash > 90) {
					if (val > 0) {
						val = random(8192);
					}
					else {
						val = -random(8192);
					}
				}
				else {
					//
				}
				virtBuf[j][i] = val;
				if (j == 0) {
					val0 = val;
				}
				else {
					//
				}
			}
			// нарисуем инпульсы при переходе через 0 в последнем канале
			if (abs(val0) < 100) {
				// countLogCh-1
				virtBuf[countLogCh - 1][i] = 7000;
			}
			else {
				virtBuf[countLogCh - 1][i] = 700;
			}
		}
	}
	catch (Exception *ex) {
		// TLog::ErrFullSaveLog(ex);
		_codeErr = -1;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

TVirtualLCard791::~TVirtualLCard791(void) {
	// queryAsync->Close();
	// delete queryAsync;
	// int cc=vecLogChannels.size();
	// for (int i = 0; i < cc; i++) {
	// delete vecLogChannels[i];
	// }
	int cc = virtBuf.size();
	for (int i = 0; i < cc; i++) {
		delete virtBuf[i];
	}
}

void TVirtualLCard791::LoadAndSetSettings(vector<TLogCh791Params>& _logChannels)
{
	try {
		// период измерений
		double measures_period_ms =
			// _logChannels.size() / measures_frequency_kHz;
			countLogCh / measures_frequency_kHz;
		// период кадров
		double kadrs_period_ms = 1000 / frequencyPerChannel_Hz;
		// межкадровая задержка
		double kadrs_delay_ms = kadrs_period_ms - measures_period_ms;

		int defSize = 1024 * 32 * countLogCh;
		bufSize = defSize;
		// if (bufSize != defSize) {
		delete data_buf;
		data_buf = new double[bufSize];
		// ToProtocol("!!! Значение буфера изменено !!!");
		// }
	}
	catch (Exception *ex) {
		// TLog::ErrFullSaveLog(ex);
		// AnsiString msg
		// programSettings.colorMSG = programSettings.colorBrak;
		// TExtFunction::UpdateStatusBar(programSettings.gsStatusBar, strStatus, _msg, programSettings.colorMSG);
		// TExtFunction::UpdateLabelStatus(programSettings.gsStatusLabel, strStatus, _msg, programSettings.colorMSG);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

// Переводит логический номер канала и усиление в формат для платы
ULONG TVirtualLCard791::CalcPortBits(int _port, int _gain, bool _diff) {
	ULONG ret;
	if (_diff)
		ret = _port & 15;
	else {
		ret = _port & 31;
		ret |= 1 << 5;
	}
	int gain;
	switch (_gain) {
	case 1:
		gain = 0;
		break;
	case 2:
		gain = 1;
		break;
	case 4:
		gain = 2;
		break;
	case 8:
		gain = 3;
		break;
	case 16:
		gain = 4;
		break;
	case 32:
		gain = 5;
		break;
	case 64:
		gain = 6;
		break;
	case 128:
		gain = 7;
		break;
	default:
		gain = 0;
	}
	ret |= gain << 6;
	return (ret);
}

ULONG TVirtualLCard791::GetValueRaw(int _ch, int _gain, bool _diff, bool* _ret)
{

	if (_ret != NULL)
		* _ret = true;
	ULONG res = (ULONG)(virtBuf[_ch][offsetBuf]);
	if (_ch == countLogCh - 1) {
		offsetBuf++;
	}
	else {
		//
	}
	if (offsetBuf >= sizeBuf) {
		offsetBuf = 0;
	}
	else {
		//
	}
	return res;
}

// Переводим значение в проценты
double TVirtualLCard791::GetValueProcent(int _val) {
	double vf = _val;
	vf *= 100;
	vf /= 8192; // нормируем до -100%...+100%
	return (vf);
}

// Сбор данных
double* TVirtualLCard791::Read(int* _readSize) {
	// pr("Read");
	DWORD CurRead = GetTickCount();
	if (LastRead != 0) {
		if (CurRead - LastRead > Period / 2) {
			// LFATAL("Превышено время периодического чтения платы, возможна потеря данных");
		}
	}
	LastRead = CurRead;
	// это хитрый указатель на первый читаемый байт
	// int cur_sync = *sync;
	int cur_sync = 1;
	*_readSize = 0;
	double val;
	double percent = 100;
	// 8192 хто ты? диапазон на L791 от -8192 до 8192
	percent /= 8192;
	SqlDBModule->queryVirt->Close();
	AnsiString sql =
		"SELECT ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13,ADC14";
	sql += ",ADC15,ADC16,ADC17,ADC18,ADC19,ADC20,ADC21,ADC22,ADC23,ADC24,ADC25,ADC26";
	sql += ",ADC27,ADC28,ADC29,ADC30,ADC31,ADC32 FROM valuesADC order by rec_id";
	SqlDBModule->queryVirt->Open();
	int cf = SqlDBModule->queryVirt->FieldCount;
	// for (; ;) {
	while (!SqlDBModule->queryVirt->Eof) {
		if (prev_sync == cur_sync)
			break;
		// double val = *((short*)(data + prev_sync));
		// int ch = GetChannel(data[prev_sync]);
		for (int fn = 0; fn < countLogCh; fn++) {
			int ch = vecLogChannels[fn].logicalChannel;
			if (CL_index != ch) {
			}
			CL_index++;
			if (CL_index == countLogCh)
				CL_index = 0;
			double val = SqlDBModule->queryVirt->FieldByName
				("ADC" + IntToStr(ch))->AsFloat;
			data_buf[(*_readSize)++] = val * percent;
			// data_buf[(*_size)++] = ch*5;
			prev_sync++;
		}
		// data_buf[(*_size)++] = prev_sync++;
		if (prev_sync == bufSize)
			prev_sync = 0;
		SqlDBModule->queryVirt->Next();
		// if(SqlDBModule->queryVirt->Eof){
		// SqlDBModule->queryVirt->First();
		// }else{
		// //
		// }

	}
	return (data_buf);
}

// Старт сбора
void TVirtualLCard791::StartRead(void) {
	prev_sync = 2;
	LastRead = GetTickCount();
	Sleep(Period_kadr*10);
	for (; ;) {
		int ch = GetChannel(data[prev_sync]);
		 AnsiString a="ch=";
		 a+=ch;
		 a+=" prev_sync=";
		 a+=prev_sync;
		 TProtocol::ProtocolSave(a);
		if (ch == 0)
			break;
		prev_sync++;
		if (prev_sync >= bufSize)
			prev_sync = 0;
	}
	CL_index = 0;
}

// Остановка сбора
void TVirtualLCard791::StopRead(void) {
	LastRead = 0;
}

// Старт платы
void TVirtualLCard791::Start() {
	if (started)
		return;
	LoadAndSetSettings(vecLogChannels);
	started = true;
	prev_sync = 0;
}

// ---------------------------------------------------------------------------
// Остановка платы
void TVirtualLCard791::Stop(void) {
	if (!started)
		return;
	started = false;
}

TLogCh791Params* TVirtualLCard791::FindChByName(AnsiString _name, int &err) {
	for (unsigned int i = 0; i < countLogCh; i++) {
		if (vecLogChannels[i].chName == _name) {
			err = 0;
			return (&vecLogChannels[i]);
		}
		else {
			err = -2;
		}

	}
	AnsiString a = "RLCard_parameters::FindPosByName: Канал не найден: ";
	a += _name;
	// TExtFunction::FATAL(a);
	err = -1;
	return (NULL);
}

// Получить значение замера по каналу
int TVirtualLCard791::GetValueByChannel(TLogCh791Params& _channel) {
	// return (GetValueMeasure(_channel.logicalChannel, _channel.adcRange,_channel.collectedMode != 0));
	return (GetValueMeasure(_channel.logicalChannel, _channel.adcRangeIndex,
		_channel.collectedMode != 0));
}

// ---------------------------------------------------------------------------
// Получить значение замера в вольтах по каналу
// double TLCard791::GetValueVolt(RChannel_parameters& _channel) {
double TVirtualLCard791::GetValueVolt(TLogCh791Params& _channel) {
	return (GetValueVolt(GetValueByChannel(_channel), _channel.adcRangeIndex));
}

// Выделяем значение замера
int TVirtualLCard791::GetValueMeasure(int _ch, int _gain, bool _diff,
	bool* _ret) {
	ULONG v = GetValueRaw(_ch, _gain, _diff, _ret);
	short* sv = (short*)(&v);
	return ((int)(*sv));
}

// ---------------------------------------------------------------------------
// Переводим значение в вольты
double TVirtualLCard791::GetValueVolt(int _val, int _gain) {
	double vf = _val;
	// vf *= 10;
	// vf /= 8192; // нормируем до -10...+10
	vf /= 10; // нормируем до -10...+10
	vf /= _gain;
	return (vf);
}
