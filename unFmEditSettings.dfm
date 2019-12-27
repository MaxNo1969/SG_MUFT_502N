object fmSettings: TfmSettings
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1048#1079#1084#1077#1085#1077#1085#1080#1077' '#1085#1072#1089#1090#1088#1086#1077#1082
  ClientHeight = 317
  ClientWidth = 583
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object DBGridSettings: TDBGrid
    Left = 0
    Top = 232
    Width = 583
    Height = 60
    Align = alBottom
    DataSource = DataSourceSettings
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        Title.Alignment = taCenter
        Visible = True
      end>
  end
  object DBNavigatorSettings: TDBNavigator
    Left = 0
    Top = 292
    Width = 583
    Height = 25
    DataSource = DataSourceSettings
    VisibleButtons = [nbEdit, nbPost, nbCancel, nbRefresh]
    Align = alBottom
    Hints.Strings = (
      #1055#1077#1088#1074#1072#1103' '#1079#1072#1087#1080#1089#1100
      #1055#1088#1077#1076#1099#1076#1091#1097#1072#1103' '#1079#1072#1087#1080#1089#1100
      #1057#1083#1077#1076#1091#1102#1097#1072#1103' '#1079#1072#1087#1080#1089#1100
      #1055#1086#1089#1083#1077#1076#1085#1103#1103' '#1079#1072#1087#1080#1089#1100
      #1042#1089#1090#1072#1074#1080#1090#1100
      #1059#1076#1072#1083#1080#1090#1100
      #1048#1079#1084#1077#1085#1080#1090#1100
      #1047#1072#1087#1080#1089#1072#1090#1100
      #1054#1090#1084#1077#1085#1072
      #1054#1073#1085#1086#1074#1080#1090#1100
      #1055#1088#1080#1085#1103#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      #1054#1090#1084#1077#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103)
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
  end
  object DataSourceSettings: TDataSource
    Left = 288
    Top = 48
  end
  object getHintsADOQuery: TADOQuery
    Parameters = <>
    Left = 288
    Top = 144
  end
end
