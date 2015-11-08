object FormAbout: TFormAbout
  Left = 684
  Top = 270
  BorderStyle = bsDialog
  Caption = 'About'
  ClientHeight = 292
  ClientWidth = 337
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel2: TBevel
    Left = 8
    Top = 104
    Width = 321
    Height = 145
  end
  object Bevel1: TBevel
    Left = 8
    Top = 24
    Width = 321
    Height = 50
    Style = bsRaised
  end
  object lblTitle: TLabel
    Left = 87
    Top = 32
    Width = 164
    Height = 13
    Caption = 'Video Image Annotation Tool'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblVersion: TLabel
    Left = 136
    Top = 48
    Width = 66
    Height = 13
    Caption = 'version 1.xxy'
  end
  object Label4: TLabel
    Left = 89
    Top = 120
    Width = 161
    Height = 13
    Caption = 'Multimedia Knowledge Laboratory'
  end
  object Label5: TLabel
    Left = 85
    Top = 136
    Width = 172
    Height = 13
    Caption = 'Informatics and Telematics Institute'
  end
  object lblURL: TLabel
    Left = 117
    Top = 200
    Width = 103
    Height = 13
    Cursor = crHandPoint
    Caption = 'http://mklab.iti.gr/via'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = lblURLClick
  end
  object Label2: TLabel
    Left = 34
    Top = 152
    Width = 270
    Height = 13
    Caption = 'Centre for Research and Technology Hellas (CERTH-ITI)'
  end
  object lblMail: TLabel
    Left = 133
    Top = 216
    Width = 72
    Height = 13
    Cursor = crHandPoint
    Caption = 'mailto:gl@iti.gr'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = lblMailClick
  end
  object lblHome: TLabel
    Left = 70
    Top = 184
    Width = 197
    Height = 13
    Cursor = crHandPoint
    Caption = 'http://sourceforge.net/projects/via-tool/'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = lblHomeClick
  end
  object ButtonOK: TButton
    Left = 256
    Top = 264
    Width = 75
    Height = 21
    Cancel = True
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
end
