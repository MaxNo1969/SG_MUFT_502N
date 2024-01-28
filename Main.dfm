object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1059#1057#1058#1040#1053#1054#1042#1050#1040' '#1050#1054#1053#1058#1056#1054#1051#1071' '#1043#1056#1059#1055#1055#1067' '#1055#1056#1054#1063#1053#1054#1057#1058#1048' '#1052#1059#1060#1058' '#1053#1050#1058'. '#1055#1088#1086#1077#1082#1090' '#1055#1050#1054'-109  '
  ClientHeight = 624
  ClientWidth = 1177
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDefault
  WindowState = wsMaximized
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object SplitterMid: TSplitter
    Left = 0
    Top = 349
    Width = 1177
    Height = 5
    Cursor = crVSplit
    Align = alBottom
    Beveled = True
    Color = clGradientActiveCaption
    ParentColor = False
    OnMoved = SplitterMidMoved
    ExplicitLeft = 8
    ExplicitTop = 380
    ExplicitWidth = 976
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 58
    Width = 1177
    Height = 40
    Align = alTop
    Panels = <
      item
        Width = 400
      end
      item
        Width = 250
      end>
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 608
    Width = 1177
    Height = 16
    Align = alBottom
    TabOrder = 1
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
      Left = 1156
      Top = 1
      Width = 20
      Height = 14
      Align = alRight
      Alignment = taCenter
      Caption = 'Max'
      Visible = False
      ExplicitHeight = 13
    end
    object scbChartDragger: TScrollBar
      Left = 17
      Top = 1
      Width = 1139
      Height = 14
      Align = alClient
      Max = 10000
      Min = 1
      PageSize = 0
      Position = 1
      TabOrder = 0
      Visible = False
      OnChange = scbChartDraggerChange
    end
  end
  object PanelChartTop: TPanel
    Left = 0
    Top = 98
    Width = 1177
    Height = 251
    Align = alClient
    BorderStyle = bsSingle
    Caption = 'PanelChartTop'
    TabOrder = 2
    object SplitterRes: TSplitter
      Left = 860
      Top = 1
      Width = 5
      Height = 245
      Align = alRight
      Color = clHighlight
      ParentColor = False
      OnMoved = SplitterResMoved
      ExplicitLeft = 661
      ExplicitHeight = 265
    end
    object SignalChart: TChart
      Left = 1
      Top = 1
      Width = 859
      Height = 245
      AllowPanning = pmNone
      BackWall.Size = 2
      BottomWall.Size = 2
      LeftWall.Color = clLime
      LeftWall.Size = 2
      Legend.CheckBoxes = True
      RightWall.Size = 2
      Title.Text.Strings = (
        'TChart')
      OnScroll = SignalChartScroll
      View3D = False
      Align = alClient
      TabOrder = 0
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        36
        15
        36)
      ColorPaletteIndex = 13
      object Series1: TFastLineSeries
        LinePen.Color = 10708548
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object Series2: TFastLineSeries
        LinePen.Color = 3513587
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object Series3: TFastLineSeries
        LinePen.Color = 1330417
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object PanelSG: TPanel
      Left = 865
      Top = 1
      Width = 307
      Height = 245
      Align = alRight
      Caption = #1048#1058#1054#1043
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -96
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
  end
  object PanelChartBottom: TPanel
    Left = 0
    Top = 354
    Width = 1177
    Height = 254
    Align = alBottom
    BorderStyle = bsSingle
    Caption = 'PanelChartBottom'
    TabOrder = 3
    object EtalonChart: TChart
      Left = 1
      Top = 1
      Width = 1171
      Height = 248
      AllowPanning = pmNone
      BackWall.Size = 2
      BottomWall.Size = 2
      LeftWall.Color = clLime
      LeftWall.Size = 2
      Legend.CheckBoxes = True
      RightWall.Size = 2
      Title.Text.Strings = (
        'TChart')
      OnScroll = SignalChartScroll
      View3D = False
      Align = alClient
      TabOrder = 0
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        36
        15
        36)
      ColorPaletteIndex = 13
      object FastLineSeries1: TFastLineSeries
        LinePen.Color = 10708548
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object FastLineSeries2: TFastLineSeries
        LinePen.Color = 3513587
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object FastLineSeries3: TFastLineSeries
        LinePen.Color = 1330417
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 1177
    Height = 58
    Align = alTop
    TabOrder = 4
    ExplicitTop = -6
    object cbTypeSize: TComboBox
      Left = 1
      Top = 1
      Width = 153
      Height = 37
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = 'cbTypeSize'
      OnChange = cbTypeSizeChange
      OnSelect = cbTypeSizeSelect
    end
    object cbSGGost: TComboBox
      Left = 154
      Top = 1
      Width = 327
      Height = 37
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alLeft
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = 'cbSGGost'
      OnSelect = cbSGGostSelect
    end
    object bStart: TButton
      Left = 586
      Top = 1
      Width = 105
      Height = 56
      Align = alLeft
      Caption = #1055#1091#1089#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = bStartClick
      ExplicitLeft = 547
      ExplicitTop = -2
    end
    object bCancel: TButton
      Left = 481
      Top = 1
      Width = 105
      Height = 56
      Align = alLeft
      Caption = #1054#1090#1084#1077#1085#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = bCancelClick
    end
    object GroupBoxNGr: TGroupBox
      Left = 777
      Top = 1
      Width = 399
      Height = 56
      Align = alRight
      Caption = #1053#1086#1074#1099#1081' '#1086#1073#1088#1072#1079#1077#1094
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      object bbtCreateEtalon: TBitBtn
        Left = 277
        Top = 21
        Width = 120
        Height = 33
        Align = alRight
        Caption = #1057#1086#1079#1076#1072#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = bbtCreateEtalonClick
      end
      object cbxSG: TComboBox
        Left = 2
        Top = 21
        Width = 269
        Height = 27
        Align = alLeft
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Text = #1042#1099#1073#1088#1072#1090#1100' '#1075#1088#1091#1087#1087#1091' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
      end
    end
    object btnExit: TButton
      Left = 672
      Top = 1
      Width = 105
      Height = 56
      Align = alRight
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnExitClick
      ExplicitLeft = 668
      ExplicitTop = -4
    end
  end
  object MainMenu: TMainMenu
    Left = 736
    Top = 312
    object N3: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object menuSettings: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1080#1079#1084#1077#1088#1077#1085#1080#1081
        OnClick = menuSettingsClick
      end
      object menuSGSett: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1043#1055
        OnClick = menuSGSettClick
      end
      object menuColorSett: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1094#1074#1077#1090#1086#1074
        OnClick = menuColorSettClick
      end
      object menuTypeSize: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1090#1080#1087#1086#1088#1072#1079#1084#1077#1088#1086#1074
        OnClick = menuTypeSizeClick
      end
      object menuEtalons: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1086#1073#1088#1072#1079#1094#1086#1074
        OnClick = menuEtalonsClick
      end
      object menuExtSet: TMenuItem
        Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        OnClick = menuExtSetClick
      end
      object N1: TMenuItem
        Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1086#1073#1088#1072#1079#1094#1072#1084#1080
      end
      object N2: TMenuItem
      end
    end
    object N6: TMenuItem
      Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072
      object menuProtocol: TMenuItem
        Caption = #1055#1088#1086#1090#1086#1082#1086#1083
        Visible = False
        OnClick = MenuProtocolClick
      end
      object mnuCheckGen: TMenuItem
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072
        OnClick = mnuCheckGenClick
      end
      object mnuCheck1730: TMenuItem
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1076#1080#1089#1082#1088#1077#1090#1085#1099#1093' '#1074#1093#1086#1076#1086#1074'-'#1074#1099#1093#1086#1076#1086#1074
        OnClick = mnuCheck1730Click
      end
    end
    object N9: TMenuItem
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
      object menuSave: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = menuSaveClick
      end
      object menuOpen: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = menuOpenClick
      end
    end
    object N10: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      Visible = False
      object menuAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = menuAboutClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '.csv'
    Filter = #1057#1080#1075#1085#1072#1083' '#1075#1088#1091#1087#1087#1099' '#1087#1088#1086#1095#1085#1086#1089#1090#1080' (*.csv)|*.csv'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 680
    Top = 235
  end
  object SaveDialog: TSaveDialog
    DefaultExt = '.csv'
    Filter = #1057#1080#1075#1085#1072#1083' '#1075#1088#1091#1087#1087#1099' '#1087#1088#1086#1095#1085#1086#1089#1090#1080' (*.csv)|*.csv'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 720
    Top = 219
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 792
    Top = 232
  end
  object queryEtalon: TADOQuery
    Parameters = <>
    Left = 840
    Top = 148
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
    Left = 824
    Top = 104
  end
  object timerCheck1730: TTimer
    Enabled = False
    Interval = 10
    Left = 728
    Top = 136
  end
end
