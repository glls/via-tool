//---------------------------------------------------------------------------

#ifndef UnitFormVideoH
#define UnitFormVideoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <IniFiles.hpp>

#include "m2v_vfapi.h"
#include "mme_project.h"
#include "query_frame.h"
#include "timecode.h"
#include "message.h"
#include <Dialogs.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "UnitUtils.h"

//---------------------------------------------------------------------------

typedef struct {
	HINSTANCE        instance;
	HWND             main_hwnd;
	HWND             callback_dlg;
	HWND             slide_bar;
	HACCEL           accel_tbl;
	M2V_VFAPI        vfapi;
	MME_PROJECT      project;
	HANDLE           clipboard;
	int              lang;
	char             openpath[MAX_PATH];
	char             savepath[MAX_PATH];
} MME_APP;

typedef struct {
	TShape *box;
  AnsiString description;
  __int64 startFrame;
  __int64 endFrame;
  TColor color;
  TList *region_data;
  TStringList *descriptors;
} TRegion;


typedef struct {
  AnsiString description;
  __int64 startFrame;
  __int64 endFrame;
  TStringList *descriptors;
} TShot;


class TFormVideo : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelVideoTop;
  TLabeledEdit *EditTimeCode;
  TLabeledEdit *LabelStatus;
  TLabeledEdit *EditFrame;
  TLabel *LabelLocked1;
  TLabel *LabelRecord;
  TLabel *LabelLocked;
  TPanel *PanelLeft;
  TPageControl *PageControlVideo;
  TTabSheet *TabSheetVideoReg;
  TButton *ButtonRegionEF;
  TButton *ButtonRegionSF;
  TButton *ButtonToFront;
  TButton *ButtonToBack;
  TButton *ButtonCreateR;
  TButton *ButtonDelR;
  TButton *ButtonAddRegionDesc;
  TButton *ButtonDelRegionDesc;
  TButton *ButtonGotoRegionStart;
  TButton *ButtonGotoRegionEnd;
  TListBox *ListBoxNodes;
  TListBox *ListBoxRegionDesc;
  TLabel *Label5;
  TEdit *EditRName;
  TEdit *EditRegionEF;
  TEdit *EditRX;
  TEdit *EditRY;
  TEdit *EditRW;
  TEdit *EditRH;
  TLabel *cxLabel3;
  TLabel *cxLabel4;
  TLabel *cxLabelRName;
  TEdit *EditRegionSF;
  TLabel *cxLabel8;
  TLabel *cxLabel9;
  TLabel *cxLabel10;
  TLabel *cxLabel5;
  TLabel *cxLabel6;
  TButton *ButtonSortR;
  TTabSheet *TabSheetVideoShot;
  TButton *ButtonAddShot;
  TButton *ButtonDelShot;
  TButton *ButtonGotoShotStart;
  TButton *ButtonShotSF;
  TButton *ButtonShotEF;
  TButton *ButtonAddShotDesc;
  TButton *ButtonDelShotDesc;
  TButton *ButtonGotoShotEnd;
  TListBox *ListBoxShots;
  TListBox *ListBoxShotDesc;
  TLabel *Label2;
  TLabel *cxLabel11;
  TLabel *cxLabel12;
  TEdit *EditShotSF;
  TEdit *EditShotEF;
  TEdit *EditShotName;
  TLabel *cxLabel13;
  TButton *ButtonSortS;
  TTabSheet *TabSheetVideoV;
  TButton *ButtonAddVideoDesc;
  TButton *ButtonDelVideoDesc;
  TListBox *ListBoxVideoDesc;
  TLabel *Label1;
  TLabel *Label3;
  TEdit *VAAnnotator;
  TEdit *VATitle;
  TEdit *VADesc;
  TEdit *VAVideoFilename;
  TEdit *VAAnnoFile;
  TLabel *cxLabel14;
  TLabel *cxLabel15;
  TLabel *cxLabel16;
  TLabel *cxLabel17;
  TLabel *cxLabel18;
  TGroupBox *GroupBoxAnno;
  TTreeView *TreeXML;
  TLabel *LabelDD;
  TButton *btnLoadAnno;
  TPanel *PanelClient;
  TPanel *PanelImg;
  TImage *ImageV;
  TShape *ShapeA;
  TButton *ButtonPlay;
  TButton *ButtonFWD;
  TButton *ButtonREW;
  TButton *ButtonREC;
  TTimer *TimerPlay;
  TOpenDialog *OpenDialogV;
  TButton *bnt1;
  TXMLDocument *XMLProject;
  TDateTimePicker *VADateTime;
  TTrackBar *TrackBarVideo;
  TColorBox *ColorBoxR;
  void __fastcall ShapeAMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall ShapeAMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall ShapeAMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall ImageVClick(TObject *Sender);
  void __fastcall TrackBarVideoPropertiesChange(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall TimerPlayTimer(TObject *Sender);
  void __fastcall ButtonRegionSFClick(TObject *Sender);
  void __fastcall ButtonRegionEFClick(TObject *Sender);
  void __fastcall ButtonGotoRegionEndClick(TObject *Sender);
  void __fastcall ButtonGotoRegionStartClick(TObject *Sender);
  void __fastcall ButtonToBackClick(TObject *Sender);
  void __fastcall ButtonToFrontClick(TObject *Sender);
  void __fastcall ButtonSortRClick(TObject *Sender);
  void __fastcall ButtonDelRClick(TObject *Sender);
  void __fastcall ButtonCreateRClick(TObject *Sender);
  void __fastcall ButtonAddRegionDescClick(TObject *Sender);
  void __fastcall ButtonDelRegionDescClick(TObject *Sender);
  void __fastcall ButtonAddShotClick(TObject *Sender);
  void __fastcall ButtonDelShotClick(TObject *Sender);
  void __fastcall ButtonSortSClick(TObject *Sender);
  void __fastcall ButtonGotoShotStartClick(TObject *Sender);
  void __fastcall ButtonGotoShotEndClick(TObject *Sender);
  void __fastcall ButtonShotEFClick(TObject *Sender);
  void __fastcall ButtonShotSFClick(TObject *Sender);
  void __fastcall ListBoxShotDescDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
  void __fastcall ListBoxShotDescDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
  void __fastcall ListBoxShotsClick(TObject *Sender);
  void __fastcall ListBoxNodesClick(TObject *Sender);
  void __fastcall ButtonAddVideoDescClick(TObject *Sender);
  void __fastcall ButtonDelVideoDescClick(TObject *Sender);
  void __fastcall ButtonDelShotDescClick(TObject *Sender);
  void __fastcall ListBoxShotsKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditRXDblClick(TObject *Sender);
  void __fastcall EditRYDblClick(TObject *Sender);
  void __fastcall EditRWDblClick(TObject *Sender);
  void __fastcall EditRHDblClick(TObject *Sender);
  void __fastcall ColorBoxRChange(TObject *Sender);
  void __fastcall EditRNameKeyPress(TObject *Sender, char &Key);
  void __fastcall EditRegionSFDblClick(TObject *Sender);
  void __fastcall EditRegionEFDblClick(TObject *Sender);
  void __fastcall EditShotSFDblClick(TObject *Sender);
  void __fastcall EditShotEFDblClick(TObject *Sender);
  void __fastcall ListBoxNodesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ListBoxVideoDescDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
  void __fastcall ListBoxVideoDescDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
  void __fastcall ListBoxRegionDescDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
  void __fastcall ListBoxRegionDescDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
  void __fastcall ListBoxRegionDescKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ListBoxShotDescKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ListBoxVideoDescKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall EditShotNameKeyPress(TObject *Sender, char &Key);
  void __fastcall ButtonAddShotDescClick(TObject *Sender);
  void __fastcall btnLoadAnnoClick(TObject *Sender);
  void __fastcall bnt1Click(TObject *Sender);
private:	// User declarations
  TRegion * __fastcall GetSelectedRegion(TObject *Sender);
 	void __fastcall NodeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall NodeMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall NodeMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall RepaintVideo(void);
  void __fastcall SetNodesVisible(bool vis);
  void __fastcall PositionNodes(TWinControl* AroundControl);
  void __fastcall ShowDIB(HDC hdc, const BITMAPINFOHEADER *header, const VOID *data);
  void __fastcall UpdateSlider(void);
  void __fastcall SetRegionsVis(void);
  void __fastcall UpdateShotProp(TShot *shot);
  void __fastcall CleanupRegions(void);
  void __fastcall CreateNodes(void);
  void __fastcall CleanupShots(void);
  bool __fastcall SaveProjectFileXML(AnsiString Filename); 
  TList *shots;
  bool NodePositioning;
  bool inReposition;
  TObjectList *FNodes;
  TWinControl *FCurrentNodeControl;
  Types::TPoint oldPos;
  TStringList *VideoDescriptors;
  MME_APP mme_app;
  void __fastcall ProcessNode(_di_IXMLNode Node);
public:		// User declarations
  bool __fastcall CheckVideoLoaded(void);
  __fastcall TFormVideo(TComponent* Owner);
  void __fastcall UpdateRegionProp(TRegion *a_region, bool all=false);
  void __fastcall RepaintRegion(TRegion *a_region, bool show_nodes=true);
  void __fastcall CopyFrameClip(void);
  void __fastcall VideoEnd(TObject *Sender);
  void __fastcall VideoStart(TObject *Sender);
  void __fastcall VideoPrevIFrame(TObject *Sender);
  void __fastcall VideoNextIFrame(TObject *Sender);
  void __fastcall VideoTimeCode(TObject *Sender);
  void __fastcall VideoGotoFrame(TObject *Sender);
  void __fastcall VideoFWD(TObject *Sender);
  void __fastcall VideoREW(TObject *Sender);
  void __fastcall ExportXML(TObject *Sender);
  void __fastcall ImportXML(TObject *Sender);
  void __fastcall ExportXMLTraj(TObject *Sender);
  void __fastcall ExportText(TObject *Sender);
  void __fastcall CleanupUI(void);
  void __fastcall BBWI(TObject *Sender);
  void __fastcall BBWD(TObject *Sender);
  void __fastcall BBHI(TObject *Sender);
  void __fastcall BBHD(TObject *Sender);
  TList *regions;
  __int64 currentFrame; // current frame
  __int64 maxFrame;			// maximum frame number
  bool __fastcall OpenVideoFile(AnsiString filename);
  bool __fastcall OpenProjectFile(AnsiString Filename, bool xml=false);
  bool __fastcall OpenProjectFileXML(AnsiString Filename);
  bool __fastcall SaveProjectFile(AnsiString Filename, bool xml=false);
  String VidFilename;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormVideo *FormVideo;
//---------------------------------------------------------------------------
#endif
