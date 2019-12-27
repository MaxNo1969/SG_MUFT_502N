// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unFmEditSettings.h"
#include "unSQLDbModule.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmSettings *fmSettings;

// ---------------------------------------------------------------------------
__fastcall TfmSettings::TfmSettings(TComponent* Owner, TADOQuery* _setADOQueryDB, bool _gridUse) : TForm(Owner) {
	setADOQueryDB = _setADOQueryDB;
	DBGridSettings->Visible = _gridUse;
    this->KeyPreview=true;
}

// ---------------------------------------------------------------------------

void __fastcall TfmSettings::FormCreate(TObject *Sender) {
	int countFields = 0;
	int heightRow = 22;
	int gorSpace = 10;
	int vertSpace = 5;
	int offsetH = 0;
	int offsetW = 0;
	int maxColunms = 0;
	int numColunm = 1;
	int fieldsForColunm = 12;
	int widthColunm = 0;
	int currFieldNum = 1; // индексы полей начинаются с 1
	AnsiString msg = "TfmSettings::FormCreate";
	bool needGetHint = false; // нужно ли получить подсказку
	//извращение :))))
	TfmSettings* pFmSettings = static_cast<TfmSettings*>(Sender);
	pFmSettings->KeyPreview = true;

	if (setADOQueryDB->Active) {
		countFields = setADOQueryDB->FieldCount;
	}
	else {
	    //setADOQueryDB->Open();
		msg = "Не установлено соединение с БД!";
		MessageDlg(msg, mtError, TMsgDlgButtons() << mbOK, NULL);
		Close();
		return;
	}
	// если не используем грид, то
	if (!DBGridSettings->Visible) {
		// максимум колонок кратен fieldsForColunm
		maxColunms = countFields / fieldsForColunm + 1;
		// текущая высота формы за вычетом высоты навигатора
		int fmHeght = pFmSettings->Height - DBNavigatorSettings->Height;
		// пропускаем первичный ключ
		currFieldNum = 2;
		// по колонкам
		for (int col = 0; col < maxColunms; col++) {
			offsetH = 0;
			// полям
			for (int f = 0; f < fieldsForColunm; f++) {
				// пробежали все поля, то выходим
				if (currFieldNum > countFields) {
					break;
				}
				else {
					//
				}
				// метки
				TLabel * newLabel = new TLabel(this);
				newLabel->Parent = pFmSettings;
				newLabel->Top = offsetH + vertSpace;
				newLabel->AutoSize = false;
				newLabel->Width = 160;
				newLabel->Left = offsetW + gorSpace;
				newLabel->Height = heightRow;
				newLabel->Alignment = taRightJustify;
				newLabel->Font->Style = TFontStyles() << fsBold;
				// поля
				newLabel->Caption = setADOQueryDB->Fields->FieldByNumber(currFieldNum)->FieldName + ": ";
				newLabel->ParentShowHint = false;
				newLabel->ShowHint = true;
				newLabel->Visible = true;
				// для усиления AnsiUpperCase подсказки
				if (UpperCase(newLabel->Caption).Pos("GAINXY") > 0) {
				newLabel->Caption="Коэфф. усиления кан. №"+IntToStr(currFieldNum);
					if (needGetHint) {
						getHintsADOQuery->Close();
						getHintsADOQuery->Connection = SqlDBModule->ADOConnectionDB;
						AnsiString strHintSQL = "select hint from Hints where UPPER(parName) like('%GAINXY%')";
						getHintsADOQuery->SQL->Text = strHintSQL;
						getHintsADOQuery->Open();
						msg = getHintsADOQuery->Fields->FieldByName("hint")->AsString;
						getHintsADOQuery->Close();
						needGetHint = false;
					}
					else {
						//
					}
					newLabel->Hint = msg;
				}
				else {
					//
				}
				// покорежим дла установок диапазона АЦП
				if (newLabel->Caption.Pos("502ADC_RANGE_V") > 0) {
					TDBComboBox* newDBComboBoxnew = new TDBComboBox(this);
					newDBComboBoxnew->Parent = pFmSettings;
					newDBComboBoxnew->Top = newLabel->Top;
					newDBComboBoxnew->Width = 80;
					newDBComboBoxnew->Left = newLabel->Left + newLabel->Width + gorSpace;
					newDBComboBoxnew->Height = heightRow;
					newDBComboBoxnew->DataSource = DataSourceSettings;
					newDBComboBoxnew->DataField = setADOQueryDB->Fields->FieldByNumber(currFieldNum)->FieldName;
					newDBComboBoxnew->Items->Add("+/-10V");
					newDBComboBoxnew->Items->Add("+/-5V");
					newDBComboBoxnew->Items->Add("+/-2V");
					newDBComboBoxnew->Items->Add("+/-1V");
					newDBComboBoxnew->Items->Add("+/-0,5V");
					newDBComboBoxnew->Items->Add("+/-0,2V");
					newDBComboBoxnew->Visible = true;
					// Ширина одной колонки
					widthColunm = newDBComboBoxnew->Left + newDBComboBoxnew->Width - newLabel->Left;
					// смещения для следующих компонентов
					offsetH = newDBComboBoxnew->Top + newDBComboBoxnew->Height;
					if (getHintsADOQuery->Active) {
						getHintsADOQuery->Close();
					}
					else {
						//
					}
					if (needGetHint) {
						getHintsADOQuery->Connection = SqlDBModule->ADOConnectionDB;
						AnsiString strHintSQL = "select hint from Hints where UPPER(parName) like('%X502ADC_RANGE_V%')";
						getHintsADOQuery->SQL->Text = strHintSQL;
						getHintsADOQuery->Open();
						msg = getHintsADOQuery->Fields->FieldByName("hint")->AsString;
						newLabel->Hint = msg;
						getHintsADOQuery->Close();
						needGetHint = false;
					}
					else {
						newLabel->Hint = msg;
					}

				}
				else {
					TDBEdit* newEdit = new TDBEdit(this);
					newEdit->Parent = pFmSettings;
					newEdit->Top = newLabel->Top;
					newEdit->Width = 80;
					newEdit->Left = newLabel->Left + newLabel->Width + gorSpace;
					newEdit->Height = heightRow;
					newEdit->DataSource = DataSourceSettings;
					newEdit->DataField = setADOQueryDB->Fields->FieldByNumber(currFieldNum)->FieldName;
					newEdit->Visible = true;
					// Ширина одной колонки
					widthColunm = newEdit->Left + newEdit->Width - newLabel->Left;
					// смещения для следующих компонентов
					offsetH = newEdit->Top + newEdit->Height;
				}

				currFieldNum++;
			}
			offsetW = offsetW + widthColunm + gorSpace;
		}
		// растягиваем форму по ширине и высоте
		pFmSettings->Height = (heightRow + vertSpace) * (fieldsForColunm + 2) + vertSpace + DBNavigatorSettings->Height;
		pFmSettings->Width = (widthColunm + gorSpace) * (maxColunms) + gorSpace * 3;
	}
	else {
		// подрегулируем ширину формы по гриду, если его используем и размажем по форме
		DBGridSettings->Columns->Count * 200;
		DBGridSettings->Align = alClient;
	}
	msg = "Форма настроек успешно открыта";
    //bool tst=DataModuleDB->ADOQueryDB->Active;
}

// ---------------------------------------------------------------------------
void __fastcall TfmSettings::FormKeyPress_old(TObject *Sender, System::WideChar &Key) {
	if (Key == VK_ESCAPE)
		Close();
}
// ---------------------------------------------------------------------------
void __fastcall TfmSettings::FormClose(TObject *Sender, TCloseAction &Action)
{
 //восстановим клиентский курсор
 setADOQueryDB->Close();
 setADOQueryDB->CursorLocation = clUseClient;
}
//---------------------------------------------------------------------------

void __fastcall TfmSettings::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE)
		Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmSettings::FormKeyPress(TObject *Sender, wchar_t &Key)
{
//
}
//---------------------------------------------------------------------------

