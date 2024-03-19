//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "unTExtFunction.h"

//---------------------------------------------------------------------------
USEFORM("SGSettings.cpp", SGSettForm);
USEFORM("Main.cpp", MainForm);
USEFORM("NewSG.cpp", NewSGForm);
USEFORM("unSQLDbModule.cpp", SqlDBModule); /* TDataModule: File Type */
USEFORM("unFmViewMeasure.cpp", fmViewMeasure);
USEFORM("unPasswordForm.cpp", PasswordForm);
USEFORM("uTFProtocol.cpp", FProtocol);
USEFORM("uTFRSensor.cpp", FRSensor); /* TFrame: File Type */
USEFORM("uTFilterSettings.cpp", FilterSettings); /* TFrame: File Type */
USEFORM("unDiagnost.cpp", fmDiagnost);
USEFORM("unEditEtalon.cpp", fmEditEtalon);
USEFORM("unFmMessage.cpp", fmMessage);
USEFORM("unFmTypeSizes.cpp", fmTypeSizes);
USEFORM("unExtSettings.cpp", fmExtSettings);
USEFORM("unFmEditSettings.cpp", fmSettings);
USEFORM("CardsFiles\A1730\uFSignalsState.cpp", FSignalsState);
USEFORM("CardsFiles\A1730\uFRSigPanel.cpp", FRSigPanel); /* TFrame: File Type */
USEFORM("ABOUT.cpp", AboutBox);
USEFORM("ADCSettings.cpp", ADCSettForm);
USEFORM("ColorSettings.cpp", FormColor);
USEFORM("FRMEtalons.cpp", FREtalons);
USEFORM("FRMGroups.cpp", FRGroups);
USEFORM("FREgroupEdit.cpp", EgroupEditFrm);
USEFORM("FRGosts.cpp", FRSprGost);
USEFORM("FRCheckMufta.cpp", FRMMuftaLevel);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TSqlDBModule), &SqlDBModule);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		//Application->ShowException(&exception);
		TExtFunction::ShowBigModalMessage(exception.ToString(), clRed);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			//Application->ShowException(&exception);
            TExtFunction::ShowBigModalMessage(exception.ToString(), clRed);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
