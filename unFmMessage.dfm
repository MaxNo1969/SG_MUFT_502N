object fmMessage: TfmMessage
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1048#1079#1074#1077#1097#1077#1085#1080#1103
  ClientHeight = 511
  ClientWidth = 956
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object labelMsg: TLabel
    Left = 0
    Top = 0
    Width = 956
    Height = 470
    Align = alClient
    Alignment = taCenter
    Caption = #1069#1090#1086' '#1086#1082#1085#1086' '#1076#1083#1103' '#1074#1099#1074#1086#1076#1072' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080' '#1086#1073' '#1086#1096#1080#1073#1082#1072#1093' '#1080' '#1087#1088#1086#1095#1077#1084'...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -48
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
    ExplicitWidth = 608
    ExplicitHeight = 174
  end
  object panelBottom: TPanel
    Left = 0
    Top = 470
    Width = 956
    Height = 41
    Align = alBottom
    TabOrder = 0
    ExplicitTop = 258
    ExplicitWidth = 635
    object speedButtonOk: TSpeedButton
      Left = 1
      Top = 1
      Width = 954
      Height = 39
      Align = alClient
      Caption = #1055#1088#1080#1085#1103#1090#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = speedButtonOkClick
      ExplicitLeft = 272
      ExplicitTop = 16
      ExplicitWidth = 23
      ExplicitHeight = 22
    end
  end
end
