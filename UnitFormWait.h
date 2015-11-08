//---------------------------------------------------------------------------

#ifndef UnitFormWaitH
#define UnitFormWaitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormWait : public TForm
{
__published:	// IDE-managed Components
  TLabel *LabelWait;
  TLabel *LabelStatus;
  TBevel *Bevel1;
private:	// User declarations
public:		// User declarations
  __fastcall TFormWait(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWait *FormWait;
//---------------------------------------------------------------------------
#endif
