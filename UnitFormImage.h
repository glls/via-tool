//---------------------------------------------------------------------------

#ifndef UnitFormImageH
#define UnitFormImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <IniFiles.hpp>
#include <Dialogs.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "GR32_Image.hpp"
#include "GR32_Layers.hpp"
#include "GR32_Polygons.hpp"
#include "UnitUtils.h"
//---------------------------------------------------------------------------

enum irt {
  rRectangle=0, rCircle=1, rEllipse=2, rPolygon=3, rFreeform=4, rSegmentation=5
};

typedef struct {
  TList *pointlist;
  TBitmap32 *bitmap;
} TImgData;

typedef struct {
	TShape *shape;
  AnsiString description;
  TColor color;
  TStringList *descriptors;
  irt rType;
  TImgData *ImgData;
} TImgRegion;


class TFormImage : public TForm
{
__published:	// IDE-managed Components
  TPanel *PanelLeftImg;
  TPageControl *PageControlImage;
  TTabSheet *TabSheetImgRegions;
  TButton *ButtonImgToFront;
  TButton *ButtonImgToBack;
  TButton *ButtonCreateImgR;
  TButton *ButtonDelImgR;
  TButton *ButtonAddImgRegionDesc;
  TButton *ButtonDelImgRegionDesc;
  TListBox *ListBoxImgNodes;
  TListBox *ListBoxImgRegionDesc;
  TLabel *lbl6;
  TLabel *lblrt;
  TLabel *lblrn;
  TEdit *EditRImgName;
  TLabel *lblColor;
  TEdit *EditRImgY;
  TEdit *EditRImgH;
  TEdit *EditRImgW;
  TEdit *EditRImgX;
  TLabel *lblx;
  TLabel *cxLabel25;
  TLabel *cxLabel26;
  TLabel *lbly;
  TButton *ButtonMerge;
  TButton *ButtonSeg;
  TTabSheet *TabSheetImg;
  TButton *ButtonAddImgDesc;
  TButton *ButtonDelImgDesc;
  TListBox *ListBoxImageDesc;
  TLabel *Label10;
  TEdit *IATitle;
  TEdit *IAAnnotator;
  TEdit *IADesc;
  TLabel *cxLabel28;
  TLabel *cxLabel29;
  TLabel *cxLabel30;
  TLabel *cxLabel31;
  TEdit *IAFilename;
  TLabel *cxLabel32;
  TEdit *IAAnnoFile;
  TLabel *cxLabel33;
  TGroupBox *grpbad;
  TTreeView *TreeXMLImg;
  TLabel *lblAnnot;
  TButton *ButtonLoadImgAnno;
  TPanel *PanelClientImg;
  TPanel *PanelImageContainer;
  TScrollBox *ScrollBox;
  TShape *ShapeImg;
  TImage32 *ImageAn;
  TOpenDialog *OpenDialogImg;
  TXMLDocument *XMLProject;
  TButton *ButtonPoints;
  TComboBox *ComboBoxRImgType;
  TDateTimePicker *IADateTime;
  TColorBox *ColorBoxRImg;
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall ImageAnMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, TCustomLayer *Layer);
  void __fastcall ImageAnMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y, TCustomLayer *Layer);
  void __fastcall ImageAnClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall ListBoxImgNodesClick(TObject *Sender);
  void __fastcall EditRImgNameKeyPress(TObject *Sender, char &Key);
  void __fastcall ButtonMergeClick(TObject *Sender);
  void __fastcall ButtonSegClick(TObject *Sender);
  void __fastcall ComboBoxRImgTypePropertiesChange(TObject *Sender);
  void __fastcall ButtonCreateImgRClick(TObject *Sender);
  void __fastcall ButtonDelImgRClick(TObject *Sender);
  void __fastcall ButtonImgToFrontClick(TObject *Sender);
  void __fastcall ButtonImgToBackClick(TObject *Sender);
  void __fastcall ListBoxImgNodesKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ListBoxImageDescDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
  void __fastcall ListBoxImageDescDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
  void __fastcall ListBoxImgRegionDescDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
  void __fastcall ListBoxImgRegionDescDragDrop(TObject *Sender,
          TObject *Source, int X, int Y);
  void __fastcall ButtonAddImgRegionDescClick(TObject *Sender);
  void __fastcall ButtonDelImgRegionDescClick(TObject *Sender);
  void __fastcall ButtonAddImgDescClick(TObject *Sender);
  void __fastcall ButtonDelImgDescClick(TObject *Sender);
  void __fastcall EditRImgXDblClick(TObject *Sender);
  void __fastcall EditRImgYDblClick(TObject *Sender);
  void __fastcall EditRImgWDblClick(TObject *Sender);
  void __fastcall EditRImgHDblClick(TObject *Sender);
  void __fastcall ListBoxImgRegionDescKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ListBoxImageDescKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ButtonLoadImgAnnoClick(TObject *Sender);
  void __fastcall ColorBoxRImgPropertiesChange(TObject *Sender);
  void __fastcall ButtonPointsClick(TObject *Sender);
private:	// User declarations
  TImgRegion * __fastcall GetSelectedImgRegion(TObject *Sender);
  void __fastcall ClearImgRegionData(TImgRegion *imgregion);
  bool __fastcall CreateImgRegionFromFile(AnsiString filename);
  void __fastcall CopyToBack(void);
	void __fastcall NodeImgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall NodeImgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall NodeImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall StartEditRegion(int mode);
  bool draw_firsttime;
  // draw_editing 0=false, 1=polygon, 2=freeform
  int draw_editing;
  TObjectList *FImgNodes;
  void __fastcall AddPoint(int X, int Y);
  void __fastcall ShapeAround(TList *l, TShape *shape);
  TList *edit_pList;
  void __fastcall ShapeImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall ShapeImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y);
  void __fastcall ShapeImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall SetImgNodesVisible(bool);
  void __fastcall PositionImgNodes(TWinControl* AroundControl);
  bool NodePositioning;
  Types::TPoint oldPos;
  TWinControl *FCurrentNodeControl;
  void __fastcall CreateImgNodes(void);
  TStringList *ImageDescriptors;
  void __fastcall DrawRegion(void);
  bool __fastcall SaveProjectFileXML(AnsiString Filename);
  void __fastcall ProcessNode(_di_IXMLNode Node);
  void __fastcall ProcessNodeLM(_di_IXMLNode Node);
public:		// User declarations
  __fastcall TFormImage(TComponent* Owner);
  void __fastcall CleanupImgRegions(void);
  void __fastcall UpdateImgRegionProp(TImgRegion *a_region);
  void __fastcall UpdateImgRegionImgData(TImgRegion *a_imgregion);
  void __fastcall RepaintImgRegionNodes(TImgRegion *a_region, bool show_nodes=true);
  void __fastcall SetImgRegionsVis(bool show);
  void __fastcall ExportText(void);
  void __fastcall ExtractMpeg7(TObject *Sender);
  void __fastcall CleanupUI(void);
  void __fastcall OpenImage(String Filename);
  bool __fastcall OpenProjectFile(AnsiString Filename, bool xml=false, int ProjectType_minor=0);
  bool __fastcall OpenProjectFileXML(AnsiString Filename);
  bool __fastcall OpenProjectFileXML_Labelme(AnsiString Filename);
  bool __fastcall SaveProjectFile(AnsiString Filename, bool xml=false);
  TList *imgregions;
  TBitmap32 *backbitmap;
  TList *edit_imgList;
  TPolygon32 *Polygon;
  String ImgFilename;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
