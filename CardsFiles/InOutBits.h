//---------------------------------------------------------------------------

#ifndef InOutBitsH
#define InOutBitsH
#include "A1730.h"
#include "x502api.h"
class InOutBits: public A1730
{
	WORD outBits;
public:
	t_x502_hnd hdr;
	InOutBits(t_x502_hnd hdr): hdr(hdr){};
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	void WriteSignals(void);
	void ReadSignals(void);
};
//---------------------------------------------------------------------------
#endif
