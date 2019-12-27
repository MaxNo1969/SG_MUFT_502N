object ADCSettForm: TADCSettForm
  Left = 195
  Top = 55
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
  ClientHeight = 477
  ClientWidth = 765
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pBottom: TPanel
    Left = 0
    Top = 407
    Width = 765
    Height = 70
    Align = alBottom
    TabOrder = 0
    object bSave: TButton
      Left = 250
      Top = 16
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
      Left = 384
      Top = 16
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
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 765
    Height = 407
    ActivePage = ppPage
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object ppPage: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1082#1086#1085#1090#1088#1086#1083#1103
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object gbSG: TGroupBox
        Left = 3
        Top = 3
        Width = 750
        Height = 367
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1075#1088#1091#1087#1087#1099' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label2: TLabel
          Left = 23
          Top = 35
          Width = 190
          Height = 19
          Caption = #1063#1072#1089#1090#1086#1090#1072' '#1074#1074#1086#1076#1072' '#1085#1072' '#1082#1072#1085#1072#1083' ('#1043#1094')'
          WordWrap = True
        end
        object Label1: TLabel
          Left = 23
          Top = 69
          Width = 139
          Height = 19
          Caption = #1063#1072#1089#1090#1086#1090#1072' '#1074#1099#1074#1086#1076#1072' ('#1043#1094')'
          Visible = False
          WordWrap = True
        end
        object lCheckMuftaLevelCaption: TLabel
          Left = 23
          Top = 295
          Width = 61
          Height = 57
          Caption = #1059#1088#1086#1074#1077#1085#1100' '#1089#1080#1075#1085#1072#1083#1072' '#1084#1091#1092#1090#1099
          Color = clBtnFace
          ParentColor = False
          WordWrap = True
        end
        object readRate: TEdit
          Left = 228
          Top = 32
          Width = 182
          Height = 27
          Enabled = False
          TabOrder = 0
        end
        object sendRate: TEdit
          Left = 228
          Top = 66
          Width = 182
          Height = 27
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inline FSSG: TFilterSettings
          Left = 450
          Top = 14
          Width = 300
          Height = 348
          TabOrder = 2
          ExplicitLeft = 450
          ExplicitTop = 14
          ExplicitWidth = 300
          ExplicitHeight = 348
          inherited GroupBox1: TGroupBox
            Left = 5
            Top = 2
            Caption = #1060#1080#1083#1100#1090#1088' '#1075#1088#1091#1087#1087#1099' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
            ExplicitLeft = 5
            ExplicitTop = 2
            inherited gbButterworth: TGroupBox
              inherited eRolloff: TEdit
                Left = 179
                ExplicitLeft = 179
              end
            end
          end
        end
        object tbCheckMuftaLevel: TTrackBar
          Left = 90
          Top = 303
          Width = 297
          Height = 45
          Max = 100000
          Position = 25
          TabOrder = 3
          TickStyle = tsNone
          OnChange = tbCheckMuftaLevelChange
        end
      end
    end
  end
  object edLevelMut: TEdit
    Left = 400
    Top = 336
    Width = 56
    Height = 21
    Color = clInfoBk
    TabOrder = 2
    Text = '10000'
    OnEnter = edLevelMutEnter
    OnExit = edLevelMutExit
    OnKeyDown = edLevelMutKeyDown
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 928
    Top = 664
  end
end
