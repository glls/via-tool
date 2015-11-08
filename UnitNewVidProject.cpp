//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitNewVidProject.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNewVid *FormNewVid;
//---------------------------------------------------------------------------
__fastcall TFormNewVid::TFormNewVid(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormNewVid::ButtonOKClick(TObject *Sender)
{
  FormMain->ProjectName = teName->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormNewVid::FormShow(TObject *Sender)
{
  teName->Text = "VideoProject";
  teName->SelectAll();
  teFile->Text = "";
  ActiveControl = teName;
}
//---------------------------------------------------------------------------

void __fastcall TFormNewVid::btnFileClick(TObject *Sender)
{
	if (OpenDialogV->Execute()) {
  	teFile->Text = OpenDialogV->FileName;
  }
}
//---------------------------------------------------------------------------

