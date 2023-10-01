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
	void WriteSignals(void);
	void ReadSignals(void);
};
//---------------------------------------------------------------------------
#endif
