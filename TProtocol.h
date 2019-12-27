#ifndef TProtocolH
#define TProtocolH
#include "uTFProtocol.h"
class TProtocol
{
private:
	TProtocol(void);
	~TProtocol(void);
	static TProtocol* Instance;
	TCriticalSection* cs;
	TFProtocol* FProtocol;
public:
	void static ProtocolSave(AnsiString _msg);
	void static Clear(void);
	void static Dispose(void);
	void static Show(void);
};
#endif
