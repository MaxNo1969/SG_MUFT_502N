//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("SGSettings.cpp", SGSettForm);
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
USEFORM("ABOUT_NTC_NK_URAN.cpp", fmAboutBox);
USEFORM("ADCSettings.cpp", ADCSettForm);
USEFORM("ColorSettings.cpp", FormColor);
USEFORM("Main.cpp", MainForm);
USEFORM("NewSG.cpp", NewSGForm);
USEFORM("ABOUT.cpp", AboutBox);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TSqlDBModule), &SqlDBModule);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
