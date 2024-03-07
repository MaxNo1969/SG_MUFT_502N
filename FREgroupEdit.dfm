object EgroupEditFrm: TEgroupEditFrm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1043#1088#1091#1087#1087#1072' '#1086#1073#1088#1072#1079#1094#1086#1074
  ClientHeight = 237
  ClientWidth = 332
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 54
    Width = 23
    Height = 13
    Caption = #1043#1086#1089#1090
  end
  object Label2: TLabel
    Left = 8
    Top = 89
    Width = 59
    Height = 13
    Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
  end
  object Label3: TLabel
    Left = 8
    Top = 16
    Width = 51
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '
  end
  object Label4: TLabel
    Left = 8
    Top = 129
    Width = 47
    Height = 13
    Caption = #1047#1072#1082#1072#1079#1095#1080#1082
  end
  object Label5: TLabel
    Left = 8
    Top = 169
    Width = 58
    Height = 13
    Caption = #1058#1080#1087' '#1088#1077#1079#1100#1073#1099
  end
  object Label6: TLabel
    Left = 8
    Top = 209
    Width = 52
    Height = 13
    Caption = #1058#1080#1087' '#1092#1072#1089#1082#1080
  end
  object cbGost: TComboBox
    Left = 88
    Top = 51
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 0
  end
  object cbTypeSizes: TComboBox
    Left = 88
    Top = 86
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 1
  end
  object edName: TEdit
    Left = 88
    Top = 13
    Width = 145
    Height = 21
    TabOrder = 2
    TextHint = #1053#1072#1079#1074#1072#1085#1080#1077' '#1075#1088#1091#1087#1087#1099
  end
  object cbCustomer: TComboBox
    Left = 88
    Top = 126
    Width = 145
    Height = 21
    TabOrder = 3
    TextHint = #1047#1072#1082#1072#1079#1095#1080#1082
    OnKeyDown = cbKeyDown
  end
  object cbThreadType: TComboBox
    Left = 88
    Top = 166
    Width = 145
    Height = 21
    TabOrder = 4
    TextHint = #1058#1080#1087' '#1088#1077#1079#1100#1073#1099
    OnKeyDown = cbKeyDown
  end
  object cbChampferType: TComboBox
    Left = 88
    Top = 206
    Width = 145
    Height = 21
    TabOrder = 5
    TextHint = #1058#1080#1087' '#1092#1072#1089#1082#1080
    OnKeyDown = cbKeyDown
  end
  object btnSave: TButton
    Left = 248
    Top = 11
    Width = 75
    Height = 25
    Caption = #1047#1072#1087#1080#1089#1072#1090#1100
    TabOrder = 6
  end
  object btnCancel: TButton
    Left = 248
    Top = 49
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 7
    OnClick = btnCancelClick
  end
end
