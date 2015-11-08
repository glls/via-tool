//---------------------------------------------------------------------------

#ifndef UnitUtilsH
#define UnitUtilsH

#include "GR32_Image.hpp"
#include "GR32_Layers.hpp"
#include "GR32_Polygons.hpp"

//---------------------------------------------------------------------------
const TColor mcolors[16] = {
  clBlack, clMaroon, clGreen, clOlive,
  clNavy, clPurple, clTeal, clGray,
  clSilver, clRed, clLime, clYellow,
  clBlue,  clFuchsia, clAqua };

void __fastcall ExecuteWait(AnsiString cmd, AnsiString params, AnsiString directory);
void __fastcall WritePPM(TBitmap32 *bitmap, AnsiString filename);
void __fastcall WritePGM(TBitmap32 *bitmap, AnsiString filename);
void __fastcall ShowError(char *msg, DWORD code);

#endif
