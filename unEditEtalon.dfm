object fmEditEtalon: TfmEditEtalon
  Left = 0
  Top = 0
  Caption = #1054#1073#1088#1072#1079#1094#1099' '#1087#1086' '#1084#1091#1092#1090#1072#1084
  ClientHeight = 510
  ClientWidth = 1125
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 25
    Width = 593
    Height = 485
    Align = alLeft
    Caption = #1054#1073#1088#1072#1079#1077#1094
    TabOrder = 0
    object navEtalon: TDBNavigator
      Left = 2
      Top = 458
      Width = 589
      Height = 25
      DataSource = dsEtalon
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete, nbPost, nbCancel]
      Align = alBottom
      TabOrder = 0
    end
    object gridEtalon: TDBGrid
      Left = 2
      Top = 15
      Width = 589
      Height = 443
      Align = alClient
      DataSource = dsEtalon
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnEditButtonClick = gridEtalonEditButtonClick
      Columns = <
        item
          Expanded = False
          FieldName = 'fenable'
          PickList.Strings = (
            '0'
            '1')
          Title.Caption = #1040#1082#1090#1080#1074
          Width = 36
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'frequency'
          Title.Alignment = taCenter
          Title.Caption = #1063#1072#1089#1090#1086#1090#1072', '#1043#1094
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'address_file'
          Title.Alignment = taCenter
          Title.Caption = #1055#1086#1083#1085#1086#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072
          Width = 105
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SGName'
          Title.Caption = #1043#1088#1091#1087#1087#1072' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
          Width = 57
          Visible = True
        end>
    end
  end
  object GroupBox2: TGroupBox
    Left = 593
    Top = 25
    Width = 332
    Height = 485
    Align = alClient
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1073#1088#1072#1079#1094#1072
    TabOrder = 1
    object navEtalonVal: TDBNavigator
      Left = 2
      Top = 458
      Width = 328
      Height = 25
      DataSource = dsEtalonVal
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete, nbPost, nbCancel]
      Align = alBottom
      TabOrder = 0
    end
    object gridEtalonVal: TDBGrid
      Left = 2
      Top = 15
      Width = 328
      Height = 443
      Align = alClient
      DataSource = dsEtalonVal
      ReadOnly = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'thres_val'
          Title.Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1089#1084#1077#1097#1077#1085#1080#1103', %'
          Width = 123
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'barkgausen_val'
          Title.Caption = #1042#1077#1083#1080#1095#1080#1085#1072' '#1041#1072#1088#1082#1075#1072#1091#1079#1077#1085#1072', '#1091#1077
          Width = 139
          Visible = True
        end>
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 1125
    Height = 25
    Align = alTop
    TabOrder = 2
    object Label1: TLabel
      Left = 1
      Top = 1
      Width = 59
      Height = 23
      Align = alLeft
      Alignment = taCenter
      Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
      Layout = tlCenter
      ExplicitHeight = 13
    end
    object Label2: TLabel
      Left = 139
      Top = 1
      Width = 23
      Height = 23
      Align = alLeft
      Alignment = taCenter
      Caption = #1043#1086#1089#1090
      Layout = tlCenter
      ExplicitHeight = 13
    end
    object cbTypeSize: TComboBox
      Left = 60
      Top = 1
      Width = 79
      Height = 21
      Align = alLeft
      TabOrder = 0
      Text = 'cbTypeSize'
      OnSelect = cbTypeSizeSelect
    end
    object bbtShowEt: TBitBtn
      Left = 241
      Top = 1
      Width = 110
      Height = 23
      Align = alLeft
      Caption = #1055#1086#1089#1084#1086#1090#1088#1077#1090#1100
      TabOrder = 1
      OnClick = bbtShowEtClick
    end
    object bbtRecalc: TBitBtn
      Left = 351
      Top = 1
      Width = 112
      Height = 23
      Align = alLeft
      Caption = #1055#1077#1088#1077#1089#1095#1077#1090' '#1086#1073#1088#1072#1079#1094#1072
      TabOrder = 2
      OnClick = bbtRecalcClick
    end
    object bbtRecalcAll: TBitBtn
      Left = 463
      Top = 1
      Width = 112
      Height = 23
      Align = alLeft
      Caption = #1055#1077#1088#1077#1089#1095#1077#1090' '#1074#1089#1077#1093
      TabOrder = 3
      OnClick = bbtRecalcAllClick
    end
    object cbSGGost: TComboBox
      Left = 162
      Top = 1
      Width = 79
      Height = 21
      Align = alLeft
      TabOrder = 4
      Text = 'cbSGGost'
      OnSelect = cbSGGostSelect
      Items.Strings = (
        #1043#1054#1057#1058' '#1056'53366-2009'
        #1043#1054#1057#1058' 633-80')
    end
  end
  object gbSGThreshold: TGroupBox
    Left = 925
    Top = 25
    Width = 200
    Height = 485
    Align = alRight
    Caption = #1055#1086#1088#1086#1075#1080
    TabOrder = 3
    object navTS: TDBNavigator
      Left = 2
      Top = 458
      Width = 196
      Height = 25
      DataSource = sourseTSz
      VisibleButtons = [nbPrior, nbNext, nbInsert, nbDelete, nbPost]
      Align = alBottom
      TabOrder = 0
    end
    object gridTSz: TDBGrid
      Left = 2
      Top = 15
      Width = 196
      Height = 443
      Align = alClient
      DataSource = sourseTSz
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
          FieldName = 'threshold_value'
          Title.Alignment = taCenter
          Title.Caption = #1057#1084#1077#1097#1077#1085#1080#1077', % '#1087#1077#1088#1080#1086#1076#1072
          Width = 125
          Visible = True
        end>
    end
  end
  object queryEtalonVal: TADOQuery
    Connection = SqlDBModule.ADOConnectionDB
    DataSource = dsEtalon
    Parameters = <>
    Left = 408
    Top = 168
  end
  object dsEtalonVal: TDataSource
    DataSet = queryEtalonVal
    Left = 448
    Top = 112
  end
  object dsEtalon: TDataSource
    DataSet = queryEtalon
    Left = 168
    Top = 104
  end
  object queryEtalon: TADOQuery
    Connection = SqlDBModule.ADOConnectionDB
    Parameters = <>
    Left = 192
    Top = 160
  end
  object cmdEtalonVal: TADOCommand
    Connection = SqlDBModule.ADOConnectionDB
    Parameters = <
      item
        Name = 'pbarkgausen_val'
        DataType = ftFloat
        NumericScale = 8
        Precision = 8
        Value = Null
      end>
    Left = 544
    Top = 216
  end
  object queryTSz: TADOQuery
    Connection = SqlDBModule.ADOConnectionDB
    BeforePost = queryTSzBeforePost
    Parameters = <>
    Left = 632
    Top = 152
  end
  object sourseTSz: TDataSource
    DataSet = queryTSz
    Left = 629
    Top = 200
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 64
    Top = 168
  end
end
