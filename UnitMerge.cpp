//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMerge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMerge *FormMerge;
//---------------------------------------------------------------------------
__fastcall TFormMerge::TFormMerge(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMerge::SelectAll1Click(TObject *Sender)
{
  for (int i=0; i < CheckListBoxRegions->Items->Count; i++) {
  	CheckListBoxRegions->Checked[i] = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMerge::SelectNone1Click(TObject *Sender)
{
  for (int i=0; i < CheckListBoxRegions->Items->Count; i++) {
  	CheckListBoxRegions->Checked[i] = false;
  }
}
//---------------------------------------------------------------------------

