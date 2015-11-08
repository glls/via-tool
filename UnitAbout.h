//---------------------------------------------------------------------------

#ifndef UnitAboutH
#define UnitAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblTitle;
  TLabel *lblVersion;
	TLabel *Label4;
	TLabel *Label5;
  TLabel *lblURL;
	TBevel *Bevel1;
	TBevel *Bevel2;
  TButton *ButtonOK;
  TLabel *Label2;
  TLabel *lblMail;
  TLabel *lblHome;
	void __fastcall lblURLClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall lblMailClick(TObject *Sender);
  void __fastcall lblHomeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
