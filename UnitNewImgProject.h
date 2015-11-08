//---------------------------------------------------------------------------

#ifndef UnitNewImgProjectH
#define UnitNewImgProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormNewImg : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblImage;
  TButton *ButtonOK;
  TButton *ButtonCancel;
  TEdit *teName;
  TLabel *lblName;
	TOpenDialog *OpenDialogImg;
  TEdit *teFile;
  TButton *btnFile;
	void __fastcall ButtonOKClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btnFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormNewImg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNewImg *FormNewImg;
//---------------------------------------------------------------------------
#endif
