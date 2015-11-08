//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitAbout.h"
#include "UnitHelp.h"
#include "UnitLog.h"
#include "UnitImport.h"
#include "UnitNewImgProject.h"
#include "UnitOptions.h"
#include "UnitNewVidProject.h"
#include "UnitMerge.h"
#include "UnitFormWait.h"
#include "UnitSelectMPEG7.h"
#include "UnitFormImage.h"
#include "UnitFormVideo.h"

#include <float.h>
#include <stdio.h>
#include <mem.h>
#include <string.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain *FormMain;
//---------------------------------------------------------------------------
template <class T> T max(T x, T y) {
	return (x > y) ? x : y;
};

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	// control floating point exceptions
  _control87(MCW_EM, MCW_EM);

	//VCL
  //PanelImg->DoubleBuffered = true;
  KeyPreview = true;
  PenWidth = 2;
  VideoInterval = 100; //ms
  lblVersion->Caption = "version 1.0s";
  //Directories
  String curdir = ExtractFilePath(Application->ExeName);
  Dir_AceToolBox = curdir+"aceToolbox";
  Dir_StoredData = curdir+"storedBOEMIEdata";
  Dir_SegTools = curdir+"segtools";
  Sysutils::ForceDirectories(Dir_AceToolBox);
  Sysutils::ForceDirectories(Dir_StoredData);
  Sysutils::ForceDirectories(Dir_SegTools);

  //prepare controls
  PageControl->ActivePage = TabSheetLogo;
  VideoPrjControls(false);
  ImagePrjControls(false);

  ReadConfig();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
  WriteConfig();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	MENUS
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuExportImgTextClick(TObject *Sender)
{
  FormImage->ExportText();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuExitClick(TObject *Sender)
{
  // TODO: ask for exit if data not saved (canClose)
  SaveChanges();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuCopyFrameClick(TObject *Sender)
{
  FormVideo->CopyFrameClip();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::MenuGotoFrameClick(TObject *Sender)
{
  FormVideo->VideoGotoFrame(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuTimeCodeClick(TObject *Sender)
{
  FormVideo->VideoTimeCode(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuNextIFrameClick(TObject *Sender)
{
  FormVideo->VideoNextIFrame(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuPreviousIFrameClick(TObject *Sender)
{
  FormVideo->VideoPrevIFrame(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuStartClick(TObject *Sender)
{
  FormVideo->VideoStart(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuEndClick(TObject *Sender)
{
  FormVideo->VideoEnd(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuAboutClick(TObject *Sender)
{
  TFormAbout *formA;
  formA = new TFormAbout(Application->MainForm);
	formA->ShowModal();
  delete formA;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuContentsClick(TObject *Sender)
{
  FormHelp->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuLogClick(TObject *Sender)
{
  FormLog->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuOpenImageClick(TObject *Sender)
{
  if (FormImage->OpenDialogImg->Execute()) {
    FormImage->OpenImage(FormImage->OpenDialogImg->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuOptionsClick(TObject *Sender)
{
	if (FormOptions->ShowModal() == mrOk) {
    WriteConfig();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuNewIAClick(TObject *Sender)
{
  // New Image Annotation
  SaveChanges();

	if (FormNewImg->ShowModal() == mrOk) {

    FormMain->ProjectName = "";
    if (FormMain->ProjectName.IsEmpty())
      FormMain->ProjectName = "Noname";
    Caption = "VIA - " + ProjectName;

	  VideoPrjControls(false);
    ImagePrjControls(true);

    if (FormImage) {
      FormImage->Hide();
      delete FormImage;
      FormImage = NULL;
    }
    FormImage = new TFormImage(Application);
    FormImage->Parent = TabSheetImage;
    FormImage->ImgFilename = FormNewImg->teFile->Text;

    ProjectType = 1;
    if (Sysutils::FileExists(FormImage->ImgFilename)) {
      FormImage->OpenImage(FormImage->ImgFilename);
    }
    else {
      //image not found /cant load
      //TODO: it
      FormImage->ImageAn->Bitmap->Clear();
    }

    FormImage->Show();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuNewVAClick(TObject *Sender)
{
  // New Video Annotation
  SaveChanges();

	if (FormNewVid->ShowModal() == mrOk) {

    if (FormMain->ProjectName.IsEmpty())
      FormMain->ProjectName = "Noname";
    Caption = "VIA - " + ProjectName;

    ImagePrjControls(false);
  	VideoPrjControls(true);

    if (FormVideo) {
      FormVideo->Hide();
      delete FormVideo;
      FormVideo = NULL;
    }
    FormVideo = new TFormVideo(Application);
    FormVideo->Parent = TabSheetVideo;
    FormVideo->VidFilename = FormNewVid->teFile->Text;

    ProjectType = 0;
    FormVideo->OpenVideoFile(FormVideo->VidFilename);
    //FormImport->MLCI->Clear();

    FormVideo->Show();
  }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//    ACTIONS
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionRecordExecute(TObject *Sender)
{
	//record mode
  ActionRecord->Checked = !ActionRecord->Checked;
  FormVideo->LabelRecord->Visible = ActionRecord->Checked;
  FormVideo->LabelLocked->Visible = !ActionRecord->Checked;
  //RecordModeMI->Checked = ActionRecord->Checked;
  //CheckBoxRecord->Checked = ActionRecord->Checked;
  ActionBBWI->Enabled = ActionRecord->Checked;
  ActionBBWD->Enabled = ActionRecord->Checked;
  ActionBBHI->Enabled = ActionRecord->Checked;
  ActionBBHD->Enabled = ActionRecord->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionPlayExecute(TObject *Sender)
{
	//play mode
  if ( FormVideo == 0 ) return;
 	if ( FormVideo->CheckVideoLoaded() ) {
	  ActionPlay->Checked = !ActionPlay->Checked;
  }
  else
	  ActionPlay->Checked = false;

 	FormVideo->TimerPlay->Enabled = ActionPlay->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionForwardExecute(TObject *Sender)
{
  FormVideo->VideoFWD(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionBackwardExecute(TObject *Sender)
{
  FormVideo->VideoREW(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionExportXMLTrajExecute(TObject *Sender)
{
  FormVideo->ExportXMLTraj(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionOpenProjectExecute(TObject *Sender)
{
  // open project
  bool xml;
  int ProjectType_minor = 0;

  if(OpenPrjDialog->Execute())
  {
    if (UpperCase(ExtractFileExt(OpenPrjDialog->FileName)) == ".ANP")
      xml=false;
    else if (UpperCase(ExtractFileExt(OpenPrjDialog->FileName)) == ".XML")
      xml=true;
    else
      return;
    //TODO: display error ?

    if ( !xml ) // ANP project file
    {

      TIniFile *prjfile;
      prjfile = new TIniFile(OpenPrjDialog->FileName);
      // check if video or image project
      // 0 video , 1 image
      ProjectType = prjfile->ReadInteger("Project", "Type", 0);
      ProjectName = prjfile->ReadString ("Project", "Name", "");
      CurrentDir = prjfile->ReadString ("Project", "Directory", "");
      delete prjfile;
    }
    else if (xml) // XML project file
    {
      // identify XML project
      ProjectType = 0;
      ProjectName = "";
      CurrentDir = "";
      //DONE: get ProjectType from XML
      _di_IXMLNode Node;
      XMLProject->FileName = OpenPrjDialog->FileName;
      XMLProject->Active = true;

      if (XMLProject->ChildNodes->First() != NULL) {
        //check XML type;
        Node = XMLProject->DocumentElement;
        if (Node->LocalName == WideString("project")) {
          // VIA XML project
          ProjectType_minor = 1;
          Node = XMLProject->DocumentElement->ChildNodes->First();
          while (Node != NULL) {
            if (Node->LocalName == WideString("name")) {
              ProjectName = Node->Text;
            }
            else if (Node->LocalName == WideString("type")) {
              ProjectType = StrToInt(Node->Text);
            }
            else if (Node->LocalName == WideString("directory")) {
              CurrentDir = Node->Text;
            }
            Node = Node->NextSibling();
          }
        }
        else if (Node->LocalName == WideString("annotation")) {
          // Labelme Web annotation
          ProjectType = 1;
          ProjectType_minor = 2;
          //
          Node = XMLProject->DocumentElement->ChildNodes->First();
          while (Node != NULL) {
            if (Node->LocalName == WideString("filename")) {
              ProjectName = Node->Text;
            }
            else if (Node->LocalName == WideString("directory")) {
              CurrentDir = Node->Text;
            }
            Node = Node->NextSibling();
          }
          //
        }
        else {
          // incortrect XML file type
          MessageDlg("XMLDocument: invalid file", mtError, TMsgDlgButtons() << mbOK, 0);
          XMLProject->Active = false;
          return;
        }
      }
      else {
        MessageDlg("XMLDocument: NULL value", mtError, TMsgDlgButtons() << mbOK, 0);
        XMLProject->Active = false;
        return;
      }

      XMLProject->Active = false;
      //
    }
  }
  else
    return;

  Caption = "VIA - " + ProjectName;

  // load video project by default.. for older VIA versions.
  //====================== video ======================
  if (ProjectType == 0) {
   if (FormVideo) {
      FormVideo->Hide();
      delete FormVideo;
      FormVideo = NULL;
    }
    FormVideo = new TFormVideo(Application);
    FormVideo->Parent = TabSheetVideo;
    ImagePrjControls(false);
    VideoPrjControls(true);
    FormVideo->OpenProjectFile(OpenPrjDialog->FileName, xml);
    FormVideo->Show();
  }
  else {
    //====================== image ======================
    if (FormImage) {
      FormImage->Hide();
      delete FormImage;
      FormImage = NULL;
    }
    FormImage = new TFormImage(Application);
    FormImage->Parent = TabSheetImage;
	  VideoPrjControls(false);
		ImagePrjControls(true);
    FormImage->OpenProjectFile(OpenPrjDialog->FileName, xml, ProjectType_minor);
    FormImage->Show();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionSaveProjectExecute(TObject *Sender)
{
  SavePrjDialog->FileName = ProjectName;
  if (SavePrjDialog->Execute()) {
    if (Sysutils::FileExists(SavePrjDialog->FileName)) {
      if (MessageDlg("File already exists, do you want to replace it?",
        mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrNo )
        return;
      DeleteFile(SavePrjDialog->FileName);
    }
    if ( ProjectType == 1) {
      FormImage->SaveProjectFile(SavePrjDialog->FileName, (SavePrjDialog->FilterIndex==2));
    }
    else {
      FormVideo->SaveProjectFile(SavePrjDialog->FileName, (SavePrjDialog->FilterIndex==2));
    }
  }
  else
    return;

  Caption = "VIA - " + ProjectName;
  MessageDlg("Project \""+SavePrjDialog->FileName+"\" saved.", mtInformation, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionCloseExecute(TObject *Sender)
{
  if (SaveChanges()) {

    if (FormImage) {
      FormImage->Hide();
      delete FormImage;
      FormImage = NULL;
    }
    else if (FormVideo) {
      FormVideo->Hide();
      delete FormVideo;
      FormVideo = NULL;
    }
    FormLog->Log("Project Closed");
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionOpenVideoExecute(TObject *Sender)
{
	if (FormVideo->ListBoxNodes->Count)
  	if (MessageDlg("Are you sure you want to load another video file ? All region data will be lost!",
		    mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrNo )
    	return;

  //OpenDialogV->Filter = mme_app.vfapi.info.cFileType;
  if ( FormVideo->OpenDialogV->Execute() )
    FormVideo->OpenVideoFile(FormVideo->OpenDialogV->FileName);
}
//---------------------------------------------------------------------------

// move to forms
bool __fastcall TFormMain::XML2Tree(TTreeView *TreeView, TXMLDocument *XMLDoc, AnsiString filename)
{
  _di_IXMLNode jNode;

  TreeView->Items->Clear();
  XMLDoc->FileName = filename;
  XMLDoc->Active = true;

  if (XMLDoc->ChildNodes->First() == NULL) {
    MessageDlg("XMLDocument: NULL value", mtError, TMsgDlgButtons() << mbOK, 0);
    return false;
  }

  jNode = XMLDoc->DocumentElement->ChildNodes->First();

  while (jNode != NULL) {
    ProcessNode(TreeView, jNode, NULL);
    jNode = jNode->NextSibling();
  }

  XMLDoc->Active = false;

  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ProcessNode(TTreeView *TreeView, _di_IXMLNode Node, TTreeNode *tn)
{
  _di_IXMLNode cNode;

  if (Node == NULL)
    return;
/*
 	if ( Node->Attributes["rdf:ID"] )
    tn = TreeXML->Items->AddChild(tn, Node->Attributes["rdf:ID"]);
  else if ( Node->Attributes["rdf:resource"] != NULL )
    tn = TreeXML->Items->AddChild(tn, Node->Attributes["rdf:resource"]);
  else //if ( Node->NodeName != "#text" )
*/

  if ( Node->HasAttribute("rdf:ID") ) {
    // add only Class -> rdf:ID
    if (Node->LocalName == WideString("Class"))
  	  tn = TreeView->Items->AddChild(tn, Node->Attributes["rdf:ID"]);
  }
	/*else if ( Node->HasAttribute("rdf:about") ) {
    tn = TreeView->Items->AddChild(tn, Node->LocalName + " " + Node->Attributes["rdf:about"]);
  }
  else {
    if (Node->LocalName != WideString("subClassOf") &&
        Node->LocalName != WideString("subPropertyOf")
    )
  	  tn = TreeView->Items->AddChild(tn, Node->LocalName);
  }
  */
  cNode = Node->ChildNodes->First();
  while (cNode) {
    ProcessNode(TreeView, cNode, tn);
    cNode = cNode->NextSibling();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if ( Key==VK_ESCAPE ) {
    ActionRecord->Checked = false;
    ActionPlay->Checked = false;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::VideoPrjControls(bool enable)
{
  MenuVideo->Enabled = enable;
  MenuEditVideo->Enabled = enable;
  TabSheetVideo->Enabled = enable;
  TabSheetVideo->Visible = enable;
  TabSheetVideo->TabVisible = enable;
  ActionImportDesc->Enabled = enable;
  ActionClose->Enabled = enable;
  ActionSaveProject->Enabled = enable;

  if (enable)
    PageControl->ActivePage = TabSheetVideo;

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ImagePrjControls(bool enable)
{
  MenuImage->Enabled = enable;
  TabSheetImage->Enabled = enable;
  TabSheetImage->Visible = enable;
  TabSheetImage->TabVisible = enable;
  ActionImportDesc->Enabled = enable;
  ActionClose->Enabled = enable;
  ActionSaveProject->Enabled = enable;

  if (enable)
    PageControl->ActivePage = TabSheetImage;

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MenuImageExtractClick(TObject *Sender)
{
  FormImage->ExtractMpeg7(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEventsException(TObject *Sender,
      Exception *E)
{
  FormLog->Log( String(__LINE__) + " Exception :: " + E->Message);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionImportXMLExecute(TObject *Sender)
{
  FormVideo->ImportXML(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionExportXMLExecute(TObject *Sender)
{
  FormVideo->ExportXML(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionImportDescExecute(TObject *Sender)
{
  if (OpenDialogDesc->Execute()) {
    if (ProjectType == 0) { //video
      //if (OpenDialogDesc->FilterIndex == 1) { //txt
        FormVideo->TreeXML->Items->Clear();
        FormVideo->TreeXML->LoadFromFile(OpenDialogDesc->FileName);
      /*}
      else { //xml : disabled
        XML2Tree(FormVideo->TreeXML, XMLDocument, OpenDialogDesc->FileName);
      }
      */
      FormVideo->VAAnnoFile->Text = OpenDialogDesc->FileName;
    }
    else { // image
      //if (OpenDialogDesc->FilterIndex == 1) { //txt
        FormImage->TreeXMLImg->Items->Clear();
        FormImage->TreeXMLImg->LoadFromFile(OpenDialogDesc->FileName);
      /*}
      else { //xlm
        XML2Tree(FormImage->TreeXMLImg, XMLDocument, OpenDialogDesc->FileName);
      }*/
      FormImage->IAAnnoFile->Text = OpenDialogDesc->FileName;
    }
    FormLog->Log("Opened descriptors file: "+OpenDialogDesc->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionBBWIExecute(TObject *Sender)
{
  // bound box width increase
  if (FormVideo) {
    FormVideo->BBWI(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionBBWDExecute(TObject *Sender)
{
  // bound box width decrease
  if (FormVideo) {
    FormVideo->BBWD(Sender);
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionBBHIExecute(TObject *Sender)
{
  // bound box heigth increase
  if (FormVideo) {
    FormVideo->BBHI(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionBBHDExecute(TObject *Sender)
{
  // bound box height decrease
  if (FormVideo) {
    FormVideo->BBHD(Sender);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::SaveChanges(void)
{
  if (FormImage || FormVideo) {
    if (MessageDlg("Do you want to save the project? All data will be lost!",
        mtConfirmation, TMsgDlgButtons() << mbYes <<mbNo, 0) == mrNo ) {

      return false;
    }
    else {

      //TODO: check if save OK
      if (FormImage) {
        FormImage->SaveProjectFile(ProjectName+".ANP", false);
      }
      else if (FormVideo) {
        FormVideo->SaveProjectFile(ProjectName+".ANP", false);
      }
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ReadConfig()
{
  TIniFile *ini;
  ini = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );

  Top     =  ini->ReadInteger( "Form", "Top", 100 );
  Left    =  ini->ReadInteger( "Form", "Left", 100 );
  Width   =  ini->ReadInteger( "Form", "Width", 800 );
  Height  =  ini->ReadInteger( "Form", "Height", 710 );
  ini->ReadBool( "Form", "InitMax", false ) ? WindowState = wsMaximized : WindowState = wsNormal;
  PenWidth =        ini->ReadInteger( "Main", "PenWidth", 2 );
  VideoInterval =   ini->ReadInteger( "Main", "VideoInterval", 100);
  RenumberSort =    ini->ReadBool(    "Main", "RenumberSort", true );
  Dir_AceToolBox =  ini->ReadString(  "Main", "Dir_AceToolBox", Dir_AceToolBox );
  Dir_SegTools =    ini->ReadString(  "Main", "Dir_SegTools", Dir_SegTools);
  Dir_StoredData =  ini->ReadString(  "Main", "Dir_StoredData", Dir_StoredData);
  SegExe =          ini->ReadString(  "Main", "SegExe", "itiseg.exe");
  SegOptions =      ini->ReadString(  "Main", "SegOptions", "%d %d %f 8 2 1 1 0 10");

  delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::WriteConfig()
{
  TIniFile *ini;
  ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ) );

  ini->WriteInteger( "Form", "Top", Top );
  ini->WriteInteger( "Form", "Left", Left );
  ini->WriteInteger( "Form", "Width", Width );
  ini->WriteInteger( "Form", "Height", Height );
  ini->WriteBool   ( "Form", "InitMax", WindowState == wsMaximized );
  ini->WriteInteger( "Main", "PenWidth", PenWidth );
  ini->WriteInteger( "Main", "VideoInterval", VideoInterval );
  ini->WriteBool(    "Main", "RenumberSort", RenumberSort );
  ini->WriteString(  "Main", "Dir_AceToolBox", Dir_AceToolBox);
  ini->WriteString(  "Main", "Dir_SegTools", Dir_SegTools);
  ini->WriteString(  "Main", "Dir_StoredData",Dir_StoredData);

  delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExportTextData1Click(TObject *Sender)
{
  FormVideo->ExportText(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::lblHomeClick(TObject *Sender)
{
	ShellExecute(Handle, "open", lblHome->Caption.c_str(),
    NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

