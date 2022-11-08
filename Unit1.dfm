object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'RatingSystemBandwidth'
  ClientHeight = 318
  ClientWidth = 612
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 208
    Width = 138
    Height = 26
    Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1087#1088#1086#1087#1091#1089#1082#1085#1072#1103' '#1089#1086#1089#1086#1073#1085#1086#1089#1090#1100' '#1048#1042#1050' :'
    Visible = False
    WordWrap = True
  end
  object Label2: TLabel
    Left = 32
    Top = 72
    Width = 199
    Height = 22
    Caption = 'RatingSystemBandwidth'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 33
    Top = 100
    Width = 543
    Height = 38
    Caption = 
      #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1076#1083#1103' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1103' '#1084#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1081' '#1087#1088#1086#1087#1091#1089#1082#1085#1086#1081' '#1089#1087#1086#1089#1086#1073#1085#1086#1089#1090#1080' '#1048#1042#1050 +
      ', '#1080' '#1076#1077#1084#1086#1085#1089#1090#1088#1072#1094#1080#1080' '#1087#1086#1096#1072#1075#1086#1074#1086#1075#1086' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' '#1072#1083#1075#1086#1088#1080#1090#1084#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object Label4: TLabel
    Left = 34
    Top = 145
    Width = 542
    Height = 57
    Caption = 
      #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1088#1072#1079#1088#1072#1073#1086#1090#1072#1085#1072' '#1074' '#1088#1072#1084#1082#1072#1093' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' '#1082#1091#1088#1089#1086#1074#1086#1075#1086' '#1087#1088#1086#1077#1082#1090#1072' '#1087#1086' '#1076 +
      #1080#1089#1094#1080#1087#1083#1080#1085#1077' "'#1054#1089#1085#1086#1074#1099' '#1087#1088#1086#1077#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103' '#1089#1088#1077#1076#1089#1090#1074' '#1074#1099#1095#1080#1089#1083#1080#1090#1077#1083#1100#1085#1086#1081' '#1090#1077#1093#1085#1080#1082#1080'"' +
      ' '#1089#1090#1091#1076#1077#1085#1090#1086#1084' 328 '#1075#1088#1091#1087#1087#1099' '#1057#1072#1093#1085#1086' '#1057#1077#1088#1075#1077#1077#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object StringGrid1: TStringGrid
    Left = 34
    Top = 28
    Width = 393
    Height = 153
    Color = clInactiveBorder
    ColCount = 6
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs]
    ParentShowHint = False
    ShowHint = False
    TabOrder = 0
    Visible = False
  end
  object BitBtn1: TBitBtn
    Left = 350
    Top = 203
    Width = 75
    Height = 25
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 1
    Visible = False
    OnClick = BitBtn1Click
  end
  object StringGrid2: TStringGrid
    Left = 97
    Top = 8
    Width = 329
    Height = 34
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    TabOrder = 2
    Visible = False
  end
  object Edit1: TEdit
    Left = 184
    Top = 208
    Width = 121
    Height = 21
    TabOrder = 3
    Visible = False
  end
  object MainMenu1: TMainMenu
    Left = 40
    Top = 16
    object N1: TMenuItem
      Caption = #1056#1072#1089#1095#1077#1090#1099
      object N4: TMenuItem
        Caption = #1053#1086#1074#1099#1077
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      end
      object N3: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N3Click
      end
    end
    object N9: TMenuItem
      Caption = #1042#1080#1076
      object N10: TMenuItem
        Caption = #1055#1086#1096#1072#1075#1086#1074#1086#1077' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1077
        OnClick = N10Click
      end
    end
    object N2: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object N7: TMenuItem
        Caption = #1057#1087#1088#1072#1074#1082#1072
      end
      object N8: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = N8Click
      end
    end
  end
end
