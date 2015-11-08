//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitAbout.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::lblURLClick(TObject *Sender)
{
	ShellExecute(Handle, "open", lblURL->Caption.c_str(),
    NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormCreate(TObject *Sender)
{
  lblVersion->Caption = FormMain->lblVersion->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::lblMailClick(TObject *Sender)
{
	ShellExecute(Handle, "open", lblMail->Caption.c_str(),
    NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::lblHomeClick(TObject *Sender)
{
	ShellExecute(Handle, "open", lblHome->Caption.c_str(),
    NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

