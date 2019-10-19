//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "main.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
//#include <string>
#define FIL 99
#define COL 2
#define SUMA 1
#define RESTA 2
#define PRODUCTO 3
#define DIVISION 4
#define RAIZ 5
#define AND 6
#define OR 7
#define XOR 8
#define NOT 9
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVPrincipal *VPrincipal;
double data[FIL][COL], sol=0, raiz=0;
int fila=0, memo=0;
int datahex[FIL][COL], solhex=0, operando=0, leftshift=0, rightshift=0;
bool divi=false, insert=false, opera=false, cero=false, hexa=false;
bool shiftL=false, shiftR=false;
void calculadora(int, double);
void calcuhexa(int, int);
double redondeo(double);
//hexstr2double(const std::string& hexstr);
//---------------------------------------------------------------------------
__fastcall TVPrincipal::TVPrincipal(TComponent* Owner)
    : TForm(Owner){
    VPrincipal->Panel3->Top=224;
    VPrincipal->ClientHeight=510;
    VPrincipal->Left=300;
    VPrincipal->Top= 300;

DWORD alignment = ES_RIGHT;                   //Alignament to right in Edit
DWORD oldStyle = GetWindowLong(Edit1->Handle, GWL_STYLE);
DWORD newStyle = (oldStyle & ~(ES_LEFT | ES_CENTER | ES_RIGHT)) | alignment;
SetWindowLong(Edit1->Handle, GWL_STYLE, newStyle);
    }
