//---------------------------------------------------------------------------

#pragma hdrstop

#include "LarkinMatrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

int **matrix;

void CreateMatrix(int Number_of_vertices)
{
  int i;
  matrix = (int**)malloc(Number_of_vertices*sizeof(int*));
  for (i = 0; i < Number_of_vertices; i++) {
	matrix[i]=(int*)malloc(Number_of_vertices*sizeof(int));
  }
}
