object SGSettForm: TSGSettForm
  Left = 146
  Top = 110
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1082#1086#1085#1090#1088#1086#1083#1103' '#1075#1088#1091#1087#1087#1099' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
  ClientHeight = 525
  ClientWidth = 753
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pBottom: TPanel
    Left = 0
    Top = 472
    Width = 753
    Height = 53
    Align = alBottom
    TabOrder = 0
    object bSave: TButton
      Left = 397
      Top = 4
      Width = 113
      Height = 41
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = bSaveClick
    end
    object bExit: TButton
      Left = 267
      Top = 4
      Width = 113
      Height = 41
      Caption = #1042#1099#1081#1090#1080
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = bExitClick
    end
  end
  object gbSinusFrequencies: TGroupBox
    Left = 0
    Top = 0
    Width = 245
    Height = 472
    Align = alLeft
    Caption = #1063#1072#1089#1090#1086#1090#1099
    TabOrder = 1
    object cbTypeSize: TComboBox
      Left = 2
      Top = 15
      Width = 241
      Height = 21
      Align = alTop
      TabOrder = 0
      Text = 'cbTypeSize'
      OnSelect = cbTypeSizeSelect
    end
    object gridFrec: TDBGrid
      Left = 2
      Top = 36
      Width = 241
      Height = 409
      Align = alClient
      Color = clSkyBlue
      DataSource = sourseFrec
      ReadOnly = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'frequency_value'
          Title.Alignment = taCenter
          Title.Caption = #1063#1072#1089#1090#1086#1090#1072', '#1043#1094
          Visible = True
        end>
    end
    object navFrec: TDBNavigator
      Left = 2
      Top = 445
      Width = 241
      Height = 25
      DataSource = sourseFrec
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete]
      Align = alBottom
      TabOrder = 2
    end
  end
  object gbSolidGroup: TGroupBox
    Left = 490
    Top = 0
    Width = 263
    Height = 472
    Align = alClient
    Caption = #1043#1088#1091#1087#1087#1072' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
    TabOrder = 2
    object cbSolidGroup: TComboBox
      Left = 23
      Top = 26
      Width = 119
      Height = 21
      TabOrder = 0
      Text = 'cbSolidGroup'
      Visible = False
    end
    object bNewSG: TButton
      Left = 160
      Top = 24
      Width = 66
      Height = 25
      Caption = #1053#1086#1074#1072#1103
      TabOrder = 1
      Visible = False
    end
    object rgCalcAlgo: TRadioGroup
      Left = 23
      Top = 64
      Width = 203
      Height = 113
      Caption = #1040#1083#1075#1086#1088#1080#1090#1084' '#1056#1072#1089#1095#1077#1090#1072
      Items.Strings = (
        #1050#1086#1088#1088#1077#1083#1103#1094#1080#1103
        #1050#1074'. '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1103)
      TabOrder = 2
    end
  end
  object gbSGThreshold: TGroupBox
    Left = 245
    Top = 0
    Width = 245
    Height = 472
    Align = alLeft
    Caption = #1055#1086#1088#1086#1075#1080
    TabOrder = 3
    object Panel1: TPanel
      Left = 2
      Top = 15
      Width = 241
      Height = 21
      Align = alTop
      TabOrder = 0
    end
    object navTS: TDBNavigator
      Left = 2
      Top = 445
      Width = 241
      Height = 25
      DataSource = sourseTSz
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete]
      Align = alBottom
      TabOrder = 1
    end
    object gridTSz: TDBGrid
      Left = 2
      Top = 36
      Width = 241
      Height = 409
      Align = alClient
      Color = clSkyBlue
      DataSource = sourseTSz
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'threshold_value'
          Title.Alignment = taCenter
          Title.Caption = #1057#1084#1077#1097#1077#1085#1080#1077', % '#1087#1077#1088#1080#1086#1076#1072
          Width = 125
          Visible = True
        end>
    end
  end
  object queryFrec: TADOQuery
    AfterInsert = queryFrecAfterInsert
    Parameters = <>
    Left = 93
    Top = 192
  end
  object sourseFrec: TDataSource
    DataSet = queryFrec
    Left = 104
    Top = 280
  end
  object sourseTSz: TDataSource
    DataSet = queryTSz
    Left = 349
    Top = 280
  end
  object queryTSz: TADOQuery
    BeforePost = queryTSzBeforePost
    Parameters = <>
    Left = 352
    Top = 184
  end
  object commandFrec: TADOCommand
    Parameters = <
      item
        DataType = ftFloat
        Value = Null
      end>
    Left = 48
    Top = 344
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 80
    Top = 272
  end
end
