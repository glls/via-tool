object FormMerge: TFormMerge
  Left = 600
  Top = 304
  ActiveControl = ButtonOK
  BorderStyle = bsDialog
  Caption = 'Merge'
  ClientHeight = 225
  ClientWidth = 207
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
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
  object CheckListBoxRegions: TCheckListBox
    Left = 8
    Top = 8
    Width = 193
    Height = 185
    ItemHeight = 13
    PopupMenu = PopupMenuMerge
    TabOrder = 2
  end
  object PopupMenuMerge: TPopupMenu
    Left = 72
    Top = 40
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
