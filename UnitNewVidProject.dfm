object FormNewVid: TFormNewVid
  Left = 578
  Top = 343
  BorderStyle = bsDialog
  Caption = 'New Video Project'
  ClientHeight = 129
  ClientWidth = 263
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lvlVideo: TLabel
    Left = 8
    Top = 48
    Width = 46
    Height = 13
    Caption = 'Video File'
  end
  object lblName: TLabel
    Left = 8
    Top = 8
    Width = 64
    Height = 13
    Caption = 'Project Name'
  end
  object ButtonOK: TButton
    Left = 104
    Top = 104
    Width = 75
    Height = 21
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = ButtonOKClick
  end
  object ButtonCancel: TButton
    Left = 184
    Top = 104
    Width = 75
    Height = 21
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
  end
  object teName: TEdit
    Left = 8
    Top = 24
    Width = 249
    Height = 21
    TabOrder = 2
  end
  object teFile: TEdit
    Left = 6
    Top = 64
    Width = 227
    Height = 21
    TabOrder = 3
  end
  object btnFile: TButton
    Left = 232
    Top = 64
    Width = 25
    Height = 25
    Caption = '...'
    TabOrder = 4
    OnClick = btnFileClick
  end
  object OpenDialogV: TOpenDialog
    Filter = 'MPEG videos|*.mpg;*.m1v;*.m2v|All files|*.*'
    Left = 168
    Top = 8
  end
end
