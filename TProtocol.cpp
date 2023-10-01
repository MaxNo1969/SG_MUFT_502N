// ---------------------------------------------------------------------------
#pragma hdrstop
#include "TProtocol.h"
#include "Main.h"
// ---------------------------------------------------------------------------
//#pragma package(smart_init)

TProtocol* TProtocol::Instance=NULL;
TProtocol::TProtocol()
{
	cs = new TCriticalSection();
	FProtocol = new TFProtocol(NULL, cs);//(MainForm,cs);
}

TProtocol::~TProtocol()
{
	//FProtocol->Save();
   //	delete FProtocol;
  //	delete cs;
}

void TProtocol::ProtocolSave(AnsiString _msg)
{
	if (Instance == NULL)
		Instance = new TProtocol();
	Instance->cs->Enter();
	{
		Instance->FProtocol->Add(_msg);
	} Instance->cs->Leave();
}

void TProtocol::Clear(void)
{
	if (Instance != NULL)
		Instance->cs->Enter();
	{
		Instance->FProtocol->mProtocol->Clear();
		Instance->FProtocol->mProtocol->Lines->Clear();
	} Instance->cs->Leave();
}

void TProtocol::Dispose(void)
{
	if (Instance != NULL)
	{
		delete Instance;
		Instance = NULL;
	}
}

void TProtocol::Show(void)
{
	if (Instance == NULL)
		Instance = new TProtocol();
	Instance->cs->Enter();
	{
		Instance->FProtocol->Show();
	} Instance->cs->Leave();
}


