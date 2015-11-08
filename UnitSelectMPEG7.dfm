object FormExtractMPEG7: TFormExtractMPEG7
  Left = 511
  Top = 254
  ActiveControl = ButtonOK
  BorderStyle = bsDialog
  Caption = 'Extract MPEG-7'
  ClientHeight = 225
  ClientWidth = 207
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object cxLabel: TLabel
    Left = 7
    Top = 8
    Width = 127
    Height = 13
    Caption = 'Select MPEG-7 descriptors'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object ButtonOK: TButton
    Left = 48
    Top = 200
    Width = 75
    Height = 21
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object ButtonCancel: TButton
    Left = 128
    Top = 200
    Width = 75
    Height = 21
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object CheckListBoxMPEG7: TCheckListBox
    Left = 8
    Top = 24
    Width = 193
    Height = 169
    ItemHeight = 13
    Items.Strings = (
      'Color Layout'
      'Color Structure'
      'Contour Shape'
      'Dominant Color'
      'Edge Histogram'
      'Homogeneous Texture'
      'Region Shape'
      'Scalable Color'
      'Texture Browsing')
    PopupMenu = PopupMenuMPEG7
    TabOrder = 2
  end
  object PopupMenuMPEG7: TPopupMenu
    Left = 152
    Top = 48
    object SelectAll1: TMenuItem
      Caption = 'Select &All'
      OnClick = SelectAll1Click
    end
    object SelectNone1: TMenuItem
      Caption = 'Select &None'
      OnClick = SelectNone1Click
    end
  end
end
