//---------------------------------------------------------------------------

#ifndef UnitSelectMPEG7H
#define UnitSelectMPEG7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TFormExtractMPEG7 : public TForm
{
__published:	// IDE-managed Components
  TButton *ButtonOK;
  TButton *ButtonCancel;
  TPopupMenu *PopupMenuMPEG7;
	TMenuItem *SelectAll1;
	TMenuItem *SelectNone1;
  TLabel *cxLabel;
  TCheckListBox *CheckListBoxMPEG7;
	void __fastcall SelectAll1Click(TObject *Sender);
	void __fastcall SelectNone1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormExtractMPEG7(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormExtractMPEG7 *FormExtractMPEG7;
//---------------------------------------------------------------------------
#endif
