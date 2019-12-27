// ---------------------------------------------------------------------------

#ifndef uTFilterSettingsH
#define uTFilterSettingsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "IniFiles.hpp"
#include "cspin.h"
// ---------------------------------------------------------------------------
class TFilterSettings : public TFrame
{
__published: // IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *gbButterworth;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TCSpinEdit *csOrder;
	TEdit *eCutoffFreq;
	TEdit *eCenterFreq;
	TEdit *eWidthFreq;
	TEdit *eRippleDb;
	TEdit *eRolloff;
	TRadioGroup *rgFilterSubType;
	TRadioGroup *rgFilterType;
	TCheckBox *CBUsed;
	void __fastcall rgFilterTypeClick(TObject *Sender);
	void __fastcall rgFilterSubTypeClick(TObject *Sender);
	// __property AnsiString PostFix = {read=GetPostFix, write=SetPostFix,default=NULL};
private: // User declarations
	void ChooseFilter();
public: // User declarations
	__fastcall TFilterSettings(TComponent* Owner);
	void Load(AnsiString _PostFix);
	void Save(AnsiString _PostFix);
	inline void SetCaption(AnsiString _caption)
	{
		GroupBox1->Caption=_caption;
	}
	void SetEnable(bool _v);
	inline bool IsUsed(void)
	{
		return (CBUsed->Checked);
	}
};
// ---------------------------------------------------------------------------
extern PACKAGE TFilterSettings *FilterSettings;
// ---------------------------------------------------------------------------
#endif
