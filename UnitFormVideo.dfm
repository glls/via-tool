object FormVideo: TFormVideo
  Left = 319
  Top = 103
  Align = alClient
  BorderStyle = bsNone
  Caption = 'FormVideo'
  ClientHeight = 722
  ClientWidth = 1136
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Default'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object PanelVideoTop: TPanel
    Left = 0
    Top = 0
    Width = 1136
    Height = 36
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object LabelLocked1: TLabel
      Left = 8
      Top = 8
      Width = 108
      Height = 13
      Caption = 'Interactive region edit :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Default'
      Font.Style = []
      ParentFont = False
      Transparent = True
    end
    object LabelRecord: TLabel
      Left = 136
      Top = 8
      Width = 58
      Height = 13
      Caption = 'Recording...'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Default'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = True
      Visible = False
    end
    object LabelLocked: TLabel
      Left = 136
      Top = 8
      Width = 36
      Height = 13
      Caption = 'Locked'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Default'
      Font.Style = []
      ParentFont = False
      Transparent = True
    end
    object EditTimeCode: TLabeledEdit
      Left = 592
      Top = 8
      Width = 113
      Height = 22
      Color = clBtnFace
      EditLabel.Width = 64
      EditLabel.Height = 16
      EditLabel.Caption = 'TimeCode'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'MS Sans Serif'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = GREEK_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 3
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object LabelStatus: TLabeledEdit
      Left = 758
      Top = 8
      Width = 195
      Height = 22
      Color = clBtnFace
      EditLabel.Width = 37
      EditLabel.Height = 16
      EditLabel.Caption = 'Status'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'MS Sans Serif'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = GREEK_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 3
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object EditFrame: TLabeledEdit
      Left = 438
      Top = 8
      Width = 73
      Height = 22
      Color = clBtnFace
      EditLabel.Width = 39
      EditLabel.Height = 16
      EditLabel.Caption = 'Frame'
      EditLabel.Font.Charset = DEFAULT_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'MS Sans Serif'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = GREEK_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 3
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
  end
  object PanelLeft: TPanel
    Left = 0
    Top = 36
    Width = 345
    Height = 686
    Align = alLeft
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      345
      686)
    object PageControlVideo: TPageControl
      Left = 8
      Top = 8
      Width = 329
      Height = 440
      ActivePage = TabSheetVideoReg
      TabIndex = 0
      TabOrder = 0
      object TabSheetVideoReg: TTabSheet
        Caption = 'Regions'
        object Label5: TLabel
          Left = 8
          Top = 256
          Width = 135
          Height = 13
          Caption = 'Selected Region Descriptors'
          Transparent = True
        end
        object cxLabel3: TLabel
          Left = 192
          Top = 168
          Width = 7
          Height = 13
          Caption = 'X'
          Transparent = True
        end
        object cxLabel4: TLabel
          Left = 256
          Top = 168
          Width = 7
          Height = 13
          Caption = 'Y'
          Transparent = True
        end
        object cxLabelRName: TLabel
          Left = 192
          Top = 8
          Width = 65
          Height = 13
          Caption = 'Region Name'
          Transparent = True
        end
        object cxLabel8: TLabel
          Left = 192
          Top = 88
          Width = 54
          Height = 13
          Caption = 'Start Frame'
          Transparent = True
        end
        object cxLabel9: TLabel
          Left = 192
          Top = 128
          Width = 51
          Height = 13
          Caption = 'End Frame'
          Transparent = True
        end
        object cxLabel10: TLabel
          Left = 192
          Top = 48
          Width = 24
          Height = 13
          Caption = 'Color'
          Transparent = True
        end
        object cxLabel5: TLabel
          Left = 256
          Top = 206
          Width = 31
          Height = 13
          Caption = 'Height'
          Transparent = True
        end
        object cxLabel6: TLabel
          Left = 192
          Top = 206
          Width = 28
          Height = 13
          Caption = 'Width'
          Transparent = True
        end
        object ButtonRegionEF: TButton
          Left = 264
          Top = 144
          Width = 49
          Height = 21
          Caption = 'Set'
          TabOrder = 5
          OnClick = ButtonRegionEFClick
        end
        object ButtonRegionSF: TButton
          Left = 264
          Top = 104
          Width = 49
          Height = 21
          Caption = 'Set'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = ButtonRegionSFClick
        end
        object ButtonToFront: TButton
          Left = 8
          Top = 224
          Width = 81
          Height = 25
          Caption = 'Bring to Front'
          TabOrder = 12
          OnClick = ButtonToFrontClick
        end
        object ButtonToBack: TButton
          Left = 88
          Top = 224
          Width = 81
          Height = 25
          Caption = 'Send to Back'
          TabOrder = 13
          OnClick = ButtonToBackClick
        end
        object ButtonCreateR: TButton
          Left = 8
          Top = 192
          Width = 25
          Height = 25
          Hint = 'Create a new region'
          Caption = '+'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 8
          OnClick = ButtonCreateRClick
        end
        object ButtonDelR: TButton
          Left = 32
          Top = 192
          Width = 25
          Height = 25
          Hint = 'Delete selected region'
          Caption = '-'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 9
          OnClick = ButtonDelRClick
        end
        object ButtonAddRegionDesc: TButton
          Left = 8
          Top = 384
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 17
          OnClick = ButtonAddRegionDescClick
        end
        object ButtonDelRegionDesc: TButton
          Left = 32
          Top = 384
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 18
          OnClick = ButtonDelRegionDescClick
        end
        object ButtonGotoRegionStart: TButton
          Left = 190
          Top = 246
          Width = 65
          Height = 25
          Caption = 'Goto Start'
          TabOrder = 10
          OnClick = ButtonGotoRegionStartClick
        end
        object ButtonGotoRegionEnd: TButton
          Left = 256
          Top = 246
          Width = 57
          Height = 25
          Caption = 'Goto End'
          TabOrder = 11
          OnClick = ButtonGotoRegionEndClick
        end
        object ListBoxNodes: TListBox
          Left = 8
          Top = 8
          Width = 177
          Height = 177
          ItemHeight = 13
          TabOrder = 0
          OnClick = ListBoxNodesClick
          OnKeyUp = ListBoxNodesKeyUp
        end
        object ListBoxRegionDesc: TListBox
          Left = 8
          Top = 272
          Width = 305
          Height = 105
          DragMode = dmAutomatic
          ItemHeight = 13
          TabOrder = 16
          OnDragDrop = ListBoxRegionDescDragDrop
          OnDragOver = ListBoxRegionDescDragOver
          OnKeyUp = ListBoxRegionDescKeyUp
        end
        object EditRName: TEdit
          Left = 192
          Top = 24
          Width = 121
          Height = 21
          TabOrder = 1
          Text = 'Region'
          OnKeyPress = EditRNameKeyPress
        end
        object EditRegionEF: TEdit
          Left = 192
          Top = 144
          Width = 65
          Height = 21
          TabOrder = 4
          Text = '0'
          OnDblClick = EditRegionEFDblClick
        end
        object EditRX: TEdit
          Left = 192
          Top = 184
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 6
          Text = '0'
          OnDblClick = EditRXDblClick
        end
        object EditRY: TEdit
          Left = 256
          Top = 184
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 7
          Text = '0'
          OnDblClick = EditRYDblClick
        end
        object EditRW: TEdit
          Left = 192
          Top = 222
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 14
          Text = '0'
          OnDblClick = EditRWDblClick
        end
        object EditRH: TEdit
          Left = 256
          Top = 222
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 15
          Text = '0'
          OnDblClick = EditRHDblClick
        end
        object EditRegionSF: TEdit
          Left = 192
          Top = 104
          Width = 65
          Height = 21
          TabOrder = 2
          Text = '0'
          OnDblClick = EditRegionSFDblClick
        end
        object ButtonSortR: TButton
          Left = 64
          Top = 192
          Width = 49
          Height = 25
          Hint = 'Sort regions by start frame'
          Caption = 'Sort'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 19
          OnClick = ButtonSortRClick
        end
        object ColorBoxR: TColorBox
          Left = 192
          Top = 64
          Width = 121
          Height = 22
          ItemHeight = 16
          TabOrder = 20
        end
      end
      object TabSheetVideoShot: TTabSheet
        Caption = 'Shots'
        ImageIndex = 1
        object Label2: TLabel
          Left = 8
          Top = 256
          Width = 123
          Height = 13
          Caption = 'Selected Shot Descriptors'
          Transparent = True
        end
        object cxLabel11: TLabel
          Left = 192
          Top = 56
          Width = 54
          Height = 13
          Caption = 'Start Frame'
          Transparent = True
        end
        object cxLabel12: TLabel
          Left = 192
          Top = 96
          Width = 51
          Height = 13
          Caption = 'End Frame'
          Transparent = True
        end
        object cxLabel13: TLabel
          Left = 192
          Top = 8
          Width = 53
          Height = 13
          Caption = 'Shot Name'
          Transparent = True
        end
        object ButtonAddShot: TButton
          Left = 8
          Top = 192
          Width = 25
          Height = 25
          Hint = 'Create a new shot'
          Caption = '+'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 6
          OnClick = ButtonAddShotClick
        end
        object ButtonDelShot: TButton
          Left = 32
          Top = 192
          Width = 25
          Height = 25
          Hint = 'Delete selected shot'
          Caption = '-'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 7
          OnClick = ButtonDelShotClick
        end
        object ButtonGotoShotStart: TButton
          Left = 192
          Top = 192
          Width = 65
          Height = 25
          Caption = 'Goto Start'
          TabOrder = 8
          OnClick = ButtonGotoShotStartClick
        end
        object ButtonShotSF: TButton
          Left = 264
          Top = 72
          Width = 49
          Height = 21
          Caption = 'Set'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = ButtonShotSFClick
        end
        object ButtonShotEF: TButton
          Left = 264
          Top = 112
          Width = 49
          Height = 21
          Caption = 'Set'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = ButtonShotEFClick
        end
        object ButtonAddShotDesc: TButton
          Left = 8
          Top = 384
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 11
          OnClick = ButtonAddShotDescClick
        end
        object ButtonDelShotDesc: TButton
          Left = 32
          Top = 384
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 12
          OnClick = ButtonDelShotDescClick
        end
        object ButtonGotoShotEnd: TButton
          Left = 256
          Top = 192
          Width = 57
          Height = 25
          Caption = 'Goto End'
          TabOrder = 9
          OnClick = ButtonGotoShotEndClick
        end
        object ListBoxShots: TListBox
          Left = 8
          Top = 8
          Width = 177
          Height = 177
          ItemHeight = 13
          TabOrder = 0
          OnClick = ListBoxShotsClick
          OnKeyUp = ListBoxShotsKeyUp
        end
        object ListBoxShotDesc: TListBox
          Left = 8
          Top = 272
          Width = 305
          Height = 105
          DragMode = dmAutomatic
          ItemHeight = 13
          TabOrder = 10
          OnDragDrop = ListBoxShotDescDragDrop
          OnDragOver = ListBoxShotDescDragOver
          OnKeyUp = ListBoxShotDescKeyUp
        end
        object EditShotSF: TEdit
          Left = 192
          Top = 72
          Width = 65
          Height = 21
          TabOrder = 2
          Text = '0'
          OnDblClick = EditShotSFDblClick
        end
        object EditShotEF: TEdit
          Left = 192
          Top = 112
          Width = 65
          Height = 21
          TabOrder = 4
          Text = '0'
          OnDblClick = EditShotEFDblClick
        end
        object EditShotName: TEdit
          Left = 192
          Top = 24
          Width = 121
          Height = 21
          TabOrder = 1
          OnKeyPress = EditShotNameKeyPress
        end
        object ButtonSortS: TButton
          Left = 64
          Top = 192
          Width = 49
          Height = 25
          Hint = 'Sort shots by start frame'
          Caption = 'Sort'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 13
          OnClick = ButtonSortSClick
        end
      end
      object TabSheetVideoV: TTabSheet
        Caption = 'Video'
        ImageIndex = 2
        object Label1: TLabel
          Left = 168
          Top = 8
          Width = 23
          Height = 13
          Caption = 'Date'
          Transparent = True
        end
        object Label3: TLabel
          Left = 8
          Top = 256
          Width = 83
          Height = 13
          Caption = 'Video Descriptors'
          Transparent = True
        end
        object cxLabel14: TLabel
          Left = 168
          Top = 48
          Width = 46
          Height = 13
          Caption = 'Annotator'
          Transparent = True
        end
        object cxLabel15: TLabel
          Left = 8
          Top = 48
          Width = 53
          Height = 13
          Caption = 'Description'
          Transparent = True
        end
        object cxLabel16: TLabel
          Left = 8
          Top = 8
          Width = 20
          Height = 13
          Caption = 'Title'
          Transparent = True
        end
        object cxLabel17: TLabel
          Left = 8
          Top = 128
          Width = 70
          Height = 13
          Caption = 'Annotation File'
          Transparent = True
        end
        object cxLabel18: TLabel
          Left = 8
          Top = 88
          Width = 46
          Height = 13
          Caption = 'Video File'
          Transparent = True
        end
        object ButtonAddVideoDesc: TButton
          Left = 8
          Top = 384
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 6
          OnClick = ButtonAddVideoDescClick
        end
        object ButtonDelVideoDesc: TButton
          Left = 32
          Top = 384
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 7
          OnClick = ButtonDelVideoDescClick
        end
        object ListBoxVideoDesc: TListBox
          Left = 8
          Top = 272
          Width = 305
          Height = 105
          DragMode = dmAutomatic
          ItemHeight = 13
          TabOrder = 5
          OnDragDrop = ListBoxVideoDescDragDrop
          OnDragOver = ListBoxVideoDescDragOver
          OnKeyUp = ListBoxVideoDescKeyUp
        end
        object VAAnnotator: TEdit
          Left = 168
          Top = 64
          Width = 137
          Height = 21
          TabOrder = 2
        end
        object VATitle: TEdit
          Left = 8
          Top = 24
          Width = 145
          Height = 21
          TabOrder = 0
        end
        object VADesc: TEdit
          Left = 8
          Top = 64
          Width = 145
          Height = 21
          TabOrder = 1
        end
        object VAVideoFilename: TEdit
          Left = 8
          Top = 104
          Width = 297
          Height = 21
          TabOrder = 3
        end
        object VAAnnoFile: TEdit
          Left = 8
          Top = 144
          Width = 297
          Height = 21
          TabOrder = 4
        end
        object VADateTime: TDateTimePicker
          Left = 168
          Top = 24
          Width = 137
          Height = 21
          CalAlignment = dtaLeft
          Date = 40217.6686089236
          Time = 40217.6686089236
          DateFormat = dfShort
          DateMode = dmComboBox
          Kind = dtkDate
          ParseInput = False
          TabOrder = 8
        end
      end
    end
    object GroupBoxAnno: TGroupBox
      Left = 8
      Top = 456
      Width = 329
      Height = 217
      Hint = 
        'Drag and drop a descriptor in the descriptors box to categorize ' +
        'content.'
      Anchors = [akLeft, akTop, akBottom]
      Caption = 'Annotation descriptors'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      DesignSize = (
        329
        217)
      object LabelDD: TLabel
        Left = 8
        Top = 16
        Width = 281
        Height = 33
        AutoSize = False
        Caption = 
          'To annotate drag a descriptor and drop it in the Selected '#13#10'Desc' +
          'riptors list box above.'
        Transparent = True
      end
      object TreeXML: TTreeView
        Left = 8
        Top = 48
        Width = 313
        Height = 157
        Anchors = [akLeft, akTop, akRight, akBottom]
        DragMode = dmAutomatic
        Indent = 19
        ReadOnly = True
        TabOrder = 2
      end
      object btnLoadAnno: TButton
        Left = 296
        Top = 17
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 0
        OnClick = btnLoadAnnoClick
      end
      object bnt1: TButton
        Left = 280
        Top = 48
        Width = 41
        Height = 25
        Caption = 'save'
        TabOrder = 1
        Visible = False
        OnClick = bnt1Click
      end
    end
  end
  object PanelClient: TPanel
    Left = 345
    Top = 36
    Width = 791
    Height = 686
    Align = alClient
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 2
    object PanelImg: TPanel
      Left = 8
      Top = 8
      Width = 768
      Height = 576
      BevelOuter = bvNone
      Color = clGreen
      FullRepaint = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object ImageV: TImage
        Left = 0
        Top = 0
        Width = 768
        Height = 576
        Align = alClient
        OnClick = ImageVClick
      end
      object ShapeA: TShape
        Left = 32
        Top = 392
        Width = 65
        Height = 65
        Brush.Style = bsClear
        Enabled = False
        Constraints.MaxHeight = 300
        Constraints.MaxWidth = 300
        Constraints.MinHeight = 2
        Constraints.MinWidth = 2
        Pen.Color = clRed
        Pen.Width = 2
        Visible = False
        OnMouseDown = ShapeAMouseDown
        OnMouseMove = ShapeAMouseMove
        OnMouseUp = ShapeAMouseUp
      end
    end
    object ButtonPlay: TButton
      Left = 16
      Top = 632
      Width = 89
      Height = 25
      Action = FormMain.ActionPlay
      TabOrder = 1
    end
    object ButtonFWD: TButton
      Left = 112
      Top = 632
      Width = 89
      Height = 25
      Action = FormMain.ActionForward
      TabOrder = 2
    end
    object ButtonREW: TButton
      Left = 208
      Top = 632
      Width = 89
      Height = 25
      Action = FormMain.ActionBackward
      TabOrder = 3
    end
    object ButtonREC: TButton
      Left = 304
      Top = 632
      Width = 97
      Height = 25
      Action = FormMain.ActionRecord
      TabOrder = 4
    end
    object TrackBarVideo: TTrackBar
      Left = 8
      Top = 584
      Width = 769
      Height = 41
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 5
      TickMarks = tmBoth
      TickStyle = tsAuto
    end
  end
  object TimerPlay: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerPlayTimer
    Left = 568
    Top = 128
  end
  object OpenDialogV: TOpenDialog
    Filter = 'MPEG videos|*.mpg;*.m1v;*.m2v|All files|*.*'
    Left = 600
    Top = 128
  end
  object XMLProject: TXMLDocument
    Left = 632
    Top = 128
    DOMVendorDesc = 'MSXML'
  end
end
