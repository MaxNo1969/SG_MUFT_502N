#ifndef TProtocolH
#define TProtocolH
#include "uTFProtocol.h"
class TProtocol
{
public:
	static FILE *f;
	void static ProtocolSave(AnsiString _msg);
};
#endif
