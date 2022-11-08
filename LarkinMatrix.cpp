//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LarkinMatrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   x = 0;
   mas = 0;
   mat = 0;
   Edit1->Text = 15;
   Edit2->Text = 300;
   for (int i=0;i<5;i++)
      for (int j=0;j<5;j++)
          StringGrid1->Cells[i][j] = i+j*5;
   StringGrid1->Cells[0][3] = "Inter";
   MatR=0;
   MatC=0; 
}
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
   //ShowMessage("destructor");
   //delete [] mas;
}
void __fastcall TForm1::Button4Click(TObject *Sender)
{
   x = StrToInt(Edit1->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   Edit1->Text = x;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   Int.x = StrToInt(Edit2->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   Edit2->Text = Int.x;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
  Int.Assign(x);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   Int.xtosx(x);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   Edit3->Text = *Int.px;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
   *(Int.px) = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
   mas = new int[4];
   for (int i=0;i<4;i++)
      mas[i] = StrToInt(StringGrid1->Cells[i+1][1]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
   for (int i=0;i<4;i++)
      mas[i] = StrToInt(StringGrid1->Cells[i+1][1]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
   for (int i=0;i<4;i++)
      StringGrid1->Cells[i+1][1] = mas[i];
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
   for (int i=0;i<4;i++)
      StringGrid1->Cells[i+1][3] = (*Int.pmas)[i];
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
   for (int i=0;i<4;i++)
      (*Int.pmas)[i] = StrToInt(StringGrid1->Cells[i+1][3]);
}
//---------------------------------------------------------------------------
//Деструктор
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete [] mas;
   if (mat == 0)
      return;
   for (int j=0;j<MatR;j++)
   {
      //delete [] mat[j];
      free (mat[j]);
   }
   free (mat);
   //delete [] mat;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NewMatClick(TObject *Sender)
{
   EditR = StrToInt(CountC->Text);
   EditC = StrToInt(CountR->Text);
   mat = new int*[EditC];
   for (int i=0; i<EditC; i++)
      mat[i] = new int[EditR];

   /*for (int i=0;i<EditC;i++)
      for (int j=0;j<EditR;j++)
         mat[i][j] = StrToInt(StringGrid1->Cells[i+1][j+1]);     */
   StaticText2->Caption = ("EditC="+IntToStr(EditC)+" EditR="+IntToStr(EditR));
}
//---------------------------------------------------------------------------
//Set Mat
void __fastcall TForm1::SetMatClick(TObject *Sender)
{
   for (int i=0; i<EditC; i++)
      for (int j=0; j<EditR; j++)
      {
         try{  mat[i][j] = StrToInt(StringGrid1->Cells[i+1][j+1]); }
         catch (EConvertError& E)
         {
            StringGrid1->Cells[i+1][j+1] = 0;
            mat[i][j] = 0;
         }
      }
}
//---------------------------------------------------------------------------
//Get Mat
void __fastcall TForm1::GetMatClick(TObject *Sender)
{
   for (int i=0; i<EditC; i++)
      for (int j=0; j<EditR; j++)
         StringGrid1->Cells[i+1][j+1] = mat[i][j];
}
//---------------------------------------------------------------------------
//Set MAT Inter
void __fastcall TForm1::IntSetMatClick(TObject *Sender)
{
   for (int i=0;i<EditR;i++)
      for (int j=0;j<EditC;j++)
         (*Int.pmat)[i][j] = StrToInt(StringGrid1->Cells[j+1][i+1]);
}
//---------------------------------------------------------------------------
//Get Mat inter
void __fastcall TForm1::IntGetMatClick(TObject *Sender)
{
   for (int i=0;i<EditR;i++)
      for (int j=0;j<EditC;j++)
         StringGrid1->Cells[j+1][i+1] = (*Int.pmat)[i][j];
}
//---------------------------------------------------------------------------
//New MaT Inter
void __fastcall TForm1::IntNewMatClick(TObject *Sender)
{
   MatR = StrToInt(LabeledEdit3->Text);
   MatC = StrToInt(LabeledEdit4->Text);
   Int.NEW(MatR, MatC);
   StaticText1->Caption = ("MatR="+IntToStr(MatR)+" MatC="+IntToStr(MatC));
   //3,4 это Mat[3][4]
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
   for (int i=1;i<5;i++)
      for (int j=1;j<5;j++)
          StringGrid1->Cells[i][j] = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
   for (int i=1;i<5;i++)
      for (int j=1;j<5;j++)
          StringGrid1->Cells[i][j] = i+j*4;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetIndexClick(TObject *Sender)
{
   Pmat = mat[SpinI->Value];
   LabelVal->Caption = "Value["+IntToStr(SpinI->Value)+"]";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GetVClick(TObject *Sender)
{
   SpinM->Value = Pmat[SpinI->Value];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetVClick(TObject *Sender)
{
   Pmat[SpinI->Value] = SpinM->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
   int R = 2, C = 3;
   int met[2][3] = {{1, 2, 3},{4,5,6}};
   //char sp[][7] = {"qwerty","asdf","zxcv"};

   int *uk = met[1];
   ShowMessage(uk[2]);
   int **M = NULL;
   M = new int *[R];
   for (int i=0; i<R; i++)
   {
      M[i] = new int [C];
      for (int j=0; j<C; j++)
         M[i][j] = 0;
   }
   M[1][2] = 6;
   ShowMessage(M[1][2]);
   for (int i=0; i<R; i++)
      delete M[i];
   delete []M;
   M = NULL;


}
//---------------------------------------------------------------------------

