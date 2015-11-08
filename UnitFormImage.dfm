object FormImage: TFormImage
  Left = 371
  Top = 181
  Align = alClient
  BorderStyle = bsNone
  Caption = 'FormImage'
  ClientHeight = 677
  ClientWidth = 1008
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PanelLeftImg: TPanel
    Left = 0
    Top = 0
    Width = 345
    Height = 677
    Align = alLeft
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      345
      677)
    object PageControlImage: TPageControl
      Left = 8
      Top = 7
      Width = 329
      Height = 458
      ActivePage = TabSheetImgRegions
      TabIndex = 0
      TabOrder = 0
      object TabSheetImgRegions: TTabSheet
        Caption = 'Regions'
        object lbl6: TLabel
          Left = 8
          Top = 272
          Width = 127
          Height = 13
          Caption = 'Current Region Descriptors'
          Transparent = True
        end
        object lblrt: TLabel
          Left = 192
          Top = 88
          Width = 61
          Height = 13
          Caption = 'Region Type'
          Transparent = True
        end
        object lblrn: TLabel
          Left = 192
          Top = 8
          Width = 65
          Height = 13
          Caption = 'Region Name'
          Transparent = True
        end
        object lblColor: TLabel
          Left = 192
          Top = 48
          Width = 24
          Height = 13
          Caption = 'Color'
          Transparent = True
        end
        object lblx: TLabel
          Left = 192
          Top = 128
          Width = 7
          Height = 13
          Caption = 'X'
          Transparent = True
        end
        object cxLabel25: TLabel
          Left = 192
          Top = 168
          Width = 28
          Height = 13
          Caption = 'Width'
          Transparent = True
        end
        object cxLabel26: TLabel
          Left = 256
          Top = 168
          Width = 31
          Height = 13
          Caption = 'Height'
          Transparent = True
        end
        object lbly: TLabel
          Left = 256
          Top = 128
          Width = 7
          Height = 13
          Caption = 'Y'
          Transparent = True
        end
        object ButtonImgToFront: TButton
          Left = 8
          Top = 240
          Width = 81
          Height = 25
          Caption = 'Bring to Front'
          TabOrder = 10
          OnClick = ButtonImgToFrontClick
        end
        object ButtonImgToBack: TButton
          Left = 88
          Top = 240
          Width = 81
          Height = 25
          Caption = 'Send to Back'
          TabOrder = 11
          OnClick = ButtonImgToBackClick
        end
        object ButtonCreateImgR: TButton
          Left = 8
          Top = 208
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 6
          OnClick = ButtonCreateImgRClick
        end
        object ButtonDelImgR: TButton
          Left = 32
          Top = 208
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 7
          OnClick = ButtonDelImgRClick
        end
        object ButtonAddImgRegionDesc: TButton
          Left = 8
          Top = 400
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 13
          OnClick = ButtonAddImgRegionDescClick
        end
        object ButtonDelImgRegionDesc: TButton
          Left = 32
          Top = 400
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 15
          OnClick = ButtonDelImgRegionDescClick
        end
        object ListBoxImgNodes: TListBox
          Left = 8
          Top = 8
          Width = 177
          Height = 199
          ItemHeight = 13
          TabOrder = 0
          OnClick = ListBoxImgNodesClick
          OnKeyUp = ListBoxImgNodesKeyUp
        end
        object ListBoxImgRegionDesc: TListBox
          Left = 8
          Top = 288
          Width = 305
          Height = 105
          DragMode = dmAutomatic
          ItemHeight = 13
          TabOrder = 12
          OnDragDrop = ListBoxImgRegionDescDragDrop
          OnDragOver = ListBoxImgRegionDescDragOver
          OnKeyUp = ListBoxImgRegionDescKeyUp
        end
        object EditRImgName: TEdit
          Left = 192
          Top = 24
          Width = 121
          Height = 21
          TabOrder = 1
          Text = 'Region'
          OnKeyPress = EditRImgNameKeyPress
        end
        object EditRImgY: TEdit
          Left = 256
          Top = 144
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          Text = '0'
          OnDblClick = EditRImgYDblClick
        end
        object EditRImgH: TEdit
          Left = 256
          Top = 184
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 5
          Text = '0'
          OnDblClick = EditRImgHDblClick
        end
        object EditRImgW: TEdit
          Left = 192
          Top = 184
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          Text = '0'
          OnDblClick = EditRImgWDblClick
        end
        object EditRImgX: TEdit
          Left = 192
          Top = 144
          Width = 57
          Height = 21
          Hint = 'Double click to change value.'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Text = '0'
          OnDblClick = EditRImgXDblClick
        end
        object ButtonMerge: TButton
          Left = 64
          Top = 208
          Width = 49
          Height = 25
          Caption = 'Merge'
          TabOrder = 8
          OnClick = ButtonMergeClick
        end
        object ButtonSeg: TButton
          Left = 112
          Top = 208
          Width = 89
          Height = 25
          Caption = 'Segmentation'
          TabOrder = 9
          OnClick = ButtonSegClick
        end
        object ButtonPoints: TButton
          Left = 264
          Top = 208
          Width = 49
          Height = 25
          Caption = 'Points'
          TabOrder = 14
          OnClick = ButtonPointsClick
        end
        object ComboBoxRImgType: TComboBox
          Left = 192
          Top = 104
          Width = 121
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 16
          Text = 'Rectangle'
          Items.Strings = (
            'Rectangle'
            'Circle'
            'Ellipse'
            'Polygon'
            'Freeform'
            'Segmentation')
        end
        object ColorBoxRImg: TColorBox
          Left = 192
          Top = 64
          Width = 121
          Height = 22
          ItemHeight = 16
          TabOrder = 17
        end
      end
      object TabSheetImg: TTabSheet
        Caption = 'Image'
        ImageIndex = 2
        object Label10: TLabel
          Left = 8
          Top = 272
          Width = 85
          Height = 13
          Caption = 'Image Descriptors'
          Transparent = True
        end
        object cxLabel28: TLabel
          Left = 8
          Top = 48
          Width = 53
          Height = 13
          Caption = 'Description'
          Transparent = True
        end
        object cxLabel29: TLabel
          Left = 8
          Top = 8
          Width = 20
          Height = 13
          Caption = 'Title'
          Transparent = True
        end
        object cxLabel30: TLabel
          Left = 168
          Top = 8
          Width = 23
          Height = 13
          Caption = 'Date'
          Transparent = True
        end
        object cxLabel31: TLabel
          Left = 168
          Top = 48
          Width = 46
          Height = 13
          Caption = 'Annotator'
          Transparent = True
        end
        object cxLabel32: TLabel
          Left = 8
          Top = 88
          Width = 48
          Height = 13
          Caption = 'Image File'
          Transparent = True
        end
        object cxLabel33: TLabel
          Left = 8
          Top = 128
          Width = 70
          Height = 13
          Caption = 'Annotation File'
          Transparent = True
        end
        object ButtonAddImgDesc: TButton
          Left = 8
          Top = 400
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 6
          OnClick = ButtonAddImgDescClick
        end
        object ButtonDelImgDesc: TButton
          Left = 32
          Top = 400
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 7
          OnClick = ButtonDelImgDescClick
        end
        object ListBoxImageDesc: TListBox
          Left = 8
          Top = 288
          Width = 305
          Height = 105
          DragMode = dmAutomatic
          ItemHeight = 13
          TabOrder = 5
          OnDragDrop = ListBoxImageDescDragDrop
          OnDragOver = ListBoxImageDescDragOver
          OnKeyUp = ListBoxImageDescKeyUp
        end
        object IATitle: TEdit
          Left = 8
          Top = 24
          Width = 145
          Height = 21
          TabOrder = 0
        end
        object IAAnnotator: TEdit
          Left = 168
          Top = 64
          Width = 137
          Height = 21
          TabOrder = 2
        end
        object IADesc: TEdit
          Left = 8
          Top = 64
          Width = 145
          Height = 21
          TabOrder = 1
        end
        object IAFilename: TEdit
          Left = 8
          Top = 104
          Width = 297
          Height = 21
          TabOrder = 3
        end
        object IAAnnoFile: TEdit
          Left = 8
          Top = 144
          Width = 297
          Height = 21
          TabOrder = 4
        end
        object IADateTime: TDateTimePicker
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
    object grpbad: TGroupBox
      Left = 8
      Top = 472
      Width = 329
      Height = 198
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
        198)
      object lblAnnot: TLabel
        Left = 8
        Top = 16
        Width = 281
        Height = 33
        AutoSize = False
        Caption = 
          'To annotate drag a descriptor and drop it in the Selected'#13#10'Descr' +
          'iptors list box above.'
        Transparent = True
      end
      object TreeXMLImg: TTreeView
        Left = 8
        Top = 48
        Width = 313
        Height = 139
        Anchors = [akLeft, akTop, akRight, akBottom]
        DragMode = dmAutomatic
        Indent = 19
        ReadOnly = True
        TabOrder = 1
      end
      object ButtonLoadImgAnno: TButton
        Left = 296
        Top = 17
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 0
        OnClick = ButtonLoadImgAnnoClick
      end
    end
  end
  object PanelClientImg: TPanel
    Left = 345
    Top = 0
    Width = 663
    Height = 677
    Align = alClient
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 1
    object PanelImageContainer: TPanel
      Left = 1
      Top = 1
      Width = 661
      Height = 675
      Align = alClient
      BevelOuter = bvNone
      Color = clMoneyGreen
      FullRepaint = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object ShapeImg: TShape
        Left = 8
        Top = 8
        Width = 65
        Height = 65
        Brush.Style = bsClear
        Enabled = False
        Constraints.MaxHeight = 300
        Constraints.MaxWidth = 300
        Constraints.MinHeight = 2
        Constraints.MinWidth = 2
        Pen.Color = clMaroon
        Pen.Width = 2
        Visible = False
      end
      object ScrollBox: TScrollBox
        Left = 0
        Top = 0
        Width = 661
        Height = 675
        HorzScrollBar.Range = 1200
        VertScrollBar.Range = 1200
        Align = alClient
        AutoScroll = False
        Color = clNone
        ParentColor = False
        TabOrder = 0
        object ImageAn: TImage32
          Left = 0
          Top = 0
          Width = 1200
          Height = 1200
          Align = alClient
          Bitmap.ResamplerClassName = 'TNearestResampler'
          BitmapAlign = baTopLeft
          Color = clBtnFace
          ParentColor = False
          Scale = 1
          ScaleMode = smNormal
          TabOrder = 0
          OnClick = ImageAnClick
          OnMouseDown = ImageAnMouseDown
          OnMouseMove = ImageAnMouseMove
        end
      end
    end
  end
  object OpenDialogImg: TOpenDialog
    Filter = 
      'Image files|*.jpg;*.png;*.bmp;*.tga;*.tif;*.gif;*.ppm;*.pgm|All ' +
      'files|*.*'
    Left = 384
    Top = 40
  end
  object XMLProject: TXMLDocument
    Left = 416
    Top = 40
    DOMVendorDesc = 'MSXML'
  end
end
