//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <IniFiles.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <AppEvnts.hpp>

#define MME_LANG_EN 0
#define MIN_REGION 2
#define MAX_REGION 1600
#define DEF_X 60
#define DEF_Y 60
#define DEF_H 80
#define DEF_W 80
#define TC_FORMAT "%02d:%02d:%02d.%02.0f"

/*******************************************************************
   type definitions
 *******************************************************************/

typedef struct {
  int x,y,w,h;
} TRegionData;


//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TSaveDialog *SaveDialog;
	TXMLDocument *XMLDocument;
  TOpenDialog *OpenDialogXML;
  TSaveDialog *SavePrjDialog;
  TOpenDialog *OpenPrjDialog;
  TActionList *ActionList;
  TAction *ActionRecord;
  TAction *ActionPlay;
  TAction *ActionForward;
  TAction *ActionBackward;
  TAction *ActionOpenProject;
  TAction *ActionSaveProject;
  TAction *ActionClose;
  TAction *ActionOpenVideo;
  TAction *ActionImportXML;
  TAction *ActionExportXMLTraj;
	TSaveDialog *SaveDialogXML;
  TAction *ActionExportXML;
  TApplicationEvents *ApplicationEvents;
  TPageControl *PageControl;
  TTabSheet *TabSheetLogo;
  TLabel *lblLogo;
  TLabel *lblMKL;
  TLabel *lblITI;
  TLabel *lblVersion;
  TAction *ActionImportDesc;
  TAction *ActionBBWI;
  TAction *ActionBBWD;
  TAction *ActionBBHI;
  TAction *ActionBBHD;
  TOpenDialog *OpenDialogDesc;
  TXMLDocument *XMLProject;
  TLabel *lblCerth;
  TTabSheet *TabSheetVideo;
  TTabSheet *TabSheetImage;
  TImageList *ImageList;
  TMainMenu *MainMenu1;
  TMenuItem *File1;
  TMenuItem *MenuEditVideo;
  TMenuItem *MenuImage;
  TMenuItem *MenuVideo;
  TMenuItem *Tools1;
  TMenuItem *Help1;
  TMenuItem *NewProject1;
  TMenuItem *ImageAnnotation1;
  TMenuItem *VideoAnnotation1;
  TMenuItem *OpenProject1;
  TMenuItem *SaveProject1;
  TMenuItem *CloseProject1;
  TMenuItem *N1;
  TMenuItem *Exit1;
  TMenuItem *N2;
  TMenuItem *ImportDescriptors1;
  TMenuItem *Contents1;
  TMenuItem *About1;
  TMenuItem *ViewLog1;
  TMenuItem *Options1;
  TMenuItem *OpenVideoFile1;
  TMenuItem *Advanced1;
  TMenuItem *ImportXMLData1;
  TMenuItem *ExportTrajectoryXMLData1;
  TMenuItem *ExportXMLData1;
  TMenuItem *ExportTextData1;
  TMenuItem *N3;
  TMenuItem *GotoFrame1;
  TMenuItem *TimeCode1;
  TMenuItem *N4;
  TMenuItem *FrameFWD1;
  TMenuItem *FrameREW1;
  TMenuItem *N5;
  TMenuItem *NextIFrame1;
  TMenuItem *Start1;
  TMenuItem *PreviousIFrame1;
  TMenuItem *N6;
  TMenuItem *End1;
  TMenuItem *OpenImageFile1;
  TMenuItem *Advanced2;
  TMenuItem *ExportTextData2;
  TMenuItem *ExtractMPEG7Descriptors1;
  TMenuItem *CopyFrametoClipboard1;
  TMenuItem *N7;
  TMenuItem *RecordMode1;
  TMenuItem *PlayMode1;
  TBevel *bvl;
  TBevel *Bevel2;
  TLabel *lblHome;
  void __fastcall FormCreate(TObject *Sender);
	void __fastcall MenuExitClick(TObject *Sender);
	void __fastcall MenuCopyFrameClick(TObject *Sender);
	void __fastcall MenuGotoFrameClick(TObject *Sender);
	void __fastcall MenuTimeCodeClick(TObject *Sender);
	void __fastcall MenuNextIFrameClick(TObject *Sender);
	void __fastcall MenuPreviousIFrameClick(TObject *Sender);
	void __fastcall MenuStartClick(TObject *Sender);
	void __fastcall MenuEndClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ActionRecordExecute(TObject *Sender);
	void __fastcall ActionPlayExecute(TObject *Sender);
  void __fastcall ActionForwardExecute(TObject *Sender);
  void __fastcall ActionBackwardExecute(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall MenuAboutClick(TObject *Sender);
  void __fastcall MenuContentsClick(TObject *Sender);
  void __fastcall MenuLogClick(TObject *Sender);
  void __fastcall ActionExportXMLTrajExecute(TObject *Sender);
	void __fastcall ActionOpenProjectExecute(TObject *Sender);
	void __fastcall ActionSaveProjectExecute(TObject *Sender);
	void __fastcall ActionCloseExecute(TObject *Sender);
	void __fastcall ActionOpenVideoExecute(TObject *Sender);
  void __fastcall MenuOpenImageClick(TObject *Sender);
	void __fastcall MenuNewIAClick(TObject *Sender);
	void __fastcall MenuOptionsClick(TObject *Sender);
	void __fastcall MenuNewVAClick(TObject *Sender);
  void __fastcall MenuExportImgTextClick(TObject *Sender);
	void __fastcall MenuImageExtractClick(TObject *Sender);
  void __fastcall ApplicationEventsException(TObject *Sender, Exception *E);
  void __fastcall ActionImportXMLExecute(TObject *Sender);
  void __fastcall ActionExportXMLExecute(TObject *Sender);
  void __fastcall ActionImportDescExecute(TObject *Sender);
  void __fastcall ActionBBWIExecute(TObject *Sender);
  void __fastcall ActionBBWDExecute(TObject *Sender);
  void __fastcall ActionBBHIExecute(TObject *Sender);
  void __fastcall ActionBBHDExecute(TObject *Sender);
  void __fastcall ExportTextData1Click(TObject *Sender);
  void __fastcall lblHomeClick(TObject *Sender);

private:	// User declarations
  void __fastcall ReadConfig(void);
  void __fastcall WriteConfig(void);
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
  bool __fastcall TFormMain::SaveChanges(void);
  void __fastcall VideoPrjControls(bool enable);
  void __fastcall ImagePrjControls(bool enable);
  bool __fastcall XML2Tree(TTreeView *TreeView, TXMLDocument *XMLDocument, AnsiString filename);
  void __fastcall ProcessNode(TTreeView *TreeView, _di_IXMLNode Node, TTreeNode *tn);

  //global options
  int PenWidth, ProjectType, VideoInterval;
  bool RenumberSort;
  String CurrentDir, ProjectName;
  String Dir_AceToolBox, Dir_StoredData, Dir_SegTools;
  String SegExe, SegOptions;
};

//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif


