//---------------------------------------------------------------------------

#pragma hdrstop

#include "InOutBits.h"
//#include <E502api.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
DWORD InOutBits::Read(void)
{
	DWORD t = 0;
	int32_t err = X502_AsyncInDig(hdr, &t);
	if (err != X502_ERR_OK) {
		TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Read: не могу прочитать плату", clRed);
	}
	return t;
}
DWORD InOutBits::ReadOut(void)
{
	return outBits;
}
void InOutBits::Write(DWORD val)
{
		int32_t err = X502_AsyncOutDig(hdr, val, 0);
        outBits = val;
		if (err != X502_ERR_OK) {
			TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Write: не могу записать на плату", clRed);
		}
}
void InOutBits::WriteSignals(void)
{

}
void InOutBits::ReadSignals(void)
{

}
