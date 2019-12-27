object fmViewMeasure: TfmViewMeasure
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'fmViewMeasure'
  ClientHeight = 623
  ClientWidth = 1270
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object chartView: TChart
    Left = 0
    Top = 0
    Width = 1270
    Height = 623
    Title.Text.Strings = (
      'TChart')
    View3D = False
    View3DWalls = False
    Align = alClient
    PopupMenu = popupMenuChartZone
    TabOrder = 0
    ExplicitLeft = 304
    ExplicitTop = 200
    ExplicitWidth = 400
    ExplicitHeight = 250
    DefaultCanvas = 'TGDIPlusCanvas'
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
  object popupMenuChartZone: TPopupMenu
    Left = 608
    Top = 120
    object ZoomUp: TMenuItem
      Caption = #1059#1074#1077#1083#1080#1095#1080#1090#1100' '#1085#1072' 1,5'
      OnClick = ZoomUpClick
    end
    object ZoomDown: TMenuItem
      Caption = #1059#1084#1077#1085#1100#1096#1080#1090#1100' '#1085#1072' 1,5'
      OnClick = ZoomDownClick
    end
    object mnuZoomReset: TMenuItem
      Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1091#1074#1077#1083#1080#1095#1077#1085#1080#1077
      OnClick = mnuZoomResetClick
    end
  end
end
