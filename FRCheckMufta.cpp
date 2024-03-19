//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FRCheckMufta.h"
#include "TLCard502.h"
#include "TLCardData.h"
#include "Filters.h"
#include "SignalListDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRMMuftaLevel *FRMMuftaLevel;
//---------------------------------------------------------------------------
__fastcall TFRMMuftaLevel::TFRMMuftaLevel(TComponent* Owner)
	: TForm(Owner)
{
	main = (TMainForm*)Owner;
}
//---------------------------------------------------------------------------
void __fastcall TFRMMuftaLevel::btnCheckClick(TObject *Sender)
{
	btnCheck->Enabled = false;
	if (SLD->iCC->Get()) // ïðîâåðÿåì öåïè óïðàâëåíèÿ
	{
		SLD->oSENSLOWPOW->Set(true); // âêëþ÷èì ñëàáîòî÷êó

		TGlobalSettings *gs = main->getGlobalSettings();
		TLCard502* lCard502 = main->getLCard();
		TLCardData * muftàSearchData = new TLCardData(lCard502, 1,lCard502->countLogCh, gs);
		TSG* muftàSearch = new TSG(gs, muftàSearchData);
		while (true)
		{
			if (muftàSearch->Exec(0) == 2)
				break;
		}
		muftàSearch->ResetState();
		int kadrsQuantity = muftàSearchData->vecMeasuresData[0].vecSensorsData[0].size();
		//îòôèëüòðóåì
		SGFilter->toFilter(&(muftàSearchData->vecMeasuresData[0].vecSensorsData[gs->checkMuftaChannel][0])
			,muftàSearchData->vecMeasuresData[0].vecSensorsData[gs->checkMuftaChannel].size());
		int currentTypeSize = gs->indexCurrentTypeSize;
		double thresVal = (double)SqlDBModule->GetIntFromSql( "select checkMuftaLevel as F1 from checkMuftaLevel where rec_id="+IntToStr(currentTypeSize));
		edMaxVal->Text = FloatToStr(thresVal);
		double maxVal = 0;
		for(int i = 0; i < kadrsQuantity; i++)
		{
			double val = muftàSearchData->vecMeasuresData[0].vecSensorsData[gs->checkMuftaChannel][i];
			if(val > maxVal)
			{
			  maxVal = val;
			}
		}
		edMaxVal->Text = FloatToStr(maxVal);
	}
	else
	{
        AnsiString msg;
		msg = "Íåò ñèãíàëà öåïåé óïðàâëåíèÿ!!! \n";
		TExtFunction::ShowBigModalMessage(msg, clRed);
	}
	SLD->oSENSLOWPOW->Set(false); // âûêëþ÷èì ñëàáîòî÷êó
	btnCheck->Enabled = true;
}
//---------------------------------------------------------------------------
