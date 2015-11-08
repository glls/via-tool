//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitLog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLog *FormLog;
//---------------------------------------------------------------------------
__fastcall TFormLog::TFormLog(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLog::Log(String s)
{
  FormLog->MemoLog->Lines->Add("[" + DateTimeToStr(Now()) + "] " + s);
}
