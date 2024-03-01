//---------------------------------------------------------------------------

#pragma hdrstop

#include "InOutBits.h"
//#include <E502api.h>
#include "unTExtFunction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
DWORD InOutBits::Read(void)
{
	return hdr?hdr->Read():0;
}
DWORD InOutBits::ReadOut(void)
{
	return outBits;
}
void InOutBits::Write(DWORD val)
{
		outBits = val;
		if(hdr)hdr->Write(val);
}
void InOutBits::WriteIn(DWORD val)
{
}
void InOutBits::WriteSignals(void)
{
	if(hdr)hdr->WriteSignals();
}
void InOutBits::ReadSignals(void)
{
	if(hdr)hdr->ReadSignals();
}
