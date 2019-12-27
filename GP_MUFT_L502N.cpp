//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("unSQLDbModule.cpp", SqlDBModule); /* TDataModule: File Type */
USEFORM("unFmViewMeasure.cpp", fmViewMeasure);
USEFORM("uTFRSensor.cpp", FRSensor); /* TFrame: File Type */
USEFORM("uTFProtocol.cpp", FProtocol);
USEFORM("uTFilterSettings.cpp", FilterSettings); /* TFrame: File Type */
USEFORM("unEditEtalon.cpp", fmEditEtalon);
USEFORM("unDiagnost.cpp", fmDiagnost);
USEFORM("unExtSettings.cpp", fmExtSettings);
USEFORM("unFmTypeSizes.cpp", fmTypeSizes);
USEFORM("unFmMessage.cpp", fmMessage);
USEFORM("unFmEditSettings.cpp", fmSettings);
USEFORM("CardsFiles\A1730\uFRSigPanel.cpp", FRSigPanel); /* TFrame: File Type */
USEFORM("CardsFiles\A1730\uFSignalsState.cpp", FSignalsState);
USEFORM("ADCSettings.cpp", ADCSettForm);
USEFORM("ABOUT_NTC_NK_URAN.cpp", fmAboutBox);
USEFORM("Main.cpp", MainForm);
USEFORM("SGSettings.cpp", SGSettForm);
USEFORM("NewSG.cpp", NewSGForm);
USEFORM("ColorSettings.cpp", FormColor);
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
