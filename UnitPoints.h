//---------------------------------------------------------------------------

#ifndef UnitPointsH
#define UnitPointsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormPoints : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *StringGrid;
private:	// User declarations
public:		// User declarations
  __fastcall TFormPoints(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPoints *FormPoints;
//---------------------------------------------------------------------------
#endif
