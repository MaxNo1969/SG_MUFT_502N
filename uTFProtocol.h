//---------------------------------------------------------------------------
#ifndef uTFProtocolH
#define uTFProtocolH
//---------------------------------------------------------------------------
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Classes.hpp>
#include <stdio.h>
#include "unSQLDbModule.h"
#include "TGlobalSettings.h"
//---------------------------------------------------------------------------
class TFProtocol : public TForm
{
__published:	// IDE-managed Components
	TMemo *mProtocol;
	TCheckBox *cbProtocolToFile;
	TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbProtocolToFileClick(TObject *Sender);
private:	// User declarations
	TCriticalSection* critSect;
	TStringList* strList;
	FILE *file;
public:		// User declarations
	__fastcall TFProtocol(TComponent* Owner,TCriticalSection* _cs);
	void Add(AnsiString _msg);
	void Save(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFProtocol *FProtocol;
//---------------------------------------------------------------------------
#endif
