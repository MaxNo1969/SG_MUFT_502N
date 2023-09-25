//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("SGSettings.cpp", SGSettForm);
USEFORM("unSQLDbModule.cpp", SqlDBModule); /* TDataModule: File Type */
USEFORM("unFmViewMeasure.cpp", fmViewMeasure);
USEFORM("uTFRSensor.cpp", FRSensor); /* TFrame: File Type */
USEFORM("uTFProtocol.cpp", FProtocol);
USEFORM("uTFilterSettings.cpp", FilterSettings); /* TFrame: File Type */
USEFORM("unFmTypeSizes.cpp", fmTypeSizes);
USEFORM("unDiagnost.cpp", fmDiagnost);
USEFORM("unEditEtalon.cpp", fmEditEtalon);
USEFORM("unFmMessage.cpp", fmMessage);
USEFORM("unFmEditSettings.cpp", fmSettings);
USEFORM("unExtSettings.cpp", fmExtSettings);
USEFORM("CardsFiles\A1730\uFSignalsState.cpp", FSignalsState);
USEFORM("CardsFiles\A1730\uFRSigPanel.cpp", FRSigPanel); /* TFrame: File Type */
USEFORM("ADCSettings.cpp", ADCSettForm);
USEFORM("ABOUT_NTC_NK_URAN.cpp", fmAboutBox);
USEFORM("ColorSettings.cpp", FormColor);
USEFORM("NewSG.cpp", NewSGForm);
USEFORM("Main.cpp", MainForm);
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
