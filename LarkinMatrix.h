//---------------------------------------------------------------------------

#ifndef LarkinMatrixH
#define LarkinMatrixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class Inter
{
private:

protected:

public:
   int x, *mas, **mat;
   int *px, **pmas, ***pmat;
   Inter(int &tox, int* &toMAS, int** &toMAT)
   {
      px = &tox;
      pmas = &toMAS;
      pmat = &toMAT;
   }
   void Assign(int &sx)
   {          sx = x;      }
   void xtosx(int &sx)
   {         x = sx;       }
   void test()
   {
      ShowMessage((*pmas)[1]); //¬Œ“ “¿ Œ≈ Œ¡–¿Ÿ≈Õ»≈  ¿Õ¿≈“
   }
   void NEW(int R, int C)
   {
       if ( *pmat )
       {
         ShowMessage("pmat Realloc");
         (*pmat) = (int**)realloc((*pmat), R * sizeof(int*));
         for (int i=0;i<R;i++)
            (*pmat)[i] = (int*)realloc((*pmat)[i], C * sizeof(int));
       }
      else
      {
         ShowMessage("pmat New");
         (*pmat) = (int**)malloc(R * sizeof(int*));
         for (int i=0;i<R;i++)
            (*pmat)[i] = (int*)malloc(C * sizeof(int));
         //»ÌËˆË‡ÎËÁ‡ˆËˇ
         for (int i=0;i<R;i++)
            for (int j=0;j<C;j++)
               (*pmat)[i][j] = i*C + j + 1;
      }


      //(*pmat)[R-1][C-1]=-100;
   }
   


};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TStringGrid *StringGrid1;
   TGroupBox *GroupBox1;
   TButton *Button1;
   TEdit *Edit2;
   TButton *Button2;
   TGroupBox *GroupBox2;
   TButton *Button3;
   TEdit *Edit1;
   TButton *Button4;
   TButton *Button5;
   TButton *Button6;
   TButton *Button7;
   TEdit *Edit3;
   TButton *Button8;
   TButton *Button9;
   TButton *Button10;
   TButton *Button11;
   TButton *Button12;
   TButton *Button13;
   TButton *NewMat;
   TButton *GetMat;
   TButton *SetMat;
   TButton *IntGetMat;
   TButton *IntSetMat;
   TLabeledEdit *CountR;
   TLabeledEdit *CountC;
   TLabeledEdit *LabeledEdit3;
   TLabeledEdit *LabeledEdit4;
   TButton *IntNewMat;
   TStaticText *StaticText1;
   TPopupMenu *PopupMenu1;
   TMenuItem *N1;
   TMenuItem *N2;
   TStaticText *StaticText2;
   TGroupBox *GroupBox3;
   TCSpinEdit *SpinI;
   TButton *SetIndex;
   TLabel *LabelVal;
   TCSpinEdit *SpinM;
   TButton *SetV;
   TButton *GetV;
   TLabel *Label2;
   TButton *Button14;
   void __fastcall Button4Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button5Click(TObject *Sender);
   void __fastcall Button6Click(TObject *Sender);
   void __fastcall Button7Click(TObject *Sender);
   void __fastcall Button8Click(TObject *Sender);
   void __fastcall Button11Click(TObject *Sender);
   void __fastcall Button10Click(TObject *Sender);
   void __fastcall Button9Click(TObject *Sender);
   void __fastcall Button12Click(TObject *Sender);
   void __fastcall Button13Click(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall NewMatClick(TObject *Sender);
   void __fastcall SetMatClick(TObject *Sender);
   void __fastcall GetMatClick(TObject *Sender);
   void __fastcall IntSetMatClick(TObject *Sender);
   void __fastcall IntGetMatClick(TObject *Sender);
   void __fastcall IntNewMatClick(TObject *Sender);
   void __fastcall N1Click(TObject *Sender);
   void __fastcall N2Click(TObject *Sender);
   void __fastcall SetIndexClick(TObject *Sender);
   void __fastcall GetVClick(TObject *Sender);
   void __fastcall SetVClick(TObject *Sender);
   void __fastcall Button14Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
   __fastcall ~TForm1();
};
   int x, *mas, **mat;
   int *Pmat;
   Inter Int(x, mas, mat);
   int MatR, MatC;
   int EditR, EditC;

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif


