object FormColor: TFormColor
  Left = 353
  Top = 233
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1094#1074#1077#1090#1072
  ClientHeight = 316
  ClientWidth = 299
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object ColorSolidGroups: TGroupBox
    Left = 0
    Top = 0
    Width = 299
    Height = 253
    Align = alClient
    Caption = #1062#1074#1077#1090#1072' '#1075#1088#1091#1087#1087' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 2
      Top = 21
      Width = 295
      Height = 230
      Align = alClient
      DataSource = DataSource1
      TabOrder = 0
      TitleFont.Charset = RUSSIAN_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -16
      TitleFont.Name = 'Times New Roman'
      TitleFont.Style = []
      OnDrawColumnCell = DBGrid1DrawColumnCell
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'rec_id'
          ReadOnly = True
          Title.Caption = #1053#1086#1084#1077#1088
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SGName'
          ReadOnly = True
          Title.Caption = #1043#1088#1091#1087#1087#1072
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Color'
          Title.Caption = #1062#1074#1077#1090
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Gost_id'
          ReadOnly = True
          Title.Caption = #1043#1054#1057#1058
          Visible = True
        end>
    end
  end
  object pBottom: TPanel
    Left = 0
    Top = 253
    Width = 299
    Height = 63
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      299
      63)
    object BClose: TButton
      Left = 99
      Top = 15
      Width = 89
      Height = 34
      Anchors = [akTop]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 0
      OnClick = BCloseClick
    end
    object BSave: TButton
      Left = 47
      Top = 15
      Width = 89
      Height = 34
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      TabOrder = 1
      Visible = False
      OnClick = BSaveClick
    end
  end
  object ColorDialog: TColorDialog
    Color = clGreen
    Left = 8
    Top = 266
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 184
    Top = 160
  end
  object ADOQuery1: TADOQuery
    Parameters = <>
    Left = 96
    Top = 184
  end
end
