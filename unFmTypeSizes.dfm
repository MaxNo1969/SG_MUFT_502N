object fmTypeSizes: TfmTypeSizes
  Left = 0
  Top = 0
  Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088#1099
  ClientHeight = 299
  ClientWidth = 267
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object gridTypeSizes: TDBGrid
    Left = 0
    Top = 0
    Width = 267
    Height = 274
    Align = alClient
    Color = clInfoBk
    DataSource = dsTypeSizes
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
        Width = 117
        Visible = True
      end
      item
        Expanded = False
        FieldName = #1044#1080#1072#1084#1077#1090#1088
        Width = 115
        Visible = True
      end>
  end
  object navTypeSizes: TDBNavigator
    Left = 0
    Top = 274
    Width = 267
    Height = 25
    DataSource = dsTypeSizes
    VisibleButtons = [nbInsert, nbPost, nbCancel]
    Align = alBottom
    Enabled = False
    TabOrder = 1
  end
  object queryTypeSizes: TADOQuery
    Connection = SqlDBModule.ADOConnectionDB
    Parameters = <>
    Left = 40
    Top = 168
  end
  object dsTypeSizes: TDataSource
    DataSet = queryTypeSizes
    Left = 32
    Top = 80
  end
  object ApplicationEventsTs: TApplicationEvents
    OnMessage = ApplicationEventsTsMessage
    Left = 128
    Top = 96
  end
end
