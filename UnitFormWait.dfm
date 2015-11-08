object FormWait: TFormWait
  Left = 629
  Top = 322
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'FormWait'
  ClientHeight = 100
  ClientWidth = 540
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 540
    Height = 100
    Align = alClient
  end
  object LabelWait: TLabel
    Left = 219
    Top = 16
    Width = 57
    Height = 13
    Caption = 'Please Wait'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object LabelStatus: TLabel
    Left = 8
    Top = 72
    Width = 521
    Height = 19
    AutoSize = False
    Caption = 'Running...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
end
