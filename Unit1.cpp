//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


int Number_of_vertices = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateMatrix()
{
  int i;
  Form1->matrix = new int*[Number_of_vertices + 1];
  for (i = 0; i < Number_of_vertices + 1; i++)
  {
	Form1->matrix[i] = new int[Number_of_vertices + 1];
  }
  Form1->matrix2 = new int*[Number_of_vertices + 1];
  for (i = 0; i < Number_of_vertices + 1; i++)
  {
	Form1->matrix2[i] = new int[Number_of_vertices + 1];
  }
  Form1->column_status = new String[Number_of_vertices + 1];
  for (i = 0; i < Number_of_vertices; i++) {
    Form1->column_status[i] = "-1";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TitleGrid()
{
  //именнуем ячейки таблицы
  int i;
  for (i = 0; i < Number_of_vertices; i++) {
	Form1->StringGrid1->Cells[0][i+1] = "E"+IntToStr(i);
	Form1->StringGrid1->Cells[i+1][0] = "E"+IntToStr(i);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  TitleGrid();
  //заполняем таблицу
  Form1->StringGrid1->Cells[2][1] = 17;
  Form1->StringGrid1->Cells[1][2] = 0;
  Form1->StringGrid1->Cells[1][3] = 0;
  Form1->StringGrid1->Cells[3][1] = 19;
  Form1->StringGrid1->Cells[3][2] = 4;
  Form1->StringGrid1->Cells[4][2] = 12;
  Form1->StringGrid1->Cells[4][3] = 8;
  Form1->StringGrid1->Cells[3][4] = 6;
  Form1->StringGrid1->Cells[3][5] = 0;
  Form1->StringGrid1->Cells[4][5] = 0;
  Form1->StringGrid1->Cells[5][3] = 9;
  Form1->StringGrid1->Cells[5][4] = 24;
}
//---------------------------------------------------------------------------
void ReadMatrix()
{
	int i,j;
	for (i = 0; i < Number_of_vertices+1; i++) {
	  for (j = 0; j < Number_of_vertices+1; j++) {
		if (Form1->StringGrid1->Cells[i+1][j+1] == "") {
		  Form1->matrix[j][i] = -1;
		}
		else {
		  Form1->matrix[j][i] = StrToInt(Form1->StringGrid1->Cells[i+1][j+1]);
		}
	  }
	}
for (i = 0; i < Number_of_vertices+1; i++) {
	  for (j = 0; j < Number_of_vertices+1; j++) {
		if (Form1->StringGrid1->Cells[i+1][j+1] == "") {
		  Form1->matrix2[j][i] = -1;
		}
		else {
		  Form1->matrix2[j][i] = StrToInt(Form1->StringGrid1->Cells[i+1][j+1]);
		}
	  }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ReadFromFile(char *path)
{
  int ch, m[6][8];
  FILE *f;
  if ((f = fopen(path, "rt")) == NULL)
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
//---------------------------------------------------------------------------
void UpdateStrigGrid()
{
	int i,j;
	for (i = 0; i < Number_of_vertices+1; i++) {
	  for (j = 0; j < Number_of_vertices+1; j++) {
		if (Form1->matrix[j][i] != -1) {
			Form1->StringGrid1->Cells[i+1][j+1] = IntToStr(Form1->matrix[j][i]);
		}
	  }
	}
}
//---------------------------------------------------------------------------
int mark_column()
{
  //помечаем столбцы
  int i, j;
  Form1->column_status[0] = '*';
  for (i = 0; i < Number_of_vertices; i++) {
	for (j = 0; j < Number_of_vertices; j++) {
	  if (Form1->matrix[i][j] > 0 && Form1->column_status[j] == "-1") {
		Form1->column_status[j] = i;
	  }
	}
  }
  if (Form1->column_status[3] == "-1" || Form1->column_status[4] == "-1") {
	return 0;
  }
  else {
	for (i = 0; i < Number_of_vertices; i++) {
		Form1->StringGrid2->Cells[i][0] = Form1->column_status[i];
	}
	return 1;
  }
}
//---------------------------------------------------------------------------
void Calculation()
{
	int min, i;
	int count = 1;
	int *array =(int*) malloc (count * sizeof (int));
	int **mtx=(int**)malloc(count*sizeof(int*));
	int strng = StrToInt(Form1->column_status[4]);
	int column = 4;
	mtx[count-1]=(int*)malloc(2*sizeof(int));
	while (1)
	{
		mtx[count-1][0] = strng;
		mtx[count-1][1] = column;
		array[count-1] = Form1->matrix[strng][column];
		if (strng == 0) {
			break;
		}
		column = strng;
		strng = StrToInt(Form1->column_status[strng]);
		count++;
		array = (int*) realloc (array, count * sizeof (int));
		mtx=(int**)realloc((void *) mtx,(count)*sizeof(int*));
		mtx[count-1]=(int*)malloc(2*sizeof(int));
	}
	min = array[0];
	for (i = 1; i < count; i++) {
		if (array[i] < min) {
			min = array[i];
		}
	}
	for (i = 0; i < count; i++) {
		Form1->matrix[mtx[i][0]][mtx[i][1]] = Form1->matrix[mtx[i][0]][mtx[i][1]] - min;
	}
}
//---------------------------------------------------------------------------
void prop()
{
	int i,j;
	for (i = 0; i < Number_of_vertices; i++) {
	  for (j = 0; j < Number_of_vertices; j++) {
		if (Form1->matrix[i][j] != -1) {
			Form1->matrix[i][j] = Form1->matrix2[i][j] - Form1->matrix[i][j];
		}
	  }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	ReadMatrix();
	int i, j, p;
	while (mark_column()) {
		Calculation();
		for (j = 0; j < Number_of_vertices; j++) {
			Form1->column_status[j] = "-1";
		}
	}
	prop();
	p = 0;
	for (i = 0; i < Number_of_vertices; i++) {
		if (Form1->matrix[0][i] != -1) {
			p = p + Form1->matrix[0][i];
		}
	}
	Edit1->Text = IntToStr(p);
	Label1->Visible = True;
	Edit1->Visible = True;
	UpdateStrigGrid();
}
//---------------------------------------------------------------------------





void __fastcall TForm1::N3Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
  Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
  Form3->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N10Click(TObject *Sender)
{
  Form1->N10->Checked = !Form1->N10->Checked;
}
//---------------------------------------------------------------------------

