//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitHelp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormHelp *FormHelp;
//---------------------------------------------------------------------------
__fastcall TFormHelp::TFormHelp(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormHelp::ButtonOKClick(TObject *Sender)
{
  Close(); 
}
//---------------------------------------------------------------------------

