//---------------------------------------------------------------------------

#ifndef UnitImportH
#define UnitImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <StrUtils.hpp>


//---------------------------------------------------------------------------

class TFormImport : public TForm
{
__published:	// IDE-managed Components
  TXMLDocument *XMLTraj;
  TTreeView *XMLTrajTree;
	TMemo *Memo1;
	TButton *ButtonParse;
  TStaticText *StaticTextI;
  TStaticText *StaticTextNode;
  TStaticText *StaticTextRegions;
	TStaticText *StaticTextE;
  TButton *ButtonOK;
	TTimer *Timer1;
  void __fastcall ButtonParseClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonOKClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	void __fastcall TrajProcessNode(_di_IXMLNode Node, TTreeNode *tn);
public:		// User declarations
	__fastcall TFormImport(TComponent* Owner);
  bool __fastcall TrajXML2Tree(AnsiString filename);
  AnsiString FileName;
  TStringList *MLCI;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImport *FormImport;
//---------------------------------------------------------------------------
#endif
