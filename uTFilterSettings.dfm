object FilterSettings: TFilterSettings
  Left = 0
  Top = 0
  Width = 288
  Height = 368
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 289
    Height = 344
    Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object gbButterworth: TGroupBox
      Left = 9
      Top = 141
      Width = 272
      Height = 196
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label11: TLabel
        Left = 8
        Top = 21
        Width = 44
        Height = 13
        Caption = #1055#1086#1088#1103#1076#1086#1082
      end
      object Label12: TLabel
        Left = 8
        Top = 51
        Width = 73
        Height = 13
        Caption = #1063#1072#1089#1090#1086#1090#1072' '#1089#1088#1077#1079#1072
      end
      object Label13: TLabel
        Left = 8
        Top = 80
        Width = 79
        Height = 13
        Caption = #1062#1077#1085#1090#1088' '#1092#1080#1083#1100#1090#1088#1072
      end
      object Label17: TLabel
        Left = 8
        Top = 109
        Width = 87
        Height = 13
        Caption = #1064#1080#1088#1080#1085#1072' '#1092#1080#1083#1100#1090#1088#1072
      end
      object Label18: TLabel
        Left = 8
        Top = 140
        Width = 169
        Height = 13
        Caption = #1055#1091#1083#1100#1089#1072#1094#1080#1080' '#1074' '#1087#1086#1083#1086#1089#1077' '#1087#1088#1086#1087#1091#1089#1082#1072#1085#1080#1103
        WordWrap = True
      end
      object Label19: TLabel
        Left = 8
        Top = 170
        Width = 165
        Height = 13
        Caption = #1055#1091#1083#1100#1089#1072#1094#1080#1080' '#1074' '#1087#1086#1083#1086#1089#1077' '#1087#1086#1076#1072#1074#1083#1077#1085#1080#1103
        WordWrap = True
      end
      object csOrder: TCSpinEdit
        Left = 188
        Top = 17
        Width = 77
        Height = 24
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        MaxValue = 20
        ParentColor = True
        ParentFont = False
        TabOrder = 0
      end
      object eCutoffFreq: TEdit
        Left = 188
        Top = 47
        Width = 76
        Height = 23
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        TabOrder = 1
      end
      object eCenterFreq: TEdit
        Left = 188
        Top = 76
        Width = 76
        Height = 23
        BevelInner = bvNone
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        TabOrder = 2
      end
      object eWidthFreq: TEdit
        Left = 187
        Top = 105
        Width = 77
        Height = 23
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        TabOrder = 3
      end
      object eRippleDb: TEdit
        Left = 187
        Top = 134
        Width = 77
        Height = 23
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        TabOrder = 4
      end
      object eRolloff: TEdit
        Left = 187
        Top = 163
        Width = 77
        Height = 23
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        TabOrder = 5
      end
    end
    object rgFilterSubType: TRadioGroup
      Left = 126
      Top = 38
      Width = 119
      Height = 103
      Caption = #1055#1086#1076#1090#1080#1087
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        #1053#1080#1079#1082#1080#1093' '#1095#1072#1089#1090#1086#1090
        #1042#1099#1089#1086#1082#1080#1093' '#1095#1072#1089#1090#1086#1090
        #1055#1086#1083#1086#1089#1086#1074#1086#1081
        #1047#1072#1075#1088#1072#1078#1076#1072#1102#1097#1080#1081)
      ParentFont = False
      TabOrder = 1
      OnClick = rgFilterSubTypeClick
    end
    object rgFilterType: TRadioGroup
      Left = 8
      Top = 38
      Width = 112
      Height = 103
      Caption = #1058#1080#1087' '#1092#1080#1083#1100#1090#1088#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        #1041#1072#1090#1090#1077#1088#1074#1086#1088#1090#1072
        #1063#1077#1073#1099#1096#1077#1074#1072
        #1069#1083#1083#1080#1087#1090#1080#1095#1077#1089#1082#1080#1081)
      ParentFont = False
      TabOrder = 2
      OnClick = rgFilterTypeClick
    end
    object CBUsed: TCheckBox
      Left = 9
      Top = 20
      Width = 97
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
  end
end
