//---------------------------------------------------------------------------

#ifndef UnitHelpH
#define UnitHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormHelp : public TForm
{
__published:	// IDE-managed Components
  TMemo *MemoHelp;
  TButton *ButtonOK;
  void __fastcall ButtonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormHelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormHelp *FormHelp;
//---------------------------------------------------------------------------
#endif
