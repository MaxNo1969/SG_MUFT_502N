object PasswordForm: TPasswordForm
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1042#1074#1077#1076#1080#1090#1077' '#1087#1072#1088#1086#1083#1100
  ClientHeight = 79
  ClientWidth = 297
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object edit: TEdit
    Left = 24
    Top = 16
    Width = 249
    Height = 21
    TabOrder = 0
  end
  object okBtn: TButton
    Left = 56
    Top = 43
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 1
    OnClick = okBtnClick
  end
  object cancelBtn: TButton
    Left = 160
    Top = 43
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 2
    OnClick = cancelBtnClick
  end
end
