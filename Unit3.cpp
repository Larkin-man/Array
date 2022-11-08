//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

extern void TitleGrid();
extern void CreateMatrix();
extern int Number_of_vertices;

AnsiString filename;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::RadioButton2Click(TObject *Sender)
{
  Form3->Label3->Enabled = True;
  Form3->Edit2->Enabled = True;
  Form3->Button1->Enabled = True;
  Form3->Label2->Enabled = False;
  Form3->Edit1->Enabled = False;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::RadioButton1Click(TObject *Sender)
{
  Form3->Label3->Enabled = False;
  Form3->Edit2->Enabled = False;
  Form3->Button1->Enabled = False;
  Form3->Label2->Enabled = True;
  Form3->Edit1->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
  if (OpenDialog1->Execute()) filename =  OpenDialog1->FileName;
  Form3->Edit2->Text = filename;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
  if (Form3->RadioButton1->Checked) {
	Number_of_vertices = StrToInt(Form3->Edit1->Text);
	Form1->StringGrid1->ColCount = Number_of_vertices+1;
	Form1->StringGrid1->RowCount = Number_of_vertices+1;
	Form1->CreateMatrix();
	Form1->TitleGrid();
  }
  else
  {
	 int ch, m[6][8];
	 FILE *f;
	 if ((f = fopen(filename.c_str(), "rt")) == NULL)
	 {
	   ShowMessage("Неудалось открыть файл");
	   return;
	 }
	 for(int i=0; i<6; i++)
	   {
	   for(int j=0; j<8; j++)
	   {
		 fscanf(f, "%d", &ch);
		 m[i][j]=ch;
	   }
	 }
	 fclose(f);
  }
  Form1->Label2->Visible = False;
  Form1->Label3->Visible = False;
  Form1->Label4->Visible = False;
  Form1->StringGrid1->Visible = True;
  Form1->BitBtn1->Visible = True;
  Close();
}
//---------------------------------------------------------------------------

