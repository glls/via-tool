//---------------------------------------------------------------------------

#ifndef UnitNewVidProjectH
#define UnitNewVidProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormNewVid : public TForm
{
__published:	// IDE-managed Components
  TLabel *lvlVideo;
  TButton *ButtonOK;
  TButton *ButtonCancel;
  TEdit *teName;
  TLabel *lblName;
	TOpenDialog *OpenDialogV;
  TEdit *teFile;
  TButton *btnFile;
	void __fastcall ButtonOKClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btnFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormNewVid(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNewVid *FormNewVid;
//---------------------------------------------------------------------------
#endif
