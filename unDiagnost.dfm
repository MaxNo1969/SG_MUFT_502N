object fmDiagnost: TfmDiagnost
  Left = 0
  Top = 0
  Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072
  ClientHeight = 420
  ClientWidth = 951
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PanelBottom: TPanel
    Left = 0
    Top = 308
    Width = 951
    Height = 93
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      951
      93)
    object btnStopGen: TBitBtn
      Left = 292
      Top = 45
      Width = 120
      Height = 25
      Caption = #1054#1089#1090#1072#1085#1086#1074' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072
      Enabled = False
      TabOrder = 0
      OnClick = btnStopGenClick
    end
    object btnStartGen: TBitBtn
      Left = 12
      Top = 45
      Width = 120
      Height = 25
      Caption = #1047#1072#1087#1091#1089#1082' '#1043#1077#1085#1077#1088#1072#1090#1086#1088#1072
      TabOrder = 1
      OnClick = btnStartGenClick
    end
    object lbeFrecSignalGSPF052: TLabeledEdit
      Left = 152
      Top = 18
      Width = 120
      Height = 21
      Alignment = taCenter
      EditLabel.Width = 104
      EditLabel.Height = 13
      EditLabel.Caption = #1063#1072#1089#1090#1086#1090#1072' '#1089#1080#1075#1085#1072#1083#1072', '#1043#1094
      TabOrder = 2
      Text = '50000'
    end
    object lbeVoltageGSPF052: TLabeledEdit
      Left = 292
      Top = 18
      Width = 120
      Height = 21
      Alignment = taCenter
      EditLabel.Width = 129
      EditLabel.Height = 13
      EditLabel.Caption = #1042#1099#1093#1086#1076#1085#1086#1077' '#1085#1072#1087#1088#1103#1078#1077#1085#1080#1077', '#1042
      TabOrder = 3
      Text = '1'
    end
    object lbeFrecDiscrGSPF052: TLabeledEdit
      Left = 12
      Top = 18
      Width = 120
      Height = 21
      Alignment = taCenter
      EditLabel.Width = 141
      EditLabel.Height = 13
      EditLabel.Caption = #1063#1072#1089#1090#1086#1090#1072' '#1076#1080#1089#1082#1088#1077#1090#1080#1079#1072#1094#1080#1080', '#1043#1094
      TabOrder = 4
      Text = '10000000'
    end
    object btnStartSer: TBitBtn
      Left = 604
      Top = 45
      Width = 120
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1087#1091#1089#1082' '#1089#1077#1088#1080#1080
      TabOrder = 5
      Visible = False
      OnClick = btnStartSerClick
    end
    object btnReCalc: TBitBtn
      Left = 452
      Top = 45
      Width = 120
      Height = 25
      Caption = #1055#1077#1088#1077#1089#1095#1077#1090' '#1076#1072#1085#1085#1099#1093
      TabOrder = 6
      OnClick = btnReCalcClick
    end
    object GroupBoxNGr: TGroupBox
      Left = 765
      Top = 1
      Width = 185
      Height = 91
      Align = alRight
      Caption = #1053#1086#1074#1099#1081' '#1101#1090#1072#1083#1086#1085
      TabOrder = 7
      DesignSize = (
        185
        91)
      object bbtCreateEtalon: TBitBtn
        Left = 9
        Top = 42
        Width = 120
        Height = 25
        Anchors = [akTop, akRight]
        Caption = #1057#1086#1079#1076#1072#1090#1100
        TabOrder = 0
        OnClick = bbtCreateEtalonClick
      end
      object cbxSGD: TComboBox
        Left = 11
        Top = 15
        Width = 118
        Height = 21
        TabOrder = 1
        Text = #1042#1099#1073#1088#1072#1090#1100' '#1075#1088#1091#1087#1087#1091' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
      end
    end
    object Button1: TButton
      Left = 900
      Top = 16
      Width = 49
      Height = 25
      Caption = 'btnTst'
      Enabled = False
      TabOrder = 8
      Visible = False
      OnClick = Button1Click
    end
  end
  object PanelGraph: TPanel
    Left = 0
    Top = 0
    Width = 951
    Height = 292
    Align = alClient
    TabOrder = 1
    object ChartGPSF052: TChart
      Left = 1
      Top = 1
      Width = 949
      Height = 290
      Title.Text.Strings = (
        'TChart')
      OnScroll = ChartGPSF052Scroll
      View3D = False
      View3DWalls = False
      Align = alClient
      TabOrder = 0
      DesignSize = (
        949
        290)
      DefaultCanvas = 'TGDIPlusCanvas'
      ColorPaletteIndex = 13
      object PanelSG: TPanel
        Left = 640
        Top = 0
        Width = 148
        Height = 41
        Anchors = [akTop, akRight]
        Caption = '???'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object Series1: TLineSeries
        Brush.BackColor = clDefault
        LinePen.Color = 10708548
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 292
    Width = 951
    Height = 16
    Align = alBottom
    TabOrder = 2
    object lMinScrollbar: TLabel
      Left = 1
      Top = 1
      Width = 16
      Height = 14
      Align = alLeft
      Alignment = taCenter
      Caption = 'Min'
      Transparent = True
      Visible = False
      ExplicitHeight = 13
    end
    object lMaxScrollbar: TLabel
      Left = 930
      Top = 1
      Width = 20
      Height = 14
      Align = alRight
      Alignment = taCenter
      Caption = 'Max'
      Visible = False
      ExplicitHeight = 13
    end
    object scbChartDraggerDiag: TScrollBar
      Left = 17
      Top = 1
      Width = 913
      Height = 14
      Align = alClient
      Max = 10000
      Min = 1
      PageSize = 0
      Position = 1
      TabOrder = 0
      OnChange = scbChartDraggerDiagChange
    end
  end
  object StatusBarDiag: TStatusBar
    Left = 0
    Top = 401
    Width = 951
    Height = 19
    Panels = <
      item
        Width = 250
      end
      item
        Width = 50
      end>
  end
  object queryEtalon: TADOQuery
    Parameters = <>
    Left = 504
    Top = 172
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
end
