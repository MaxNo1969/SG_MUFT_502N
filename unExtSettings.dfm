object fmExtSettings: TfmExtSettings
  Left = 0
  Top = 0
  Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 299
  ClientWidth = 537
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
  object gridExtSet: TDBGrid
    Left = 0
    Top = 0
    Width = 537
    Height = 274
    Align = alClient
    Color = clInfoBk
    DataSource = dsExtSet
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = gridExtSetDblClick
  end
  object navExtSet: TDBNavigator
    Left = 0
    Top = 274
    Width = 537
    Height = 25
    DataSource = dsExtSet
    VisibleButtons = [nbFirst, nbPrior, nbPost, nbCancel]
    Align = alBottom
    Enabled = False
    TabOrder = 1
  end
  object dsExtSet: TDataSource
    DataSet = queryExtSet
    Left = 32
    Top = 80
  end
  object apEvExtSet: TApplicationEvents
    OnMessage = apEvExtSetMessage
    Left = 152
    Top = 80
  end
  object queryExtSet: TADOQuery
    Connection = SqlDBModule.ADOConnectionDB
    BeforePost = queryExtSetBeforePost
    Parameters = <>
    Left = 40
    Top = 168
  end
  object openDExtSet: TOpenDialog
    Left = 192
    Top = 184
  end
end
