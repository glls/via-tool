//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitUtils.h"
#include "UnitFormWait.h"
#include "UnitLog.h"

#include <stdio.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
// utility functions
//---------------------------------------------------------------------------

void __fastcall ExecuteWait(AnsiString cmd, AnsiString params, AnsiString directory)
{
  SHELLEXECUTEINFO execinfo;

  memset (&execinfo, 0, sizeof(execinfo));
  execinfo.cbSize = sizeof(execinfo);
  execinfo.lpVerb = "open";
  execinfo.lpFile = cmd.c_str();
  execinfo.lpParameters = params.c_str();
  execinfo.lpDirectory = directory.c_str();

  execinfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  //execinfo.nShow = SW_SHOWDEFAULT;
  execinfo.nShow = SW_HIDE;

  FormWait = new TFormWait(Application);
  FormWait->Show();
  FormWait->LabelStatus->Caption = "Running "+cmd+"...";
  FormLog->MemoLog->Lines->Add("Running "+cmd+" "+params+" (directory:"+directory+")");
  Application->ProcessMessages();
  if (ShellExecuteEx (&execinfo))
    WaitForSingleObject(execinfo.hProcess, INFINITE);
  FormWait->Close();
  delete FormWait;
}

//---------------------------------------------------------------------------
void __fastcall WritePPM(TBitmap32 *bitmap, AnsiString filename)
{
  FILE *out;
  TColor32 p;
  int r, g, b;

  if ((out = fopen(filename.c_str(), "wb")) == NULL) {
    return;
  }

  fprintf(out, "P6\n%d %d\n255\n", bitmap->Width, bitmap->Height);

  for (int Y = 0; Y < bitmap->Height; Y++) {
    for (int X = 0; X < bitmap->Width ; X++) {
      p = bitmap->Pixel[X][Y];
      r = RedComponent(p);
      g = GreenComponent(p);
      b = BlueComponent(p);
      fputc ((unsigned char)r, out);
      fputc ((unsigned char)g, out);
      fputc ((unsigned char)b, out);
    }
  }
  fclose(out);
}
//---------------------------------------------------------------------------

void __fastcall WritePGM(TBitmap32 *bitmap, AnsiString filename)
{
  // pgm for VIA mask
  FILE *out;
  TColor32 p;
  int r, g, b;

  if ((out = fopen(filename.c_str(), "wb")) == NULL) {
    return;
  }

  fprintf(out, "P5\n%d %d\n255\n", bitmap->Width, bitmap->Height);

  for (int Y = 0; Y < bitmap->Height; Y++) {
    for (int X = 0; X < bitmap->Width ; X++) {
      p = bitmap->Pixel[X][Y];
      r = RedComponent(p);
      g = GreenComponent(p);
      b = BlueComponent(p);
     	fputc (r+g+b, out);
    }
  }
  fclose(out);
}
//---------------------------------------------------------------------------

void __fastcall ShowError(char *msg, DWORD code)
{
  AnsiString s;
  s.printf("%s\n\n\tCODE:\t%u\nREASON:\t%s", msg, code);
  MessageDlg(s, mtError, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------
