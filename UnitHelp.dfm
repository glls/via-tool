object FormHelp: TFormHelp
  Left = 1099
  Top = 111
  Width = 569
  Height = 603
  Caption = 'Help'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    561
    576)
  PixelsPerInch = 96
  TextHeight = 13
  object MemoHelp: TMemo
    Left = 16
    Top = 8
    Width = 529
    Height = 519
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = bsNone
    Color = clBtnFace
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Video Image Annotation Tool'
      '=========================='
      'Video annotation shortcuts'
      'F5 - Toggle Record mode'
      'F6 - Play Video'
      'F7 - Goto Frame'
      'CTRL-F9 - Previous Frame'
      'CTRL-F10 - Next Frame'
      'CTRL-I Next I Frame'
      'CTRL-U Previous I Frame'
      'CTRL-W Close all'
      ''
      
        'You can move and resize regions on video frame ONLY when in '#39'Edi' +
        't mode'#39'.'
      ''
      'To enter a new Region Name edit the name and press Enter.'
      ''
      'Go to a specific frame and press the '#39'Set'#39' button to set the '
      'starting or ending frame for regions or shots.'
      ''
      'You can Double-Click inside the X,Y,Width and Height edit '
      'boxes to set the data manually.'
      ''
      'You can delete nodes inside list boxes by pressing the DEL key.'
      ''
      'Insert new regions or shots with '#39'INS'#39' key.'
      ''
      'Supported video formats: MPEG1, MPEG2'
      ''
      'Bounding Box ShortCut keys work only in EDIT mode [F5]')
    ParentCtl3D = False
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object ButtonOK: TButton
    Left = 480
    Top = 544
    Width = 75
    Height = 21
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = ButtonOKClick
  end
end
