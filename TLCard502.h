// ---------------------------------------------------------------------------
#ifndef TLCard502H
#define TLCard502H
//#include "RLCard_parameters.h"
#include "TLogCh502Params.h"
#include "l502api.h"
#include <E502api.h>
#include "TGlobalSettings.h"
#include <vector>
#include <fstream>

#define LCard502_INIT_SIZE 2000
#define LCard502_ADD_PERCENT 50
using namespace std;
// ---------------------------------------------------------------------------
#pragma comment(lib, "x502api.lib")
#pragma comment(lib, "e502api.lib")
class TLCard502
{
WORD outBits;
CRITICAL_SECTION cs;
public:
	// ! ����� �����
	t_x502_hnd handle;
private:
	int raw_size;
	unsigned int* rawi;
	double* raw;
	double* rawc;
	bool IsStarted;
	// ! ������� ��� ����� (� ����� �������� ����� ��������� ������ �� ��� � ������� �����,��)
//	int RECV_TOUT;
//	int MainSensors;
//	int OtherSensors;
	void SetRawSize(int _size);
	void LFATAL(AnsiString _msg, int _err);
	bool CheckError(int _err);
//	void LoadMainSettings();

//	RLCard_parameters* Parameters;

public:
	//����� ������
	AnsiString LastError;

	//����������� � �������� �����
	TLCard502(TGlobalSettings* _mainGlobalSettings,int &_codeErr);
	//���������� � �������� �����
	~TLCard502(void);
	//����� �����
	void Start(void);
	//��������� �����
	void Stop(void);
	//������ ������ � �����
	double* Read(int* _size);
	//�������� �������� � ������
	double GetValue(int _ch);

	// ������ ��������� � ������� � �����
	void LoadAndSetSettings();

	inline double* GetRawC(void)
	{
		return(rawc);
	}

	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	void WriteIn(DWORD _v);
	void WriteSignals(void);
	void ReadSignals(void);
	//-----------------------------------------

	// ! ������� ��� ����� (� ����� �������� ����� ��������� ������ �� ��� � ������� �����,��)
	int RECV_TOUT;
	// ! @brief ����� �������������
	// ! @li 0 ���������� ������
	// ! @li 1 �� �������� ������� �� ������� �������������
	// ! @li 2 �� ������ ������� DI_SYN1
	// ! @li 3 �� ������ ������� DI_SYN2
	// ! @li 6 �� ����� ������� DI_SYN1
	// ! @li 7 �� ����� ������� DI_SYN2
	uint32_t syncMode;
	// ! �������� ������� ����������� �����/������ ��. ������ @link syncMode
	uint32_t syncStartMode;
	// ! ������� �� ����� (��.)
	double frequencyPerChannel_Hz;
	//���������� �������������� �������
	int	countLogCh;
	//��������� �� ���������
	TGlobalSettings* globalSettings;

	// ! ���������� ���-�� ������������ �������
	int getCountChannels()
	{
		return vecLogChannels.size();// + others.size();
	}

	// ! �������������� ��������� ��� ������� ������
	vector<TLogCh502Params> vecLogChannels;
	// ! @brief �������������� ������
	// ! @li 0 - ��� ���������� ��������
	// ! @li 1 - ���������� ���������� ��������
	// ! @li 2 - ��� ���������� ��������
	// ! @li 3 - ���������� ���������� ��������
	// ! @li 4 - ��� ������ ���������
	// ! @li 5 - ���������� ������ ���������
	// ! @li 6 - ���������� �� �����
//	vector<TLogCh502Params> others;

//	int LSensors;
//	int CSensors;
//	int GSensors;
//	int OSensors;

//	void LoadSettings(void);
//	void SaveSettings(void);

	TLogCh502Params* FindChByName(AnsiString _name);
	int FindPosByName(AnsiString _name);
	// �������� ������ �������
	bool loadChannels();
   	bool CheckCard(t_x502_devrec* x502_item);
	bool CheckCardMsg();


};
#endif
