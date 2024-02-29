#pragma hdrstop
#include "unTExtFunction.h"
#include "TProtocol.h"
#include "TLCard502.h"
#include "unTUtils.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
#ifndef TLCARD502TEST
TLCard502::TLCard502(TGlobalSettings* _mainGlobalSettings,int &_codeErr)
{
	AnsiString aStr="";
	InitializeCriticalSection(&cs);
	try
	{
		handle=NULL;
		globalSettings = _mainGlobalSettings;
		_codeErr = 0;
		raw_size = LCard502_INIT_SIZE;
		rawi = new unsigned int[raw_size];
		raw = new double[raw_size];
		rawc = new double[raw_size];
		t_x502_devrec x502_item;
		//Проверим есть ли плата в системе
		if(CheckCard(&x502_item))
		{
			//Если есть - получаем дескриптор и открываем плату
			handle = X502_Create();
			int err = X502_OpenByDevRecord(handle, &x502_item);
			if (X502_ERR_OK != err)
			{
				AnsiString mess = "Ошибка установления связи с модулем ";
				mess +=  X502_GetErrorString(err);
				LFATAL(mess, 1);
			}
		}
	   //	X502_FreeDevRecordList(&x502_item, 1);

		IsStarted = false;
		loadChannels();
		// частота кадров (частота на канал)
		frequencyPerChannel_Hz = SqlDBModule->GetFloatFieldSQL("L502Params",
			"frequencyPerChannel_Hz", NULL, 100, _codeErr);
		RECV_TOUT = SqlDBModule->GetIntFieldSQL("L502Params", "RECV_TOUT",
			NULL, 0, _codeErr);
		syncMode = SqlDBModule->GetIntFieldSQL("L502Params", "syncMode",
			NULL, 0, _codeErr);
		syncStartMode = SqlDBModule->GetIntFieldSQL("L502Params",
			"syncStartMode", NULL, 0, _codeErr);
		// --------- припишем настройки в плату
		LastError = "";

	}
	catch (Exception *ex) {
		TProtocol::ProtocolSave(ex->Message);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
		LFATAL(ex->Message,1);
		throw &ex;
	}
}

// заполним вектор каналов
bool TLCard502::loadChannels()
{
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
			TLogCh502Params* tlcp = new TLogCh502Params();
			tlcp->chName = SqlDBModule->ADOQueryDB->FieldByName("chName")
				->AsString;
			tlcp->adcRangeIndex = SqlDBModule->ADOQueryDB->FieldByName
				("adcRangeIndex")->AsInteger;
			tlcp->logicalChannel = SqlDBModule->ADOQueryDB->FieldByName
				("numLogCh")->AsInteger;
			tlcp->collectedMode = SqlDBModule->ADOQueryDB->FieldByName
				("collectedMode")->AsInteger;
			tlcp->chGain = SqlDBModule->ADOQueryDB->FieldByName("chGain")
				->AsInteger;
			vecLogChannels.push_back(*tlcp);
			SqlDBModule->ADOQueryDB->Next();
		}
		SqlDBModule->ADOQueryDB->Close();
		countLogCh = vecLogChannels.size();
		return true;
}

bool TLCard502::CheckCard(t_x502_devrec* px502_item)
{
	int32_t res = E502_UsbGetDevRecordsList(px502_item, 1, 0, NULL);
	if (!res)
	{
		return false;
	}
	return true;
}
bool TLCard502::CheckCardMsg()
{
	t_x502_devrec x502_item;
	int32_t res = E502_UsbGetDevRecordsList(&x502_item, 1, 0, NULL);
	if (!res)
	{
		LFATAL("LCard502::LCard502: Ни одной платы не найдено !",1);
		return false;
	}
	return true;
}


