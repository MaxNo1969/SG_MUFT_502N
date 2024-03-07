//---------------------------------------------------------------------------

#ifndef EtalonDatasH
#define EtalonDatasH
#include <vector>
#include <Classes.hpp>
#include <Graphics.hpp>
using namespace std;

//---------------------------------------------------------------------------
class Etalon //����� �������� ������
{
public:
	Etalon();
	~Etalon();
	//id ������� � ����
	int Etalon_id;
	//�������
	int Frequency;
	//������ ��������� ������
	int SG_id;
	//������ ��������� ���
	AnsiString SG_name;
	//����
	TColor Color;
	//������
	vector<int> Thresholds;
	//�������� �� �������
	vector<double> BarkValues;
};
//---------------------------------------------------------------------------
class EtalonDatas //����� �������� ������� ��� �����������
{
public:
	EtalonDatas(int _TS_id, int _SGGost_id);
	~EtalonDatas();
	//�������
	vector<Etalon> Etalons;
};
//---------------------------------------------------------------------------
class TSThresholds //����� �������� ������ �����������
{
public:
	TSThresholds(int _TS_id);
	~TSThresholds();
	//������
	vector<int> Thresholds;

};

//������ ��������
class EtalonArray
{
private:
public:
	//�������� �������
	AnsiString name;
	//����������
	int ts_id;
	//����
	int gost_id;
	vector<Etalon> Etalons;

	EtalonArray(AnsiString _name,int _TS_id, int _SGGost_id):
		name(name),ts_id(_TS_id),gost_id(_SGGost_id){};
	~EtalonArray(){Etalons.clear();};

};


#endif
