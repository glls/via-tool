object FormOptions: TFormOptions
  Left = 480
  Top = 194
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 436
  ClientWidth = 517
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Default'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  DesignSize = (
    517
    436)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 328
    Top = 8
    Width = 112
    Height = 13
    Caption = 'Keyboard Shortcuts'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 82
    Height = 13
    Caption = 'User Interface'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel1: TBevel
    Left = 312
    Top = 8
    Width = 9
    Height = 369
    Shape = bsLeftLine
  end
  object Label3: TLabel
    Left = 8
    Top = 120
    Width = 62
    Height = 13
    Caption = 'Directories'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel2: TBevel
    Left = 8
    Top = 264
    Width = 305
    Height = 9
    Shape = bsTopLine
  end
  object Bevel3: TBevel
    Left = 136
    Top = 8
    Width = 25
    Height = 105
    Shape = bsLeftLine
  end
  object Label4: TLabel
    Left = 160
    Top = 8
    Width = 62
    Height = 13
    Caption = 'Annotation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel4: TBevel
    Left = 8
    Top = 112
    Width = 305
    Height = 9
    Shape = bsTopLine
  end
  object Label5: TLabel
    Left = 8
    Top = 272
    Width = 78
    Height = 13
    Caption = 'Segmentation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object cxLabel2: TLabel
    Left = 16
    Top = 24
    Width = 65
    Height = 13
    Caption = 'Video Interval'
    Transparent = True
  end
  object cxLabel19: TLabel
    Left = 81
    Top = 41
    Width = 13
    Height = 13
    Caption = 'ms'
    Transparent = True
  end
  object cxLabel20: TLabel
    Left = 16
    Top = 64
    Width = 50
    Height = 13
    Caption = 'Pen Width'
    Transparent = True
  end
  object cxLabel1: TLabel
    Left = 81
    Top = 81
    Width = 26
    Height = 13
    Caption = 'pixels'
    Transparent = True
  end
  object cxLabel3: TLabel
    Left = 328
    Top = 40
    Width = 57
    Height = 13
    Caption = 'Frame FWD'
    Transparent = True
  end
  object cxLabel4: TLabel
    Left = 328
    Top = 72
    Width = 58
    Height = 13
    Caption = 'Frame REW'
    Transparent = True
  end
  object cxLabel5: TLabel
    Left = 16
    Top = 288
    Width = 229
    Height = 13
    Caption = 'Executable (inside Segmentation Tools directory)'
    Transparent = True
  end
  object cxLabel6: TLabel
    Left = 16
    Top = 176
    Width = 58
    Height = 13
    Caption = 'Output Data'
    Transparent = True
  end
  object cxLabel7: TLabel
    Left = 16
    Top = 216
    Width = 94
    Height = 13
    Caption = 'Segmentation Tools'
    Transparent = True
  end
  object cxLabel8: TLabel
    Left = 328
    Top = 104
    Width = 93
    Height = 13
    Caption = 'Increase Box Width'
    Transparent = True
  end
  object cxLabel9: TLabel
    Left = 328
    Top = 128
    Width = 98
    Height = 13
    Caption = 'Decrease Box Width'
    Transparent = True
  end
  object cxLabel10: TLabel
    Left = 328
    Top = 152
    Width = 96
    Height = 13
    Caption = 'Increase Box Height'
    Transparent = True
  end
  object cxLabel11: TLabel
    Left = 328
    Top = 176
    Width = 101
    Height = 13
    Caption = 'Decrease Box Height'
    Transparent = True
  end
  object cxLabel12: TLabel
    Left = 16
    Top = 136
    Width = 58
    Height = 13
    Caption = 'AceToolBox'
    Transparent = True
  end
  object cxLabel13: TLabel
    Left = 16
    Top = 328
    Width = 118
    Height = 13
    Caption = 'Command line arguments'
    Transparent = True
  end
  object cxLabel14: TLabel
    Left = 16
    Top = 368
    Width = 215
    Height = 13
    Caption = '%f : input image filename without file extention'
    Transparent = True
  end
  object cxLabel15: TLabel
    Left = 16
    Top = 400
    Width = 270
    Height = 13
    Caption = '%d: output directory (Output Data directory + Imagename)'
    Transparent = True
  end
  object cxLabel16: TLabel
    Left = 16
    Top = 384
    Width = 119
    Height = 13
    Caption = '%F : input image filename'
    Transparent = True
  end
  object Label6: TLabel
    Left = 170
    Top = 48
    Width = 129
    Height = 13
    Caption = 'region names when sorting '
  end
  object btnOK: TButton
    Left = 356
    Top = 408
    Width = 75
    Height = 21
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 11
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 436
    Top = 408
    Width = 75
    Height = 21
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
  object HotKeyFrameFWD: THotKey
    Left = 440
    Top = 40
    Width = 57
    Height = 19
    HotKey = 121
    InvalidKeys = [hcNone, hcShift]
    Modifiers = []
    TabOrder = 1
  end
  object HotKeyFrameREW: THotKey
    Left = 440
    Top = 72
    Width = 57
    Height = 19
    HotKey = 120
    InvalidKeys = [hcNone, hcShift]
    Modifiers = []
    TabOrder = 2
  end
  object btnDirAce: TButton
    Left = 276
    Top = 152
    Width = 25
    Height = 21
    Caption = '...'
    TabOrder = 4
    OnClick = btnDirAceClick
  end
  object EditDirAce: TEdit
    Left = 16
    Top = 152
    Width = 258
    Height = 21
    TabOrder = 3
  end
  object EditDirSeg: TEdit
    Left = 16
    Top = 232
    Width = 258
    Height = 21
    TabOrder = 5
  end
  object btnDirSeg: TButton
    Left = 276
    Top = 232
    Width = 25
    Height = 21
    Caption = '...'
    TabOrder = 6
    OnClick = btnDirSegClick
  end
  object EditDirOut: TEdit
    Left = 16
    Top = 192
    Width = 257
    Height = 21
    TabOrder = 7
  end
  object btnDirOut: TButton
    Left = 276
    Top = 192
    Width = 25
    Height = 21
    Caption = '...'
    TabOrder = 9
    OnClick = btnDirOutClick
  end
  object chkbxRenumberSort: TCheckBox
    Left = 152
    Top = 32
    Width = 145
    Height = 17
    Caption = 'Rename and renumber'
    TabOrder = 8
  end
  object HotKeyBBWI: THotKey
    Left = 440
    Top = 104
    Width = 57
    Height = 19
    HotKey = 88
    InvalidKeys = [hcShift]
    Modifiers = []
    TabOrder = 10
  end
  object HotKeyBBWD: THotKey
    Left = 440
    Top = 128
    Width = 57
    Height = 19
    HotKey = 67
    InvalidKeys = [hcShift]
    Modifiers = []
    TabOrder = 12
  end
  object HotKeyBBHI: THotKey
    Left = 440
    Top = 152
    Width = 57
    Height = 19
    HotKey = 87
    InvalidKeys = [hcShift]
    Modifiers = []
    TabOrder = 13
  end
  object HotKeyBBHD: THotKey
    Left = 440
    Top = 176
    Width = 57
    Height = 19
    HotKey = 69
    InvalidKeys = [hcShift]
    Modifiers = []
    TabOrder = 14
  end
  object EditSegExe: TEdit
    Left = 16
    Top = 304
    Width = 258
    Height = 21
    TabOrder = 15
    Text = 'itiseg.exe'
  end
  object EditSegOptions: TEdit
    Left = 16
    Top = 344
    Width = 258
    Height = 21
    TabOrder = 16
    Text = '%d %d %f 8 2 1 1 0 10'
  end
  object EditVideoInt: TEdit
    Left = 16
    Top = 40
    Width = 65
    Height = 21
    TabOrder = 17
    Text = '100'
  end
  object EditPenWidth: TEdit
    Left = 16
    Top = 80
    Width = 65
    Height = 21
    TabOrder = 18
    Text = '2'
  end
end
