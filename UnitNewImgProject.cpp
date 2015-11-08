//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitNewImgProject.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNewImg *FormNewImg;
//---------------------------------------------------------------------------
__fastcall TFormNewImg::TFormNewImg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormNewImg::ButtonOKClick(TObject *Sender)
{
  FormMain->ProjectName = teName->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormNewImg::FormShow(TObject *Sender)
{
  teName->Text = "ImageProject";
  teName->SelectAll();
  teFile->Text = "";
  ActiveControl = teName;
}
//---------------------------------------------------------------------------

void __fastcall TFormNewImg::btnFileClick(TObject *Sender)
{
	if (OpenDialogImg->Execute()) {
  	teFile->Text = OpenDialogImg->FileName;
	}
}
//---------------------------------------------------------------------------

