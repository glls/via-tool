//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormVideo.h"
#include "UnitMain.h"
#include "UnitOptions.h"
#include "UnitLog.h"

#include <limits.h>
#include "UnitImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormVideo *FormVideo;
//---------------------------------------------------------------------------
__fastcall TFormVideo::TFormVideo(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::FormCreate(TObject *Sender)
{
  FNodes = new TObjectList(false);
  regions = new TList;
  shots = new TList;
  VideoDescriptors = new TStringList;

  Top = 0;
  Left = 0;
  currentFrame = 0;
  VidFilename = "";

  //VFAPI
  memset(&mme_app, 0, sizeof(MME_APP));
  mme_app.lang = MME_LANG_EN;
  if(!open_m2v_vfapi(&(mme_app.vfapi))) {
		Application->MessageBox( "Failed to load \"m2v.vfp\" VFAPI Plugin", "ERROR", MB_OK|MB_ICONERROR);
    Application->Terminate();
	}
  mme_app.instance = HInstance;
  mme_app.main_hwnd = FormMain->Handle;

  CreateNodes();
  CleanupUI();

  //TrackBarVideo->Frequency = TrackBarVideo->Max / 10;
  //TrackBarVideo->Properties->Frequency = TrackBarVideo->Properties->Max / 10;
  //TrackBarVideo->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::FormDestroy(TObject *Sender)
{
  TRegionData *data;
  TRegion *region;
  TShot *shot;

  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

	//delete regions
  if (ListBoxNodes->Count) {
    for (int i=0; i < ListBoxNodes->Count; i++) {
      region = (TRegion *) (regions->Items[i]);

      for (int k = 0; k < region->region_data->Count; k++) {
        data = (TRegionData *) (region->region_data->Items[k]);
        delete data;
      }
      delete region->region_data;
      delete region->box;
      delete region->descriptors;
      delete region;
    }
  }
	delete regions;

  //delete shots;
  if (ListBoxNodes->Count) {
    for (int i=0; i < ListBoxShots->Count; i++) {
      shot = (TShot *) (shots->Items[i]);
      delete shot->descriptors;
      delete shot;
    }
    delete shots;
  }

  delete VideoDescriptors;
 	delete FNodes;

  if(is_open_mme(&(mme_app.project)))
    close_mme(&(mme_app.project));

	close_m2v_vfapi(&(mme_app.vfapi));
	GlobalFree(mme_app.clipboard);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::FormKeyPress(TObject *Sender, char &Key)
{
	if (inReposition)
  	Key = '\0';
}

//---------------------------------------------------------------------------
TRegion * __fastcall TFormVideo::GetSelectedRegion(TObject *Sender)
{
  TRegion *p,*sel = NULL;

  for (int i=0; i < regions->Count; i++) {
    p = (TRegion *) (regions->Items[i]);
    if (p->box == (TShape *)(Sender) )
      sel = p;
  }
  return sel;
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::ShapeAMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TRegion *a_region;
  // only move if in record mode
  if (FormMain->ActionRecord->Checked)
    inReposition = true;

  GetCursorPos(&oldPos);
  SetNodesVisible(false);
  PositionNodes( (TWinControl *)(Sender) );
  SetNodesVisible(true);

  // find selected region in listbox
  for (int i=0; i < regions->Count; i++) {
    a_region = (TRegion *) (regions->Items[i]);
    if (a_region->box == (TShape *)(Sender) )
    {
      ListBoxNodes->Selected[i] = true;
      UpdateRegionProp(a_region, true);
      return;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ShapeAMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	TObject *t;
  Types::TPoint newPos;
  TRegion *a_region;
  TRegionData *data;

  if (inReposition)
  {
		if (Shift.Contains(ssLeft))
	  {
      SetNodesVisible(false);
      GetCursorPos(&newPos);
    	Screen->Cursor = crSize;
      //((TShape *)(Sender))->Pen->Mode = pmXor;
      //((TShape *)(Sender))->Pen->Style = psDot;
      ((TWinControl *)(Sender))->Left = ((TWinControl *)(Sender))->Left - oldPos.x + newPos.x;
      ((TWinControl *)(Sender))->Top = ((TWinControl *)(Sender))->Top - oldPos.y + newPos.y;
      oldPos = newPos;
      //PositionNodes( (TWinControl *)(Sender) );

      a_region = GetSelectedRegion(Sender);
      if (a_region) {
      	int x, y, w, h;
        if (FormMain->ActionRecord->Checked) {
        	// if recording set region data
          if ( (currentFrame >= 0) && (currentFrame < a_region->region_data->Count) ) {
            data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
            data->x = ((TWinControl *)(Sender))->Left;
            data->y = ((TWinControl *)(Sender))->Top;
            data->w = ((TWinControl *)(Sender))->Width;
            data->h = ((TWinControl *)(Sender))->Height;
            x = data->x;
            y = data->y;
            w = data->w;
            h = data->h;
            // copy data to all the following frames from current to the end
            // TODO: check & optimize
            // DO THIS only if in Play mode OR NOT ???
            if ( (currentFrame < maxFrame) /*&& (ActionPlay->Checked)*/ ) {
            	for (int k = currentFrame+1; k < a_region->region_data->Count; k++) {
	              data = (TRegionData *) (a_region->region_data->Items[k]);
  	            data->x = x;
    	          data->y = y;
      	        data->w = w;
        	      data->h = h;
              }
            }
          }
        } // record
        UpdateRegionProp(a_region);
      } // region
    } // left mb
  } // inReposition
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ShapeAMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TRegion *a_region;
  TRegionData *data;

	if (inReposition) {
  	Screen->Cursor = crDefault;
    //((TShape *)(Sender))->Pen->Mode = pmCopy;
    PositionNodes( (TWinControl *)(Sender) );
    SetNodesVisible(true);
    inReposition = false;

    //update region data
    a_region = GetSelectedRegion(Sender);
    if (a_region) {
      if (FormMain->ActionRecord->Checked) {
      	// if recording set region data
        if ( (currentFrame >= 0) && (currentFrame < a_region->region_data->Count) ) {
          data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
          data->x = ((TWinControl *)(Sender))->Left;
          data->y = ((TWinControl *)(Sender))->Top;
          data->w = ((TWinControl *)(Sender))->Width;
          data->h = ((TWinControl *)(Sender))->Height;
        }
      }
      UpdateRegionProp(a_region);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ImageVClick(TObject *Sender)
{
	// click on image
  SetNodesVisible(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::TrackBarVideoPropertiesChange(TObject *Sender)
{
  if (
  //(ActiveControl == TrackBarVideo) &&
  (Sender == TrackBarVideo)) {
  	__int64 index = get_frame_index_mme(&(mme_app.project));

  	if (index == set_frame_index_mme(&(mme_app.project), TrackBarVideo->Position)) {
      // not changed
    }
    RepaintVideo();
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::RepaintVideo(void)
{
	AnsiString s;
  TRegion *region;

  if( is_open_mme(&(mme_app.project)) ) {

    ShowDIB( ImageV->Canvas->Handle, get_dib_header_mme(&(mme_app.project)),
      get_frame_mme(&(mme_app.project)) );
    ImageV->Refresh();

    // update status text
    LabelStatus->Text = get_status_str_mme(&(mme_app.project));
		// TIMECODE
		TIMECODE tc;
    int fps,drop;

		fps = (mme_app.project.video_info.dwRate + mme_app.project.video_info.dwScale-1) / mme_app.project.video_info.dwScale;
    drop = mme_app.project.video_info.dwRate % mme_app.project.video_info.dwScale;
    frame2timecode(&(mme_app.project.frame_index), &tc, fps, drop);
    s.printf("%02d:%02d:%02d:%02d", tc.hh, tc.mm, tc.ss, tc.ff);
    EditTimeCode->Text = s;
    // TIMECODE end

    // update slider
    UpdateSlider();
    SetRegionsVis();

    // repaint regions
    if (regions->Count)
    {
	    for (int r=0; r <  regions->Count; r++ )
      {
  	  	region = (TRegion *) (regions->Items[r]);

        //selected one
        if ( r == ListBoxNodes->ItemIndex ) {
          UpdateRegionProp(region, true);
          RepaintRegion(region);			// show nodes
        }

        if (! inReposition )
	        RepaintRegion(region, false); // dont show nodes
      }
    }
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormVideo::CheckVideoLoaded(void)
{
	if(is_open_mme(&(mme_app.project)))
  	return true;

  return false;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::NodeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (FormMain->ActionRecord->Checked) {
    NodePositioning = true;
    GetCursorPos(&oldPos);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::NodeMouseMove(TObject *Sender, TShiftState Shift, int X,int Y)
{
	Types::TPoint newPos, frmPoint;
  Types::TRect OldRect;
  bool AdjL,AdjR,AdjT,AdjB;

  if (NodePositioning)
  {
      SetNodesVisible(false);
      GetCursorPos(&newPos);
      frmPoint = FCurrentNodeControl->Parent->ScreenToClient(Mouse->CursorPos);
      OldRect = FCurrentNodeControl->BoundsRect;
      AdjL = false; AdjR = false;
      AdjT = false; AdjB = false;
      //switch (FNodes->IndexOf( dynamic_cast<TWinControl *>(Sender))) {
      switch (FNodes->IndexOf( (TWinControl *)(Sender))) {
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
	    PositionNodes(FCurrentNodeControl);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::NodeMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (NodePositioning)
	{
    Screen->Cursor = crDefault;
    NodePositioning = false;
    SetNodesVisible(true);
    //update region data
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonAddShotClick(TObject *Sender)
{
  TShot *shot;
  TShot *a_shot;
  __int64 prev_startframe = currentFrame;

  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) (shots->Items[ListBoxShots->Count-1]);
    prev_startframe = a_shot->endFrame + 1;
  }

  shot = new TShot;
  shot->description.printf("Shot %02d", ListBoxShots->Count+1);
  shot->startFrame = prev_startframe;
  shot->endFrame = prev_startframe+1;
  //check
  if (shot->startFrame > maxFrame)
    shot->startFrame = maxFrame;
  if (shot->endFrame > maxFrame)
    shot->endFrame = maxFrame;

  shot->descriptors = new TStringList;
  shots->Add(shot);

  UpdateShotProp(shot);
  ListBoxShots->Items->Add(shot->description);
  ListBoxShots->Selected[ListBoxShots->Count-1] = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxShotDescDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = Source->ClassNameIs("TcxDragControlObject") ;
    //TODO: check
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxShotDescDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  TShot *a_shot;
  
  if (ListBoxShots->ItemIndex < 0) {
    MessageDlg("No shot selected.\nYou must select a shot to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  if (Sender->ClassNameIs("TListBox") && Source->ClassNameIs("TcxDragControlObject"))
  {
    TListBox *DestList = (TListBox *)Sender;
    //String targdesc = ((TcxTreeView *)Source)->Selected->Text;
    AnsiString targdesc = TreeXML->Selected->Text;
    if ( DestList->Items->IndexOf(targdesc) == -1 )
    {
      DestList->Items->Add(targdesc);
      DestList->Selected[DestList->Count-1] = true;
      a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
      a_shot->descriptors->Add(targdesc);
    }
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxShotsClick(TObject *Sender)
{
  TShot *a_shot;

  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
    UpdateShotProp(a_shot);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::UpdateShotProp(TShot *shot)
{
  EditShotName->Text = shot->description;
  EditShotSF->Text = IntToStr(shot->startFrame);
  EditShotEF->Text = IntToStr(shot->endFrame);
  ListBoxShotDesc->Items->Assign(shot->descriptors);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonDelShotClick(TObject *Sender)
{
  TShot *a_shot;
  //del shot
  int i = ListBoxShots->ItemIndex;
  if ( (i >= 0) && ( MessageDlg("Are you sure you want to delete the selected shot and its descriptors?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    a_shot = (TShot *) shots->Items[i];
    a_shot->descriptors->Clear();
    delete a_shot->descriptors;
    ListBoxShots->Items->Delete(i); //delete selected
    delete a_shot;
    shots->Delete(i);
    if (i < ListBoxShots->Count-1 )
      ListBoxShots->Selected[i] = true;
    else
      if (ListBoxShots->Count)
        ListBoxShots->Selected[ListBoxShots->Count-1] = true;
    ListBoxShotsClick(Sender);
    ListBoxShots->Refresh();
  }
}
//---------------------------------------------------------------------------
int __fastcall CompareShots(void *Item1, void *Item2)
{
  TShot *shot1, *shot2;
  shot1 = (TShot *) Item1;
  shot2 = (TShot *) Item2;
  if (shot1->startFrame < shot2->startFrame)
    return -1;
  else if (shot1->startFrame > shot2->startFrame)
    return 1;
  else
    return 0;
}

void __fastcall TFormVideo::ButtonSortSClick(TObject *Sender)
{
  // Sort shots by frame start
  if (ListBoxShots->Count < 1) return;

  TShot *ashot;
  //quicksort
  shots->Sort(CompareShots);

  //rewrite ListBoxNodes
  for (int k=0; k<shots->Count; k++) {
    ashot = (TShot *) shots->Items[k];
    if (FormMain->RenumberSort)
      ashot->description.printf("Shot %02d", k+1);
    ListBoxShots->Items->Strings[k] = ashot->description;
  }

  // finished select last and redraw
  ListBoxShots->Selected[ListBoxShots->Count-1] = true;
  ListBoxShotsClick(Sender);
  ListBoxShots->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonDelShotDescClick(TObject *Sender)
{
  //del shot desc
  int i = ListBoxShots->ItemIndex;
  int d = ListBoxShotDesc->ItemIndex;
  TShot *a_shot;

  if ( (i >= 0) && (d >= 0) && ( MessageDlg("Are you sure you want to delete the selected descriptor?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    // delete descriptor
    a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
    a_shot->descriptors->Delete(d);
    ListBoxShotDesc->Items->Delete(d);

    UpdateShotProp(a_shot);

    if (d < ListBoxShotDesc->Count-1 )
      ListBoxShotDesc->Selected[d] = true;
    else
      if (ListBoxShotDesc->Count)
        ListBoxShotDesc->Selected[ListBoxShotDesc->Count-1] = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxShotsKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelShotClick(Sender);
  }
  else if (Key == VK_INSERT) {
    ButtonAddShotClick(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormVideo::UpdateRegionProp(TRegion *a_region, bool all)
{
  TRegionData *a_data;

  if (a_region) {
	  // TODO: decide when to update, optimize, ALWAYS true?
    if ( (currentFrame >= 0) && (currentFrame < a_region->region_data->Count) ) {
      a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
      EditRX->Text = a_data->x;
      EditRY->Text = a_data->y;
      EditRW->Text = a_data->w;
      EditRH->Text = a_data->h;
    }
    /*
    else { // region not in selected frame
      EditRX->Text = "no data";
      EditRY->Text = "no data";
      EditRW->Text = "no data";
      EditRH->Text = "no data";
    }
    */
    if (all) {
	    EditRegionSF->Text = a_region->startFrame;
  	  EditRegionEF->Text = a_region->endFrame;
   		EditRName->Text = a_region->description;
	    ColorBoxR->Selected = a_region->color;
      ListBoxRegionDesc->Items->Assign(a_region->descriptors);
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormVideo::RepaintRegion(TRegion *a_region, bool show_nodes)
{
	TRegionData *a_data;
  // frame data available?
  if ( (currentFrame >= 0) && (currentFrame < a_region->region_data->Count) ) {
	  a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
	  a_region->box->Left = a_data->x;
	  a_region->box->Top = a_data->y;
	  a_region->box->Width = a_data->w;
	  a_region->box->Height = a_data->h;

		if (show_nodes) {
	    // repaint nodes
  	  SetNodesVisible(false);
    	PositionNodes( (TWinControl *)(a_region->box) );
      if ( (currentFrame >= a_region->startFrame) && (currentFrame <= a_region->endFrame))
		    SetNodesVisible(true);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ShowDIB(HDC hdc, const BITMAPINFOHEADER *header, const VOID *data)
{
	StretchDIBits(hdc, 0, 0,
  	header->biWidth,
    header->biHeight, 0, 0,
    header->biWidth,
    header->biHeight,
    data, (BITMAPINFO *)(header),
    DIB_RGB_COLORS,
    SRCCOPY);
}
//---------------------------------------------------------------------------

bool __fastcall TFormVideo::OpenVideoFile(AnsiString filename)
{
  bool ok = true;
  char path[MAX_PATH];
  int w, h;

  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

  if (!Sysutils::FileExists(filename))
    return false;

  //clean up Regions, TRegionData etc.
	CleanupRegions();
  SetNodesVisible(false);
  ImageV->Canvas->Brush->Color = clGreen;
  ImageV->Canvas->FillRect(Types::TRect(0,0,ImageV->Width,ImageV->Height));

  if(is_open_mme(&(mme_app.project))) {
		close_mme(&(mme_app.project));
    LabelStatus->Text = "Status Message";
		TrackBarVideo->Enabled = false;
    maxFrame = 0;
    currentFrame = 0;
    ImageV->Canvas->Brush->Color = clGreen;
    ImageV->Canvas->FillRect(Types::TRect(0,0,ImageV->Width,ImageV->Height));
  }

  memcpy(path, filename.c_str(), strlen(filename.c_str())+1);
  VAVideoFilename->Text = filename;

	if (!open_mme(path, &(mme_app.project), &(mme_app.vfapi.func), &(mme_app.vfapi.func_edit_ext), mme_app.lang))
  {
    LabelStatus->Text = "Status Message";
    TrackBarVideo->Enabled = false;
   	MessageDlg(get_error_msg_mme(&(mme_app.project)), mtError, TMsgDlgButtons() << mbOK, 0);
    ok = false;
	}
  else {
		//resize(get_frame_width_mme(&(mme_app.project)), get_frame_height_mme(&(mme_app.project)));

    FormLog->Log("Opened video file: "+filename);
    w = get_frame_width_mme(&(mme_app.project));
    h = get_frame_height_mme(&(mme_app.project));
    maxFrame = get_frame_count_mme(&(mme_app.project));
    maxFrame--;

    int fps = (mme_app.project.video_info.dwRate + mme_app.project.video_info.dwScale-1) / mme_app.project.video_info.dwScale;

    FormLog->Log("Width:"+IntToStr(w)+" Height:"+IntToStr(h)+"  total frames: "+
      IntToStr(maxFrame + 1)+" ("+IntToStr(fps)+"fps)");

		if (maxFrame > INT_MAX)
      TrackBarVideo->Position = INT_MAX;
		else
	    TrackBarVideo->Max = maxFrame;

		TrackBarVideo->Position = 0;
    TrackBarVideo->Frequency = TrackBarVideo->Max / 10;
    TrackBarVideo->Enabled = true;
    RepaintVideo();
	}
  return ok;
}

//---------------------------------------------------------------------------
//	Video annotation
//---------------------------------------------------------------------------
// updates slider and currentframe variable
void __fastcall TFormVideo::UpdateSlider(void)
{
	__int64 index;

	index = get_frame_index_mme(&(mme_app.project));
  // update current frame number
  currentFrame = index;
  // update on screen counter
  EditFrame->Text = IntToStr(index);

	if(index > INT_MAX) {
    TrackBarVideo->Position = INT_MAX;
	}
  else {
    TrackBarVideo->Position = index;
	}
}
//---------------------------------------------------------------------------

// set all region boxes to visible depending on current frame
void __fastcall TFormVideo::SetRegionsVis(void)
{
	TRegion * region;
  for (int i=0; i < regions->Count; i++) {
    region = (TRegion *) (regions->Items[i]);
    if ( (currentFrame >= region->startFrame) && (currentFrame <= region->endFrame ) ) {
      region->box->Visible = true;
    }
    else {
      region->box->Visible = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::CreateNodes(void)
{
	int node;
  TPanel *panel;

  for (node=0; node <=7; node ++)
  {
  	panel = new TPanel(FormMain);
    FNodes->Add(panel);
    panel->BevelOuter = bvNone;
    panel->Color = clBlack;
    panel->Name = "Node" + IntToStr(node);
    panel->Width = 5;
    panel->Height = 5;
    panel->FullRepaint = false;

    // prevent drawing on main form
    panel->Parent = PanelImg; //this
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
    panel->OnMouseDown = NodeMouseDown;
    panel->OnMouseMove = NodeMouseMove;
    panel->OnMouseUp = NodeMouseUp;
  }
}
//---------------------------------------------------------------------------

// position sizing nodes around control
void __fastcall TFormVideo::PositionNodes(TWinControl* AroundControl)
{
	int Node,T,L,CT,CL,FR,FB,FT,FL;
  Types::TPoint TopLeft;
  TRegion *a_region;

  FCurrentNodeControl = NULL;
	for (Node=0; Node <=7; Node ++)
  {
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
    TopLeft = ((TPanel *)(FNodes->Items[Node]))->Parent->ScreenToClient(TopLeft);
    ((TPanel *)(FNodes->Items[Node]))->Top = TopLeft.y;
    ((TPanel *)(FNodes->Items[Node]))->Left = TopLeft.x;
  }
  FCurrentNodeControl = AroundControl;

  // update selected region
  a_region = GetSelectedRegion(FCurrentNodeControl);
  if (a_region) {
    TRegionData *data;
    //if (CheckBoxRecord->Checked) {
    if (FormMain->ActionRecord->Checked) {
      if ( (currentFrame >= 0) && (currentFrame < a_region->region_data->Count) ) {
        data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
        data->x = ((TWinControl *)(FCurrentNodeControl))->Left;
        data->y = ((TWinControl *)(FCurrentNodeControl))->Top;
        data->w = ((TWinControl *)(FCurrentNodeControl))->Width;
        data->h = ((TWinControl *)(FCurrentNodeControl))->Height;
      }
    }
    UpdateRegionProp(a_region);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::SetNodesVisible(bool vis)
{
	for (int Node=0; Node <=7; Node ++)
    ((TPanel *)(FNodes->Items[Node]))->Visible = vis;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::TimerPlayTimer(TObject *Sender)
{
	__int64 index;

	index = get_frame_index_mme(&(mme_app.project));
	if (index == set_frame_index_mme(&(mme_app.project), index+1)) {
    TimerPlay->Enabled = false;
    //CheckBoxPlay->Checked = false;
		MessageBox(mme_app.main_hwnd, get_error_msg_mme(&(mme_app.project)), "INFO", MB_OK|MB_ICONINFORMATION);
	}
  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonCreateRClick(TObject *Sender)
{
  TRegionData *data;
  TRegion *region;
	//create shaped region
  region = new TRegion;
  region->box = new TShape(FormVideo);
  region->region_data = new TList;

  region->box->Parent = PanelImg;
  region->box->Visible = false;
  region->box->Shape = stRectangle;
  region->box->Brush->Style = bsClear;
  region->box->Pen->Color = ColorBoxR->Selected;
  region->box->Pen->Width = FormMain->PenWidth;
  region->box->OnMouseDown = ShapeAMouseDown;
  region->box->OnMouseMove = ShapeAMouseMove;
  region->box->OnMouseUp = ShapeAMouseUp;
  region->box->Constraints->MaxHeight = MAX_REGION;
  region->box->Constraints->MaxWidth = MAX_REGION;
  region->box->Constraints->MinHeight = MIN_REGION;
  region->box->Constraints->MinWidth = MIN_REGION;
  region->box->Top = DEF_Y;
  region->box->Left = DEF_X;
  region->box->Width = DEF_W;
  region->box->Height = DEF_H;
  region->box->Visible = true;

  region->description.printf("Region %02d", ListBoxNodes->Count+1);
  region->color = ColorBoxR->Selected;
  region->startFrame = currentFrame;
  region->endFrame = maxFrame;
  region->descriptors = new TStringList;

  //set per frame data for all frames
  for (int i=0; i <= maxFrame; i++) {
    data = new TRegionData;
    data->x = region->box->Left;
    data->y = region->box->Top;
    data->w = region->box->Width;
    data->h = region->box->Height;
    region->region_data->Add(data);
  }

  regions->Add(region);
  UpdateRegionProp(region, true);
  ListBoxNodes->Items->Add(region->description);
  ListBoxNodes->Selected[ListBoxNodes->Count-1] = true;

  // update display
  SetNodesVisible(false);
  PositionNodes( (TWinControl *)(region->box) );
  SetNodesVisible(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonDelRClick(TObject *Sender)
{
  TRegion *selregion;
  TRegionData *data;
	//delete selected shaped region
  int i = ListBoxNodes->ItemIndex;

  if ( (i >= 0) && ( MessageDlg("Are you sure you want to delete the selected region?", mtConfirmation,
  	TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    // delete region
    SetNodesVisible(false);
    selregion = (TRegion *) (regions->Items[i]);
    for (int k=0; k < selregion->region_data->Count; k++) {
      data = (TRegionData *) (selregion->region_data->Items[k]);
      delete data;
    }
    delete selregion->box;
    delete selregion;
    ListBoxNodes->DeleteSelected();
    regions->Delete(i);

    // select another in listbox
    if (i < ListBoxNodes->Count-1 )
      ListBoxNodes->Selected[i] = true;
    else
      if (ListBoxNodes->Count)
        ListBoxNodes->Selected[ListBoxNodes->Count-1] = true;

    ListBoxNodesClick(Sender);
    ListBoxNodes->Refresh();
  }
}
//---------------------------------------------------------------------------

int __fastcall CompareRegions(void *Item1, void *Item2)
{
  TRegion *region1, *region2;
  region1 = (TRegion *) (Item1);
  region2 = (TRegion *) (Item2);
  if (region1->startFrame < region2->startFrame)
    return -1;
  else if (region1->startFrame > region2->startFrame)
    return 1;
  else
    return 0;
}

void __fastcall TFormVideo::ButtonSortRClick(TObject *Sender)
{
  // Sort regions by frame start
  if (ListBoxNodes->Count < 1) return;

  TRegion *regiona;
  SetNodesVisible(false);
  //quicksort
  regions->Sort(CompareRegions);

  //rewrite ListBoxNodes
  for (int k=0; k<regions->Count; k++) {
    regiona = (TRegion *) (regions->Items[k]);
    if (FormMain->RenumberSort)
      regiona->description.printf("Region %02d", k+1);
    ListBoxNodes->Items->Strings[k] = regiona->description;
  }

  // finished select last and redraw
  ListBoxNodes->Selected[ListBoxNodes->Count-1] = true;
  ListBoxNodesClick(Sender);
  ListBoxNodes->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxNodesClick(TObject *Sender)
{
  TRegion *a_region;

  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    UpdateRegionProp(a_region, true);
    RepaintRegion(a_region, true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ColorBoxRChange(TObject *Sender)
{
  TRegion *a_region;
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_region->box->Pen->Color = ColorBoxR->Selected;
    a_region->color = ColorBoxR->Selected;
    a_region->box->Refresh();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditRNameKeyPress(TObject *Sender, char &Key)
{
  TRegion *a_region;

  if (Key == 13) {
    int i = ListBoxNodes->ItemIndex;
    if (i >= 0) {
      a_region = (TRegion *) (regions->Items[i]);
      a_region->description = EditRName->Text;
      ListBoxNodes->Items->Strings[i] = EditRName->Text;
      ListBoxNodes->Selected[i] = true;
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormVideo::ButtonToBackClick(TObject *Sender)
{
  int i = ListBoxNodes->ItemIndex;
  TRegion *a_region;

  if (i >= 0) {
    a_region = (TRegion *) (regions->Items[i]);
    a_region->box->SendToBack();
    ImageV->SendToBack();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonToFrontClick(TObject *Sender)
{
  int i = ListBoxNodes->ItemIndex;
  TRegion *a_region;

  if (i >= 0) {
    a_region = (TRegion *) (regions->Items[i]);
    a_region->box->BringToFront();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonRegionSFClick(TObject *Sender)
{
  TRegion *a_region;
  //set starting frame for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_region->startFrame = currentFrame;
    EditRegionSF->Text = IntToStr(a_region->startFrame);
    // check end frame
    if (a_region->endFrame < a_region->startFrame) {
	    a_region->endFrame = a_region->startFrame;
      EditRegionEF->Text = IntToStr(a_region->endFrame);
    }
    // if out of range dont show
    RepaintVideo();
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditRegionSFDblClick(TObject *Sender)
{
  TRegion *a_region;

  if (ListBoxNodes->ItemIndex >= 0) {

    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    __int64 v = a_region->startFrame;
    AnsiString s = IntToStr(v);

    if (InputQuery("Enter Start Frame", "Enter value :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if ( v < 0 ) v = 0;
      else if ( v > maxFrame ) v = maxFrame;
      a_region->startFrame = v;
      EditRegionSF->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------
void __fastcall TFormVideo::EditRegionEFDblClick(TObject *Sender)
{
  TRegion *a_region;

  if (ListBoxNodes->ItemIndex >= 0) {

    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    __int64 v = a_region->endFrame;
    AnsiString s = IntToStr(v);

    if (InputQuery("Enter End Frame", "Enter value :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if ( v < 0 ) v = 0;
      else if ( v > maxFrame ) v = maxFrame;
      a_region->endFrame = v;
      EditRegionEF->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);

}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditShotSFDblClick(TObject *Sender)
{
 TShot *a_shot;
 //set starting frame
  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) (shots->Items[ListBoxShots->ItemIndex]);
    __int64 v = a_shot->startFrame;
    AnsiString s = IntToStr(v);

    if (InputQuery("Enter Start Frame", "Enter value :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if ( v < 0 ) v = 0;
      else if ( v > maxFrame ) v = maxFrame;
      else if ( v > a_shot->endFrame) v = a_shot->endFrame;
      a_shot->startFrame = v;
      EditShotSF->Text = IntToStr(v);
    }
  }
  else
  	MessageDlg("No shot selected.\nYou must select a shot to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditShotEFDblClick(TObject *Sender)
{
  TShot *a_shot;
  //set end frame
  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) (shots->Items[ListBoxShots->ItemIndex]);
    __int64 v = a_shot->endFrame;
    AnsiString s = IntToStr(v);

    if (InputQuery("Enter End Frame", "Enter value :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if ( v < 0 ) v = 0;
      else if ( v > maxFrame ) v = maxFrame;
      else if ( v < a_shot->startFrame) v = a_shot->startFrame;
      a_shot->endFrame = v;
      EditShotEF->Text = IntToStr(v);
    }
  }
  else
  	MessageDlg("No shot selected.\nYou must select a shot to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonRegionEFClick(TObject *Sender)
{
  TRegion *a_region;
  //set end frame for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_region->endFrame = currentFrame;
    EditRegionEF->Text = IntToStr(currentFrame);
    // check start frame
    if (a_region->startFrame > a_region->endFrame) {
	    a_region->startFrame = a_region->endFrame;
      EditRegionSF->Text = IntToStr(a_region->startFrame);
    }
    // if out of range dont show
    RepaintVideo();
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------


void __fastcall TFormVideo::EditRXDblClick(TObject *Sender)
{
  TRegionData *a_data;
  TRegion *a_region;
  //set X for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);

    int v = a_data->x;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter X", "Enter value for X :", s)) {
      v = StrToIntDef(s, 0);
      a_data->x = v;
      EditRX->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditRYDblClick(TObject *Sender)
{
  TRegionData *a_data;
  TRegion *a_region;
  //set X for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);

    int v = a_data->y;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Y", "Enter value for Y :", s)) {
      v = StrToIntDef(s, 0);
      a_data->y = v;
      EditRY->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditRWDblClick(TObject *Sender)
{
  TRegionData *a_data;
  TRegion *a_region;
  //set X for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);

    int v = a_data->w;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Width", "Enter value for Width :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if (v < MIN_REGION) v = MIN_REGION;
      if (v > MAX_REGION) v = MAX_REGION;
      a_data->w = v;
      EditRW->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditRHDblClick(TObject *Sender)
{
  TRegionData *a_data;
  TRegion *a_region;
  //set X for selected region
  if (ListBoxNodes->ItemIndex >= 0) {
    a_region = (TRegion *) regions->Items[ListBoxNodes->ItemIndex];
    a_data = (TRegionData *) a_region->region_data->Items[currentFrame];

    int v = a_data->h;
    AnsiString s = IntToStr(v);
    if (InputQuery("Enter Height", "Enter value for Height :", s)) {
      v = StrToIntDef(s, MIN_REGION);
      if (v < MIN_REGION) v = MIN_REGION;
      if (v > MAX_REGION) v = MAX_REGION;
      a_data->h = v;
      EditRH->Text = IntToStr(v);
      RepaintRegion(a_region);
    }
  }
  else
  	MessageDlg("No region selected.\nYou must select a region to change a value.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::CleanupRegions(void)
{
	TRegionData *data;
  TRegion *region;

	//delete regions
  if (ListBoxNodes->Count) {
    for (int i=0; i < ListBoxNodes->Count; i++) {
      region = (TRegion *) regions->Items[i];

      for (int k = 0; k < region->region_data->Count; k++) {
        data = (TRegionData *) region->region_data->Items[k];
        delete data;
      }
      delete region->region_data;
      delete region->box;
      delete region;
    }
  }
  regions->Clear();
  ListBoxNodes->Clear();
  ListBoxRegionDesc->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TFormVideo::ListBoxNodesKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelRClick(Sender);
  }
  else if (Key == VK_INSERT) {
    ButtonCreateRClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxVideoDescDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  if (Sender->ClassNameIs("TListBox") //&& Source->ClassNameIs("TcxDragControlObject")
  ) {
    TListBox *DestList = (TListBox *)Sender;
    AnsiString targdesc = TreeXML->Selected->Text;
    if ( DestList->Items->IndexOf(targdesc) == -1 )
    {
      DestList->Items->Add(targdesc);
      DestList->Selected[DestList->Count-1] = true;
      VideoDescriptors->Add(targdesc);
    }
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxVideoDescDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = Source->ClassNameIs("TcxDragControlObject");
    //TODO: check
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxRegionDescDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = Source->ClassNameIs("TcxDragControlObject");
  //TODO: check
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxRegionDescDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
  if (ListBoxNodes->ItemIndex < 0) {
    MessageDlg("No region selected.\nYou must select a region to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  TRegion *a_region;
  if (Sender->ClassNameIs("TListBox") //&& Source->ClassNameIs("TcxDragControlObject")
  ) {
    TListBox *DestList = (TListBox *)Sender;
    //String targdesc = ((TcxTreeView *)Source)->Selected->Text;
    AnsiString targdesc = TreeXML->Selected->Text;
    if ( DestList->Items->IndexOf(targdesc) == -1 )
    {
      DestList->Items->Add(targdesc);
      DestList->Selected[DestList->Count-1] = true;
      a_region = (TRegion *) regions->Items[ListBoxNodes->ItemIndex];
      a_region->descriptors->Add(targdesc);
     }
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonDelRegionDescClick(TObject *Sender)
{
  //delete shot description
  int i = ListBoxNodes->ItemIndex;
  int d = ListBoxRegionDesc->ItemIndex;
  TRegion *a_region;

  if ( (i >= 0) && (d >= 0) && ( MessageDlg("Are you sure you want to delete the selected descriptor?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    // delete descriptor
    a_region = (TRegion *) regions->Items[ListBoxNodes->ItemIndex];
    a_region->descriptors->Delete(d);
    ListBoxRegionDesc->Items->Delete(d);

    UpdateRegionProp(a_region);

    if (d < ListBoxRegionDesc->Count-1 )
      ListBoxRegionDesc->Selected[d] = true;
    else
      if (ListBoxRegionDesc->Count)
        ListBoxRegionDesc->Selected[ListBoxRegionDesc->Count-1] = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonDelVideoDescClick(TObject *Sender)
{
  // delete video descriptors
  int d = ListBoxVideoDesc->ItemIndex;

  if ( (d >= 0) && ( MessageDlg("Are you sure you want to delete the selected descriptor?",
  	mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes ) )  {
    VideoDescriptors->Delete(d);
    ListBoxVideoDesc->Items->Delete(d);
    ListBoxVideoDesc->Items->Assign(VideoDescriptors);

    if (d < ListBoxVideoDesc->Count-1 )
      ListBoxVideoDesc->Selected[d] = true;
    else
      if (ListBoxVideoDesc->Count)
        ListBoxVideoDesc->Selected[ListBoxVideoDesc->Count-1] = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxRegionDescKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelRegionDescClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxShotDescKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelShotDescClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ListBoxVideoDescKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_DELETE) {
    ButtonDelVideoDescClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::EditShotNameKeyPress(TObject *Sender, char &Key)
{
  TShot *a_shot;

  if (Key == 13) {
    int i = ListBoxShots->ItemIndex;
    if (i >= 0) {
      a_shot = (TShot *) shots->Items[i];
      a_shot->description = EditShotName->Text;
      ListBoxShots->Items->Strings[i] = EditShotName->Text;
      ListBoxShots->Selected[i] = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonShotSFClick(TObject *Sender)
{
  TShot *a_shot;

  //set starting frame for selected shot
  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
    a_shot->startFrame = currentFrame;
    EditShotSF->Text = IntToStr(a_shot->startFrame);
    // check end frame
    if (a_shot->endFrame < a_shot->startFrame ) {
	    a_shot->endFrame = a_shot->startFrame;
      EditShotEF->Text = IntToStr(a_shot->endFrame);
    }
  }
  else
  	MessageDlg("No shot selected.\nYou must select a shot to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);

}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonShotEFClick(TObject *Sender)
{
  TShot *a_shot;
  //set end frame for selected region
  if (ListBoxShots->ItemIndex >= 0) {
    a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
    a_shot->endFrame = currentFrame;
    EditShotEF->Text = IntToStr(currentFrame);
    // check start frame
    if (a_shot->startFrame > a_shot->endFrame ) {
	    a_shot->startFrame = a_shot->endFrame;
      EditShotSF->Text = IntToStr(a_shot->startFrame);
    }
  }
  else
  	MessageDlg("No shot selected.\nYou must select a shot to set the frame.", mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonAddRegionDescClick(TObject *Sender)
{
	// add descriptor to region
  if (ListBoxNodes->ItemIndex < 0) {
    MessageDlg("No region selected.\nYou must select a region to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  AnsiString targdesc;
  TRegion *a_region;

  if (InputQuery("Input", "Descriptor", targdesc)) {
  	ListBoxRegionDesc->Items->Add(targdesc);
    ListBoxRegionDesc->Selected[ListBoxRegionDesc->Count-1] = true;
    a_region = (TRegion *) regions->Items[ListBoxNodes->ItemIndex];
    a_region->descriptors->Add(targdesc);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonAddShotDescClick(TObject *Sender)
{
	// add descriptor to shot
  if (ListBoxShots->ItemIndex < 0) {
    MessageDlg("No shot selected.\nYou must select a shot to annotate.", mtError, TMsgDlgButtons() << mbOK, 0);
    return;
  }

  AnsiString targdesc;
  TShot *a_shot;
  
  if (InputQuery("Input", "descriptor", targdesc)) {
  	ListBoxShotDesc->Items->Add(targdesc);
    ListBoxShotDesc->Selected[ListBoxShotDesc->Count-1] = true;
    a_shot = (TShot *) shots->Items[ListBoxShots->ItemIndex];
    a_shot->descriptors->Add(targdesc);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonAddVideoDescClick(TObject *Sender)
{
  AnsiString targdesc;

  if (InputQuery("Input", "descriptor", targdesc)) {
  	ListBoxVideoDesc->Items->Add(targdesc);
    ListBoxVideoDesc->Selected[ListBoxVideoDesc->Count-1] = true;
    VideoDescriptors->Add(targdesc);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonGotoRegionStartClick(TObject *Sender)
{
	// goto starting frame of selected region
	TRegion *selregion;

  int i = ListBoxNodes->ItemIndex;
  __int64 goframe;

  if ( i >= 0  )  {
    selregion = (TRegion *) regions->Items[i];
    goframe = selregion->startFrame;
    if (!CheckVideoLoaded()) return;
		if(goframe != set_frame_index_mme(&(mme_app.project), goframe)) {
      MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
		}
	  UpdateSlider();
  	RepaintVideo();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonGotoRegionEndClick(TObject *Sender)
{
	// goto end frame of selected region
	TRegion *selregion;

  int i = ListBoxNodes->ItemIndex;
  __int64 goframe;

  if ( i >= 0  )  {
    selregion = (TRegion *) regions->Items[i];
    goframe = selregion->endFrame;
    if (!CheckVideoLoaded()) return;
		if(goframe != set_frame_index_mme(&(mme_app.project), goframe)) {
      MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
		}
	  UpdateSlider();
  	RepaintVideo();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ButtonGotoShotStartClick(TObject *Sender)
{
	// goto starting frame of selected shot
	TShot *selshot;

  int i = ListBoxShots->ItemIndex;
  __int64 goframe;

  if ( i >= 0  )  {
    selshot = (TShot *) shots->Items[i];
    goframe = selshot->startFrame;
    if (!CheckVideoLoaded()) return;
		if(goframe != set_frame_index_mme(&(mme_app.project), goframe)) {
      MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
		}
	  UpdateSlider();
  	RepaintVideo();
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormVideo::ButtonGotoShotEndClick(TObject *Sender)
{
	// goto end frame of selected shot
	TShot *selshot;

  int i = ListBoxShots->ItemIndex;
  __int64 goframe;

  if ( i >= 0  )  {
    selshot = (TShot *) shots->Items[i];
    goframe = selshot->endFrame;
    if (!CheckVideoLoaded()) return;
		if(goframe != set_frame_index_mme(&(mme_app.project), goframe)) {
      MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
		}
	  UpdateSlider();
  	RepaintVideo();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::CleanupShots()
{
  // clean up shots data
  TShot *shot;
  if (ListBoxNodes->Count) {
    for (int i=0; i < ListBoxShots->Count; i++) {
      shot = (TShot *) shots->Items[i];
      delete shot->descriptors;
      delete shot;
    }
    //delete shots;
    shots->Clear();
  }
  EditShotSF->Text="0";
  EditShotEF->Text="0";
  ListBoxShots->Clear();
  ListBoxShotDesc->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::CopyFrameClip()
{
	// clipboard copy
  // check if video loaded
  if (!CheckVideoLoaded()) return;

	char *p;
	const BITMAPINFOHEADER *bih;

	if(!OpenClipboard(mme_app.main_hwnd)){
		ShowError("MSG_FAILED_TO_OPEN_CLIPBOARD", GetLastError());
		return;
	}

	if(!EmptyClipboard()){
		CloseClipboard();
		ShowError("MSG_FAILED_TO_GET_CLIPBOARD_OWNERSHIP", GetLastError());
		return;
	}

	bih = get_dib_header_mme(&(mme_app.project));
	if(mme_app.clipboard != NULL){
		GlobalFree(mme_app.clipboard);
	}
	mme_app.clipboard = GlobalAlloc(GMEM_MOVEABLE, bih->biSize + bih->biSizeImage);
	if(mme_app.clipboard == NULL){
		CloseClipboard();
		ShowError(msg_table[mme_app.lang][MSG_NO_ENOUGH_MEMORY], GetLastError());
		return;
	}
	p = (char *)GlobalLock(mme_app.clipboard);

	memcpy(p, bih, bih->biSize);
	memcpy(p+bih->biSize, get_frame_mme(&(mme_app.project)), bih->biSizeImage);

	GlobalUnlock(mme_app.clipboard);

	SetClipboardData(CF_DIB, mme_app.clipboard);
	CloseClipboard();

	return;
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::VideoGotoFrame(TObject *Sender)
{
	__int64 index;
	AnsiString s;
	FRAME_BY_NUMBER prm;
  __int64 frame;

  if (!CheckVideoLoaded()) return;

	prm.current = get_frame_index_mme(&(mme_app.project));
	prm.max = maxFrame;
  s = IntToStr(prm.current);
  if (InputQuery("Go to Frame (0-"+IntToStr(prm.max)+")", "Number :", s))
  {
  	frame = StrToInt64Def(s, currentFrame);
    if (frame > prm.max)
	    frame = prm.max;
		if(frame != set_frame_index_mme(&(mme_app.project), frame)){
      MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
		}
	  UpdateSlider();
  	RepaintVideo();
	}

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoTimeCode(TObject *Sender)
{
	__int64 index;

	FRAME_BY_TIMECODE prm;

	prm.current = get_frame_index_mme(&(mme_app.project));
	prm.max = get_frame_count_mme(&(mme_app.project))-1;
	prm.lang = mme_app.lang;
	prm.rate = mme_app.project.video_info.dwRate;
	prm.scale = mme_app.project.video_info.dwScale;

	index = query_frame_by_timecode(mme_app.instance, mme_app.main_hwnd, &prm);

	if(index != set_frame_index_mme(&(mme_app.project), index)){
    MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
	}

  RepaintVideo();

	return;

}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoNextIFrame(TObject *Sender)
{
	__int64 index;

  if (!CheckVideoLoaded()) return;
	index = get_frame_index_mme(&(mme_app.project));
	if(index == go_next_i_frame_mme(&(mme_app.project))){
    MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
	}

  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoPrevIFrame(TObject *Sender)
{
	__int64 index;

  if (!CheckVideoLoaded()) return;
	index = get_frame_index_mme(&(mme_app.project));
	if(index == go_prev_i_frame_mme(&(mme_app.project))){
    MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
	}

  RepaintVideo();

	return;

}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoStart(TObject *Sender)
{
	if (!CheckVideoLoaded()) return;
	go_start_frame_mme(&(mme_app.project));
  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoEnd(TObject *Sender)
{
  if (!CheckVideoLoaded()) return;
	go_end_frame_mme(&(mme_app.project));
  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoFWD(TObject *Sender)
{
  	__int64 index;
  if (!CheckVideoLoaded()) return;

	index = get_frame_index_mme(&(mme_app.project));
	if (index == set_frame_index_mme(&(mme_app.project), index+1)) {
    MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
	}
  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::VideoREW(TObject *Sender)
{
  	__int64 index;

  if (!CheckVideoLoaded()) return;

	index = get_frame_index_mme(&(mme_app.project));
	if(index == set_frame_index_mme(&(mme_app.project), index-1)){
    MessageDlg( get_error_msg_mme(&(mme_app.project)), mtInformation, TMsgDlgButtons() << mbOK, 0);;
	}
  RepaintVideo();

	return;
}
//---------------------------------------------------------------------------
void __fastcall TFormVideo::ExportXML(TObject *Sender)
{
  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

	// save XML file
  TRegionData *data, *data2;
  TRegion *region;
  TShot *shot;
  AnsiString as;
  float ms;
  TIMECODE tc;
  int fps,drop;
  __int64 frame;


  if (FormMain->SaveDialogXML->Execute()) {
  	//save list in XML format

	  TStringList *exp;
  	exp = new TStringList;
	  exp->Add("<?xml version=\"1.0\" ?>");
		exp->Add("<DOCANALYSIS MODALITY=\"Video\">");
    exp->Add(" <DOCREF TYPE=\"File\">");
    exp->Add("  <FILE>"+VAVideoFilename->Text+"</FILE>"); // filename
		exp->Add(" </DOCREF>");

    exp->Add(" <SEGMENT_LIST>");
    // region segments
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      region = (TRegion *) (regions->Items[i]);
      exp->Add("  <SEGMENT TYPE=\"VideoSegment\">");
			exp->Add("   <ID>"+region->description+"</ID>");
      exp->Add("   <POS TYPE=\"ISO8601StartDuration\">");
      fps = (mme_app.project.video_info.dwRate + mme_app.project.video_info.dwScale-1) / mme_app.project.video_info.dwScale;
      drop = mme_app.project.video_info.dwRate % mme_app.project.video_info.dwScale;
      frame = region->startFrame;
      frame2timecode(&frame, &tc, fps, drop);
      ms = 100.0 * tc.ff/fps;
      as.printf(TC_FORMAT, tc.hh, tc.mm, tc.ss, ms);
      exp->Add("    <START>"+as+"</START>");
      frame = region->endFrame - region->startFrame + 1;
      frame2timecode( &frame, &tc, fps, drop); //TODO: check if correct
      ms = 100.0 * tc.ff/fps;
      as.printf(TC_FORMAT, tc.hh, tc.mm, tc.ss, ms);
      exp->Add("    <DURATION>PT"+as+"</DURATION>");
      exp->Add("   </POS>");
      exp->Add("  </SEGMENT>");
    }
    // shot segments
    for (int i=0; i < ListBoxShots->Count ; i++) {
      shot = (TShot *) (shots->Items[i]);
      exp->Add("  <SEGMENT TYPE=\"VideoSegment\">");
			exp->Add("   <ID>"+shot->description+"</ID>");
      exp->Add("   <POS TYPE=\"ISO8601StartDuration\">");
      fps = (mme_app.project.video_info.dwRate + mme_app.project.video_info.dwScale-1) / mme_app.project.video_info.dwScale;
      drop = mme_app.project.video_info.dwRate % mme_app.project.video_info.dwScale;
      frame = shot->startFrame;
      frame2timecode(&frame, &tc, fps, drop);
      ms = 100.0*tc.ff/fps;
      as.printf(TC_FORMAT, tc.hh, tc.mm, tc.ss, ms);
      exp->Add("    <START>"+as+"</START>");
      frame = shot->endFrame - shot->startFrame + 1;
      frame2timecode( &frame, &tc, fps, drop); //TODO: check if correct
      ms = 100.0*tc.ff/fps;
      as.printf(TC_FORMAT, tc.hh, tc.mm, tc.ss, ms);
      exp->Add("    <DURATION>PT"+as+"</DURATION>");
      exp->Add("   </POS>");
      exp->Add("  </SEGMENT>");
    }
    exp->Add(" </SEGMENT_LIST>");

    exp->Add(" <MLCI_LIST>");
    // MLCI from regions
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      region = (TRegion *) (regions->Items[i]);
      exp->Add("    <MLCI>");
      exp->Add("   <ID>"+region->description+"</ID>");
      exp->Add("   <ELEMENTREF>"+region->description+"</ELEMENTREF>");
      for (int m=0; m < region->descriptors->Count; m++) {
        exp->Add("   <LABEL>"+region->descriptors->Strings[m]+"</LABEL>");
      }
      // we loose tag <CONFIDENCE>180.500</CONFIDENCE>
      exp->Add("  </MLCI>");
    }
    // MLCI from shots
    for (int i=0; i < ListBoxShots->Count ; i++) {
      shot = (TShot *) (shots->Items[i]);
      exp->Add("  <MLCI>");
      exp->Add("   <ID>"+shot->description+"</ID>");
      exp->Add("   <ELEMENTREF>"+shot->description+"</ELEMENTREF>");
      for (int m=0; m < shot->descriptors->Count; m++) {
        exp->Add("   <LABEL>"+shot->descriptors->Strings[m]+"</LABEL>");
      }
      // we loose tag <CONFIDENCE>180.500</CONFIDENCE>
      exp->Add("  </MLCI>");
    }
    exp->Add(" </MLCI_LIST>");

/*
    <SEGMENT TYPE="VideoSegment">
     <ID>seg28</ID>
     <POS TYPE="ISO8601StartDuration">
      <START>00:00:39,16</START>
      <DURATION>PT00:00:00,52</DURATION>
     </POS>
    </SEGMENT>

   <MLCI>
    <ID>mlc22</ID>
    <ELEMENTREF>seg28</ELEMENTREF>
    <LABEL>Jump</LABEL>
    <CONFIDENCE>180.500</CONFIDENCE>
   </MLCI>
*/
    // trajectories from regions
    exp->Add(" <TRAJECTORYSET>");
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      region = (TRegion *) (regions->Items[i]);
	   	exp->Add("  <TRAJECTORY>");
			exp->Add("   <ID>"+region->description+"</ID>");

      for (int k=region->startFrame; k <= region->endFrame; k++)
      { //region data
				data = (TRegionData *) (region->region_data->Items[k]);
	 			exp->Add("   <POS TYPE=\"BBOXSEQUENCE\">");
 				exp->Add("   <BOX>");
        exp->Add("    <FRAME>"+IntToStr(k)+"</FRAME>");
        exp->Add("    <LEFT>"+IntToStr(data->x)+"</LEFT>");
        exp->Add("    <TOP>"+IntToStr(data->y)+"</TOP>");
        exp->Add("    <WIDTH>"+IntToStr(data->w)+"</WIDTH>");
        exp->Add("    <HEIGHT>"+IntToStr(data->h)+"</HEIGHT>");
  			exp->Add("  </BOX>");
        exp->Add("   </POS>");
        //exp->Add("<INFO>");
      } // for k [region data]
      exp->Add("  </TRAJECTORY>");
    } // for i	[regions]
    exp->Add(" </TRAJECTORYSET>");
    exp->Add("</DOCANALYSIS>");

  	exp->SaveToFile(FormMain->SaveDialogXML->FileName);
    FormLog->Log("XML export to file "+FormMain->SaveDialogXML->FileName);
	  exp->Clear();
	  delete exp;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ImportXML(TObject *Sender)
{
  // IMPORT XML from BOEMIE type data
  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

  if(FormMain->OpenDialogXML->Execute()) {

    CleanupRegions();
    FormImport->FileName = FormMain->OpenDialogXML->FileName;
    Cursor = crHourGlass;
    FormImport->ShowModal();
    Cursor = crDefault;
    //TODO: get labels from MLCI
  }
  else
    return;
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::ExportXMLTraj(TObject *Sender)
{
// stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

	// save XML file
  TRegionData *data, *data2;
  TRegion *region;

//  if(ListBoxNodes->Count <= 0) // no regions
//  	return;

  if (FormMain->SaveDialogXML->Execute()) {
  	//save list in XML format

	  TStringList *exp;
  	exp = new TStringList;
	  exp->Add("<?xml version=\"1.0\" ?>");
		exp->Add("<DOCANALYSIS MODALITY=\"Video\">");
    exp->Add(" <DOCREF TYPE=\"File\">");
    exp->Add("  <FILE>"+VAVideoFilename->Text+"</FILE>"); // filename
		exp->Add(" </DOCREF>");
    exp->Add(" <SEGMENT_LIST>");
    exp->Add(" </SEGMENT_LIST>");

    // add MLCI if we have data
    if (FormImport->MLCI) {
      AnsiString as,as1,as2;
      int pos;

      exp->Add(" <MLCI_LIST>");
      exp->Add("  <MLCI>");
      for (int k=0 ; k < FormImport->MLCI->Count; k++) {
        as = FormImport->MLCI->Strings[k];
        pos = as.AnsiPos(",");
        if (pos) {
          as1 = LeftStr(as, pos-1);
          as2 = MidStr(as, pos+1, as.Length()-pos);
          exp->Add("   <"+as1+">" + as2+ "</"+as1+">");
        }
      }
      exp->Add("  </MLCI>");
      exp->Add(" </MLCI_LIST>");
    }

    exp->Add(" <TRAJECTORYSET>");
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      region = (TRegion *) (regions->Items[i]);
	   	exp->Add("  <TRAJECTORY>");
			exp->Add("   <ID>"+region->description+"</ID>");

      for (int k=region->startFrame; k <= region->endFrame; k++)
      { //region data
				data = (TRegionData *) (region->region_data->Items[k]);
	 			exp->Add("   <POS TYPE=\"BBOXSEQUENCE\">");
 				exp->Add("   <BOX>");
        exp->Add("    <FRAME>"+IntToStr(k)+"</FRAME>");
        exp->Add("    <LEFT>"+IntToStr(data->x)+"</LEFT>");
        exp->Add("    <TOP>"+IntToStr(data->y)+"</TOP>");
        exp->Add("    <WIDTH>"+IntToStr(data->w)+"</WIDTH>");
        exp->Add("    <HEIGHT>"+IntToStr(data->h)+"</HEIGHT>");
  			exp->Add("   </BOX>");
        exp->Add("   </POS>");
        //exp->Add("<INFO>");
      } // for k [region data]
      exp->Add("  </TRAJECTORY>");
    } // for i	[regions]
    exp->Add(" </TRAJECTORYSET>");
    exp->Add("</DOCANALYSIS>");

  	exp->SaveToFile(FormMain->SaveDialogXML->FileName);
    FormLog->Log("XML export to file "+FormMain->SaveDialogXML->FileName);
	  exp->Clear();
	  delete exp;
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::ExportText(TObject *Sender)
{
  TRegionData *data, *data2;
  TRegion *region;
  TShot *shot;
  TStringList *exp;

  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

	// export frame data
  exp = new TStringList;

	//export video
	exp->Add("[Video Information]");
  exp->Add("Title:");
  exp->Add(VATitle->Text);
	exp->Add("Date:");
  exp->Add(VADateTime->Date.DateTimeString());
  exp->Add("Description:");
  exp->Add(VADesc->Text);
  exp->Add("Annotator:");
  exp->Add(VAAnnotator->Text);
  exp->Add("Video filename:");
  exp->Add(VAVideoFilename->Text);
  exp->Add("Video Descriptors filename:");
  exp->Add(VAAnnoFile->Text);
	exp->Add("Video Descriptors ("+IntToStr(VideoDescriptors->Count)+"):");
  if (VideoDescriptors->Count) {
  	for(int i=0; i< VideoDescriptors->Count ; i++) {
    	exp->Add(VideoDescriptors->Strings[i]);
    }
  }
  exp->Add("");

  //export shots
  if (ListBoxShots->Count) {
	  exp->Add("[Shots Information]");
    for (int i=0; i < ListBoxShots->Count ; i++) {
      shot = (TShot *) (shots->Items[i]);
      exp->Add("Object Number #"+IntToStr(i+1));
      exp->Add("Shot Description:");
      exp->Add(shot->description);
      exp->Add("Start Frame:"+IntToStr(shot->startFrame));
      exp->Add("End Frame:"+IntToStr(shot->endFrame));
      exp->Add("Shot Descriptors (" + IntToStr(shot->descriptors->Count) + "):");
      for (int k=0; k < shot->descriptors->Count; k++ ) {
      	exp->Add(shot->descriptors->Strings[k]);
      }
    }
	}
  exp->Add("");

  //export regions
  if (ListBoxNodes->Count) {

	  exp->Add("[Region Information]");
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      region = (TRegion *) (regions->Items[i]);
      exp->Add("Object Number #"+IntToStr(i+1));
      exp->Add("Region Description:");
      exp->Add(region->description);
      exp->Add("Start Frame:"+IntToStr(region->startFrame));
      exp->Add("End Frame:"+IntToStr(region->endFrame));
      exp->Add("Region Descriptors ("+IntToStr(region->descriptors->Count)+"):");
      for (int m=0; m < region->descriptors->Count; m++) {
        exp->Add(region->descriptors->Strings[m]);
      }
      exp->Add("Region frames data");

      for (int k=0; k < region->region_data->Count; k++) {

        data = (TRegionData *) (region->region_data->Items[k]);
				// export only valid frames
        // k is the frame number
        if ( (k >= region->startFrame) && (k <= region->endFrame) )
        {
          __int64 range_start = k;
          __int64 range_end = k;
          // if same data for all frames put them as range "fs to fe"
          for (int k2 = range_start + 1; k2 <= region->endFrame; k2++ ) {
            //compare with frames ahead
            data2 = (TRegionData *) (region->region_data->Items[k2]);
            if ( (data->x == data2->x) && (data->y == data2->y) &&
                 (data->w == data2->w) && (data->h == data2->h))
              range_end=k2;
          } // for k2
          if (range_end != k) {
            // we have range of frames
            k = range_end; // skip ahead
            exp->Add("Frames: "+IntToStr(range_start)+" to "+IntToStr(range_end) );
          }
          else
            exp->Add("Frame: "+IntToStr(k));

  	      exp->Add("x: "+IntToStr(data->x));
    	    exp->Add("y: "+IntToStr(data->y));
      	  exp->Add("width: "+IntToStr(data->w));
        	exp->Add("height: "+IntToStr(data->h));
	        exp->Add("");
        } // if
      } // for k
    } // for i
    exp->Add("");
  }

  if (FormMain->SaveDialog->Execute()) {
  	exp->SaveToFile(FormMain->SaveDialog->FileName);
    FormLog->Log("Text data exported to "+FormMain->SaveDialog->FileName);
  }

  exp->Clear();
  delete exp;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::CleanupUI(void)
{
  // video
  SetNodesVisible(false);
  EditRegionEF->Text = "0";
  EditRegionSF->Text = "0";

  LabelStatus->Text = "Status Message";
  TrackBarVideo->Enabled = false;
  maxFrame = 0;
  currentFrame = 0;
  ImageV->Canvas->Brush->Color = clGreen;
  ImageV->Canvas->FillRect(Types::TRect(0,0,ImageV->Width,ImageV->Height));
  // disable record mode
  FormMain->ActionRecord->Checked = false;
  LabelRecord->Visible = FormMain->ActionRecord->Checked;
  LabelLocked->Visible = !FormMain->ActionRecord->Checked;
  //RecordModeMI->Checked = ActionRecord->Checked;
  //CheckBoxRecord->Checked = ActionRecord->Checked;
  // clean project video and descriptors filename
  VAVideoFilename->Text="";
  VAAnnoFile->Text="";
  VATitle->Text="";
  VADateTime->Date = Date();
  VADesc->Text="";
  VAAnnotator->Text="";
  ListBoxVideoDesc->Clear();
  TreeXML->Items->Clear();
}

//---------------------------------------------------------------------------

void __fastcall TFormVideo::btnLoadAnnoClick(TObject *Sender)
{
  FormMain->ActionImportDescExecute(Sender);
}
//---------------------------------------------------------------------------

bool __fastcall TFormVideo::OpenProjectFile(AnsiString Filename, bool xml)
{
  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

 	if( is_open_mme(&(mme_app.project)) ) {
		close_mme(&(mme_app.project));
	}

  // cleanup first
  CleanupShots();
  CleanupRegions();
  CleanupUI();

  if(!xml) {

    // open ini type (ANP) project
    TIniFile *prjfile;
    prjfile = new TIniFile(Filename);
    TRegionData *data, *data2;
    TShot *shot;

    TimerPlay->Interval = prjfile->ReadInteger("Project", "TimerInterval", 100);
    FormImport->MLCI->Clear();

    TRegion *region;
    // --- load video
    try {
      VATitle->Text = prjfile->ReadString("Video", "Title", "");
      VADateTime->Date = prjfile->ReadDate("Video", "Date", Now());
      VADesc->Text = prjfile->ReadString("Video", "Description", "");
      VAAnnotator->Text = prjfile->ReadString("Video", "Annotator", "");
      VAVideoFilename->Text = prjfile->ReadString("Video", "VideoFilename", "");
      maxFrame = prjfile->ReadInteger("Video", "MaxFrame", 0);

      if (!Sysutils::FileExists(VAVideoFilename->Text)) {
        if (MessageDlg("Video file "+VAVideoFilename->Text+" not found. Do you want to locate the video file manually ?",
          mtError, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes )
          if ( OpenDialogV->Execute() )
            VAVideoFilename->Text = OpenDialogV->FileName;
        }

      if (OpenVideoFile(VAVideoFilename->Text) == false) {
        throw Exception("Error opening video file:\n"+VAVideoFilename->Text);
      }

      VAAnnoFile->Text = prjfile->ReadString("Video", "VideoDescFilename", "");
      // load video annotation descriptors
      if( Sysutils::FileExists(VAAnnoFile->Text) )
        FormMain->XML2Tree(TreeXML, FormMain->XMLDocument, VAAnnoFile->Text);

      //load descriptors
      int c=0;
      AnsiString targdesc;
      c = prjfile->ReadInteger("Video", "VideoDescriptorsNumber", 0);
      for(int i=0; i < c ; i++) {
        targdesc = prjfile->ReadString("Video", "VideoDescriptor"+IntToStr(i), "");
        ListBoxVideoDesc->Items->Add(targdesc);
        VideoDescriptors->Add(targdesc);
      }
      if (ListBoxVideoDesc->Count)
        ListBoxVideoDesc->Selected[ListBoxVideoDesc->Count-1] = true;
    }
    catch (Exception &exception) {
      MessageDlg("Error opening project file:\n"+Filename+
                +"\n\n(invalid video section information)\n"+
                 "The file is either in unknown format or damaged\n",
                  mtError, TMsgDlgButtons() << mbOK, 0);
      //TODO:cleanup
    }

    // --- load shots
    try {
      int c=0, d=0;
      AnsiString targdesc;
      c = prjfile->ReadInteger("Shots", "Count", 0);
      for(int i=0; i < c ; i++) {
        shot = new TShot;
        shot->description = prjfile->ReadString("Shot#"+IntToStr(i), "Description", "");
        shot->startFrame = prjfile->ReadInteger("Shot#"+IntToStr(i), "StartFrame", 0);
        shot->endFrame = prjfile->ReadInteger("Shot#"+IntToStr(i), "EndFrame", 0);
        shot->descriptors = new TStringList;
        shots->Add(shot);
        ListBoxShots->Items->Add(shot->description);
        //shot descriptoprs
        d = prjfile->ReadInteger("Shot#"+IntToStr(i), "ShotDescriptorsNumber", 0);
        for(int j=0; j < d ; j++) {
          targdesc = prjfile->ReadString("Shot#"+IntToStr(i), "ShotDescriptor"+IntToStr(j), 0);
          shot->descriptors->Add(targdesc);
        }
      }
      if (ListBoxShots->Count) {
        ListBoxShots->Selected[ListBoxShots->Count-1] = true;
        UpdateShotProp(shot);
      }
    }
    catch (Exception &exception) {
      MessageDlg("Error opening project file:\n"+Filename+
                +"\n\n(invalid shot section information)\n"+
                 "The file is either in unknown format or damaged",
                  mtError, TMsgDlgButtons() << mbOK, 0);
      //TODO:cleanup
    }

    // --- load regions
    try {
      int c=0, d=0;
      AnsiString targdesc;
      c = prjfile->ReadInteger("Regions", "Count", 0);
      for(int i=0; i < c ; i++) {
        region = new TRegion;
        region->region_data = new TList;
        region->box = new TShape(FormVideo);

        region->box->Parent = PanelImg;
        region->box->Visible = false;
        region->description = prjfile->ReadString("Region#"+IntToStr(i), "Description", "");
        region->startFrame = prjfile->ReadInteger("Region#"+IntToStr(i), "StartFrame", 0);
        region->endFrame = prjfile->ReadInteger("Region#"+IntToStr(i), "EndFrame", 0);
        region->color = StringToColor(prjfile->ReadString("Region#"+IntToStr(i), "Color", ColorToString(clRed)));

        region->box->Shape = stRectangle;
        region->box->Brush->Style = bsClear;
        region->box->Pen->Color = region->color;
        region->box->OnMouseDown = ShapeAMouseDown;
        region->box->OnMouseMove = ShapeAMouseMove;
        region->box->OnMouseUp = ShapeAMouseUp;
        region->box->Constraints->MaxHeight = MAX_REGION;
        region->box->Constraints->MaxWidth = MAX_REGION;
        region->box->Constraints->MinHeight = MIN_REGION;
        region->box->Constraints->MinWidth = MIN_REGION;

        //set per frame data for all frames
        for (int i=0; i <= maxFrame; i++) {
          data = new TRegionData;
          data->x = DEF_X;
          data->y = DEF_Y;
          data->w = DEF_W;
          data->h = DEF_H;
          region->region_data->Add(data);
        }
        // load frame data
        int dc = prjfile->ReadInteger("Region#"+IntToStr(i), "RegionFrameDataNumber", 0);
        for (int j=0; j <= dc; j++) {

          int fs = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameStart", 0);
          int fe = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameEnd", 0);

          //optimization (dont read from file for everyframe)
          int x = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameX", DEF_X);
          int y = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameY", DEF_Y);
          int w = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameW", DEF_W);
          int h = prjfile->ReadInteger("Region#"+IntToStr(i)+"."+IntToStr(j), "FrameDataFrameH", DEF_H);

          if (j==0) {
            region->box->Top = y;
            region->box->Left = x;
            region->box->Width = w;
            region->box->Height = h;
            region->box->Visible = true;
          }

          for (int k = fs; k <= fe; k++) {
            data = (TRegionData *) (region->region_data->Items[k]);
            data->x = x;
            data->y = y;
            data->w = w;
            data->h = h;
          }
        }

        //region descriptors
        region->descriptors = new TStringList;
        d = prjfile->ReadInteger("Region#"+IntToStr(i), "RegionDescriptorsNumber", 0);
        for(int j=0; j < d ; j++) {
          targdesc = prjfile->ReadString("Region#"+IntToStr(i), "RegionDescriptor"+IntToStr(j), 0);
          region->descriptors->Add(targdesc);
        }

        regions->Add(region);
        RepaintRegion(region);
        ListBoxNodes->Items->Add(region->description);
      } // for i - every region

      // update display
      if(ListBoxNodes->Count)
      {
        //draw last region
        ListBoxNodes->Selected[0] = true;
        UpdateRegionProp((TRegion *) (regions->Items[0]), true);
        RepaintRegion((TRegion *) (regions->Items[0]), true);
      }
    }
    catch (Exception &exception) {
      MessageDlg("Error opening project file:\n"+Filename+
                +"\n\n(invalid region section information)\n"+
                 "The file is either in unknown format or damaged\n",
                 mtError, TMsgDlgButtons() << mbOK, 0);
      //TODO:cleanup
    }
  }
  else //XML project file
  {
    OpenProjectFileXML(Filename);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TFormVideo::OpenProjectFileXML(AnsiString Filename)
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

  VidFilename = VAVideoFilename->Text;
  if (!Sysutils::FileExists(VidFilename)) {
    if (MessageDlg("Video file "+VidFilename+" not found. Do you want to locate the video file manually ?",
      mtError, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrYes )
      if(OpenDialogV->Execute())
        VidFilename = OpenDialogV->FileName;
  }
  if (Sysutils::FileExists(VidFilename)) {

    FormLog->Log("Loaded video file: "+VidFilename);

  }
  else
    FormLog->Log("Error opening video file: "+VidFilename);

  XMLProject->Active = false;
  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::ProcessNode(_di_IXMLNode Node)
{

}
//---------------------------------------------------------------------------

bool __fastcall TFormVideo::SaveProjectFile(AnsiString Filename, bool xml)
{
  TIniFile *prjfile;
  TShot *shot;
  TRegionData *data, *data2;

  // stop if playing
  if (TimerPlay->Enabled)
	  TimerPlay->Enabled = false;

  if (xml)
  {
    // .XML project file
    SaveProjectFileXML(Filename);
  }
  else
  {
    // .ANP project file (ini based)
    prjfile = new TIniFile(Filename);
    prjfile->WriteString( "Project", "Name", FormMain->ProjectName);
    prjfile->WriteInteger("Project", "Type", FormMain->ProjectType);
    prjfile->ReadString ( "Project", "Directory", FormMain->CurrentDir);
    prjfile->ReadInteger( "Project", "TimerInterval", TimerPlay->Interval);

    TRegion *region;
    prjfile->WriteString( "Video", "Title", VATitle->Text);
    prjfile->WriteDate(   "Video", "Date", VADateTime->DateTime);
    prjfile->WriteString( "Video", "Description", VADesc->Text);
    prjfile->WriteString( "Video", "Annotator", VAAnnotator->Text);
    prjfile->WriteString( "Video", "VideoFilename", VAVideoFilename->Text);
    prjfile->WriteString( "Video", "VideoDescFilename", VAAnnoFile->Text);
    prjfile->WriteInteger("Video", "MaxFrame", maxFrame);
    prjfile->WriteInteger("Video", "VideoDescriptorsNumber", VideoDescriptors->Count);
    if (VideoDescriptors->Count) {
      for(int i=0; i< VideoDescriptors->Count ; i++) {
        prjfile->WriteString("Video", "VideoDescriptor"+IntToStr(i), VideoDescriptors->Strings[i]);
      }
    }

    //export shots
    if (ListBoxShots->Count) {
      prjfile->WriteInteger("Shots", "Count", ListBoxShots->Count);
      for (int i=0; i < ListBoxShots->Count ; i++) {
        shot = (TShot *) (shots->Items[i]);
        prjfile->WriteString( "Shot#"+IntToStr(i), "Description", shot->description);
        prjfile->WriteInteger("Shot#"+IntToStr(i), "StartFrame", shot->startFrame);
        prjfile->WriteInteger("Shot#"+IntToStr(i), "EndFrame", shot->endFrame);
        prjfile->WriteInteger("Shot#"+IntToStr(i), "ShotDescriptorsNumber", shot->descriptors->Count);
        for (int k=0; k < shot->descriptors->Count; k++ ) {
          prjfile->WriteString("Shot#"+IntToStr(i), "ShotDescriptor"+IntToStr(k), shot->descriptors->Strings[k]);
        }
      }
    }

    //export regions
    if (ListBoxNodes->Count) {

      prjfile->WriteInteger("Regions", "Count", ListBoxNodes->Count);
      for (int i=0; i < ListBoxNodes->Count ; i++) {
        region = (TRegion *) (regions->Items[i]);
        prjfile->WriteString( "Region#"+IntToStr(i), "Description", region->description);
        prjfile->WriteInteger("Region#"+IntToStr(i), "StartFrame", region->startFrame);
        prjfile->WriteInteger("Region#"+IntToStr(i), "EndFrame", region->endFrame);
        prjfile->WriteString( "Region#"+IntToStr(i), "Color", ColorToString(region->color));
        prjfile->WriteInteger("Region#"+IntToStr(i), "RegionDescriptorsNumber", region->descriptors->Count);
        for (int m=0; m < region->descriptors->Count; m++) {
          prjfile->WriteString("Region#"+IntToStr(i), "RegionDescriptor"+IntToStr(m), region->descriptors->Strings[m]);
        }

        int dc=0;
        for (int k=0; k < region->region_data->Count; k++) {
          data = (TRegionData *) (region->region_data->Items[k]);
          // export only valid frames
          // k is the frame number
          if ( (k >= region->startFrame) && (k <= region->endFrame) )
          {
            __int64 range_start=k;
            __int64 range_end=k;
            // if same data for all frames put them as range "fs to fe"
            for (int k2 = range_start + 1; k2 <= region->endFrame; k2++ ) {
              //compare with frames ahead
              data2 = (TRegionData *) (region->region_data->Items[k2]);
              if ( (data->x == data2->x) && (data->y == data2->y) &&
                   (data->w == data2->w) && (data->h == data2->h))
                range_end=k2;
            } // for k2
            dc++;
            if (range_end != k) {
              // we have range of frames
              k = range_end; // skip ahead
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameStart", range_start);
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameEnd", range_end);
            }
            else {
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameStart", k);
              prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameEnd", k);
            }

            prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameX", data->x);
            prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameY", data->y);
            prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameW", data->w);
            prjfile->WriteInteger("Region#"+IntToStr(i)+"."+IntToStr(dc), "FrameDataFrameH", data->h);
          } // if

        } // for k
        prjfile->WriteInteger("Region#"+IntToStr(i), "RegionFrameDataNumber", dc);
      } // for i
    }

    FormLog->Log("project saved to ANP file "+Filename);
    delete prjfile;
  } // end of .ANP
}
//---------------------------------------------------------------------------

bool __fastcall TFormVideo::SaveProjectFileXML(AnsiString Filename)
{
  TShot *shot;
  TStringList *exp;
  TRegionData *data, *data2;

  exp = new TStringList;
  exp->Add("<?xml version=\"1.0\" ?>");
  exp->Add("<project>");
  exp->Add( "<name>"+ FormMain->ProjectName + "</name>");
  exp->Add( "<type>"+ IntToStr(FormMain->ProjectType) + "</type>");
  exp->Add( "<directory>"+ FormMain->CurrentDir + "</directory>");
  exp->Add( "<timerinterval>"+ IntToStr(TimerPlay->Interval) + "</timerinterval>");

  TRegion *region;
  exp->Add("<video>");
  exp->Add("<title>"+ VATitle->Text +"</title>");
  exp->Add("<date>"+ VADateTime->Date +"</date>" );
  exp->Add("<videoid>"+ VADesc->Text+ "</videoid>");
  exp->Add("<annotator>"+ VAAnnotator->Text+ "</annotator>");
  exp->Add("<videofilename>"+ VAVideoFilename->Text + "</videofilename>");
  exp->Add("<annotationfilename>"+ VAAnnoFile->Text+ "</annotationfilename>");
  exp->Add("<maxframe>"+ IntToStr(maxFrame) +"</maxframe>");
  //exp->Add("<VideoDescriptorsNumber>"+ IntToStr( VideoDescriptors->Count)+ "</VideoDescriptorsNumber>");
  if (VideoDescriptors->Count) {
    exp->Add("<videoannotation>");
    for(int i=0; i< VideoDescriptors->Count ; i++) {
      exp->Add("<term>"+VideoDescriptors->Strings[i]+"</term>");
    }
    exp->Add("</videoannotation>");
  }
  exp->Add("</video>");

  //export shots
  exp->Add("<shots>");
  if (ListBoxShots->Count) {
    exp->Add("<count>"+ IntToStr(ListBoxShots->Count)+ "</count>");
    for (int i=0; i < ListBoxShots->Count ; i++) {
      shot = (TShot *) (shots->Items[i]);
      exp->Add("<shot>");
      exp->Add("<shotID>"+ shot->description +"</shotID>");
      exp->Add("<startFrame>"+ IntToStr(shot->startFrame) +"</startFrame>");
      exp->Add("<endFrame>"+ IntToStr(shot->endFrame) +"</endFrame>");
      //exp->Add("<ShotDescriptorsNumber>"+ IntToStr(shot->descriptors->Count) + "</ShotDescriptorsNumber>");
      exp->Add("<shotannotation>");
      for (int k=0; k < shot->descriptors->Count; k++ ) {
        exp->Add("<term>"+ shot->descriptors->Strings[k] + "</term>");
      }
      exp->Add("</shotannotation>");
      exp->Add("</shot>");
    }
  }
  exp->Add("</shots>");

  //export regions
  exp->Add("<regions>");
  exp->Add("<count>"+ IntToStr(ListBoxNodes->Count) + "</count>");
  if (ListBoxNodes->Count) {
    for (int i=0; i < ListBoxNodes->Count ; i++) {
      exp->Add("<region>");
      region = (TRegion *) (regions->Items[i]);
      exp->Add("<regionid>"+ region->description + "</regionid>");
      exp->Add("<startframe>"+ IntToStr(region->startFrame) + "</startframe>" );
      exp->Add("<endframe>"+ IntToStr(region->endFrame) + "</endframe>");
      exp->Add("<color>"+ IntToStr(ColorToRGB(region->color))+"</color>" );
      //exp->Add("<RegionDescriptorsNumber>"+ IntToStr(region->descriptors->Count) + "</RegionDescriptorsNumber>" );

      exp->Add("<regionannotation>");
      for (int m=0; m < region->descriptors->Count; m++) {
        exp->Add("<term>" + region->descriptors->Strings[m] + "</term>" );
      }
      exp->Add("</regionannotation>");
      int dc=0;
      for (int k=0; k < region->region_data->Count; k++) {
        data = (TRegionData *) (region->region_data->Items[k]);
        // export only valid frames
        // k is the frame number
        if ( (k >= region->startFrame) && (k <= region->endFrame) )
        {
          __int64 range_start=k;
          __int64 range_end=k;
          // if same data for all frames put them as range "fs to fe"
          for (int k2 = range_start + 1; k2 <= region->endFrame; k2++ ) {
            //compare with frames ahead
            data2 = (TRegionData *) (region->region_data->Items[k2]);
            if ( (data->x == data2->x) && (data->y == data2->y) &&
                 (data->w == data2->w) && (data->h == data2->h))
              range_end=k2;
          } // for k2
          dc++;

          exp->Add("<locator>");
          if (range_end != k) {
            // we have range of frames
            k = range_end; // skip ahead
            exp->Add("<start>" + IntToStr(range_start) + "</start>" );
            exp->Add("<end>" + IntToStr(range_end) + "</end>" );
          }
          else {
            exp->Add("<start>" + IntToStr(k) + "</start>" );
            exp->Add("<end>" + IntToStr(k) + "</end>" );
          }

          exp->Add("<x>" + IntToStr(data->x) + "</x>" );
          exp->Add("<y>" + IntToStr(data->y) + "</y>" );
          exp->Add("<width>" + IntToStr(data->w) + "</width>" );
          exp->Add("<height>" + IntToStr(data->h) + "</height>" );
          exp->Add("</locator>");
        } // if
      } // for k
      exp->Add("</region>");
    } // for i
  }
  exp->Add("</regions>");

  exp->Add("</project>");
  exp->SaveToFile(Filename);
  FormLog->Log("project saved to XML file :"+Filename);
  exp->Clear();
  delete exp;

}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::BBWI(TObject *Sender)
{
  if (ListBoxNodes->ItemIndex >= 0) {
    TRegionData *a_data;
    TRegion *a_region;
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
    int v = a_data->w;
    v = v + 2;
    if (v < MIN_REGION) v = MIN_REGION;
    if (v > MAX_REGION) v = MAX_REGION;
    a_data->w = v;
    EditRW->Text = IntToStr(v);
    RepaintRegion(a_region);
    SetNodesVisible(true);
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::BBWD(TObject *Sender)
{
  if (ListBoxNodes->ItemIndex >= 0) {
    TRegionData *a_data;
    TRegion *a_region;
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
    int v = a_data->w;
    v = v - 2;
    if (v < MIN_REGION) v = MIN_REGION;
    if (v > MAX_REGION) v = MAX_REGION;
    a_data->w = v;
    EditRW->Text = IntToStr(v);
    RepaintRegion(a_region);
    SetNodesVisible(true);
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::BBHI(TObject *Sender)
{
  if (ListBoxNodes->ItemIndex >= 0) {
    TRegionData *a_data;
    TRegion *a_region;
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
    int v = a_data->h;
    v = v + 2;
    if (v < MIN_REGION) v = MIN_REGION;
    if (v > MAX_REGION) v = MAX_REGION;
    a_data->h = v;
    EditRH->Text = IntToStr(v);
    RepaintRegion(a_region);
    SetNodesVisible(true);
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormVideo::BBHD(TObject *Sender)
{
  if (ListBoxNodes->ItemIndex >= 0) {
    TRegionData *a_data;
    TRegion *a_region;
    a_region = (TRegion *) (regions->Items[ListBoxNodes->ItemIndex]);
    a_data = (TRegionData *) (a_region->region_data->Items[currentFrame]);
    int v = a_data->h;
    v = v - 2;
    if (v < MIN_REGION) v = MIN_REGION;
    if (v > MAX_REGION) v = MAX_REGION;
    a_data->h = v;
    EditRH->Text = IntToStr(v);
    RepaintRegion(a_region);
    SetNodesVisible(true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormVideo::bnt1Click(TObject *Sender)
{
  TreeXML->SaveToFile("c:\\treenodes.txt");
}
//---------------------------------------------------------------------------

//TODO: check if needed: disable text edit controls when in edit mode (ActionRecord->Checked) ?
// latest XML info : http://www.w3.org/TR/xml/


