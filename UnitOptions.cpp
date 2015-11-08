//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitOptions.h"
#include "UnitMain.h"

#include <FileCtrl.hpp>
const SELDIRHELP = 1000;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormOptions *FormOptions;
//---------------------------------------------------------------------------

__fastcall TFormOptions::TFormOptions(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::btnOKClick(TObject *Sender)
{
  FormMain->VideoInterval = StrToIntDef(EditVideoInt->Text, 100);
	FormMain->PenWidth = StrToIntDef(EditPenWidth->Text,2);
  FormMain->Dir_AceToolBox = EditDirAce->Text;
  FormMain->Dir_SegTools = EditDirSeg->Text;
  FormMain->Dir_StoredData = EditDirOut->Text;
  FormMain->SegExe =  EditSegExe->Text;
  FormMain->SegOptions = EditSegOptions->Text;

  FormMain->ActionForward->ShortCut = HotKeyFrameFWD->HotKey;
  FormMain->ActionBackward->ShortCut = HotKeyFrameREW->HotKey;
  FormMain->ActionBBWI->ShortCut = HotKeyBBWI->HotKey;
  FormMain->ActionBBWD->ShortCut = HotKeyBBWD->HotKey;
  FormMain->ActionBBHI->ShortCut = HotKeyBBHI->HotKey;
  FormMain->ActionBBHD->ShortCut = HotKeyBBHD->HotKey;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormShow(TObject *Sender)
{
  EditDirAce->Text = FormMain->Dir_AceToolBox;
  EditDirSeg->Text = FormMain->Dir_SegTools;
  EditDirOut->Text = FormMain->Dir_StoredData;
  EditPenWidth->Text = IntToStr(FormMain->PenWidth);
  EditVideoInt->Text = IntToStr(FormMain->VideoInterval);
  chkbxRenumberSort->Checked = FormMain->RenumberSort;
  EditSegExe->Text = FormMain->SegExe;
  EditSegOptions->Text = FormMain->SegOptions;

  HotKeyFrameFWD->HotKey = FormMain->ActionForward->ShortCut;
  HotKeyFrameREW->HotKey = FormMain->ActionBackward->ShortCut;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::btnDirAceClick(TObject *Sender)
{
  AnsiString Dir;
  Dir = EditDirAce->Text;
  if (SelectDirectory("Select directory", "", Dir))
    EditDirAce->Text = Dir;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::btnDirOutClick(TObject *Sender)
{
  AnsiString Dir;
  Dir = EditDirOut->Text;
  if (SelectDirectory("Select directory", "", Dir))
    EditDirOut->Text = Dir;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::btnDirSegClick(TObject *Sender)
{
  AnsiString Dir;
  Dir = EditDirSeg->Text;
  if (SelectDirectory("Select directory", "", Dir))
    EditDirSeg->Text = Dir;
}
//---------------------------------------------------------------------------

