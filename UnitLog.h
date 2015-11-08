//---------------------------------------------------------------------------

#ifndef UnitLogH
#define UnitLogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormLog : public TForm
{
__published:	// IDE-managed Components
  TMemo *MemoLog;
private:	// User declarations
public:		// User declarations
  __fastcall TFormLog(TComponent* Owner);
  void __fastcall Log(String s);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLog *FormLog;
//---------------------------------------------------------------------------
#endif
