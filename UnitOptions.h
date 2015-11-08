//---------------------------------------------------------------------------

#ifndef UnitOptionsH
#define UnitOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>


//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
  TLabel *cxLabel2;
  TLabel *cxLabel19;
  TLabel *cxLabel20;
  TButton *btnOK;
  TButton *btnCancel;
  TLabel *cxLabel1;
	THotKey *HotKeyFrameFWD;
	THotKey *HotKeyFrameREW;
  TLabel *cxLabel3;
  TLabel *cxLabel4;
	TLabel *Label1;
	TLabel *Label2;
	TBevel *Bevel1;
	TLabel *Label3;
  TLabel *cxLabel5;
  TLabel *cxLabel6;
	TBevel *Bevel2;
  TLabel *cxLabel7;
  TButton *btnDirAce;
  TEdit *EditDirAce;
  TEdit *EditDirSeg;
  TButton *btnDirSeg;
  TEdit *EditDirOut;
  TButton *btnDirOut;
  TBevel *Bevel3;
  TLabel *Label4;
  TCheckBox *chkbxRenumberSort;
  THotKey *HotKeyBBWI;
  THotKey *HotKeyBBWD;
  THotKey *HotKeyBBHI;
  THotKey *HotKeyBBHD;
  TLabel *cxLabel8;
  TLabel *cxLabel9;
  TLabel *cxLabel10;
  TLabel *cxLabel11;
  TBevel *Bevel4;
  TLabel *Label5;
  TLabel *cxLabel12;
  TLabel *cxLabel13;
  TEdit *EditSegExe;
  TEdit *EditSegOptions;
  TLabel *cxLabel14;
  TLabel *cxLabel15;
  TLabel *cxLabel16;
  TEdit *EditVideoInt;
  TEdit *EditPenWidth;
  TLabel *Label6;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
  void __fastcall btnDirAceClick(TObject *Sender);
  void __fastcall btnDirOutClick(TObject *Sender);
  void __fastcall btnDirSegClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
