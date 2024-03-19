// ---------------------------------------------------------------------------
#pragma hdrstop
#include "TProtocol.h"
#include "Main.h"
// ---------------------------------------------------------------------------
//#pragma package(smart_init)
FILE* TProtocol::f = NULL;

void TProtocol::ProtocolSave(UnicodeString _msg)
{
	if(f == NULL)
	{
		f = fopen("protocol.txt","a");
	}
	if(f)
	{
		TDateTime currentDT;
    	AnsiString strCurrentDT = FormatDateTime("yyyy.mm.dd hh:mm:ss", currentDT.CurrentDateTime());
		strCurrentDT = strCurrentDT + " ;" + _msg + "\n";
		fputs(strCurrentDT.c_str(),f);
		fflush(f);
	}
	{
       OutputDebugString(_msg.c_str());
	}
}