DWORD TLCard502::Read(void)
{

	uint32_t t = 0;
	EnterCriticalSection(&cs);
	int32_t err = 0;
	if(handle)
	  err = X502_AsyncInDig(handle, &t);
	LeaveCriticalSection(&cs);
	if (err != X502_ERR_OK) {
		TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Read: не могу прочитать плату", clRed);
	}
	return t;
}
DWORD TLCard502::ReadOut(void)
{
	return outBits;
}
void TLCard502::Write(DWORD val)
{
	EnterCriticalSection(&cs);
	int32_t err = 0;
	if(handle)
		err = X502_AsyncOutDig(handle, val, 0);
	LeaveCriticalSection(&cs);
	outBits = val;
	if (err != X502_ERR_OK) {
		TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Write: не могу записать на плату", clRed);
	}
}
void TLCard502::WriteSignals(void)
{
}
void TLCard502::ReadSignals(void)
{
}

// ---------------------------------------------------------------------------
TLCard502::~TLCard502(void)
{
if (handle!=NULL) {
	if(handle)
	{
		EnterCriticalSection(&cs);
		X502_StreamsStop(handle);
		X502_Close(handle);
		X502_Free(handle);
		 handle = NULL;
		LeaveCriticalSection(&cs);
	}
	}else{
	  //
	}
	DeleteCriticalSection(&cs);
	delete rawi;
	delete raw;
	delete rawc;
}

// ---------------------------------------------------------------------------
void TLCard502::LFATAL(AnsiString _msg, int _err)
{
	if (_err == 0)
		return;
	AnsiString a = _msg;
	if (_err < 0) {
		a += " ";
		a += X502_GetErrorString(_err);
	}
	TExtFunction::ShowBigModalMessage(a, clRed);
}
// ---------------------------------------------------------------------------
bool TLCard502::CheckError(int _err)
{
	if (_err == 0)
		return (false);
	LastError = X502_GetErrorString(_err);
	return (true);
}
// ---------------------------------------------------------------------------
// Читает настройки и вбивает в плату
void TLCard502::LoadAndSetSettings()
{
	EnterCriticalSection(&cs);
	AnsiString a = "LCard502::LoadAndSetSettings: Не удалось задать параметры";
	countLogCh = vecLogChannels.size();
	if(handle)
	{
		LFATAL(a, X502_SetLChannelCount(handle, countLogCh));
	}
	AnsiString names[] = {"chBarkgausen", "chCurrentControl", "chVoltageSol"};
	for(int i = 0; i < countLogCh; ++i)
	for (int z = 0; z < countLogCh; z++)
	{
		if(0 == AnsiCompareStr(names[i],vecLogChannels[z].chName))
		{
			unsigned logicalChannel = vecLogChannels[z].logicalChannel;
			unsigned collectedMode = vecLogChannels[z].collectedMode;
			unsigned adcRangeIndex =  vecLogChannels[z].adcRangeIndex;
			if(handle)
			{
				int res = X502_SetLChannel(handle, i,logicalChannel,collectedMode,adcRangeIndex, 0);
				if(res != X502_ERR_OK)
				{
					AnsiString strErr = "Ошибка при установке канала "+vecLogChannels[z].chName+": ";
					strErr = strErr+X502_GetErrorString(res);
					TProtocol::ProtocolSave(strErr);
				}
			}
			break;
		}
	}

	if(handle)
	{
		// Настраиваем источник частоты синхронизации
		LFATAL(a, X502_SetSyncMode(handle, syncMode));
		// Настраиваем  источник запуска сбора
		LFATAL(a, X502_SetSyncStartMode(handle, syncStartMode));
		double f_acq = frequencyPerChannel_Hz * countLogCh;
		double f_lch = frequencyPerChannel_Hz;
		// настраиваем частоту сбора с АЦП
		LFATAL(a, X502_SetAdcFreq(handle, &f_acq, &f_lch));
		// Записываем настройки в модуль
		LFATAL(a, X502_Configure(handle, 0));
	}
	LeaveCriticalSection(&cs);
}
// ---------------------------------------------------------------------------
void TLCard502::Start(void)
{
	if (!IsStarted)
	{
		LoadAndSetSettings();
		IsStarted = true;
		if(handle)
		{
			EnterCriticalSection(&cs);
			LFATAL("LCard502::Start: не смогли разрешить потоки: ",X502_StreamsEnable(handle, X502_STREAM_ADC));
			LFATAL("LCard502::Start: не смогли стартовать: ",X502_StreamsStart(handle));
			LeaveCriticalSection(&cs);
        }
	}
}

