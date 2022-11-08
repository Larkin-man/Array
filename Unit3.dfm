object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1053#1086#1074#1099#1077' '#1088#1072#1089#1095#1077#1090#1099
  ClientHeight = 189
  ClientWidth = 349
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 129
    Height = 13
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1074#1072#1088#1080#1072#1085#1090' '#1074#1074#1086#1076#1072
  end
  object Label2: TLabel
    Left = 8
    Top = 50
    Width = 75
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1074#1077#1088#1096#1080#1085':'
  end
  object Label3: TLabel
    Left = 8
    Top = 112
    Width = 73
    Height = 13
    Caption = #1055#1091#1090#1100' '#1082' '#1092#1072#1081#1083#1091':'
    Enabled = False
  end
  object RadioButton1: TRadioButton
    Left = 8
    Top = 27
    Width = 113
    Height = 17
    Caption = #1057' '#1082#1083#1072#1074#1080#1072#1090#1091#1088#1099
    Checked = True
    TabOrder = 0
    TabStop = True
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 8
    Top = 89
    Width = 113
    Height = 17
    Caption = #1057' '#1092#1072#1081#1083#1072
    TabOrder = 1
    OnClick = RadioButton2Click
  end
  object Edit1: TEdit
    Left = 113
    Top = 50
    Width = 195
    Height = 21
    NumbersOnly = True
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 105
    Top = 112
    Width = 203
    Height = 21
    Enabled = False
    TabOrder = 3
  end
  object Button1: TButton
    Left = 314
    Top = 112
    Width = 25
    Height = 21
    Caption = '...'
    Enabled = False
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 264
    Top = 152
    Width = 75
    Height = 25
    Caption = #1042#1074#1077#1089#1090#1080
    TabOrder = 5
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Left = 192
    Top = 144
  end
end
