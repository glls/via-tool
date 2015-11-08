object FormImport: TFormImport
  Left = 699
  Top = 266
  Width = 392
  Height = 182
  Caption = 'Import Trajectory XML file'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Default'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  DesignSize = (
    384
    155)
  PixelsPerInch = 96
  TextHeight = 13
  object XMLTrajTree: TTreeView
    Left = 8
    Top = 48
    Width = 177
    Height = 88
    Cursor = crHourGlass
    Anchors = [akLeft, akTop, akBottom]
    DragMode = dmAutomatic
    Indent = 19
    ReadOnly = True
    TabOrder = 3
    Visible = False
  end
  object Memo1: TMemo
    Left = 192
    Top = 48
    Width = 177
    Height = 88
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 4
    Visible = False
  end
  object ButtonParse: TButton
    Left = 16
    Top = 8
    Width = 75
    Height = 21
    Caption = 'Parse'
    TabOrder = 0
    Visible = False
    OnClick = ButtonParseClick
  end
  object StaticTextI: TStaticText
    Left = 129
    Top = 14
    Width = 126
    Height = 17
    Cursor = crHourGlass
    Caption = 'Importing XML data...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object StaticTextNode: TStaticText
    Left = 16
    Top = 136
    Width = 50
    Height = 17
    Cursor = crHourGlass
    Caption = 'Nodes : 0'
    TabOrder = 5
  end
  object StaticTextRegions: TStaticText
    Left = 80
    Top = 136
    Width = 58
    Height = 17
    Cursor = crHourGlass
    Caption = 'Regions : 0'
    TabOrder = 6
  end
  object StaticTextE: TStaticText
    Left = 117
    Top = 30
    Width = 151
    Height = 17
    Cursor = crHourGlass
    Caption = 'ERROR: invalid XML data'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object ButtonOK: TButton
    Left = 304
    Top = 120
    Width = 75
    Height = 21
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 7
    OnClick = ButtonOKClick
  end
  object XMLTraj: TXMLDocument
    Left = 56
    Top = 64
    DOMVendorDesc = 'MSXML'
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 24
    Top = 64
  end
end
