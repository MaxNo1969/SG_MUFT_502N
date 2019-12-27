#pragma hdrstop
#include "unTExtFunction.h"
#include "TProtocol.h"
#include "TVirtualLCard502.h"
#include "unTUtils.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
TVirtualLCard502::TVirtualLCard502(TGlobalSettings* _mainGlobalSettings,int &_codeErr)
{    AnsiString aStr="";
	try
	{
		globalSettings = _mainGlobalSettings;
		_codeErr = 0;
		raw_size = LCard502_INIT_SIZE;
		rawi = new unsigned int[raw_size];
		raw = new double[raw_size];
		rawc = new double[raw_size];
		IsStarted = false;

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
		//---
	//	RECV_TOUT = 250;
		countLogCh = vecLogChannels.size();
		LastError = "";

		// частота кадров (частота на канал)
		// frequencyPerChannel_Hz = 100;
		frequencyPerChannel_Hz = SqlDBModule->GetFloatFieldSQL("L502Params",
			"frequencyPerChannel_Hz", NULL, 100, _codeErr);
		RECV_TOUT = SqlDBModule->GetIntFieldSQL("L502Params", "RECV_TOUT",
			NULL, 0, _codeErr);
		syncMode = SqlDBModule->GetIntFieldSQL("L502Params", "syncMode",
			NULL, 0, _codeErr);
		syncStartMode = SqlDBModule->GetIntFieldSQL("L502Params",
			"syncStartMode", NULL, 0, _codeErr);

		// --------- припишем настройки в плату
		LoadAndSetSettings(vecLogChannels);
		// -----------
	}
	catch (Exception *ex) {
		 TLog::ErrFullSaveLog(ex);
		_codeErr=-55;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

// ---------------------------------------------------------------------------
TVirtualLCard502::~TVirtualLCard502(void)
{
	Stop();
	delete rawi;
	delete raw;
	delete rawc;
}

// ---------------------------------------------------------------------------
void TVirtualLCard502::LFATAL(AnsiString _msg, int _err)
{
	if (_err == 0)
		return;
	AnsiString a = _msg;
	if (_err < 0) {
		a += " ";
		a += L502_GetErrorString(_err);
	}
	TExtFunction::ShowBigModalMessage(a, clRed);
//	FATAL(a);

}
// ---------------------------------------------------------------------------
bool TVirtualLCard502::CheckError(int _err)
{
	if (_err == 0)
		return (false);
	LastError = "Ошибка "+IntToStr(_err);
	return (true);
}
// ---------------------------------------------------------------------------
// Читает настройки и вбивает в плату
void TVirtualLCard502::LoadAndSetSettings(vector<TLogCh502Params>& _logChannels)
{
	AnsiString a = "LCard502::LoadAndSetSettings: Не удалось задать параметры";
	countLogCh = _logChannels.size();
	double f_acq = frequencyPerChannel_Hz * countLogCh;
	double f_lch = frequencyPerChannel_Hz;
	// настраиваем частоту сбора с АЦП
}
// ---------------------------------------------------------------------------
void TVirtualLCard502::Start(void)
{
	if (IsStarted)
		return;
	LoadAndSetSettings(vecLogChannels);
	IsStarted = true;
}

// ---------------------------------------------------------------------------
void TVirtualLCard502::Stop(void)
{
	if (!IsStarted)
		return;
	IsStarted = false;
}

// ---------------------------------------------------------------------------
double* TVirtualLCard502::Read(int* _size)
{
	uint32_t count = raw_size;
	count /= countLogCh;
	count *= countLogCh;
	SetRawSize(count);
	// переводим АЦП в Вольты
	unsigned int count1 = count;
	//Здесь надо что-нибудь записать
	if (count != count1)
	{
		*_size = -6;
		LastError =
			"Размер преобразование полученный не равен размеру запрошенному";
		return (NULL);
	}
	*_size = count;
	return (raw);
}

// ---------------------------------------------------------------------------
void TVirtualLCard502::SetRawSize(int _size)
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
double TVirtualLCard502::GetValue(int _ch)
{
	double* buf = new double[countLogCh];
	for(int i = 0; i < countLogCh; i++)
		buf[i] = 0;
	double ret = buf[_ch];
	delete buf;
	return (ret);
}
// ---------------------------------------------------------------------------
TLogCh502Params* TVirtualLCard502::FindChByName(AnsiString _name)
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
int TVirtualLCard502::FindPosByName(AnsiString _name)
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

