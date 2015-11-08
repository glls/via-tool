object FormMain: TFormMain
  Left = 321
  Top = 111
  Width = 999
  Height = 763
  Caption = 'VIA'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Default'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 991
    Height = 717
    ActivePage = TabSheetLogo
    Align = alClient
    MultiLine = True
    ScrollOpposite = True
    TabIndex = 0
    TabOrder = 0
    TabPosition = tpBottom
    object TabSheetLogo: TTabSheet
      Caption = 'VIA'
      ImageIndex = 2
      object bvl: TBevel
        Left = 8
        Top = 8
        Width = 433
        Height = 217
      end
      object lblLogo: TLabel
        Left = 24
        Top = 24
        Width = 350
        Height = 29
        Caption = 'Video Image Annotation Tool'
        Font.Charset = GREEK_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
      end
      object lblMKL: TLabel
        Left = 24
        Top = 112
        Width = 240
        Height = 19
        Caption = 'Multimedia Knowledge Laboratory'
        Font.Charset = GREEK_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object lblITI: TLabel
        Left = 24
        Top = 136
        Width = 254
        Height = 19
        Caption = 'Informatics and Telematics Institute'
        Font.Charset = GREEK_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object lblVersion: TLabel
        Left = 24
        Top = 56
        Width = 79
        Height = 19
        Caption = 'version 1.0'
        Font.Charset = GREEK_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object lblCerth: TLabel
        Left = 24
        Top = 160
        Width = 399
        Height = 19
        Caption = 'Centre for Research and Technology Hellas (CERTH-ITI)'
        Font.Charset = GREEK_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object Bevel2: TBevel
        Left = 24
        Top = 88
        Width = 401
        Height = 9
      end
      object lblHome: TLabel
        Left = 24
        Top = 192
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
    end
    object TabSheetVideo: TTabSheet
      Caption = 'Video'
      ImageIndex = 1
    end
    object TabSheetImage: TTabSheet
      Caption = 'Image'
      ImageIndex = 2
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text files|*.txt|All files|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 632
    Top = 192
  end
  object XMLDocument: TXMLDocument
    Left = 520
    Top = 232
    DOMVendorDesc = 'MSXML'
  end
  object OpenDialogXML: TOpenDialog
    DefaultExt = 'owl'
    Filter = 'Supported Files (*.XML;*.OWL)|*.XML;*.OWL|All files (*.*)|*.*'
    Left = 600
    Top = 224
  end
  object SavePrjDialog: TSaveDialog
    DefaultExt = 'ANP'
    Filter = 
      'Annotation projects (*.ANP)|*.ANP|XML Annotation projects (*.XML' +
      ')|*.XML|All files (*.*)|*.*'
    Left = 632
    Top = 160
  end
  object OpenPrjDialog: TOpenDialog
    DefaultExt = 'ANP'
    Filter = 
      'Project Files (*.ANP,*.XML)|*.ANP;*.XML|Annotation projects (*.A' +
      'NP)|*.ANP|XML Annotation projects (*.XML)|*.XML|All files (*.*)|' +
      '*.*'
    Left = 600
    Top = 160
  end
  object ActionList: TActionList
    Left = 520
    Top = 192
    object ActionRecord: TAction
      Caption = 'Record Mode'
      ImageIndex = 42
      ShortCut = 116
      OnExecute = ActionRecordExecute
    end
    object ActionPlay: TAction
      Caption = 'Play Mode'
      ImageIndex = 40
      ShortCut = 117
      OnExecute = ActionPlayExecute
    end
    object ActionForward: TAction
      Caption = 'Frame FWD'
      ImageIndex = 44
      ShortCut = 16505
      OnExecute = ActionForwardExecute
    end
    object ActionBackward: TAction
      Caption = 'Frame REW'
      ImageIndex = 43
      ShortCut = 16504
      OnExecute = ActionBackwardExecute
    end
    object ActionOpenProject: TAction
      Caption = 'Open Project'
      ImageIndex = 33
      ShortCut = 16463
      OnExecute = ActionOpenProjectExecute
    end
    object ActionSaveProject: TAction
      Caption = 'Save Project'
      ImageIndex = 34
      ShortCut = 16467
      OnExecute = ActionSaveProjectExecute
    end
    object ActionClose: TAction
      Caption = 'Close Project'
      ImageIndex = 32
      ShortCut = 16499
      OnExecute = ActionCloseExecute
    end
    object ActionOpenVideo: TAction
      Caption = 'Open Video'
      OnExecute = ActionOpenVideoExecute
    end
    object ActionImportXML: TAction
      Caption = 'Import XML Data...'
      OnExecute = ActionImportXMLExecute
    end
    object ActionExportXMLTraj: TAction
      Caption = 'Export XML Data...'
      OnExecute = ActionExportXMLTrajExecute
    end
    object ActionExportXML: TAction
      Caption = 'Export XML Data...'
      OnExecute = ActionExportXMLExecute
    end
    object ActionImportDesc: TAction
      Caption = 'Import Descriptors...'
      OnExecute = ActionImportDescExecute
    end
    object ActionBBWI: TAction
      Caption = 'ActionBBWI'
      Enabled = False
      ShortCut = 88
      OnExecute = ActionBBWIExecute
    end
    object ActionBBWD: TAction
      Caption = 'ActionBBWD'
      Enabled = False
      ShortCut = 67
      OnExecute = ActionBBWDExecute
    end
    object ActionBBHI: TAction
      Caption = 'ActionBBHI'
      Enabled = False
      ShortCut = 87
      OnExecute = ActionBBHIExecute
    end
    object ActionBBHD: TAction
      Caption = 'ActionBBHD'
      Enabled = False
      ShortCut = 69
      OnExecute = ActionBBHDExecute
    end
  end
  object SaveDialogXML: TSaveDialog
    DefaultExt = 'xml'
    Filter = 'XML files|*.xml|All files|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 632
    Top = 224
  end
  object ApplicationEvents: TApplicationEvents
    OnException = ApplicationEventsException
    Left = 552
    Top = 160
  end
  object OpenDialogDesc: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text files (*.TXT)|*.TXT|All files (*.*)|*.*'
    Left = 600
    Top = 192
  end
  object XMLProject: TXMLDocument
    Left = 520
    Top = 264
    DOMVendorDesc = 'MSXML'
  end
  object ImageList: TImageList
    Left = 520
    Top = 160
  end
  object MainMenu1: TMainMenu
    Left = 552
    Top = 192
    object File1: TMenuItem
      Caption = '&File'
      object NewProject1: TMenuItem
        Caption = 'New Project'
        object ImageAnnotation1: TMenuItem
          Caption = 'Image Annotation'
          OnClick = MenuNewIAClick
        end
        object VideoAnnotation1: TMenuItem
          Caption = 'Video Annotation'
          OnClick = MenuNewVAClick
        end
      end
      object OpenProject1: TMenuItem
        Caption = 'Open Project'
        ShortCut = 16463
        OnClick = ActionOpenProjectExecute
      end
      object SaveProject1: TMenuItem
        Caption = 'Save Project'
        ShortCut = 16467
        OnClick = ActionSaveProjectExecute
      end
      object CloseProject1: TMenuItem
        Caption = 'Close Project'
        ShortCut = 16499
        OnClick = ActionCloseExecute
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object ImportDescriptors1: TMenuItem
        Caption = 'Import Descriptors...'
        OnClick = ActionImportDescExecute
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        ShortCut = 16465
        OnClick = MenuExitClick
      end
    end
    object MenuEditVideo: TMenuItem
      Caption = '&Edit'
      object CopyFrametoClipboard1: TMenuItem
        Caption = 'Copy Frame to Clipboard'
        OnClick = MenuCopyFrameClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object RecordMode1: TMenuItem
        Caption = 'Record Mode'
        ShortCut = 116
        OnClick = ActionRecordExecute
      end
      object PlayMode1: TMenuItem
        Caption = 'Play Mode'
        ShortCut = 117
        OnClick = ActionPlayExecute
      end
    end
    object MenuImage: TMenuItem
      Caption = '&Image'
      object OpenImageFile1: TMenuItem
        Caption = 'Open Image File...'
        OnClick = MenuOpenImageClick
      end
      object Advanced2: TMenuItem
        Caption = 'Advanced'
        object ExportTextData2: TMenuItem
          Caption = 'Export Text Data...'
          OnClick = MenuExportImgTextClick
        end
        object ExtractMPEG7Descriptors1: TMenuItem
          Caption = 'Extract MPEG-7 Descriptors'
          OnClick = MenuImageExtractClick
        end
      end
    end
    object MenuVideo: TMenuItem
      Caption = '&Video'
      object OpenVideoFile1: TMenuItem
        Caption = 'Open Video File...'
        OnClick = ActionOpenVideoExecute
      end
      object Advanced1: TMenuItem
        Caption = 'Advanced'
        object ImportXMLData1: TMenuItem
          Caption = 'Import XML Data...'
          OnClick = ActionImportXMLExecute
        end
        object ExportTrajectoryXMLData1: TMenuItem
          Caption = 'Export Trajectory XML Data...'
          OnClick = ActionExportXMLTrajExecute
        end
        object ExportXMLData1: TMenuItem
          Caption = 'Export XML Data...'
          OnClick = ActionExportXMLExecute
        end
        object ExportTextData1: TMenuItem
          Caption = 'Export Text Data...'
          OnClick = ExportTextData1Click
        end
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object GotoFrame1: TMenuItem
        Caption = 'Goto Frame'
        ShortCut = 118
        OnClick = MenuGotoFrameClick
      end
      object TimeCode1: TMenuItem
        Caption = 'TimeCode'
        Enabled = False
        ShortCut = 119
        OnClick = MenuTimeCodeClick
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object FrameFWD1: TMenuItem
        Caption = 'Frame FWD'
        ShortCut = 16505
        OnClick = ActionForwardExecute
      end
      object FrameREW1: TMenuItem
        Caption = 'Frame REW'
        ShortCut = 16504
        OnClick = ActionBackwardExecute
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object NextIFrame1: TMenuItem
        Caption = 'Next I Frame'
        ShortCut = 16457
        OnClick = MenuNextIFrameClick
      end
      object PreviousIFrame1: TMenuItem
        Caption = 'Previous I Frame'
        ShortCut = 16469
        OnClick = MenuPreviousIFrameClick
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object Start1: TMenuItem
        Caption = 'Start Frame'
        ShortCut = 36
        OnClick = MenuStartClick
      end
      object End1: TMenuItem
        Caption = 'End Frame'
        ShortCut = 35
        OnClick = MenuEndClick
      end
    end
    object Tools1: TMenuItem
      Caption = '&Tools'
      object ViewLog1: TMenuItem
        Caption = 'View Log'
        OnClick = MenuLogClick
      end
      object Options1: TMenuItem
        Caption = 'Options...'
        OnClick = MenuOptionsClick
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object Contents1: TMenuItem
        Caption = '&Contents'
        ShortCut = 112
        OnClick = MenuContentsClick
      end
      object About1: TMenuItem
        Caption = '&About...'
        OnClick = MenuAboutClick
      end
    end
  end
end
