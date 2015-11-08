//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitImport.h"
#include "UnitMain.h"
#include "UnitUtils.h"
#include "UnitFormVideo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormImport *FormImport;
//---------------------------------------------------------------------------
__fastcall TFormImport::TFormImport(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool __fastcall TFormImport::TrajXML2Tree(AnsiString filename)
{
  _di_IXMLNode jNode;
  AnsiString as;

  XMLTrajTree->Items->Clear();

  try {
	  XMLTraj->FileName = filename;
  	XMLTraj->Active = true;
  }
  catch(...)
  {
		StaticTextE->Visible = true;
    return false;
  }

  if (XMLTraj->ChildNodes->First() == NULL) {
    StaticTextE->Visible = true;
    return false;
  }
  jNode = XMLTraj->DocumentElement;

  as = jNode->NodeName;

  if (as != "DOCANALYSIS") {
  	//
    StaticTextE->Visible = true;
  	return false;
  }

  while (jNode != NULL) {
    TrajProcessNode(jNode, NULL);
    jNode = jNode->NextSibling();
  }

  XMLTraj->Active = false;
  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::TrajProcessNode(_di_IXMLNode Node, TTreeNode *tn)
{
  _di_IXMLNode cNode;
  AnsiString s;
  int count;

  if (Node == NULL) return;
  StaticTextNode->Caption = "Nodes : "+IntToStr(XMLTrajTree->Items->Count);

	//s = Node->LocalName;
  s = Node->NodeName;
  if (Node->IsTextElement)
  	s =s +"," + Node->Text;
	else
    cNode = Node->ChildNodes->First();

  // get attributes
  count = Node->AttributeNodes->Count;
  if (count) {
    if ( Node->HasAttribute("TYPE") )
	  	s = s +"="+ Node->Attributes["TYPE"];
  }
  tn = XMLTrajTree->Items->AddChild(tn, s);

  while (cNode) {
    TrajProcessNode(cNode, tn);
    cNode = cNode->NextSibling();
  }
};
//---------------------------------------------------------------------------

void __fastcall TFormImport::ButtonParseClick(TObject *Sender)
{
  TTreeNode *tn_trajec, *tn_pos, *tn_box, *tn_prop;
  TTreeNode *tn_MLCI_LIST, *tn_MLCI;
  int count, frame, top, left, width, height, pos, regions_parsed;
  AnsiString region_name, info, check, as;
  bool firstframe;
  int ColorIndex = 9;

  regions_parsed = 0;

  TRegionData *data, *data2;
  TRegion *region;

  try {

    count = XMLTrajTree->Items->Count;

    if (count) {

/*
  <MLCI_LIST>
   <MLCI>
    <ID>mlc1</ID>
    <ELEMENTREF>seg0</ELEMENTREF>
    <LABEL>Pole Vault</LABEL>
    <CONFIDENCE>0.996</CONFIDENCE>
   </MLCI>
  </MLCI_LIST>
*/
      // Get all in MLCI and add them to string list for later (save)
      tn_MLCI_LIST = XMLTrajTree->Items->GetFirstNode();
      // get "MLCI_LIST"
      while ( tn_MLCI_LIST ) {
	      if (tn_MLCI_LIST->Text == "MLCI_LIST" )
        	break;
        tn_MLCI_LIST = tn_MLCI_LIST->GetNext();
      }

      // get <MLCI>
      tn_MLCI_LIST = tn_MLCI_LIST->getFirstChild();
      MLCI->Clear();

      while (tn_MLCI_LIST)
      {
        tn_MLCI = tn_MLCI_LIST->getFirstChild();
        while(tn_MLCI) {
          as = tn_MLCI->Text;
          MLCI->Add(as);
          tn_MLCI = tn_MLCI->getNextSibling();
        }
        tn_MLCI_LIST = tn_MLCI_LIST->getNextSibling();
      }

      // MLCI end

      // goto start again
      tn_trajec = XMLTrajTree->Items->GetFirstNode();
      // get "TRAJECTORYSET"
      while ( tn_trajec ) {
	      if (tn_trajec->Text == "TRAJECTORYSET" )
        	break;
        tn_trajec = tn_trajec->GetNext();
      }

      // get <TRAJECTORY>
     	tn_trajec = tn_trajec->getFirstChild();

      while (tn_trajec) {

        width = 0;
        left = 0;
        top = 0;
        height= 0;
        firstframe = true;
        // get first child
        tn_pos = tn_trajec->getFirstChild();

//        Memo1->Lines->Add("<TRAJECTORY>");

        if (tn_pos->Text.AnsiPos("ID") == 1) {

          as = tn_pos->Text;
          region_name = MidStr(as, 4, as.Length()-3);
//          Memo1->Lines->Add(as); // print ID
          regions_parsed++;
          StaticTextRegions->Caption = "Regions : "+IntToStr(regions_parsed);
          //add region (main)
          //
          tn_pos = tn_pos->getNextSibling();

          // get region properties
          while (tn_pos) {

//            Memo1->Lines->Add("<POS>");
            // get BOX
            check = tn_pos->Text;
            if (check == "POS=BBOXSEQUENCE") {

              tn_box = tn_pos->getFirstChild();

              while (tn_box) {

//                Memo1->Lines->Add("\t<BOX>");
                // get properties
                tn_prop = tn_box->getFirstChild();

                while (tn_prop) {

                  if ( (pos = tn_prop->Text.AnsiPos("FRAME,")) == 1) {
                    as = StringReplace(tn_prop->Text, "FRAME,", "", TReplaceFlags() << rfIgnoreCase);
                    frame = StrToIntDef(as, 0);
                  }
                  if (tn_prop->Text.AnsiPos("WIDTH,") == 1) {
                    as = StringReplace(tn_prop->Text, "WIDTH,", "", TReplaceFlags() << rfIgnoreCase);
                    width = StrToIntDef(as, 0);
                  }
                  if (tn_prop->Text.AnsiPos("HEIGHT,") == 1) {
                    as = StringReplace(tn_prop->Text, "HEIGHT,", "", TReplaceFlags() << rfIgnoreCase);
                    height = StrToIntDef(as, 0);                }
                  if (tn_prop->Text.AnsiPos("TOP,") == 1) {
                    as = StringReplace(tn_prop->Text, "TOP,", "", TReplaceFlags() << rfIgnoreCase);
                    top = StrToIntDef(as, 0);                }
                  if (tn_prop->Text.AnsiPos("LEFT,") == 1) {
                    as = StringReplace(tn_prop->Text, "LEFT,", "", TReplaceFlags() << rfIgnoreCase);
                    left = StrToIntDef(as, 0);
                  }
                  // TODO: save INFO (extra from XML nodes)
                  //Memo1->Lines->Add("----------[PROPERTY]="+tn_prop->Text);
                  tn_prop = tn_prop->getNextSibling();
                }
                as.printf("\t\tframe=%d left=%d top=%d w=%d h=%d", frame, left, top, width, height);

                if (firstframe) {
                  // add region
                  int c=0, d=0;
                  AnsiString targdesc;
                  // c = number of regions
                  // while region exists
                  region = new TRegion;
                  region->region_data = new TList;
                  region->box = new TShape(FormMain);
                  region->descriptors = new TStringList;

                  region->box->Parent = FormVideo->PanelImg;
                  region->box->Visible = false;
                  region->description = region_name;
                  region->startFrame = frame;
                  region->endFrame = frame;
                  region->color = mcolors[ColorIndex++]; //TODO: check
                  if (ColorIndex > 17) ColorIndex = 0;
                  region->box->Shape = stRectangle;
                  region->box->Brush->Style = bsClear;
                  region->box->Pen->Color = region->color;
                  region->box->OnMouseDown = FormVideo->ShapeAMouseDown;
                  region->box->OnMouseMove = FormVideo->ShapeAMouseMove;
                  region->box->OnMouseUp = FormVideo->ShapeAMouseUp;
                  region->box->Constraints->MaxHeight = MAX_REGION;
                  region->box->Constraints->MaxWidth = MAX_REGION;
                  region->box->Constraints->MinHeight = MIN_REGION;
                  region->box->Constraints->MinWidth = MIN_REGION;

                  //set per frame data for all frames
                  for (int i=0; i <= FormVideo->maxFrame; i++) {
                    data = new TRegionData;
                    data->x = DEF_X;
                    data->y = DEF_Y;
                    data->w = DEF_W;
                    data->h = DEF_H;
                    region->region_data->Add(data);
                  }
                  firstframe = false;
                } // end if firstframe

                // current frame = frame
                region->endFrame = frame;
                // check if region->region_data->Items[frame] exists
                // add current frame data
                if (frame <= FormVideo->maxFrame ) {
                	// skip frame if > maxFrame
                  data = (TRegionData *) (region->region_data->Items[frame]);
                  data->x = left;
                  data->y = top;
                  data->w = width;
                  data->h = height;
                  //region->region_data->Add(data);
                }

                tn_box = tn_box->getNextSibling();
//                Memo1->Lines->Add("\t</BOX>");
              } // </BOX>

              Application->ProcessMessages();

            } // IF <POS>

            tn_pos = tn_pos->getNextSibling();
//            Memo1->Lines->Add("</POS>");
          } // while (tn_pos)
        } // if ID
        tn_trajec = tn_trajec->getNextSibling();
//        Memo1->Lines->Add("</TRAJECTORY>");

        FormVideo->regions->Add(region);
        FormVideo->RepaintRegion(region);
        FormVideo->ListBoxNodes->Items->Add(region->description);

      } // </TRAJECTORY>
    } // if Count
  } // try
  catch(...)
  {
		StaticTextE->Visible = true;
  }

  // update display
  if(FormVideo->ListBoxNodes->Count)
  {
  	//draw last region
	  FormVideo->ListBoxNodes->Selected[0] = true;
    FormVideo->UpdateRegionProp((TRegion *) (FormVideo->regions->Items[0]), true);
    FormVideo->RepaintRegion((TRegion *) (FormVideo->regions->Items[0]), true);
  }
	ButtonOK->Enabled = true;
  Cursor = crDefault;
  StaticTextI->Cursor = crDefault;
  StaticTextNode->Cursor = crDefault;
  StaticTextRegions->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::FormShow(TObject *Sender)
{
#ifdef _DEBUG
	XMLTrajTree->Visible = true;
	Memo1->Visible = true;
  ButtonParse->Visible = true;
#endif
  StaticTextE->Visible = false;
  StaticTextNode->Caption = "Nodes : 0";
  StaticTextRegions->Caption = "Regions : 0";
  ButtonOK->Enabled = false;
  Cursor = crHourGlass;
  StaticTextI->Cursor = crHourGlass;
  StaticTextNode->Cursor = crHourGlass;
  StaticTextRegions->Cursor = crHourGlass;
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::ButtonOKClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	Application->ProcessMessages();
  TrajXML2Tree(FileName);
  Application->ProcessMessages();
  ButtonParseClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::FormCreate(TObject *Sender)
{
  MLCI = new TStringList;
}
//---------------------------------------------------------------------------

void __fastcall TFormImport::FormDestroy(TObject *Sender)
{
  delete MLCI;
}
//---------------------------------------------------------------------------

