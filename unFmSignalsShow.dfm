object fmSignalsShow: TfmSignalsShow
  Left = 0
  Top = 0
  Caption = #1057#1080#1075#1085#1072#1083#1099' - '#1090#1077#1082#1091#1097#1080#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
  ClientHeight = 671
  ClientWidth = 1282
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PanelRight: TPanel
    Left = 0
    Top = 0
    Width = 1282
    Height = 671
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Microsoft Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object StringGridDIO: TStringGrid
      Left = 1
      Top = 42
      Width = 839
      Height = 549
      Align = alClient
      Color = clSkyBlue
      ColCount = 4
      FixedColor = clInactiveCaption
      RowCount = 35
      GradientEndColor = clActiveCaption
      GradientStartColor = clSkyBlue
      GridLineWidth = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      TabOrder = 0
      OnDrawCell = StringGridDIODrawCell
      ColWidths = (
        156
        132
        125
        368)
      RowHeights = (
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24)
    end
    object StatusBarSignalsState: TStatusBar
      Left = 1
      Top = 591
      Width = 1280
      Height = 19
      Panels = <>
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 610
      Width = 1280
      Height = 19
      Panels = <>
    end
    object PanelBottom: TPanel
      Left = 1
      Top = 629
      Width = 1280
      Height = 41
      Align = alBottom
      TabOrder = 3
      object ButtonStart: TButton
        Left = 1
        Top = 1
        Width = 192
        Height = 39
        Align = alLeft
        Caption = #1047#1072#1087#1091#1089#1082' '#1087#1088#1086#1089#1084#1086#1090#1088#1072
        TabOrder = 0
        OnClick = ButtonStartClick
      end
      object ButtonStop: TButton
        Left = 1102
        Top = 1
        Width = 177
        Height = 39
        Align = alRight
        Caption = #1055#1088#1077#1082#1088#1072#1090#1080#1090#1100' '#1087#1088#1086#1089#1084#1086#1090#1088
        Enabled = False
        TabOrder = 1
        OnClick = ButtonStopClick
      end
    end
    object StringGridADC: TStringGrid
      Left = 840
      Top = 42
      Width = 441
      Height = 549
      Align = alRight
      Color = clSkyBlue
      ColCount = 2
      FixedColor = clInactiveCaption
      RowCount = 33
      GradientEndColor = clActiveCaption
      GradientStartColor = clSkyBlue
      GridLineWidth = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      TabOrder = 4
      OnDrawCell = StringGridDIODrawCell
      ColWidths = (
        319
        87)
      RowHeights = (
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24)
    end
    object PanelTop: TPanel
      Left = 1
      Top = 1
      Width = 1280
      Height = 41
      Align = alTop
      TabOrder = 5
      object Label1: TLabel
        Left = 1
        Top = 1
        Width = 776
        Height = 39
        Align = alLeft
        Alignment = taCenter
        AutoSize = False
        Caption = #1062#1080#1092#1088#1086#1074#1099#1077' '#1074#1093#1086#1076#1099'-'#1074#1099#1093#1086#1076#1099
      end
      object Label2: TLabel
        Left = 845
        Top = 1
        Width = 434
        Height = 39
        Align = alRight
        Alignment = taCenter
        AutoSize = False
        Caption = #1042#1093#1086#1076#1099' '#1040#1062#1055
      end
    end
  end
  object timerCheckSignals: TTimer
    Enabled = False
    Interval = 200
    OnTimer = timerCheckSignalsTimer
    Left = 504
    Top = 376
  end
end
