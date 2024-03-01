//---------------------------------------------------------------------------

#ifndef InOutBitsH
#define InOutBitsH
#include "A1730.h"
#include "TLCard502.h"
class InOutBits: public A1730
{
	WORD outBits;
public:
	TLCard502 *hdr;
	InOutBits(TLCard502 *hdr): hdr(hdr){};
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	void WriteIn(DWORD _v);
	void WriteSignals(void);
	void ReadSignals(void);
};
class InOutBitsEmul: public A1730
{
	WORD inBits;
	WORD outBits;
public:
	TLCard502 *hdr;
	InOutBitsEmul(TLCard502 *hdr): hdr(hdr),inBits(0),outBits(0){};
	DWORD Read(void){return inBits;};
	DWORD ReadOut(){return outBits;};
	void Write(DWORD _v){outBits=_v;};
	void WriteIn(DWORD _v){inBits=_v;};
	void WriteSignals(void){};
	void ReadSignals(void){};
};
//---------------------------------------------------------------------------
#endif
