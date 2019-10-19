//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TVPrincipal : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel3;
    TImage *Image1;
    TImage *Image2;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TButton *Button7;
    TButton *Button8;
    TButton *Button9;
    TButton *Button10;
    TButton *Button12;
    TButton *Button13;
    TButton *Button14;
    TButton *Button15;
    TButton *Button16;
    TButton *Button18;
    TButton *Button22;
    TButton *Button11;
    TPanel *Panel4;
    TButton *Button17;
    TButton *Button19;
    TButton *Button21;
    TButton *Button23;
    TButton *Button24;
    TButton *Button25;
    TButton *Button26;
    TButton *Button27;
    TButton *Button28;
    TButton *Button29;
    TPanel *Panel5;
    TEdit *Edit1;
    TButton *Button20;
    TEdit *Edit2;
    TPanel *Panel1;
    TPanel *Panel2;
    TCheckBox *CheckBoxDeci;
    TCheckBox *CheckBoxHexa;
    TButton *Button31;
    TButton *Button30;
    TMainMenu *MainMenu1;
    TMenuItem *MenuModo;
    TMenuItem *MenuDecimal;
    TMenuItem *MenuHexadecimal;
    TMenuItem *MenuColor;
    TMenuItem *MenuSpain;
    TMenuItem *MenuRepublica;
    TMenuItem *MenuAlemania;
    void __fastcall OnClickNum(TObject *Sender);
    void __fastcall ButtonOperator(TObject *Sender);
    void __fastcall ButtonsClear(TObject *Sender);
    void __fastcall ButtonsMemo(TObject *Sender);
    void __fastcall OnClickDeci(TObject *Sender);
    void __fastcall OnClickHexa(TObject *Sender);
    void __fastcall ButtonOperatorHex(TObject *Sender);
    void __fastcall MenuSpainClick(TObject *Sender);
    void __fastcall MenuRepublicaClick(TObject *Sender);
    void __fastcall MenuAlemaniaClick(TObject *Sender);
    void __fastcall MenuDecimalClick(TObject *Sender);
    void __fastcall MenuHexadecimalClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TVPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVPrincipal *VPrincipal;
//---------------------------------------------------------------------------
#endif
