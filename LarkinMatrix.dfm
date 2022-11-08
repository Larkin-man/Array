object Form1: TForm1
  Left = 63
  Top = 124
  Width = 656
  Height = 393
  Caption = #1058#1091#1090' '#1087#1086#1095#1090#1080' '#1074#1077#1079#1100#1076#1077' '#1087#1086#1087#1091#1090#1072#1085#1099' [C][R]'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 20
  object StringGrid1: TStringGrid
    Left = 0
    Top = 0
    Width = 329
    Height = 161
    Align = alCustom
    ColCount = 12
    DefaultColWidth = 34
    DefaultRowHeight = 22
    RowCount = 8
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    PopupMenu = PopupMenu1
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 200
    Top = 168
    Width = 281
    Height = 185
    Caption = 'Inter '#1090#1091#1090' '#1087#1077#1088#1077#1087#1091#1090#1072#1085#1086' '#1057' '#1080' R'
    TabOrder = 1
    object Button1: TButton
      Left = 8
      Top = 24
      Width = 73
      Height = 25
      Caption = 'GetX'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Edit2: TEdit
      Left = 80
      Top = 24
      Width = 73
      Height = 28
      TabOrder = 1
      Text = 'Edit2'
    end
    object Button2: TButton
      Left = 152
      Top = 24
      Width = 73
      Height = 25
      Caption = 'SetX'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button5: TButton
      Left = 8
      Top = 56
      Width = 73
      Height = 25
      Caption = 'sx = x'
      TabOrder = 3
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 152
      Top = 56
      Width = 73
      Height = 25
      Caption = 'x = sx'
      TabOrder = 4
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 8
      Top = 88
      Width = 73
      Height = 25
      Caption = 'GetPX'
      TabOrder = 5
      OnClick = Button7Click
    end
    object Edit3: TEdit
      Left = 80
      Top = 88
      Width = 73
      Height = 28
      TabOrder = 6
      Text = 'Edit3'
    end
    object Button8: TButton
      Left = 152
      Top = 88
      Width = 73
      Height = 25
      Caption = 'SetPX'
      TabOrder = 7
      OnClick = Button8Click
    end
    object LabeledEdit3: TLabeledEdit
      Left = 112
      Top = 152
      Width = 41
      Height = 28
      EditLabel.Width = 40
      EditLabel.Height = 20
      EditLabel.Caption = 'Rows'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 8
      Text = '4'
    end
    object LabeledEdit4: TLabeledEdit
      Left = 8
      Top = 152
      Width = 41
      Height = 28
      EditLabel.Width = 62
      EditLabel.Height = 20
      EditLabel.Caption = 'Columns'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 9
      Text = '4'
    end
    object IntNewMat: TButton
      Left = 48
      Top = 154
      Width = 65
      Height = 25
      Caption = 'NewMat'
      TabOrder = 10
      OnClick = IntNewMatClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 168
    Width = 185
    Height = 185
    Caption = 'Form1'
    TabOrder = 2
    object Button3: TButton
      Left = 8
      Top = 24
      Width = 49
      Height = 25
      Caption = 'GetX'
      TabOrder = 0
      OnClick = Button3Click
    end
    object Edit1: TEdit
      Left = 56
      Top = 24
      Width = 73
      Height = 28
      TabOrder = 1
      Text = 'Edit1'
    end
    object Button4: TButton
      Left = 128
      Top = 24
      Width = 49
      Height = 25
      Caption = 'SetX'
      TabOrder = 2
      OnClick = Button4Click
    end
    object Button11: TButton
      Left = 104
      Top = 56
      Width = 75
      Height = 25
      Caption = 'NewMas'
      TabOrder = 3
      OnClick = Button11Click
    end
    object NewMat: TButton
      Left = 16
      Top = 136
      Width = 89
      Height = 25
      Caption = 'NewMat'
      TabOrder = 4
      OnClick = NewMatClick
    end
    object CountR: TLabeledEdit
      Left = 72
      Top = 104
      Width = 41
      Height = 28
      EditLabel.Width = 40
      EditLabel.Height = 20
      EditLabel.Caption = 'Rows'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      Text = '4'
    end
    object CountC: TLabeledEdit
      Left = 8
      Top = 104
      Width = 41
      Height = 28
      EditLabel.Width = 62
      EditLabel.Height = 20
      EditLabel.Caption = 'Columns'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 6
      Text = '3'
    end
  end
  object Button9: TButton
    Left = 336
    Top = 36
    Width = 75
    Height = 25
    Caption = 'GetMas'
    TabOrder = 3
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 408
    Top = 36
    Width = 75
    Height = 25
    Caption = 'SetMas'
    TabOrder = 4
    OnClick = Button10Click
  end
  object Button12: TButton
    Left = 336
    Top = 88
    Width = 75
    Height = 25
    Caption = 'GetMas'
    TabOrder = 5
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 408
    Top = 88
    Width = 75
    Height = 25
    Caption = 'SetMas'
    TabOrder = 6
    OnClick = Button13Click
  end
  object GetMat: TButton
    Left = 336
    Top = 60
    Width = 75
    Height = 25
    Caption = 'GetMAT'
    TabOrder = 7
    OnClick = GetMatClick
  end
  object SetMat: TButton
    Left = 408
    Top = 60
    Width = 75
    Height = 25
    Caption = 'SetMAT'
    TabOrder = 8
    OnClick = SetMatClick
  end
  object IntGetMat: TButton
    Left = 336
    Top = 112
    Width = 75
    Height = 25
    Caption = 'GetMAT'
    TabOrder = 9
    OnClick = IntGetMatClick
  end
  object IntSetMat: TButton
    Left = 408
    Top = 112
    Width = 75
    Height = 25
    Caption = 'SetMAT'
    TabOrder = 10
    OnClick = IntSetMatClick
  end
  object StaticText1: TStaticText
    Left = 368
    Top = 290
    Width = 84
    Height = 24
    Caption = 'StaticText1'
    TabOrder = 11
  end
  object StaticText2: TStaticText
    Left = 336
    Top = 8
    Width = 126
    Height = 24
    Caption = 'Mat[EditC][EditR]'
    TabOrder = 12
  end
  object GroupBox3: TGroupBox
    Left = 488
    Top = 8
    Width = 153
    Height = 345
    Caption = #1059#1082#1072#1079#1072#1090#1077#1083#1100' '#1085#1072' Mat'
    TabOrder = 13
    DesignSize = (
      153
      345)
    object LabelVal: TLabel
      Left = 48
      Top = 80
      Width = 41
      Height = 20
      Caption = 'Value'
    end
    object Label2: TLabel
      Left = 8
      Top = 24
      Width = 126
      Height = 20
      Caption = 'Pmat* = **mat[idx]'
    end
    object SpinI: TCSpinEdit
      Left = 8
      Top = 45
      Width = 57
      Height = 30
      Hint = 'Index'
      Anchors = [akTop]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
    object SetIndex: TButton
      Left = 72
      Top = 48
      Width = 75
      Height = 25
      Caption = 'SetIndex'
      TabOrder = 1
      OnClick = SetIndexClick
    end
    object SpinM: TCSpinEdit
      Left = 48
      Top = 109
      Width = 57
      Height = 30
      Hint = 'Value'
      Anchors = [akTop]
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object SetV: TButton
      Left = 104
      Top = 112
      Width = 41
      Height = 25
      Caption = 'Set'
      TabOrder = 3
      OnClick = SetVClick
    end
    object GetV: TButton
      Left = 8
      Top = 112
      Width = 41
      Height = 25
      Caption = 'Get'
      TabOrder = 4
      OnClick = GetVClick
    end
    object Button14: TButton
      Left = 8
      Top = 256
      Width = 75
      Height = 25
      Caption = 'Button14'
      TabOrder = 5
      OnClick = Button14Click
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 128
    Top = 48
    object N1: TMenuItem
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1055#1077#1088#1077#1079#1072#1087#1086#1083#1085#1080#1090#1100
      OnClick = N2Click
    end
  end
end
