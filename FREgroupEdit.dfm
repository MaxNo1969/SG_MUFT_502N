object EgroupEditFrm: TEgroupEditFrm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1043#1088#1091#1087#1087#1072' '#1086#1073#1088#1072#1079#1094#1086#1074
  ClientHeight = 363
  ClientWidth = 338
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
    Top = 8
    Width = 36
    Height = 13
    Caption = #1043#1088#1091#1087#1087#1072
  end
  object Label4: TLabel
    Left = 8
    Top = 153
    Width = 47
    Height = 13
    Caption = #1047#1072#1082#1072#1079#1095#1080#1082
  end
  object Label5: TLabel
    Left = 8
    Top = 193
    Width = 58
    Height = 13
    Caption = #1058#1080#1087' '#1088#1077#1079#1100#1073#1099
  end
  object Label6: TLabel
    Left = 8
    Top = 233
    Width = 52
    Height = 13
    Caption = #1058#1080#1087' '#1092#1072#1089#1082#1080
  end
  object Label7: TLabel
    Left = 8
    Top = 126
    Width = 48
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077
  end
  object Label8: TLabel
    Left = 8
    Top = 280
    Width = 75
    Height = 13
    Caption = #1055#1086#1088#1086#1075' '#1085#1072#1083#1080#1095#1080#1103
  end
  object cbGost: TComboBox
    Left = 88
    Top = 44
    Width = 145
    Height = 21
    TabOrder = 0
    OnChange = onElementChange
  end
  object cbTypeSizes: TComboBox
    Left = 88
    Top = 86
    Width = 145
    Height = 21
    TabOrder = 1
    OnChange = onElementChange
  end
  object edName: TEdit
    Left = 57
    Top = 8
    Width = 185
    Height = 21
    ReadOnly = True
    TabOrder = 2
    TextHint = #1053#1072#1079#1074#1072#1085#1080#1077' '#1075#1088#1091#1087#1087#1099
  end
  object cbCustomer: TComboBox
    Left = 88
    Top = 150
    Width = 145
    Height = 21
    TabOrder = 3
    TextHint = #1047#1072#1082#1072#1079#1095#1080#1082
    OnChange = onElementChange
    OnKeyDown = cbKeyDown
  end
  object cbThreadType: TComboBox
    Left = 88
    Top = 190
    Width = 145
    Height = 21
    TabOrder = 4
    TextHint = #1058#1080#1087' '#1088#1077#1079#1100#1073#1099
    OnChange = onElementChange
    OnKeyDown = cbKeyDown
  end
  object cbChampferType: TComboBox
    Left = 88
    Top = 230
    Width = 145
    Height = 21
    TabOrder = 5
    TextHint = #1058#1080#1087' '#1092#1072#1089#1082#1080
    OnChange = onElementChange
    OnKeyDown = cbKeyDown
  end
  object btnAdd: TButton
    Left = 248
    Top = 11
    Width = 75
    Height = 25
    Caption = #1053#1086#1074#1072#1103
    TabOrder = 6
    OnClick = btnAddClick
  end
  object btnCancel: TButton
    Left = 249
    Top = 84
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 7
    OnClick = btnCancelClick
  end
  object Button1: TButton
    Left = 249
    Top = 42
    Width = 75
    Height = 25
    Caption = #1047#1072#1087#1080#1089#1072#1090#1100
    TabOrder = 8
    OnClick = btnSaveClick
  end
  object cbName: TComboBox
    Left = 88
    Top = 123
    Width = 145
    Height = 21
    TabOrder = 9
    TextHint = #1048#1084#1103' '#1075#1088#1091#1087#1087#1099
    OnChange = onElementChange
    OnKeyDown = cbKeyDown
  end
  object edCheckMuftaLevelMax: TEdit
    Left = 104
    Top = 277
    Width = 49
    Height = 21
    TabOrder = 10
  end
  object edCheckMuftaLevelMin: TEdit
    Left = 168
    Top = 277
    Width = 49
    Height = 21
    TabOrder = 11
  end
  object lbeFreqSignal: TLabeledEdit
    Left = 8
    Top = 326
    Width = 120
    Height = 21
    Alignment = taCenter
    EditLabel.Width = 104
    EditLabel.Height = 13
    EditLabel.Caption = #1063#1072#1089#1090#1086#1090#1072' '#1089#1080#1075#1085#1072#1083#1072', '#1043#1094
    TabOrder = 12
    Text = '195000 '
  end
  object lbeVoltage: TLabeledEdit
    Left = 154
    Top = 326
    Width = 120
    Height = 21
    Alignment = taCenter
    EditLabel.Width = 129
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1099#1093#1086#1076#1085#1086#1077' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1077', '#1042
    TabOrder = 13
    Text = '3'
  end
end
