//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSelectMPEG7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormExtractMPEG7 *FormExtractMPEG7;
//---------------------------------------------------------------------------
__fastcall TFormExtractMPEG7::TFormExtractMPEG7(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormExtractMPEG7::SelectAll1Click(TObject *Sender)
{
  for (int i=0; i < CheckListBoxMPEG7->Items->Count; i++) {
    CheckListBoxMPEG7->Checked[i] = true;

  }
}
//---------------------------------------------------------------------------

void __fastcall TFormExtractMPEG7::SelectNone1Click(TObject *Sender)
{
  for (int i=0; i < CheckListBoxMPEG7->Items->Count; i++) {
  	CheckListBoxMPEG7->Checked[i] = false;
  }
}
//---------------------------------------------------------------------------

