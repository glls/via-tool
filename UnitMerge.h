//---------------------------------------------------------------------------

#ifndef UnitMergeH
#define UnitMergeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TFormMerge : public TForm
{
__published:	// IDE-managed Components
  TButton *ButtonOK;
  TButton *ButtonCancel;
	TPopupMenu *PopupMenuMerge;
	TMenuItem *SelectAll1;
	TMenuItem *SelectNone1;
  TCheckListBox *CheckListBoxRegions;
	void __fastcall SelectAll1Click(TObject *Sender);
	void __fastcall SelectNone1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormMerge(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMerge *FormMerge;
//---------------------------------------------------------------------------
#endif
