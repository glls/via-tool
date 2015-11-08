//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormImage.h"
#include "UnitMain.h"
#include "UnitLog.h"
#include "UnitMerge.h"    

#include "UnitSelectMPEG7.h"
#include "UnitImport.h"

#include <stdio.h>
#include "UnitPoints.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GR32_Image"
#pragma resource "*.dfm"

TFormImage *FormImage;
//---------------------------------------------------------------------------
__fastcall TFormImage::TFormImage(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::FormCreate(TObject *Sender)
{
  FImgNodes = new TObjectList(false);
  imgregions = new TList();
  edit_imgList = new TList();
  ImageDescriptors = new TStringList;

  draw_firsttime = true;
  draw_editing = 0;
  PageControlImage->ActivePage = TabSheetImgRegions;
  Top = 0;
  Left = 0;
  ImgFilename = "";

  CreateImgNodes();
  CleanupUI();
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::FormDestroy(TObject *Sender)
{
  TImgRegion *imgregion;
  TImgRegion *a_imgregion;
  TPoint *p;
  TImgData *pImgData;

	//delete image regions
  if (ListBoxImgNodes->Count) {
    for (int i=0; i < ListBoxImgNodes->Count; i++) {
      a_imgregion = (TImgRegion *) (imgregions->Items[i]);
      if (a_imgregion->ImgData) {
        TPoint *p;
        for(int i=0; i < a_imgregion->ImgData->pointlist->Count; i++) {
          p = (TPoint *) (a_imgregion->ImgData->pointlist->Items[i]);
          delete p;
        }
        delete a_imgregion->ImgData->pointlist;
        delete a_imgregion->ImgData->bitmap;
        delete a_imgregion->ImgData;
      }
      delete a_imgregion->shape;
      delete a_imgregion->descriptors;
      delete a_imgregion;
    }
  }

  for(int k=0; k < edit_imgList->Count; k++) {
    pImgData = (TImgData *)edit_imgList->Items[k];
    for(int i=0; i < pImgData->pointlist->Count; i++) {
      p = (TPoint *) pImgData->pointlist->Items[i];
      delete p;
    }
    delete pImgData->bitmap;
    delete pImgData;
  }

	delete imgregions;
  delete edit_imgList;
  delete backbitmap;
  delete FImgNodes;
  delete ImageDescriptors;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ImageAnMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y,
      TCustomLayer *Layer)
{
	if (!draw_editing)
    return;

  if (Button == mbLeft) {
    AddPoint(X,Y);
  }
  else if (Button == mbRight)
  {
	  TPoint *p1,*p2;
    TImgData *imgd;

   	// stop edit mode
    draw_firsttime = true;
    draw_editing = 0;
    SetImgRegionsVis(true);

    // if no points added exit
    if (edit_pList->Count == 0) {
    	MessageDlg("Cannot add points to region.\nNo points added!", mtError, TMsgDlgButtons() << mbOK, 0);
      return;
    }

    // close region
    // addpoint - first point
    p1 = (TPoint *)edit_pList->Items[0];
    if (edit_pList->Count > 1) {
	    p2 = (TPoint *)edit_pList->Items[edit_pList->Count-1];
	    // if last point <> first
      if ( (p2->x != p1->x) && (p2->y != p1->y) )
	  	  AddPoint(p1->x, p1->y);
    }

    // selected node shape
    TImgRegion *selregion;
	  int i = ListBoxImgNodes->ItemIndex;
    selregion = (TImgRegion *) imgregions->Items[i];

    imgd = new TImgData;
    imgd->pointlist = edit_pList;
    ShapeAround(imgd->pointlist, selregion->shape);
    //RepaintImgRegion(selregion, true);
    selregion->ImgData = imgd;

    // copy all to bitmap
    TBitmap32 *b;
    b = new TBitmap32();
    //b->Width = ImageAn->Width;
    //b->Height = ImageAn->Height;
    b->Width = selregion->shape->Width;
    b->Height = selregion->shape->Height;
    b->DrawMode = dmTransparent;

    //draw regions on bitmap
    TPoint *p;
    if (edit_pList->Count) {
      /* old draw method - no fill
      p = (TPoint *) edit_pList->Items[0];
      b->PenColor = clBlack32;
      b->MoveTo(p->x - selregion->shape->Left, p->y - selregion->shape->Top);
      for(int i=1; i < edit_pList->Count; i++) {
        p = (TPoint *) edit_pList->Items[i];
        b->Canvas->LineTo(p->x - selregion->shape->Left, p->y - selregion->shape->Top);
        b->LineToS(p->x - selregion->shape->Left, p->y - selregion->shape->Top);  */
      TPoint *points = new TPoint[edit_pList->Count];
      b->Canvas->Brush->Color = selregion->color;
      b->Canvas->Brush->Style = bsDiagCross;
      for (int p=0; p < edit_pList->Count; p++) {
        points[p] = *(TPoint *)edit_pList->Items[p];
        points[p].x = points[p].x - selregion->shape->Left;
        points[p].y = points[p].y - selregion->shape->Top;
      }
      b->Canvas->Polygon(points, edit_pList->Count-1);
      delete points;
    }

    edit_pList = NULL;
    imgd->bitmap = b;
    //edit_imgList->Add(imgd);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ImageAnMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y, TCustomLayer *Layer)
{
  // not working when on shape
  //Types::TPoint xy = ImageAn->ControlToBitmap(Gr32::Point(X, Y));
  //LabelXY->Caption = Format("X: %d Y: %d", ARRAYOFCONST(((int)xy.x,(int)xy.y)));
  if (!draw_editing)
    return;
  if (draw_editing == 2) {
    // freeform
    if (Shift.Contains(ssLeft) ) {
      AddPoint(X,Y);
    }
  }
}
//---------------------------------------------------------------------------

TImgRegion * __fastcall TFormImage::GetSelectedImgRegion(TObject *Sender)
{
  TImgRegion *p, *sel;
  sel = NULL;

  for (int i=0; i < imgregions->Count; i++) {
    p = (TImgRegion *) imgregions->Items[i];
    if (p->shape == (TShape *)(Sender) )
      sel = p;
  }
  return sel;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::CleanupImgRegions(void)
{
  TImgRegion *imgregion;

  if (ListBoxImgNodes->Count) {
    for (int i=0; i < ListBoxImgNodes->Count; i++) {
      imgregion = (TImgRegion *) imgregions->Items[i];
      delete imgregion->shape;
      delete imgregion;
    }
  }
  imgregions->Clear();
  ListBoxImgNodes->Clear();
  ListBoxImgRegionDesc->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::CopyToBack(void)
{
  delete backbitmap;
  backbitmap = new TBitmap32();
  backbitmap->Assign(ImageAn->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ClearImgRegionData(TImgRegion *a_imgregion)
{
  //clear bitmap & points
  if (a_imgregion->ImgData) {
    TPoint *p;
    for(int i=0; i < a_imgregion->ImgData->pointlist->Count; i++) {
      p = (TPoint *) a_imgregion->ImgData->pointlist->Items[i];
      delete p;
    }
    delete a_imgregion->ImgData->pointlist;
    delete a_imgregion->ImgData->bitmap;
    delete a_imgregion->ImgData;
    a_imgregion->ImgData = NULL;
    ImageAn->Bitmap->Assign(backbitmap);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TFormImage::CreateImgRegionFromFile(AnsiString filename)
{
  AnsiString s;
  TPoint *p, *p1, *p2;
  int X, Y;
  TImgData *imgd;
  TImgRegion *region;
  TStringList *sl;

  if (!Sysutils::FileExists(filename))
    return false;

  sl = new TStringList;
  sl->LoadFromFile(filename);
  if (sl->Count <2) {
    // invalid data
    delete sl;
    return false;
  }
  // prepare for new data
  edit_pList = new TList;

  for (int i = 0; i < sl->Count; i++) {
    s = sl->Strings[i];
    sscanf(s.c_str(), "%d %d", &X, &Y);
    p = new TPoint(X,Y);
    edit_pList->Add(p);
  }
  delete sl;

	//create shaped image region
  region = new TImgRegion;
  region->shape = new TShape(FormImage);
  region->shape->Parent = ImageAn;
  region->shape->Visible = false;
  region->shape->Shape = stRectangle;
  region->rType = rSegmentation;
  region->shape->Brush->Style = bsClear;

  region->color = mcolors[random(15)];
  region->shape->Pen->Color = region->color;

  //region->shape->Pen->Mode = pmMask;
  region->shape->Pen->Width = 1;
  //region->shape->Pen->Width = PenWidth;

  region->shape->OnMouseDown = ShapeImgMouseDown;
  region->shape->OnMouseMove = ShapeImgMouseMove;
  region->shape->OnMouseUp = ShapeImgMouseUp;
  region->shape->Constraints->MaxHeight = MAX_REGION;
  region->shape->Constraints->MaxWidth = MAX_REGION;
  region->shape->Constraints->MinHeight = MIN_REGION;
  region->shape->Constraints->MinWidth = MIN_REGION;
  region->shape->Top = DEF_Y;
  region->shape->Left = DEF_X;
  region->shape->Width = DEF_W;
  region->shape->Height = DEF_H;
  region->shape->Visible = true;
  region->ImgData = NULL;
  // disable on change
  //TODO: check if needed (was DevEx)
  ComboBoxRImgType->OnChange = NULL;
  ComboBoxRImgType->ItemIndex = 0;
  ComboBoxRImgType->OnChange = ComboBoxRImgTypePropertiesChange;

  region->description.printf("Segment %02d", ListBoxImgNodes->Count+1);
  region->descriptors = new TStringList;

  imgregions->Add(region);
  UpdateImgRegionProp(region);
  ListBoxImgNodes->Items->Add(region->description);
  ListBoxImgNodes->Selected[ListBoxImgNodes->Count-1] = true;

  p1 = (TPoint *)edit_pList->Items[0];
  if (edit_pList->Count > 1) {
    p2 = (TPoint *)edit_pList->Items[edit_pList->Count-1];
    // if last point <> first
    if ( (p2->x != p1->x) && (p2->y != p1->y) )
      AddPoint(p1->x, p1->y);
  }
  imgd = new TImgData;
  imgd->pointlist = edit_pList;
  ShapeAround(imgd->pointlist, region->shape);
  region->ImgData = imgd;

  // copy all to bitmap
  TBitmap32 *b;
  b = new TBitmap32();
  b->Width = region->shape->Width;
  b->Height = region->shape->Height;
  b->DrawMode = dmTransparent;

  //draw regions on bitmap
  if (edit_pList->Count) {
    p = (TPoint *) edit_pList->Items[0];
    b->PenColor = Color32(region->color);//clBlack32;
    /*
    b->MoveTo(p->x - region->shape->Left, p->y - region->shape->Top);
    for(int i=1; i < edit_pList->Count; i++) {
      p = (TPoint *) edit_pList->Items[i];
      b->Canvas->LineTo(p->x - region->shape->Left, p->y - region->shape->Top);
      // TODO: check canvas
      b->LineToS(p->x - region->shape->Left, p->y - region->shape->Top);
    }
    */
      TPoint *points = new TPoint[edit_pList->Count];
      b->Canvas->Brush->Color = region->color;
      b->Canvas->Brush->Style = bsDiagCross;
        for (int p=0; p < edit_pList->Count; p++) {
          points[p] = *(TPoint *)edit_pList->Items[p];
          points[p].x = points[p].x - region->shape->Left;
          points[p].y = points[p].y - region->shape->Top;
        }
        b->Canvas->Polygon(points, edit_pList->Count-1);
        delete points;
  }

  edit_pList = NULL;
  imgd->bitmap = b;

  // update display
  RepaintImgRegionNodes(region, true);

  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::NodeImgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TImgRegion *selregion;
	int i = ListBoxImgNodes->ItemIndex;
  selregion = (TImgRegion *) imgregions->Items[i];
  if (selregion->rType > rEllipse)
    return;

  NodePositioning = true;
  GetCursorPos(&oldPos);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::NodeImgMouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
  Types::TPoint newPos, frmPoint;
  Types::TRect OldRect;
  bool AdjL,AdjR,AdjT,AdjB;

  if (NodePositioning) {
    SetImgNodesVisible(false);
    GetCursorPos(&newPos);
    frmPoint = FCurrentNodeControl->Parent->ScreenToClient(Mouse->CursorPos);
    OldRect = FCurrentNodeControl->BoundsRect;
    AdjL = false; AdjR = false;
    AdjT = false; AdjB = false;
    switch (FImgNodes->IndexOf( (TWinControl *)(Sender))) {
      case 0: AdjL = true; AdjT = true;
        break;
      case 1: AdjT = true;
        break;
      case 2: AdjR = true; AdjT = true;
        break;
      case 3: AdjR = true;
        break;
      case 4: AdjR = true; AdjB = true;
        break;
      case 5: AdjB = true;
        break;
      case 6: AdjL = true; AdjB = true;
        break;
      case 7: AdjL = true;
        break;
    }
    if (AdjL) OldRect.Left = frmPoint.x;
    if (AdjR) OldRect.Right = frmPoint.x;
    if (AdjT) OldRect.Top = frmPoint.y;
    if (AdjB) OldRect.Bottom = frmPoint.y;
    FCurrentNodeControl->SetBounds(OldRect.Left, OldRect.Top, OldRect.Right - OldRect.Left, OldRect.Bottom - OldRect.Top);
    ((TWinControl *)(Sender))->Left = ((TWinControl *)(Sender))->Left -oldPos.x + newPos.x;
    ((TWinControl *)(Sender))->Top = ((TWinControl *)(Sender))->Top -oldPos.y + newPos.y;
    oldPos = newPos;
    // repaint nodes and update region data
    PositionImgNodes(FCurrentNodeControl);
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormImage::NodeImgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (NodePositioning) {
    Screen->Cursor = crDefault;
    NodePositioning = false;
    SetImgNodesVisible(true);
    //update region data
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::UpdateImgRegionImgData(TImgRegion *a_imgregion)
{
  // draw image if exists
  if (a_imgregion) {
    if (a_imgregion->ImgData) {
      if(a_imgregion->ImgData->bitmap) {
        ImageAn->Bitmap->DrawMode = dmTransparent;
        // restore original bitmap
        ImageAn->Bitmap->Assign(backbitmap);
        ImageAn->Bitmap->Draw(a_imgregion->shape->Left, a_imgregion->shape->Top,
          a_imgregion->ImgData->bitmap);
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::UpdateImgRegionProp(TImgRegion *a_imgregion)
{
	if (a_imgregion) {
  	EditRImgX->Text = a_imgregion->shape->Left;
    EditRImgY->Text = a_imgregion->shape->Top;
    EditRImgW->Text = a_imgregion->shape->Width;
    EditRImgH->Text = a_imgregion->shape->Height;
    EditRImgName->Text = a_imgregion->description;

    // do not fire event if we change the combo here
    ComboBoxRImgType->OnChange = NULL;
    if (a_imgregion->rType == rRectangle)
			ComboBoxRImgType->ItemIndex = 0;
    else if (a_imgregion->rType == rCircle)
			ComboBoxRImgType->ItemIndex = 1;
    else if (a_imgregion->rType == rEllipse)
	    ComboBoxRImgType->ItemIndex = 2;
    else if (a_imgregion->rType == rPolygon)
	    ComboBoxRImgType->ItemIndex = 3;
    else if (a_imgregion->rType == rFreeform)
	    ComboBoxRImgType->ItemIndex = 4;
    else if (a_imgregion->rType == rSegmentation)
	    ComboBoxRImgType->ItemIndex = 5;
    ComboBoxRImgType->OnChange = ComboBoxRImgTypePropertiesChange;

    ColorBoxRImg->OnChange = NULL;
	  ColorBoxRImg->Selected = a_imgregion->color;
    ColorBoxRImg->OnChange = ColorBoxRImgPropertiesChange;
    if (a_imgregion->descriptors)
      ListBoxImgRegionDesc->Items->Assign(a_imgregion->descriptors);

    UpdateImgRegionImgData(a_imgregion);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::SetImgRegionsVis(bool show)
{
	TImgRegion * imgregion;
  for (int i=0; i < imgregions->Count; i++) {
    imgregion = (TImgRegion *) imgregions->Items[i];
    if (show)
      imgregion->shape->Visible = true;
    else
      imgregion->shape->Visible = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::RepaintImgRegionNodes(TImgRegion *a_imgregion, bool show_nodes)
{
	if (show_nodes) {
  	SetImgNodesVisible(false);
    PositionImgNodes( (TWinControl *)(a_imgregion->shape) );
    SetImgNodesVisible(true);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	Image annotation
//---------------------------------------------------------------------------
void __fastcall TFormImage::ButtonCreateImgRClick(TObject *Sender)
{
  TImgRegion *region;
	//create shaped image region
  region = new TImgRegion;
  region->shape = new TShape(FormImage);
  region->shape->Parent = ImageAn;
  region->shape->Visible = false;
  region->shape->Shape = stRectangle;
  region->rType = rRectangle;
  region->shape->Brush->Style = bsClear;
  
  region->shape->Pen->Color = 4;
  //region->shape->Pen->Mode = pmMask;
  region->shape->Pen->Width = FormMain->PenWidth;
  region->shape->OnMouseDown = ShapeImgMouseDown;
  region->shape->OnMouseMove = ShapeImgMouseMove;
  region->shape->OnMouseUp = ShapeImgMouseUp;
  region->shape->Constraints->MaxHeight = MAX_REGION;
  region->shape->Constraints->MaxWidth = MAX_REGION;
  region->shape->Constraints->MinHeight = MIN_REGION;
  region->shape->Constraints->MinWidth = MIN_REGION;
  region->shape->Top = DEF_Y;
  region->shape->Left = DEF_X;
  region->shape->Width = DEF_W;
  region->shape->Height = DEF_H;
  region->shape->Visible = true;
  region->ImgData = NULL;
  // disable on change
  ComboBoxRImgType->OnChange = NULL;
  ComboBoxRImgType->ItemIndex = 0;
  ComboBoxRImgType->OnChange = ComboBoxRImgTypePropertiesChange;

  region->description.printf("Region %02d", ListBoxImgNodes->Count+1);
  region->color = ColorBoxRImg->Selected;
  region->descriptors = new TStringList;

  imgregions->Add(region);
  UpdateImgRegionProp(region);
  ListBoxImgNodes->Items->Add(region->description);
  ListBoxImgNodes->Selected[ListBoxImgNodes->Count-1] = true;

  // update display
  RepaintImgRegionNodes(region, true);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ShapeImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
// click on shape
  TImgRegion *a_imgregion;

  for (int i=0; i < imgregions->Count; i++) {
    a_imgregion = (TImgRegion *) imgregions->Items[i];

    if (a_imgregion->shape == (TShape *)(Sender) ) {
      GetCursorPos(&oldPos);
      RepaintImgRegionNodes(a_imgregion);
      ListBoxImgNodes->Selected[i] = true;
      //not needed UpdateImgRegionProp(a_imgregion);
      return;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ShapeImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	TObject *t;
  Types::TPoint newPos;
  TImgRegion *a_imgregion;

  if (Shift.Contains(ssLeft)) {
    a_imgregion = GetSelectedImgRegion(Sender);
    if (a_imgregion) {
      //dont move polygon/freeform/segm
      if (a_imgregion->rType > rEllipse)
        return;
    }

    SetImgNodesVisible(false);
    GetCursorPos(&newPos);
    Screen->Cursor = crSize;
    //((TShape *)(Sender))->Pen->Mode = pmXor;
    //((TShape *)(Sender))->Pen->Style = psDot;
    ((TWinControl *)(Sender))->Left = ((TWinControl *)(Sender))->Left - oldPos.x + newPos.x;
    ((TWinControl *)(Sender))->Top = ((TWinControl *)(Sender))->Top - oldPos.y + newPos.y;

    oldPos = newPos;
    UpdateImgRegionProp(a_imgregion);

/*  if ((oldPos.x != newPos.x) && (oldPos.y != newPos.y))
    {
      oldPos = newPos;
      UpdateImgRegionProp(a_imgregion);
    }
    */
  } // left mb
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ShapeImgMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TImgRegion *a_imgregion;

  Screen->Cursor = crDefault;
  //((TShape *)(Sender))->Pen->Mode = pmCopy;
  PositionImgNodes( (TWinControl *)(Sender) );
  SetImgNodesVisible(true);

  //update region data
  a_imgregion = GetSelectedImgRegion(Sender);
  UpdateImgRegionProp(a_imgregion);
}
//---------------------------------------------------------------------------


void __fastcall TFormImage::ButtonDelImgRClick(TObject *Sender)
{
  //delete selected shaped region
  int i = ListBoxImgNodes->ItemIndex;

  if ( (i >= 0) && (
  	MessageDlg("Are you sure you want to delete the selected region?", mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0)
    	== mrYes ) )
    {
    // delete image region
    TImgRegion *selregion;
    SetImgNodesVisible(false);
    selregion = (TImgRegion *) imgregions->Items[i];
    ClearImgRegionData(selregion);
    delete selregion->shape;
    delete selregion;
    ListBoxImgNodes->DeleteSelected();
    imgregions->Delete(i);

    // select another in listbox
    if (i < ListBoxImgNodes->Count-1 )
      ListBoxImgNodes->Selected[i] = true;
    else
      if (ListBoxImgNodes->Count)
        ListBoxImgNodes->Selected[ListBoxImgNodes->Count-1] = true;

    ListBoxImgNodesClick(Sender);
    ListBoxImgNodes->Refresh();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImgNodesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelImgRClick(Sender);
  }
  else if (Key == VK_INSERT) {
    ButtonCreateImgRClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImgNodesClick(TObject *Sender)
{
  TImgRegion *a_imgregion;

  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    //UpdateImgRegionProp(a_imgregion);
    RepaintImgRegionNodes(a_imgregion, true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonImgToBackClick(TObject *Sender)
{
  int i = ListBoxImgNodes->ItemIndex;
  TImgRegion *a_imgregion;

  if (i >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[i];
    a_imgregion->shape->SendToBack();
    ImageAn->SendToBack();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonImgToFrontClick(TObject *Sender)
{
  int i = ListBoxImgNodes->ItemIndex;
  TImgRegion *a_imgregion;

  if (i >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[i];
    a_imgregion->shape->BringToFront();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::PositionImgNodes(TWinControl* AroundControl)
{
	int Node,T,L,CT,CL,FR,FB,FT,FL;
  Types::TPoint TopLeft;
  TImgRegion *a_imgregion;

  FCurrentNodeControl = AroundControl;
  a_imgregion = GetSelectedImgRegion(FCurrentNodeControl);
  if (!a_imgregion) return;

	for (Node=0; Node <=7; Node ++) {
  	CL = (AroundControl->Width / 2) + AroundControl->Left -2;
    CT = (AroundControl->Height / 2) + AroundControl->Top -2;
    FR = AroundControl->Left + AroundControl->Width - 2;
    FB = AroundControl->Top + AroundControl->Height - 2;
    FT = AroundControl->Top - 2;
    FL = AroundControl->Left - 2;
    switch (Node) {
    	case 0: T = FT; L = FL;
      	break;
    	case 1: T = FT; L = CL;
      	break;
    	case 2: T = FT; L = FR;
      	break;
    	case 3: T = CT; L = FR;
      	break;
    	case 4: T = FB; L = FR;
      	break;
    	case 5: T = FB; L = CL;
      	break;
    	case 6: T = FB; L = FL;
      	break;
    	case 7: T = CT; L = FL;
      	break;
      default:
      	T = 0; L = 0;
    }
    TopLeft = AroundControl->Parent->ClientToScreen(Classes::Point(L,T));
    TopLeft = ((TPanel *)(FImgNodes->Items[Node]))->Parent->ScreenToClient(TopLeft);
    ((TPanel *)(FImgNodes->Items[Node]))->Top = TopLeft.y;
    ((TPanel *)(FImgNodes->Items[Node]))->Left = TopLeft.x;
  }

  // update selected image region
	UpdateImgRegionProp(a_imgregion);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::SetImgNodesVisible(bool vis)
{
	for (int Node=0; Node <=7; Node ++)
    ((TPanel *)(FImgNodes->Items[Node]))->Visible = vis;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::CreateImgNodes(void)
{
	int node;
  TPanel *panel;

  for (node=0; node <=7; node ++) {
  	panel = new TPanel(FormImage);
    FImgNodes->Add(panel);
    panel->BevelOuter = bvNone;
    panel->Color = clBlack;
    panel->Name = "NodeImg" + IntToStr(node);
    panel->Width = 5;
    panel->Height = 5;
    panel->FullRepaint = false;

    // prevent drawing on main form
    panel->Parent = ImageAn; //this
    //panel->DoubleBuffered = true;
    panel->Visible = false;

    switch (node) {
    	case 0 :
      case 4 : panel->Cursor=crSizeNWSE; break;
      case 1 :
      case 5 : panel->Cursor=crSizeNS; break;
      case 2 :
      case 6 : panel->Cursor=crSizeNESW; break;
      case 3 :
      case 7 : panel->Cursor=crSizeWE; break;
    }
    panel->OnMouseDown = NodeImgMouseDown;
    panel->OnMouseMove = NodeImgMouseMove;
    panel->OnMouseUp = NodeImgMouseUp;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ColorBoxRImgPropertiesChange(TObject *Sender)
{
  TImgRegion *a_imgregion;

  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    a_imgregion->shape->Pen->Color = ColorBoxRImg->Selected;
    a_imgregion->color = ColorBoxRImg->Selected;
    a_imgregion->shape->Refresh();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ComboBoxRImgTypePropertiesChange(
      TObject *Sender)
{
  TImgRegion *a_imgregion;

  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];

    bool has_data = (a_imgregion->ImgData != NULL);
    switch (ComboBoxRImgType->ItemIndex) {
    	//Rectangle
    	case 0:
        if (!has_data) {
  	      a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rRectangle;
        }
        else if (MessageDlg("Discard data points and change region type to Rectangle?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
          a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rRectangle;
        }
      break;
      //Circle
    	case 1:
        if (!has_data) {
          a_imgregion->shape->Shape = stCircle;
          a_imgregion->rType = rCircle;
        }
        else if (MessageDlg("Discard data points and change region type to Circle?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
          a_imgregion->shape->Shape = stCircle;
          a_imgregion->rType = rCircle;
        }
      break;
      //Ellipse
    	case 2:
        if (!has_data) {
        	a_imgregion->shape->Shape = stEllipse;
          a_imgregion->rType = rEllipse;
        }
        else if (MessageDlg("Discard data points and change region type to Ellipse?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
        	a_imgregion->shape->Shape = stEllipse;
          a_imgregion->rType = rEllipse;
        }
      break;
      //Polygon
    	case 3:
        if (!has_data) {
          a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rPolygon;
          StartEditRegion(1);
        }
        else if (MessageDlg("Discard data points and change region type to Polygon?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
        	a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rPolygon;
          StartEditRegion(1);
        }
      break;
      //Freeform
    	case 4:
        if (!has_data) {
          a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rFreeform;
          StartEditRegion(2);
        }
        else if (MessageDlg("Discard data points and change region type to Freeform?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
          a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rFreeform;
          StartEditRegion(2);
        }
      break;
      //Segmentation
      case 5:
      if (!has_data) {
	      a_imgregion->shape->Shape = stRectangle;
        a_imgregion->rType = rSegmentation;
        // run segmentation?
      }
      else if (MessageDlg("Discard data points and change region type to Segmentation?",
                 mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) {
          ClearImgRegionData(a_imgregion);
          a_imgregion->shape->Shape = stRectangle;
          a_imgregion->rType = rSegmentation;
          // run segmentation?
        }
      break;
    }
    a_imgregion->shape->Refresh();
    UpdateImgRegionProp(a_imgregion);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::EditRImgNameKeyPress(TObject *Sender, char &Key)
{
  TImgRegion *a_imgregion;
  
  if (Key == 13) {
    int i = ListBoxImgNodes->ItemIndex;
    if (i >= 0) {
      a_imgregion = (TImgRegion *) imgregions->Items[i];
      a_imgregion->description = EditRImgName->Text;
      ListBoxImgNodes->Items->Strings[i] = EditRImgName->Text;
      ListBoxImgNodes->Selected[i] = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::EditRImgXDblClick(TObject *Sender)
{
  TImgRegion *a_imgregion;
  
  //set X for selected region
  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    if (a_imgregion->rType >= rPolygon) return;

    int v = a_imgregion->shape->Left;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter X", "Enter value for X :", s)) {
      v = StrToIntDef(s, 0);
      a_imgregion->shape->Left = v;
      EditRImgX->Text = IntToStr(v);
      RepaintImgRegionNodes(a_imgregion);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImgRegionDescDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  if (ListBoxImgNodes->ItemIndex < 0) {
    MessageDlg("No region selected.\nYou must select a region to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }
  TImgRegion *a_imgregion;
  if (Sender->ClassNameIs("TListBox") //&& Source->ClassNameIs("TcxDragControlObject")
  ) {
    TListBox *DestList = (TListBox *)Sender;
    if (TreeXMLImg->Selected == NULL)
      return;
    AnsiString targdesc = TreeXMLImg->Selected->Text;
    if ( DestList->Items->IndexOf(targdesc) == -1 )
    {
      DestList->Items->Add(targdesc);
      DestList->Selected[DestList->Count-1] = true;
      a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
      a_imgregion->descriptors->Add(targdesc);
    }
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImgRegionDescDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = Source->ClassNameIs("TcxDragControlObject");
  //TODO: check
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonAddImgRegionDescClick(TObject *Sender)
{
	// add descriptor to image region
  if (ListBoxImgNodes->ItemIndex < 0) {
    MessageDlg("No region selected.\nYou must select a region to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  TImgRegion *a_imgregion;
  AnsiString targdesc;

  if (InputQuery("Input", "Descriptor", targdesc)) {
  	ListBoxImgRegionDesc->Items->Add(targdesc);
    ListBoxImgRegionDesc->Selected[ListBoxImgRegionDesc->Count-1] = true;
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    a_imgregion->descriptors->Add(targdesc);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonDelImgRegionDescClick(TObject *Sender)
{
  //del image region desc
  int i = ListBoxImgNodes->ItemIndex;
  int d = ListBoxImgRegionDesc->ItemIndex;
  TImgRegion *a_imgregion;

  if ( (i >= 0) && (d >= 0) && ( MessageDlg("Are you sure you want to delete the selected descriptor?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    // delete descriptor
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    a_imgregion->descriptors->Delete(d);
    ListBoxImgRegionDesc->Items->Delete(d);

    UpdateImgRegionProp(a_imgregion);

    if (d < ListBoxImgRegionDesc->Count-1 )
      ListBoxImgRegionDesc->Selected[d] = true;
    else
      if (ListBoxImgRegionDesc->Count)
        ListBoxImgRegionDesc->Selected[ListBoxImgRegionDesc->Count-1] = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImgRegionDescKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelImgRegionDescClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::EditRImgYDblClick(TObject *Sender)
{
  TImgRegion *a_imgregion;
  
  //set Y for selected region
  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    if (a_imgregion->rType >= rPolygon) return;

    int v = a_imgregion->shape->Top;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Y", "Enter value for Y :", s)) {
      v = StrToIntDef(s, 0);
      a_imgregion->shape->Top = v;
      EditRImgY->Text = IntToStr(v);
      RepaintImgRegionNodes(a_imgregion);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::EditRImgWDblClick(TObject *Sender)
{
  TImgRegion *a_imgregion;
  
  //set Y for selected region
  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    if (a_imgregion->rType >= rPolygon) return;

    int v = a_imgregion->shape->Width;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Width", "Enter value for Width :", s)) {
      v = StrToIntDef(s, 0);
      a_imgregion->shape->Width = v;
      EditRImgW->Text = IntToStr(v);
      RepaintImgRegionNodes(a_imgregion);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::EditRImgHDblClick(TObject *Sender)
{
  TImgRegion *a_imgregion;
  
  //set H for selected region
  if (ListBoxImgNodes->ItemIndex >= 0) {
    a_imgregion = (TImgRegion *) imgregions->Items[ListBoxImgNodes->ItemIndex];
    if (a_imgregion->rType >= rPolygon) return;
    
    int v = a_imgregion->shape->Height;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Height", "Enter value for Height :", s)) {
      v = StrToIntDef(s, 0);
      a_imgregion->shape->Height = v;
      EditRImgH->Text = IntToStr(v);
      RepaintImgRegionNodes(a_imgregion);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.",
    	mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImageDescDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  if (Sender->ClassNameIs("TListBox") //&& Source->ClassNameIs("TcxDragControlObject")
  )
  {
    TListBox *DestList = (TListBox *)Sender;
    //BUG: if drag and drop from ListBoxImg* to self
    //TODO: accept only from TreeXMLImg
    if (TreeXMLImg->Selected == NULL)
      return;
    AnsiString targdesc = TreeXMLImg->Selected->Text;
    if ( DestList->Items->IndexOf(targdesc) == -1 )
    {
      DestList->Items->Add(targdesc);
      DestList->Selected[DestList->Count-1] = true;
      ImageDescriptors->Add(targdesc);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImageDescDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = Source->ClassNameIs("TcxDragControlObject");
  //TODO: check
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ListBoxImageDescKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelImgDescClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonAddImgDescClick(TObject *Sender)
{
  AnsiString targdesc;

  if (InputQuery("Input", "Descriptor", targdesc)) {
  	ListBoxImageDesc->Items->Add(targdesc);
    ListBoxImageDesc->Selected[ListBoxImageDesc->Count-1] = true;
    ImageDescriptors->Add(targdesc);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonDelImgDescClick(TObject *Sender)
{
  // delete image descriptors
  int d = ListBoxImageDesc->ItemIndex;
  if ( (d >= 0) && ( MessageDlg("Are you sure you want to delete the selected descriptor?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    ImageDescriptors->Delete(d);
    ListBoxImageDesc->Items->Delete(d);
    ListBoxImageDesc->Items->Assign(ImageDescriptors);

    if (d < ListBoxImageDesc->Count-1 )
      ListBoxImageDesc->Selected[d] = true;
    else
      if (ListBoxImageDesc->Count)
        ListBoxImageDesc->Selected[ListBoxImageDesc->Count-1] = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ImageAnClick(TObject *Sender)
{
  SetImgNodesVisible(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::AddPoint(int X, int Y)
{
  TPoint *p;

  if (draw_firsttime) {
    draw_firsttime = false;
    ImageAn->Canvas->MoveTo(X,Y);
  }
  else {
    ImageAn->Canvas->LineTo(X,Y);
  }
  p = new TPoint(X,Y);
  edit_pList->Add(p);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::DrawRegion(void)
{
//NOT USED
#ifdef NOT_USED
  if (edit_imgList->Count) {
    for(int k=0; k < edit_imgList->Count; k++) {
      pImgData = (TImgData *)edit_imgList->Items[k];
      ImageAn->Bitmap->DrawMode = dmTransparent;
      ImageAn->Bitmap->Draw(0, 0, pImgData->bitmap);
    }
  }
#endif
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ExportText(void)
{
	// export frame data
  TImgRegion *imgregion;
  TImgRegion *a_imgregion;
  TStringList *exp;
  AnsiString s;
  exp = new TStringList;

	//export video
	exp->Add("[Image Information]");
  exp->Add("Title:");
  exp->Add(IATitle->Text);
	exp->Add("Date:");
  exp->Add(IADateTime->DateTime.DateString());
  exp->Add("Description:");
  exp->Add(IADesc->Text);
  exp->Add("Annotator:");
  exp->Add(IAAnnotator->Text);
  exp->Add("Image filename:");
  exp->Add(IAFilename->Text);
  exp->Add("Image Descriptors filename:");
  exp->Add(IAAnnoFile->Text);
	exp->Add("Image Descriptors ("+IntToStr(ImageDescriptors->Count)+"):");
  if (ImageDescriptors->Count) {
  	for(int i=0; i< ImageDescriptors->Count ; i++) {
    	exp->Add(ImageDescriptors->Strings[i]);
    }
  }
  exp->Add("");

  //export regions
  if (ListBoxImgNodes->Count) {
	  exp->Add("[Region Information]");
    for (int i=0; i < ListBoxImgNodes->Count ; i++) {
      imgregion = (TImgRegion *) (imgregions->Items[i]);

      exp->Add("Object Number #"+IntToStr(i+1));
      exp->Add("Region Description:");
      exp->Add(imgregion->description);
      exp->Add("Region Shape:");
      if (imgregion->shape->Shape == stRectangle)
        s = "Rectangle";
      else if (imgregion->shape->Shape == stCircle)
        s = "Cirlce";
      else if (imgregion->shape->Shape == stEllipse)
        s = "Ellipse";
      exp->Add(s);
      exp->Add("Region Width:");
      exp->Add(imgregion->shape->Width);
      exp->Add("Region Height:");
      exp->Add(imgregion->shape->Height);
      exp->Add("Region X:");
      exp->Add(imgregion->shape->Left);
      exp->Add("Region Y:");
      exp->Add(imgregion->shape->Top);

      exp->Add("Region Descriptors ("+IntToStr(imgregion->descriptors->Count)+"):");
      for (int m=0; m < imgregion->descriptors->Count; m++) {
        exp->Add(imgregion->descriptors->Strings[m]);
      }
      exp->Add("");
    } // for i
  }

  if (FormMain->SaveDialog->Execute()) {
  	exp->SaveToFile(FormMain->SaveDialog->FileName);
    FormLog->Log("Text data exported to "+FormMain->SaveDialog->FileName);
  }

  exp->Clear();
  delete exp;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonMergeClick(TObject *Sender)
{
	// merge regions

  TFormMerge *FormM;
  FormM = new TFormMerge(Application->MainForm);
  FormM->CheckListBoxRegions->Items->Clear();

  for (int i=0; i<ListBoxImgNodes->Items->Count; i++) {
    FormM->CheckListBoxRegions->Items->Add(ListBoxImgNodes->Items->Strings[i]);
  } // check add all ?

  //select regions
  if (FormM->ShowModal() == mrOk) {
    int cc = 0;
    // check if selected > 1
    for (int i=0; i < FormM->CheckListBoxRegions->Items->Count; i++) {
      if (FormM->CheckListBoxRegions->Checked[i])
        cc++;
    }
    if(cc < 2) {
      // you must select more than 1 region
      MessageDlg("You must select more than one region", mtError, TMsgDlgButtons() << mbOK, 0);
      return;
    }
    TBitmap32 *b;
    b = new TBitmap32();
    b->Width = ImageAn->Bitmap->Width;
    b->Height = ImageAn->Bitmap->Height;
    b->Clear();

    b->PenColor = clWhite32;
    b->Canvas->Pen->Color = clWhite;
    b->Canvas->Brush->Color = clWhite;
    b->Canvas->Brush->Style = bsSolid;

    TImgRegion *selregion;
    for (int i = 0; i < FormM->CheckListBoxRegions->Items->Count; i++)
    {
      if (FormM->CheckListBoxRegions->Checked[i]) {
        selregion = (TImgRegion *) imgregions->Items[i];
        // draw regions
        // each region must have diff color
        //b->PenColor = i+1;
        //b->Canvas->Pen->Color = i+1;
        //b->Canvas->Brush->Color = i+1;

        if (selregion->rType == rRectangle) {
          //draw rectangle
          b->Canvas->Rectangle(selregion->shape->Left, selregion->shape->Top,
            selregion->shape->Left + selregion->shape->Width,
            selregion->shape->Top + selregion->shape->Height);
        }
        else if ((selregion->rType == rCircle) || (selregion->rType == rEllipse)) {
          //draw ellipse
          b->Canvas->Ellipse(selregion->shape->Left, selregion->shape->Top,
            selregion->shape->Left + selregion->shape->Width,
            selregion->shape->Top + selregion->shape->Height);
        }
        else if ((selregion->rType == rPolygon) || (selregion->rType == rFreeform) || selregion->rType == rSegmentation) {
          if(selregion->ImgData)
            if(selregion->ImgData->pointlist) {
              TPoint *points = new TPoint[selregion->ImgData->pointlist->Count];
              for (int p=0; p < selregion->ImgData->pointlist->Count; p++)
                points[p] = *(TPoint *)selregion->ImgData->pointlist->Items[p];
              //draw polygon
              b->Canvas->Polygon(points, selregion->ImgData->pointlist->Count-1);
              delete points;
            }
        }
        // end draw regions
      } // checked
    } // for (parse regions)

		// delete regions
    for (int i = FormM->CheckListBoxRegions->Items->Count-1; i >= 0; i--)
    { // reverse order for ListBoxImgNodes->Items->Delete(i);
      if (FormM->CheckListBoxRegions->Checked[i]) {
        selregion = (TImgRegion *) imgregions->Items[i];
        if (selregion->ImgData) {
          TPoint *p;
          for(int k=0; k < selregion->ImgData->pointlist->Count; k++) {
            p = (TPoint *) selregion->ImgData->pointlist->Items[k];
            delete p;
          }
          delete selregion->ImgData->pointlist;
          delete selregion->ImgData->bitmap;
          delete selregion->ImgData;
          ImageAn->Bitmap->Assign(backbitmap);
        }
        delete selregion->shape;
        delete selregion;
        ListBoxImgNodes->Items->Delete(i);
        imgregions->Delete(i);
      }
    }
    // create new region(s) from segmentation
		// export mask
#ifdef _DEBUG
    b->SaveToFile("d:\\output_mask.bmp");
#endif
    AnsiString curdir = ExtractFilePath(Application->ExeName);
    AnsiString pgm, params, outdir;;
    AnsiString inputImageName, segcmd;
    TSearchRec sr;
    inputImageName = ExtractFileName(ImgFilename);
    inputImageName = ChangeFileExt(inputImageName, "");
    outdir = FormMain->Dir_StoredData+"\\tmp";
    Sysutils::ForceDirectories(outdir);
    outdir = ExtractShortPathName(outdir);

    pgm = ChangeFileExt(inputImageName, "");
    DeleteFile(outdir+"\\"+pgm+".seg");
    WritePGM(b, outdir+"\\"+pgm+".seg");
    //del %1\%2_*.txt
    if (FindFirst(outdir+"\\"+inputImageName+"_*.txt", faAnyFile, sr) == 0) {
      do {
        DeleteFile(outdir+"\\"+sr.Name);
      } while (FindNext(sr) == 0);
      FindClose(sr);
    }
    //segcmd = Dir_SegTools+"\\itiseg.exe";
    //params = outdir + " " + outdir + " " + inputImageName + " 8 2 1 1 0 10";
    //ExecuteWait(segcmd, params, curdir);
    segcmd = FormMain->Dir_SegTools+"\\regionboundaries.exe";
    params = outdir + " " + outdir + " " + inputImageName;
    ExecuteWait(segcmd, params, curdir);

    if (FindFirst(outdir+"\\"+inputImageName+"_*.txt", faAnyFile, sr) == 0) {
      do {
        CreateImgRegionFromFile(outdir+"\\"+sr.Name);
      } while (FindNext(sr) == 0);
      FindClose(sr);
    }
    // end seg routine

    // redraw listbox
    if (ListBoxImgNodes->Count)
    	ListBoxImgNodes->Selected[ListBoxImgNodes->Count-1] = true;
    ListBoxImgNodesClick(Sender);
    ListBoxImgNodes->Refresh();

  } // mrOk
  FormM = NULL;
  delete FormM;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonSegClick(TObject *Sender)
{
	//TODO: create routine for segmentation
  AnsiString curdir = ExtractFilePath(Application->ExeName);
  AnsiString ppm, params, outdir;;
	AnsiString inputImageName, inputImageNameExt, segcmd;
  TSearchRec sr;

  //segoptions = "8 2 1 1 0 10";
  inputImageName = ExtractFileName(ImgFilename);
  inputImageNameExt = ExtractFileName(ImgFilename);
  if (!Sysutils::FileExists(inputImageName)) {
    MessageDlg("Image '"+inputImageName+"' not found.\nSegmentation cannot continue.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }
  inputImageName = ChangeFileExt(inputImageName, "");
  outdir = FormMain->Dir_StoredData+"\\"+inputImageName;
  Sysutils::ForceDirectories(outdir);
  outdir = ExtractShortPathName(outdir);
  ppm = ChangeFileExt(inputImageName, ".ppm");
  WritePPM(ImageAn->Bitmap, outdir+"\\"+ppm);
  //del %1\%2.seg
  DeleteFile(outdir+"\\"+inputImageName+".seg");
  //del %1\%2_*.txt
  if (FindFirst(outdir+"\\"+inputImageName+"_*.txt", faAnyFile, sr) == 0) {
    do {
      DeleteFile(outdir+"\\"+sr.Name);
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  //segcmd = FormMain->Dir_SegTools+"\\itiseg.exe";
  segcmd = FormMain->Dir_SegTools+"\\"+FormMain->SegExe;
  //params = outdir + " " + outdir + " " + inputImageName + " 8 2 1 1 0 10";
  params = FormMain->SegOptions;
  params = AnsiReplaceStr(params, "%f", inputImageName);
  params = AnsiReplaceStr(params, "%F", inputImageNameExt);
  params = AnsiReplaceStr(params, "%d", outdir);
  ExecuteWait(segcmd, params, curdir);
  //get polygons
  segcmd = FormMain->Dir_SegTools+"\\regionboundaries.exe";
  params = outdir + " " + outdir + " " + inputImageName;
  ExecuteWait(segcmd, params, curdir);

  if (FindFirst(outdir+"\\"+inputImageName+"_*.txt", faAnyFile, sr) == 0) {
    do {
      CreateImgRegionFromFile(outdir+"\\"+sr.Name);
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::StartEditRegion(int mode)
{
	if (draw_editing) {
  	//already editing;
    MessageDlg("Already in edit mode.\nRight click to finish.", mtWarning, TMsgDlgButtons() << mbOK, 0);
  	return;
  }
  // disable region boxes
  SetImgRegionsVis(false);
  SetImgNodesVisible(false);

  MessageDlg("Left Click on picture to add points.\nRight Click to finish and connect to first point.",
		mtInformation, TMsgDlgButtons() << mbOK, 0);

  draw_firsttime = true;
  // polygon = 1
  // freeform = 2
  draw_editing = mode;

  // prepare for new data
  edit_pList = new TList;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ExtractMpeg7(TObject *Sender)
{
	// extract mpeg7 descriptors
  AnsiString xmcmd, params, inputImageName, outfile;
  AnsiString outdirf, xmlout;
  bool it;

  TFormExtractMPEG7 *FormE;
  FormE = new TFormExtractMPEG7(Application->MainForm);
  if (FormE->ShowModal() == mrCancel) {
    delete FormE;
    return;
  }

  inputImageName = ExtractFileName(ImgFilename);
  inputImageName = ChangeFileExt(inputImageName, "");
  // storagePath + inputname_dir + inputnameFile
  outdirf = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+ExtractFileName(ImgFilename);
  Sysutils::ForceDirectories(FormMain->Dir_StoredData+"\\"+inputImageName);
  // copy original image to dir
  //FileCopy(ImgFilename, outdirf, true);
  //TODO: check, replace if exists
  CopyFileA(ImgFilename.c_str(), outdirf.c_str(), true);
  //check if image exists (seg)

  //imagename + "_a" ?
  //extract regions and run XMwin for each
//TODO: check
  // add <label> tag

  // write in images.lst
  outfile = FormMain->Dir_AceToolBox+"\\parfiles\\images.lst";
  FILE *out;
  if ((out = fopen(outfile.c_str(), "wt")) == NULL) {
    return;
  }
  fprintf(out, "%s\n", outdirf.c_str());
  fclose(out);

  //xmcmd = "aceExtract.exe";
  xmcmd = "XMWinExe.exe";
  //TODO: check if xmcmd exists

  it = FormE->CheckListBoxMPEG7->Checked[0];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"ColLayout.xml";
    params = "-pparfiles/ColLayout.par -a ColorLayoutServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[1];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"ColorStructure.xml";
    params = "-pparfiles/ColorStructure.par -a ColorStructureServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[2];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"ContourShape.xml";
    params = "-pparfiles/ContourShape.par -a ContourShapeServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[3];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"DominantColor.xml";
    params = "-pparfiles/DominantColor.par -a DominantColorServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[4];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"EdgeHistogram.xml";
    params = "-pparfiles/EdgeHistogram.par -a EdgeHistogramServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[5];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"HomogeneousTexture.xml";
    params = "-pparfiles/HomogeneousTexture.par -a HomogeneousTextureServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  // video only
  /*
  xmlout = Dir_StoredData+"\\"+inputImageName+"\\"+"MotionActivity.xml";
  params = "-pparfiles/MotionActivity.par -a MotionActivityServer -b"+xmlout;
  ExecuteWait(xmcmd, params, Dir_AceToolBox);

  xmlout = Dir_StoredData+"\\"+inputImageName+"\\"+"GoFGoPColor.xml";
  params = "-pparfiles/GoFGoPColor.par -a GoFGoPColorServer -b"+xmlout;
  ExecuteWait(xmcmd, params, Dir_AceToolBox);
  */
  it = FormE->CheckListBoxMPEG7->Checked[6];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"RegionShape.xml";
    params = "-pparfiles/RegionShape.par -a RegionShapeServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[7];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"ScalColor.xml";
    params = "-pparfiles/ScalColor.par -a ScalableColorServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  it = FormE->CheckListBoxMPEG7->Checked[8];
  if (it) {
    xmlout = FormMain->Dir_StoredData+"\\"+inputImageName+"\\"+"TextureBrowsing.xml";
    params = "-pparfiles/TextureBrowsing.par -a TextureBrowsingServer -b"+xmlout;
    ExecuteWait(xmcmd, params, FormMain->Dir_AceToolBox);
  }
  delete FormE;
}

//---------------------------------------------------------------------------

void __fastcall TFormImage::OpenImage(String FileName)
{
  try {
    ImageAn->Bitmap->LoadFromFile(FileName);
    ImgFilename = FileName;
    CopyToBack();
    ScrollBox->HorzScrollBar->Range = ImageAn->Bitmap->Width;
    ScrollBox->VertScrollBar->Range = ImageAn->Bitmap->Height;
    IAFilename->Text = FileName;
    FormLog->Log("Opened image file: "+FileName);
  }
  catch (...) {
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ShapeAround(TList *l, TShape *shape)
{
  int left, top, width, height;
  TPoint *p;

  if (l->Count) {
    p = (TPoint *) l->Items[0];
    left = p->x;
    top = p->y;
    width = left;
    height = top;
    for(int i=1; i < l->Count; i++) {
      p = (TPoint *) l->Items[i];
      if ( p->x < left ) left = p->x;
      if ( p->y < top ) top = p->y;
      if ( p->x > width ) width = p->x;
      if ( p->y > height ) height = p->y;
    }
    shape->Top = top;
    shape->Left = left;
    shape->Width = width-left+1;
    shape->Height = height-top+1;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::CleanupUI(void)
{
  SetImgNodesVisible(false);
  ImageAn->Bitmap->Clear();
  EditRImgName->Text = "";
  IATitle->Text = "";
  IADateTime->Date = Date();
  IADesc->Text="";
  IAAnnotator->Text="";
  IAFilename->Text="";
  IAAnnoFile->Text="";
  ListBoxImageDesc->Clear();
  TreeXMLImg->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonLoadImgAnnoClick(TObject *Sender)
{
  FormMain->ActionImportDescExecute(Sender);
}
//---------------------------------------------------------------------------

bool __fastcall TFormImage::OpenProjectFile(AnsiString Filename, bool xml, int ProjectType_minor)
{
  CleanupImgRegions();
  CleanupUI();
  FormImport->MLCI->Clear();

  if(!xml) {
    TRegionData *data, *data2;
    TIniFile *prjfile;
    prjfile = new TIniFile(Filename);
    TImgRegion *region;
  	//--- load image project
    IATitle->Text = prjfile->ReadString("Image", "Title", "");
    IADateTime->Date = prjfile->ReadDate("Image", "Date", Now());
    IADesc->Text = prjfile->ReadString("Image", "Description", "");
    IAAnnotator->Text = prjfile->ReadString("Image", "Annotator", "");
    IAFilename->Text = prjfile->ReadString("Image", "Filename", "");
    IAAnnoFile->Text = prjfile->ReadString("Image", "ImageDescFilename", "");

    try {
      ImgFilename = IAFilename->Text;
      if (!Sysutils::FileExists(ImgFilename)) {
        if (MessageDlg("Image file "+ImgFilename+" not found. Do you want to locate the image file manually ?",
  	      mtError, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes )
          if(OpenDialogImg->Execute())
            ImgFilename = OpenDialogImg->FileName;
      }
      if (Sysutils::FileExists(ImgFilename)) {
        ImageAn->Bitmap->LoadFromFile(ImgFilename);
        CopyToBack();
        FormLog->Log("Loaded image file: "+ImgFilename);
        ScrollBox->HorzScrollBar->Range = ImageAn->Bitmap->Width;
        ScrollBox->VertScrollBar->Range = ImageAn->Bitmap->Height;
      }
      else
        FormLog->Log("Error opening image file: "+ImgFilename);

      // load image annotation descriptors
      //TODO: change with new format (TAB delim)
/*      if( Sysutils::FileExists(IAAnnoFile->Text) )
        FormMain->XML2Tree(TreeXMLImg, FormMain->XMLDocument, IAAnnoFile->Text);
*/
      //load descriptors
      int c=0;
      AnsiString targdesc;
      c = prjfile->ReadInteger("Image", "ImageDescriptorsNumber", 0);
      for(int i=0; i < c ; i++) {
        targdesc = prjfile->ReadString("Image", "ImageDescriptor"+IntToStr(i), "");
        ListBoxImageDesc->Items->Add(targdesc);
      }
      if (ListBoxImageDesc->Count)
        ListBoxImageDesc->Selected[ListBoxImageDesc->Count-1] = true;
    }
    catch (Exception &exception) {
      MessageDlg("Error opening project file:\n"+Filename+
                +"\n\n(invalid file-section information)\n"+
                 "The file is either in unknown format or damaged",
                  mtError, TMsgDlgButtons() << mbOK, 0);
      }
    // --- load regions
    try {
      int c=0, d=0;
      AnsiString targdesc;
      c = prjfile->ReadInteger("Regions", "Count", 0);
      for(int i=0; i < c ; i++) {
        region = new TImgRegion;
        region->shape = new TShape(FormImage);
        region->shape->Parent = ImageAn;
        int shp = prjfile->ReadInteger("Region#"+IntToStr(i), "Shape", 0);
        switch (shp) {
          case 0:
            region->shape->Shape = stRectangle;
            region->rType = rRectangle;
          break;
          case 1:
            region->shape->Shape = stCircle;
            region->rType = rCircle;
          break;
          case 2:
            region->shape->Shape = stEllipse;
            region->rType = rEllipse;
          break;
          case 3:
    	      region->shape->Shape = stRectangle;
            region->rType = rPolygon;
          break;
          case 4:
            region->shape->Shape = stRectangle;
            region->rType = rFreeform;
          break;
          //Segmentation
          case 5:
            region->shape->Shape = stRectangle;
            region->rType = rSegmentation;
          break;
        }
        region->shape->Visible = false;
        region->shape->Brush->Style = bsClear;
        region->color = StringToColor(prjfile->ReadString("Region#"+IntToStr(i), "Color", ColorToString(clRed)));
        region->shape->Pen->Color = region->color;
        region->shape->Pen->Width = FormMain->PenWidth;
        region->shape->OnMouseDown = ShapeImgMouseDown;
        region->shape->OnMouseMove = ShapeImgMouseMove;
        region->shape->OnMouseUp = ShapeImgMouseUp;
        region->shape->Constraints->MaxHeight = MAX_REGION;
        region->shape->Constraints->MaxWidth = MAX_REGION;
        region->shape->Constraints->MinHeight = MIN_REGION;
        region->shape->Constraints->MinWidth = MIN_REGION;
        region->shape->Top = prjfile->ReadInteger("Region#"+IntToStr(i), "Top", DEF_Y);
        region->shape->Left = prjfile->ReadInteger("Region#"+IntToStr(i), "Left", DEF_X);
        region->shape->Width = prjfile->ReadInteger("Region#"+IntToStr(i), "Width", DEF_W);
        region->shape->Height = prjfile->ReadInteger("Region#"+IntToStr(i), "Height", DEF_H);
        region->shape->Visible = true;
        region->description = prjfile->ReadString("Region#"+IntToStr(i), "Description", "");
        region->ImgData = NULL;
        //load polygons data
        //TODO: FIX update display
        if (region->rType >= rPolygon) {
          int pc = prjfile->ReadInteger("Region#"+IntToStr(i), "PointsNumber", 0);
          if (pc) {
            //add point data
            TImgData *imgd = new TImgData;
            edit_pList = new TList;
            TPoint *p, *p1, *p2;

            for(int k=0; k < pc; k++) {
              p = new TPoint;
              p->x = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(k), "X", 0);
              p->y = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(k), "Y", 0);
              edit_pList->Add(p);
            }
            imgd->pointlist = edit_pList;
            region->ImgData =imgd;

            // copy all to bitmap
            TBitmap32 *b;
            b = new TBitmap32();
            b->Width = region->shape->Width;
            b->Height = region->shape->Height;
            b->DrawMode = dmTransparent;
            //draw regions on bitmap
            if (edit_pList->Count) {
              p = (TPoint *) edit_pList->Items[0];
              b->PenColor = Color32(region->color);//clBlack32;
              TPoint *points = new TPoint[edit_pList->Count];
              b->Canvas->Brush->Color = region->color;
              b->Canvas->Brush->Style = bsDiagCross;
              for (int p=0; p < edit_pList->Count; p++) {
                points[p] = *(TPoint *)edit_pList->Items[p];
                points[p].x = points[p].x - region->shape->Left;
                points[p].y = points[p].y - region->shape->Top;
              }
              b->Canvas->Polygon(points, edit_pList->Count-1);
              delete points;
            }
            imgd->bitmap = b;
            edit_pList = NULL;
            // end : add point data
          }
        }
        //region descriptors
        region->descriptors = new TStringList;
        d = prjfile->ReadInteger("Region#"+IntToStr(i), "RegionDescriptorsNumber", 0);
        for(int j=0; j < d ; j++) {
          targdesc = prjfile->ReadString("Region#"+IntToStr(i), "RegionDescriptor"+IntToStr(j), 0);
          region->descriptors->Add(targdesc);
        }
        imgregions->Add(region);
        RepaintImgRegionNodes(region);
        ListBoxImgNodes->Items->Add(region->description);
        //Needed else weird but with top/left region appears
        Application->ProcessMessages();
      } // for i - every region

      // update display
      if(ListBoxImgNodes->Count) {
        //draw last region
        ListBoxImgNodes->Selected[0] = true;
        //UpdateImgRegionProp((TImgRegion *) (imgregions->Items[0]));
        RepaintImgRegionNodes((TImgRegion *) (imgregions->Items[0]));
      }
    }
    catch (Exception &exception) {
      MessageDlg("Error opening project file:\n"+Filename+
                +"\n\n(invalid region section information)\n"+
                 "The file is either in unknown format or damaged\n",
                 mtError, TMsgDlgButtons() << mbOK, 0);
    }
  }
  else //XML project file
  {
    if (ProjectType_minor == 1)
      OpenProjectFileXML(Filename);
    else if (ProjectType_minor == 2)
      OpenProjectFileXML_Labelme(Filename);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TFormImage::OpenProjectFileXML(AnsiString Filename)
{
  _di_IXMLNode jNode;
  XMLProject->FileName = Filename;
  XMLProject->Active = true;

  if (XMLProject->ChildNodes->First() == NULL) {
    MessageDlg("XMLDocument: NULL value", mtError, TMsgDlgButtons() << mbOK, 0);
    return false;
  }
  jNode = XMLProject->DocumentElement->ChildNodes->First();

  while (jNode != NULL) {
    ProcessNode( jNode);
    jNode = jNode->NextSibling();
  }

  ImgFilename = IAFilename->Text;
  if (!Sysutils::FileExists(ImgFilename)) {
    if (MessageDlg("Image file "+ImgFilename+" not found. Do you want to locate the image file manually ?",
      mtError, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes )
      if(OpenDialogImg->Execute())
        ImgFilename = OpenDialogImg->FileName;
  }
  if (Sysutils::FileExists(ImgFilename)) {
    ImageAn->Bitmap->LoadFromFile(ImgFilename);
    CopyToBack();
    FormLog->Log("Loaded image file: "+ImgFilename);
    ScrollBox->HorzScrollBar->Range = ImageAn->Bitmap->Width;
    ScrollBox->VertScrollBar->Range = ImageAn->Bitmap->Height;
  }
  else
    FormLog->Log("Error opening image file: "+ImgFilename);

  XMLProject->Active = false;
  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ProcessNode(_di_IXMLNode Node)
{
  _di_IXMLNode cNode;
  if (Node == NULL)
    return;

  //cNode = Node->ChildNodes->First();
  if (Node->LocalName == WideString("image")) {
    cNode = Node->ChildNodes->First();
    while (cNode) {
      if (cNode->LocalName == WideString("title"))
        IATitle->Text = cNode->Text;
      else if (cNode->LocalName == WideString("date"))
        IADateTime->Date = Sysutils::StrToDateDef(cNode->Text, Now()); //TODO: check
      else if (cNode->LocalName == WideString("imageid"))
        IADesc->Text = cNode->Text;
      else if (cNode->LocalName == WideString("annotator"))
        IAAnnotator->Text = cNode->Text;
      else if (cNode->LocalName == WideString("imagefilename"))
        IAFilename->Text = cNode->Text;
      else if (cNode->LocalName == WideString("annotationfilename"))
        IAAnnoFile->Text = cNode->Text;
      else if (cNode->LocalName == WideString("imageannotation")) {
        _di_IXMLNode bNode;
        bNode = cNode->ChildNodes->First();
        while(bNode) {
          if( bNode->LocalName == WideString("term"))
            ListBoxImageDesc->Items->Add(bNode->Text);
          bNode = bNode->NextSibling();
        }
        if (ListBoxImageDesc->Count)
          ListBoxImageDesc->Selected[ListBoxImageDesc->Count-1] = true;
      }
      cNode = cNode->NextSibling();
    }
  }

  if (Node->LocalName == WideString("regions")) {
    cNode = Node->ChildNodes->First();
    while (cNode) {
      TImgRegion *region;
      if (cNode->LocalName == WideString("region"))
      {
        //create new region
        region = new TImgRegion;
        region->shape = new TShape(FormImage);
        region->shape->Parent = ImageAn;
        region->shape->Visible = false;
        region->shape->Brush->Style = bsClear;
        region->descriptors = new TStringList;

        _di_IXMLNode aNode;
        aNode = cNode->ChildNodes->First();
        while (aNode) {
          // get region data
          if (aNode->LocalName == WideString("y"))
            region->shape->Top = StrToInt(aNode->Text);
          else if (aNode->LocalName == WideString("x"))
            region->shape->Left = StrToInt(aNode->Text);
          else if (aNode->LocalName == WideString("width"))
            region->shape->Width = StrToInt(aNode->Text);
          else if (aNode->LocalName == WideString("height"))
            region->shape->Height = StrToInt(aNode->Text);
          else if (aNode->LocalName == WideString("color")) {
            region->color = StringToColor("0x"+aNode->Text);
            region->shape->Pen->Color = region->color;
          }
          else if (aNode->LocalName == WideString("regionid"))
            region->description = aNode->Text;
          else if (aNode->LocalName == WideString("regionannotation"))
          {
            _di_IXMLNode bNode;
            bNode = aNode->ChildNodes->First();
            while(bNode) {
              if( bNode->LocalName == WideString("term"))
                region->descriptors->Add(bNode->Text);
              bNode = bNode->NextSibling();
            }
          }
          else if (aNode->LocalName == WideString("shape"))
          {
            if (aNode->Text == WideString("rectangle")) {
                region->shape->Shape = stRectangle;
                region->rType = rRectangle;
            }
            else if (aNode->Text == WideString("circle")) {
                region->shape->Shape = stCircle;
                region->rType = rCircle;
            }
            else if (aNode->Text == WideString("ellipse")) {
                region->shape->Shape = stEllipse;
                region->rType = rEllipse;
            }
            else if (aNode->Text == WideString("polygon")) {
               region->shape->Shape = stRectangle;
                region->rType = rPolygon;
            }
            else if (aNode->Text == WideString("freeform")) {
                region->shape->Shape = stRectangle;
                region->rType = rFreeform;
            }
            else if (aNode->Text == WideString("segmentation")) {
                region->shape->Shape = stRectangle;
                region->rType = rSegmentation;
            }
          } // shape
          else if (aNode->LocalName == WideString("pointdata"))
          {
            //add point data
            TImgData *imgd = new TImgData;
            edit_pList = new TList;
            TPoint *p, *p1, *p2;

            _di_IXMLNode bNode;
            bNode = aNode->ChildNodes->First();
            while(bNode) {
              if( bNode->LocalName == WideString("pt"))
              {
                p = new TPoint;
              // get x,y values
                _di_IXMLNode p1Node, p2Node;
                p1Node = bNode->ChildNodes->First();
                if (p1Node->LocalName == WideString("x") )
                  p->x = StrToInt(p1Node->Text);
                else if (p1Node->LocalName == WideString("y") )
                  p->y = StrToInt(p1Node->Text);

                p2Node = p1Node->NextSibling();
                if (p2Node->LocalName == WideString("x") )
                  p->x = StrToInt(p2Node->Text);
                else if (p2Node->LocalName == WideString("y") )
                  p->y = StrToInt(p2Node->Text);
                // we got x,y add them
                edit_pList->Add(p);
              }
              bNode = bNode->NextSibling();
            }
            imgd->pointlist = edit_pList;
            region->ImgData =imgd;

            // copy all to bitmap
            TBitmap32 *b;
            b = new TBitmap32();
            b->Width = region->shape->Width;
            b->Height = region->shape->Height;
            b->DrawMode = dmTransparent;
            //draw regions on bitmap
            if (edit_pList->Count) {
              p = (TPoint *) edit_pList->Items[0];
              b->PenColor = Color32(region->color);//clBlack32;
              TPoint *points = new TPoint[edit_pList->Count];
              b->Canvas->Brush->Color = region->color;
              b->Canvas->Brush->Style = bsDiagCross;
              for (int p=0; p < edit_pList->Count; p++) {
                points[p] = *(TPoint *)edit_pList->Items[p];
                points[p].x = points[p].x - region->shape->Left;
                points[p].y = points[p].y - region->shape->Top;
              }
              b->Canvas->Polygon(points, edit_pList->Count-1);
              delete points;
            }
            imgd->bitmap = b;
            edit_pList = NULL;
            // end : add point data
          }
          aNode = aNode->NextSibling();
        }
        
        region->shape->Pen->Width = FormMain->PenWidth;
        region->shape->OnMouseDown = ShapeImgMouseDown;
        region->shape->OnMouseMove = ShapeImgMouseMove;
        region->shape->OnMouseUp = ShapeImgMouseUp;
        region->shape->Constraints->MaxHeight = MAX_REGION;
        region->shape->Constraints->MaxWidth = MAX_REGION;
        region->shape->Constraints->MinHeight = MIN_REGION;
        region->shape->Constraints->MinWidth = MIN_REGION;
        region->shape->Visible = true;
        region->ImgData = NULL;

        imgregions->Add(region);
        RepaintImgRegionNodes(region);
        ListBoxImgNodes->Items->Add(region->description);
        //Needed else weird but with top/left region appears
        Application->ProcessMessages();

      }
      //
      cNode = cNode->NextSibling();
    }
  }

  while (cNode) {
    ProcessNode(cNode);
    cNode = cNode->NextSibling();
  }
}
//---------------------------------------------------------------------------

bool __fastcall TFormImage::OpenProjectFileXML_Labelme(AnsiString Filename)
{
  _di_IXMLNode jNode;
  XMLProject->FileName = Filename;
  XMLProject->Active = true;

  if (XMLProject->ChildNodes->First() == NULL) {
    MessageDlg("XMLDocument: NULL value", mtError, TMsgDlgButtons() << mbOK, 0);
    return false;
  }
  jNode = XMLProject->DocumentElement->ChildNodes->First();

  while (jNode != NULL) {
    ProcessNodeLM( jNode);
    jNode = jNode->NextSibling();
  }

  ImgFilename = IAFilename->Text;
  if (!Sysutils::FileExists(ImgFilename)) {
    if (MessageDlg("Image file "+ImgFilename+" not found. Do you want to locate the image file manually ?",
      mtError, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes )
      if(OpenDialogImg->Execute())
        ImgFilename = OpenDialogImg->FileName;
  }
  if (Sysutils::FileExists(ImgFilename)) {
    ImageAn->Bitmap->LoadFromFile(ImgFilename);
    CopyToBack();
    FormLog->Log("Loaded image file: "+ImgFilename);
    ScrollBox->HorzScrollBar->Range = ImageAn->Bitmap->Width;
    ScrollBox->VertScrollBar->Range = ImageAn->Bitmap->Height;
  }
  else
    FormLog->Log("Error opening image file: "+ImgFilename);

  XMLProject->Active = false;
  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ProcessNodeLM(_di_IXMLNode Node)
{
  _di_IXMLNode cNode;
  if (Node == NULL)
    return;

  //cNode = Node->ChildNodes->First();
  if (Node->LocalName == WideString("source")) {
    cNode = Node->ChildNodes->First();
    while (cNode) {
      if (cNode->LocalName == WideString("sourceImage"))
        IATitle->Text = cNode->Text;
      else if (cNode->LocalName == WideString("sourceAnnotation"))
        IADesc->Text = cNode->Text;
      cNode = cNode->NextSibling();
    }
  }

  if (Node->LocalName == WideString("object"))
  {
    TImgRegion *region;
    //create new region
    region = new TImgRegion;
    region->shape = new TShape(FormImage);
    region->shape->Parent = ImageAn;
    region->shape->Visible = false;
    region->shape->Brush->Style = bsClear;
    region->descriptors = new TStringList;
    region->shape->Shape = stRectangle;
    region->rType = rPolygon;
    /*
    region->shape->Top = StrToInt(aNode->Text);
    region->shape->Left = StrToInt(aNode->Text);
    region->shape->Width = StrToInt(aNode->Text);
    region->shape->Height = StrToInt(aNode->Text);
    region->color = StringToColor("0x"+aNode->Text);
    region->shape->Pen->Color = region->color;
    */
    region->ImgData = NULL;
    region->shape->Pen->Width = FormMain->PenWidth;
    region->shape->OnMouseDown = ShapeImgMouseDown;
    region->shape->OnMouseMove = ShapeImgMouseMove;
    region->shape->OnMouseUp = ShapeImgMouseUp;
    region->shape->Constraints->MaxHeight = MAX_REGION;
    region->shape->Constraints->MaxWidth = MAX_REGION;
    region->shape->Constraints->MinHeight = MIN_REGION;
    region->shape->Constraints->MinWidth = MIN_REGION;
    region->shape->Visible = true;

    cNode = Node->ChildNodes->First();
    while (cNode) {
      if (cNode->LocalName == WideString("name"))
        region->description = cNode->Text;
      else if (cNode->LocalName == WideString("polygon")) {

        //add point data
        TImgData *imgd = new TImgData;
        edit_pList = new TList;
        TPoint *p, *p1, *p2;
        p = new TPoint;

        _di_IXMLNode bNode;
        bNode = cNode->ChildNodes->First();
        while(bNode) {
          if( bNode->LocalName == WideString("pt"))
          {
            // get x,y values
            p = new TPoint;
            _di_IXMLNode p1Node, p2Node;
            p1Node = bNode->ChildNodes->First();
            if (p1Node->LocalName == WideString("x") )
              p->x = StrToInt(p1Node->Text);
            else if (p1Node->LocalName == WideString("y") )
              p->y = StrToInt(p1Node->Text);

            p2Node = p1Node->NextSibling();
            if (p2Node->LocalName == WideString("x") )
              p->x = StrToInt(p2Node->Text);
            else if (p2Node->LocalName == WideString("y") )
              p->y = StrToInt(p2Node->Text);
            // we got x,y add them
            edit_pList->Add(p);
          }
          bNode = bNode->NextSibling();
        }
        imgd->pointlist = edit_pList;
        region->ImgData = imgd;
        // get surrounding attributes
        ShapeAround(imgd->pointlist, region->shape);

        // copy all to bitmap
        TBitmap32 *b;
        b = new TBitmap32();
        b->Width = region->shape->Width;
        b->Height = region->shape->Height;
        b->DrawMode = dmTransparent;
        //draw regions on bitmap
        if (edit_pList->Count) {
          p = (TPoint *) edit_pList->Items[0];
          b->PenColor = Color32(region->color);//clBlack32;
          TPoint *points = new TPoint[edit_pList->Count];
          b->Canvas->Brush->Color = region->color;
          b->Canvas->Brush->Style = bsDiagCross;
          for (int p=0; p < edit_pList->Count; p++) {
            points[p] = *(TPoint *)edit_pList->Items[p];
            points[p].x = points[p].x - region->shape->Left;
            points[p].y = points[p].y - region->shape->Top;
          }
          b->Canvas->Polygon(points, edit_pList->Count-1);
          delete points;
        }
        imgd->bitmap = b;
        edit_pList = NULL;

        // end : add point data
      }
      cNode = cNode->NextSibling();
    }
    imgregions->Add(region);
    RepaintImgRegionNodes(region);
    ListBoxImgNodes->Items->Add(region->description);
    //Needed else weird but with top/left region appears
    Application->ProcessMessages();
  }
  //
  while (cNode) {
    ProcessNodeLM(cNode);
    cNode = cNode->NextSibling();
  }
}
//---------------------------------------------------------------------------


bool __fastcall TFormImage::SaveProjectFile(AnsiString Filename, bool xml)
{
  if (xml)
  {
    // .XML project file
    return SaveProjectFileXML(Filename);
  }
  else
  {
    TIniFile *prjfile;
    // .ANP project file (ini based)
    prjfile = new TIniFile(Filename);
    prjfile->WriteString( "Project", "Name", FormMain->ProjectName);
    prjfile->WriteInteger("Project", "Type", FormMain->ProjectType);
    prjfile->ReadString ( "Project", "Directory", FormMain->CurrentDir);

    TImgRegion *region;
    prjfile->WriteString("Image", "Title", IATitle->Text);
    prjfile->WriteDate(  "Image", "Date", IADateTime->Date);
    prjfile->WriteString("Image", "Description", IADesc->Text);
    prjfile->WriteString("Image", "Annotator", IAAnnotator->Text);
    prjfile->WriteString("Image", "Filename", IAFilename->Text);
    prjfile->WriteString("Image", "ImageDescFilename", IAAnnoFile->Text);
    prjfile->WriteInteger("Image", "ImageDescriptorsNumber", ImageDescriptors->Count);

    if (ImageDescriptors->Count) {
      for(int i=0; i< ImageDescriptors->Count ; i++) {
        prjfile->WriteString("Image", "ImageDescriptor"+IntToStr(i), ImageDescriptors->Strings[i]);
      }
    }

    //export image regions
    prjfile->WriteInteger("Regions", "Count", ListBoxImgNodes->Count);
    if (ListBoxImgNodes->Count) {
      for (int i=0; i < ListBoxImgNodes->Count ; i++) {
        region = (TImgRegion *) (imgregions->Items[i]);
        prjfile->WriteString("Region#"+IntToStr(i), "Description", region->description);
        prjfile->WriteString("Region#"+IntToStr(i), "Color", ColorToString(region->color));
        prjfile->WriteInteger("Region#"+IntToStr(i), "RegionDescriptorsNumber", region->descriptors->Count);
        prjfile->WriteInteger("Region#"+IntToStr(i), "Top", region->shape->Top);
        prjfile->WriteInteger("Region#"+IntToStr(i), "Left", region->shape->Left );
        prjfile->WriteInteger("Region#"+IntToStr(i), "Width", region->shape->Width);
        prjfile->WriteInteger("Region#"+IntToStr(i), "Height", region->shape->Height);
        prjfile->WriteInteger("Region#"+IntToStr(i), "Shape", region->rType);
        if (region->rType >= rPolygon) {
          //save points data
          if (region->ImgData) {
            TPoint *p;
            prjfile->WriteInteger("Region#"+IntToStr(i), "PointsNumber", region->ImgData->pointlist->Count);
            for(int k=0; k < region->ImgData->pointlist->Count; k++) {
              p = (TPoint *) (region->ImgData->pointlist->Items[k]);
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(k), "X", p->x);
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(k), "Y", p->y);
            }
          }
        }
        for (int m=0; m < region->descriptors->Count; m++) {
          prjfile->WriteString("Region#"+IntToStr(i), "RegionDescriptor"+IntToStr(m), region->descriptors->Strings[m]);
        }
      } // for i
    }
    FormLog->Log("Image annotation project saved to ANP file :"+Filename);
    delete prjfile;
  }
  return true;
}
//---------------------------------------------------------------------------

bool __fastcall TFormImage::SaveProjectFileXML(AnsiString Filename)
{
  TStringList *exp;
  TImgRegion  *region;

  exp = new TStringList;
  exp->Add("<?xml version=\"1.0\" ?>");
  exp->Add("<project>");
  exp->Add( "<name>"+ FormMain->ProjectName + "</name>");
  exp->Add( "<type>"+ IntToStr(FormMain->ProjectType) + "</type>");
  exp->Add( "<directory>"+ FormMain->CurrentDir + "</directory>");

  exp->Add("<image>");   // global metadata
  exp->Add("<title>"+ IATitle->Text +"</title>");
  exp->Add("<date>"+ DateTimeToStr(IADateTime->Date) +"</date>" );
  exp->Add("<imageid>"+ IADesc->Text+ "</imageid>");
  exp->Add("<annotator>"+ IAAnnotator->Text+ "</annotator>");
  exp->Add("<imagefilename>"+ IAFilename->Text + "</imagefilename>");
  exp->Add("<annotationfilename>"+ IAAnnoFile->Text+ "</annotationfilename>");

  if (ImageDescriptors->Count) {
    exp->Add("<imageannotation>");
    for(int i=0; i< ImageDescriptors->Count ; i++) {
      exp->Add("<term>"+ImageDescriptors->Strings[i]+"</term>");
    }
    exp->Add("</imageannotation>");
  }
  exp->Add("</image>");

  //export image regions
  exp->Add("<regions>");
  exp->Add("<count>"+ IntToStr(ListBoxImgNodes->Count) + "</count>");
  if (ListBoxImgNodes->Count) {

    for (int i=0; i < ListBoxImgNodes->Count ; i++) {
      exp->Add("<region>");
      region = (TImgRegion *) (imgregions->Items[i]);

      exp->Add("<regionid>"+ region->description + "</regionid>");
      long L=ColorToRGB(region->color);
      AnsiString mc;
      mc.sprintf("%x",L);
      exp->Add("<color>"+mc+"</color>" );

      exp->Add("<regionannotation>");
      for (int m=0; m < region->descriptors->Count; m++) {
        exp->Add("<term>" + region->descriptors->Strings[m] + "</term>" );
      }
      exp->Add("</regionannotation>");

      AnsiString shp;
      if (region->rType == rRectangle)
        shp = "rectangle";
      else if (region->rType == rCircle)
        shp = "circle";
      else if (region->rType == rEllipse)
        shp = "ellipse";
      else if (region->rType == rPolygon)
        shp = "polygon";
      else if (region->rType == rFreeform)
        shp = "freeform";
      else if (region->rType == rSegmentation)
        shp = "segmentation";
      exp->Add("<shape>"+shp+"</shape>");

      if (region->rType >= rPolygon) {
        if (region->ImgData) {
          TPoint *p;
          exp->Add("<pointdata>");
          for(int k=0; k < region->ImgData->pointlist->Count; k++) {
            p = (TPoint *) (region->ImgData->pointlist->Items[k]);
            exp->Add("<pt>");
            exp->Add("<x>"+IntToStr(p->x)+"</x>");
            exp->Add("<y>"+IntToStr(p->y)+"</y>");
            exp->Add("</pt>");
          }
          exp->Add("</pointdata>");
        }
      }

      exp->Add("<x>" + IntToStr(region->shape->Left) + "</x>" );
      exp->Add("<y>" + IntToStr(region->shape->Top) + "</y>" );
      exp->Add("<width>" + IntToStr(region->shape->Width) + "</width>" );
      exp->Add("<height>" + IntToStr(region->shape->Height) + "</height>" );

      exp->Add("</region>");
    } // for i
  }
  exp->Add("</regions>");

  exp->Add("</project>");
  exp->SaveToFile(Filename);
  FormLog->Log("Image annotation project saved to XML file :"+Filename);
  exp->Clear();
  delete exp;

  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ButtonPointsClick(TObject *Sender)
{
  TImgRegion *selregion;
  int i = ListBoxImgNodes->ItemIndex;
  TPoint *p;
  if (i >= 0)
    selregion = (TImgRegion *) imgregions->Items[i];
  else return;

  if (selregion) {
    if (selregion->ImgData) {
      if (selregion->ImgData->pointlist->Count) {
        //TODO: clear or make form now

        FormPoints->StringGrid->RowCount = selregion->ImgData->pointlist->Count + 1;
        FormPoints->StringGrid->Cells[0][0] = "";
        FormPoints->StringGrid->Cells[1][0] = "x";
        FormPoints->StringGrid->Cells[2][0] = "y";

        for (int j = 0; j < selregion->ImgData->pointlist->Count; j++) {
          p = (TPoint *) selregion->ImgData->pointlist->Items[j];
          FormPoints->StringGrid->Cells[0][j+1] = j;
          FormPoints->StringGrid->Cells[1][j+1] = p->x;
          FormPoints->StringGrid->Cells[2][j+1] = p->y;
        }
        FormPoints->Show();
      }
    }
  }
}
//---------------------------------------------------------------------------