//---------------------------------------------------------------------------
void __fastcall TVPrincipal::OnClickNum(TObject *Sender)
{
    if(Sender == Button1){Edit1->Text=Edit1->Text+1;}
    if(Sender == Button2){Edit1->Text=Edit1->Text+2;}
    if(Sender == Button3){Edit1->Text=Edit1->Text+3;}
    if(Sender == Button4){Edit1->Text=Edit1->Text+4;}
    if(Sender == Button5){Edit1->Text=Edit1->Text+5;}
    if(Sender == Button6){Edit1->Text=Edit1->Text+6;}
    if(Sender == Button7){Edit1->Text=Edit1->Text+7;}
    if(Sender == Button8){Edit1->Text=Edit1->Text+8;}
    if(Sender == Button9){Edit1->Text=Edit1->Text+9;}
    if(Sender == Button10){Edit1->Text=Edit1->Text+0;}
    if(Sender == Button11){Edit1->Text=Edit1->Text*"-1";}
    if(Sender == Button12){Edit1->Text=Edit1->Text+",";}
    if(Sender == Button17){Edit1->Text=Edit1->Text+"A";}
    if(Sender == Button19){Edit1->Text=Edit1->Text+"B";}
    if(Sender == Button21){Edit1->Text=Edit1->Text+"C";}
    if(Sender == Button29){Edit1->Text=Edit1->Text+"D";}
    if(Sender == Button28){Edit1->Text=Edit1->Text+"E";}
    if(Sender == Button27){Edit1->Text=Edit1->Text+"F";}
    datahex[0][0]= SUMA;  // Asume primer numero positivo por defecto
    data[0][0]= SUMA;  // Asume primer numero positivo por defecto
    opera=true;     // Para el signo menos
    insert=true;    // Para detectar numero en Edit1
    if(hexa){}
}
//---------------------------------------------------------------------------
void __fastcall TVPrincipal::ButtonOperator(TObject *Sender)
{
if(!opera && Sender==Button15){Edit1->Text="-"; insert=false; opera=true;
}else if(!insert ){Edit1->Text="Error insert num";
}else{
    data[fila][1]= Edit1->Text.ToDouble();

    if(Sender == Button14){                            // suma
        fila++;
        data[fila][0]= SUMA;
        Edit2->Text=Edit2->Text+data[fila-1][1]+"+";
        Edit1->Clear();
        insert=false;
    }
    if(Sender == Button15){                            // resta
        fila++;
        data[fila][0]= RESTA;
        Edit1->Clear();
        Edit2->Text=Edit2->Text+data[fila-1][1]+"-";
        insert=false;
    }
    if(Sender == Button16){                            // producto
        fila++;
        data[fila][0]= PRODUCTO;
        Edit2->Text=Edit2->Text+data[fila-1][1]+"x";
        Edit1->Clear();
        insert=false;
    }
    if(Sender == Image2){                              // división
        fila++;
        data[fila][0]= DIVISION;
        Edit2->Text=Edit2->Text+data[fila-1][1]+"/";
        Edit1->Clear();
        divi=true;
        insert=false;
    }
    if(Sender == Image1){                              // raíz
        double temp = data[fila][1];
        if(temp < 0){
            VPrincipal->Edit1->Text="Solución no real";
            goto Label2;
        }
        raiz = sqrt(data[fila][1]);
        data[fila][1]= redondeo(raiz);
        Edit2->Text=Edit2->Text+"SQRT("+temp+")=";
        Edit1->Text=data[fila][1];
        Label2:
    }
    if(Sender == Button18){                              // Botón igual
        sol = 0;
        Edit2->Text=Edit2->Text+data[fila][1]+"=";
            for(uint8_t i=0; i<=fila; i++){
                calculadora(data [i][0], data [i][1]);
                if(cero){
                VPrincipal->Edit1->Text="Error, X/0";
                goto Label1;
                }
            }
        Edit1->Clear();
        Edit1->Text=sol;
        TVPrincipal::ButtonsClear(Button18);
        Label1:
    }
}
}
//---------------------  OPERACIONES EN EXADECIMAL -----------------------------
void __fastcall TVPrincipal::ButtonOperatorHex(TObject *Sender)
{
if(!opera && Sender==Button15){Edit1->Text="-"; insert=false; opera=true;
}else if(!insert){Edit1->Text="Error insert num";
//}else if(hexa){TVPrincipal::ButtonsClear(Button18);
}else{

    if(Sender == Button14){                            // suma HEX
        operando = Edit1->Text.ToInt();
        datahex[fila][1] = operando;
        fila++;
        datahex[fila][0]= SUMA;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+"+";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Button15){                            // resta HEX
        operando = Edit1->Text.ToInt();
        datahex[fila][1] = operando;
        fila++;
        datahex[fila][0]= RESTA;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+"-";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Button16){                            // producto HEX
        operando = Edit1->Text.ToInt();
        datahex[fila][1] = operando;
        fila++;
        datahex[fila][0]= PRODUCTO;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+"*";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Image2){                              // división HEX
        operando = Edit1->Text.ToInt();
        datahex[fila][1] = operando;
        fila++;
        datahex[fila][0]= DIVISION;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+"/";
        Edit1->Text="0x";
        divi=true;
        insert=false;
    }
    if(Sender == Button23){                              // AND
        operando = Edit1->Text.ToInt();
        datahex[fila][1]= operando;
        fila++;
        datahex[fila][0]= AND;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+" AND ";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Button24){                              // OR
        operando = Edit1->Text.ToInt();
        datahex[fila][1]= operando;
        fila++;
        datahex[fila][0]= OR;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+" OR ";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Button26){                              // XOR
        operando = Edit1->Text.ToInt();
        datahex[fila][1]= operando;
        fila++;
        datahex[fila][0]= XOR;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+" XOR ";
        Edit1->Text="0x";
        insert=false;
    }
    if(Sender == Button25){                              // NOT
        Edit2->Text="NOT (0x"+Edit1->Text+")=";
        solhex = ~operando;
        Edit1->Text="0x"+IntToHex(solhex, 4);
        insert=false;
    }
    if(Sender == Button30){                              // Shift lefth<<
        shiftR=false;
        if(shiftL){goto next1;}
        leftshift=0;
        operando = Edit1->Text.ToInt();
        Edit2->Text="("+Edit1->Text+") << =";
        next1:
        leftshift++;
        solhex = operando<<leftshift;
        Edit1->Text="0x"+IntToHex(solhex, 4);
        shiftL=true;
    }
    if(Sender == Button31){                              // Shift right>>
        shiftL=false;
        if(shiftR){goto next2;}
        rightshift=0;
        operando = Edit1->Text.ToInt();
        Edit2->Text="("+Edit1->Text+") >> =";
        next2:
        rightshift++;
        solhex = operando>>rightshift;
        Edit1->Text="0x"+IntToHex(solhex, 4);
        shiftR=true;
    }
    if(Sender == Button18){                              // Botón igual HEX
        solhex= 0;
        operando = Edit1->Text.ToInt();
        datahex[fila][1] = operando;
        Edit2->Text=Edit2->Text+"0x"+IntToHex(operando, 4)+"=";
            for(uint8_t i=0; i<=fila; i++){
                calcuhexa(datahex [i][0], datahex [i][1]);
                if(cero){
                VPrincipal->Edit1->Text="Error, X/0";
                goto Label1;
                }
            }
        Edit1->Text="0x"+IntToHex(solhex, 4);
        //TVPrincipal::ButtonsClear(Button18);
        Label1:
    }
}
}
//---------------------------------------------------------------------------
void calculadora(int oper, double dato){               // Decimal
    switch (oper){
        case SUMA: sol += dato;
                break;
        case RESTA: sol -= dato;
                break;
        case PRODUCTO: sol *= dato;
                break;
        case DIVISION: if(divi && dato==0){
                cero=true;
                }else{sol /= dato;
                      sol=redondeo(sol);
                break;}
    }
}
//---------------------------------------------------------------------------
void calcuhexa(int oper, int dato){                    // Hexadecimal
    switch (oper){
        case SUMA: solhex += dato;
                   break;

        case RESTA: solhex -= dato;
                    break;

        case PRODUCTO: solhex *= dato;
                       break;

        case DIVISION: if(divi && dato==0){
                       cero=true;
                       }else{solhex /= dato;
                       break;}

        case AND: solhex &= dato; break;

        case OR:  solhex |= dato; break;

        case XOR: solhex ^= dato; break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TVPrincipal::ButtonsClear(TObject *Sender)
{
    if(!hexa && Sender == Button13){           // Cancelar (Borra todo)
        Edit1->Clear();
        Edit2->Clear();
        divi=false;
        cero=false;
        opera=false;
        insert=false;
        fila= 0;
            for(int i=0; i<=FIL; i++){
                for(int j=0; j<=COL; j++){
                    data[i][j]=0;
                }
            }
    }
    else if(hexa && Sender == Button13){        // Cancelar (Borra todo) Hex
    Edit1->Text="0x";
    Edit2->Clear();
    divi=false;
    cero=false;
    opera=false;
    insert=false;
    fila= 0;
        for(int i=0; i<=FIL; i++){
            for(int j=0; j<=COL; j++){
                datahex[i][j]=0;
            }
        }
    }
                                     // Cancelar Entrada (Borra última entrada)
    if(!hexa && Sender == Button22){Edit1->Clear();}
    else if(hexa && Sender == Button22){Edit1->Text="0x";;}

    if(Sender == Button18){          // Cancelar (Borra todo menos Edit1)
    //Edit2->Clear();
    divi=false;
    cero=false;
    opera=false;
    insert=true;
    hexa=false;
    fila= 0;
        for(int i=0; i<=FIL; i++){
            for(int j=0; j<=COL; j++){
                datahex[i][j]=0;
                data[i][j]=0;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TVPrincipal::ButtonsMemo(TObject *Sender)
{
    if(!hexa && Sender == Panel1){                      // Memoria
        if(!insert){Edit1->Text="Error insert num";
        }else{
        memo = Edit1->Text.ToDouble();
        VPrincipal->Panel1->Font->Color=clRed;
        VPrincipal->Panel2->Font->Color=clRed;}
    }
    else if(hexa && Sender == Panel1){                 // Memoria Hex
        if(!insert){Edit1->Text="Error insert num";
        }else{
        memo = Edit1->Text.ToInt();
        VPrincipal->Panel1->Font->Color=clRed;
        VPrincipal->Panel2->Font->Color=clRed;}
    }
    if(Sender == Panel2){                              // Clear
        memo = 0;
        VPrincipal->Panel1->Font->Color=clWindowText;
        VPrincipal->Panel2->Font->Color=clWindowText;
    }                       
    if(!hexa && Sender == Button20){                   // Recall
        Edit1->Text=memo;
        insert=true;
    }
    else if(hexa && Sender == Button20){               // Recall Hex
        Edit1->Text="0x"+IntToHex(memo, 4);
        insert=true;
    }
}
//---------------------------------------------------------------------------
double redondeo(double num){
    double rounded = (int)(num * 1000000.0)/1000000.0;
    return rounded;
}
//---------------------------------------------------------------------------

void __fastcall TVPrincipal::OnClickDeci(TObject *Sender)
{
    hexa=false;
    TVPrincipal::ButtonsClear(Button13);
    VPrincipal->CheckBoxHexa->Checked=false;
    VPrincipal->ClientHeight=510;
    VPrincipal->Panel3->Top=224;
    VPrincipal->Panel3->Visible=VPrincipal->CheckBoxDeci->Checked;
    VPrincipal->Panel4->Visible=false;
    VPrincipal->Image1->Visible=true;
    VPrincipal->Button12->Visible=true;
    VPrincipal->Button18->Width=49;
    VPrincipal->Button18->Left=272;
    VPrincipal->Button10->Width=49;
    VPrincipal->Button14->OnClick=ButtonOperator;
    VPrincipal->Button15->OnClick=ButtonOperator;
    VPrincipal->Button16->OnClick=ButtonOperator;
    VPrincipal->Image2->OnClick=ButtonOperator;
    VPrincipal->Button18->OnClick=ButtonOperator;
}
//---------------------------------------------------------------------------

void __fastcall TVPrincipal::OnClickHexa(TObject *Sender)
{
    hexa=true;
    TVPrincipal::ButtonsClear(Button13);
    VPrincipal->CheckBoxDeci->Checked=false;
    VPrincipal->ClientHeight=634;
    VPrincipal->Panel3->Top=352;
    VPrincipal->Panel4->Visible=VPrincipal->CheckBoxHexa->Checked;
    VPrincipal->Panel3->Visible=VPrincipal->CheckBoxHexa->Checked;
    VPrincipal->Image1->Visible=false;
    VPrincipal->Button12->Visible=false;
    VPrincipal->Button18->Width=113;
    VPrincipal->Button18->Left=208;
    VPrincipal->Button10->Width=113;
    VPrincipal->Button14->OnClick=ButtonOperatorHex;
    VPrincipal->Button15->OnClick=ButtonOperatorHex;
    VPrincipal->Button16->OnClick=ButtonOperatorHex;
    VPrincipal->Image2->OnClick=ButtonOperatorHex;
    VPrincipal->Button18->OnClick=ButtonOperatorHex;
    Edit1->Text="0x";
}
//---------------------------------------------------------------------------