// ---------------------------------------------------------------------------
void TLCard502::Stop(void)
{
	if (IsStarted)
	{
		IsStarted = false;
		if(handle)
		{
			EnterCriticalSection(&cs);
			LFATAL("LCard502::Start: не смогли остановиться: ",X502_StreamsStop(handle));
			LeaveCriticalSection(&cs);
		}
	}
}

// ---------------------------------------------------------------------------
double* TLCard502::Read(int* _size)
{
	Sleep(1000);
	uint32_t count = 0;
	if(handle)
	{
		if (CheckError(X502_GetRecvReadyCount(handle, &count)))
		{
			*_size = -1;
			return (NULL);
		}
	}
	count /= countLogCh;
	count *= countLogCh;
	SetRawSize(count);
	if(handle)
	{
		int rcv_size = X502_Recv(handle, rawi, count, RECV_TOUT);
		/* значение меньше нуля означает ошибку... */
		/* получаем номер лог. канала, соответствующий первому
		 отсчету АЦП, так как до этого могли обработать
		 некратное количество кадров */
		unsigned int firstLch;
		X502_GetNextExpectedLchNum(handle, &firstLch);
		AnsiString a="firstLch=";
		a+=firstLch;
		TProtocol::ProtocolSave(a);
		if (CheckError(X502_GetNextExpectedLchNum(handle, &firstLch)))
		{
			*_size = -2;
			return (NULL);
		}
		if (rcv_size != (int)count)
		{
			*_size = -3;
			LastError = "Размер полученный не равен размеру запрошенному";
			return (NULL);
		}
		// переводим АЦП в Вольты
		unsigned int count1 = count;
		if (CheckError(X502_ProcessAdcData(handle, rawi, raw, &count1,0)))
		{
			*_size = -5;
			return (NULL);
		}
		if (count != count1)
		{
			*_size = -6;
			LastError =	"Размер преобразование полученный не равен размеру запрошенному";
			return (NULL);
		}
	}
	*_size = count;
	return (raw);
}

// ---------------------------------------------------------------------------
void TLCard502::SetRawSize(int _size)
{
	if (_size > raw_size)
	{
		delete rawi;
		delete raw;
		double k = LCard502_ADD_PERCENT;
		k /= 100;
		k += 1;
		raw_size = (int)(_size * k);
		rawi = new unsigned int[raw_size];
		raw = new double[raw_size];
	}
}

// ---------------------------------------------------------------------------
double TLCard502::GetValue(int _ch)
{
	if(handle)
	{
		double* buf = new double[countLogCh];
		LFATAL("RLCard502::GetValue: не смогли получить значение: ",X502_AsyncGetAdcFrame(handle, X502_PROC_FLAGS_VOLT, 1000, buf));
		double ret = buf[_ch];
		delete buf;
		return (ret);
	}
	return 0.0;
}
// ---------------------------------------------------------------------------
TLogCh502Params* TLCard502::FindChByName(AnsiString _name)
{
	for(unsigned int i=0;i<vecLogChannels.size();i++)
	{
		if(vecLogChannels[i].chName==_name)
			return(&vecLogChannels[i]);
	}
	AnsiString a="TLCard502::FindChByName: Канал не найден: ";
	a+=_name;
	LFATAL(a,1);
	return(NULL);
}
// ---------------------------------------------------------------------------
int TLCard502::FindPosByName(AnsiString _name)
{
	for(unsigned int i=0;i<vecLogChannels.size();i++)
	{
		if(vecLogChannels[i].chName==_name)
			return(i);
	}
	AnsiString a="TLCard502::FindPosByName: Канал не найден: ";
	a+=_name;
	LFATAL(a,1);
	return(-1);
}
// ---------------------------------------------------------------------------
#endif

