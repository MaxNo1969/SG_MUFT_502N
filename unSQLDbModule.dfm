object SqlDBModule: TSqlDBModule
  OldCreateOrder = False
  Height = 329
  Width = 400
  object ADOConnectionDB: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=1;Persist Security Info=True;User I' +
      'D=sa;Initial Catalog=buran5033;Data Source=PC-WIN7060\SQLEXPRESS'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    BeforeConnect = ADOConnectionDBBeforeConnect
    Left = 56
    Top = 32
  end
  object ADOCommandDB: TADOCommand
    Connection = ADOConnectionDB
    Parameters = <>
    Left = 56
    Top = 104
  end
  object ADOQueryDB: TADOQuery
    Connection = ADOConnectionDB
    AfterClose = ADOQueryDBAfterClose
    Parameters = <>
    Left = 56
    Top = 168
  end
  object ADOTableDB: TADOTable
    Connection = ADOConnectionDB
    Left = 56
    Top = 232
  end
  object ADODataSet: TADODataSet
    Connection = ADOConnectionDB
    CursorType = ctStatic
    FieldDefs = <
      item
        Name = #1053#1086#1084#1077#1088' '#1090#1088#1091#1073#1099
        DataType = ftWideString
        Size = 50
      end
      item
        Name = #1057#1077#1088#1080#1081#1085#1099#1081' '#1085#1086#1084#1077#1088
        DataType = ftWideString
        Size = 50
      end
      item
        Name = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
        Attributes = [faFixed]
        DataType = ftInteger
      end
      item
        Name = #1057#1090#1072#1090#1091#1089
        DataType = ftWideString
        Size = 50
      end
      item
        Name = #1047#1072#1082#1072#1079#1095#1080#1082
        DataType = ftWideString
        Size = 50
      end
      item
        Name = #1054#1087#1077#1088#1072#1090#1086#1088
        DataType = ftWideString
        Size = 50
      end
      item
        Name = #1044#1072#1090#1072' '#1080' '#1074#1088#1077#1084#1103' '#1079#1072#1087#1080#1089#1080
        Attributes = [faReadonly]
        DataType = ftWideString
        Size = 10
      end>
    Parameters = <>
    StoreDefs = True
    Left = 168
    Top = 40
  end
  object queryVirt: TADOQuery
    ConnectionString = 'FILE NAME=D:\Work\GP_Muft_2017_08\Win32\Debug\connectSQLVirt.udl'
    Parameters = <>
    SQL.Strings = (
      'select * from LCardDout')
    Left = 224
    Top = 184
  end
end
