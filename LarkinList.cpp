/*************************************************************\
* ���������� ������ v1.2                                      *
- ��������� �� �������� ������, ������� � ������
- bg ������ ��������� Add ��������� ��� dupaccept ����� clear ������ �����
- ����� �������� � ���������� ��� ������ (������� ��� ������� � add
  �� ������ delete ���!!!         *
\*************************************************************/
#include <_null.h>
//#include <stdio.h>
//#include <system.hpp>
//#include <Dialogs.hpp>     //��� ShowMessage
//#include <dstring.h>
//#include <Classes.hpp>  //��� �����������
//#include <conio.h>  //*/
#pragma hdrstop       
#include "LarkinList.h"

//---------------------------------------------------------------------------
//�����������
TEMPLT LRList IST::LRList()
{
   FCount = 0;
   Mid = 0;
   Begin = NULL;
   End = NULL;
   FCompareFunction = NULL;
   FSorted = false;
   FDuplicates = dupAccept;   
   FIterator = NULL;
   MidReveal = true;
}
//---------------------------------------------------------------------------
//Get - �������� ������ �� �������
TEMPLT LRList IST::Link* LRList IST::Get(int Index) const
{
   if (Index <= 0)
      return Begin;
   else if (Index >= FCount)
      return End;
   Link *linker;
   if ( Index > Mid )
   {  //C �����
      linker = End;
      for (int i=FCount-1; i>Index; i--)
         linker = linker->prev;
   }
   else
   {  //C ������
      linker = Begin;
      for (int i=0; i<Index; i++)
         linker = linker->next;
   }
   return linker;
}
//---------------------------------------------------------------------------
//Find - ���� ������� ������ �� �������. NULL ���� ����.
TEMPLT LRList IST::Link* LRList IST::Find(T* Item)
{  
   if (FCompareFunction == NULL)
   {
      for (Linker = Begin; Linker != NULL; Linker=Linker->next)
         if (Linker->Store == Item)
            return Linker;
   }
   else
   {
      for (Linker = Begin; Linker != NULL; Linker=Linker->next)
         if (FCompareFunction(Item, Linker->Store) == 0)
            return Linker;
   }
   return NULL;
}
//---------------------------------------------------------------------------
//Push - ��������� ������� ����� Position, ������� ��� � ��� �����������. Count++
TEMPLT void LRList IST::Push(Link* Position, Link* CurrLink)
{
   //������� ������� � ������
   if (Position == Begin) //��� ��������� ����� begin=NULL � Pos=NULL
   {  //� ������
      CurrLink->next = Begin;
      CurrLink->prev = NULL;
      if (Begin != NULL)
         Begin->prev = CurrLink;
      Begin = CurrLink;
      if (End == NULL)
         End = CurrLink;
   }
   else if (Position == NULL)
   {   //� ����� ����� ����� ����������
      CurrLink->next = NULL;
      CurrLink->prev = End;
      if (Begin == NULL)
         Begin = CurrLink;
      else
         End->next = CurrLink;
      End = CurrLink;
   }
   else
   {  //��������� ������� ����� Position
      CurrLink->next = Position;
      CurrLink->prev = Position->prev;
      Position->prev->next = CurrLink;
      Position->prev = CurrLink;
   }
   FCount++;
   MidReveal = !MidReveal;
   if (MidReveal)
      Mid++;
   //Mid = FCount / 2;
}
//---------------------------------------------------------------------------
//CreateItem - ������� ������� ������
TEMPLT inline LRList IST::Link* LRList IST::CreateLink(T* Item)
{
   Link *NewLink = new Link;
   NewLink->Store = Item;
   return NewLink;
}
//---------------------------------------------------------------------------
//Add - �������� ������� � ���������� ������
TEMPLT int LRList IST::Add(T* Item)
{
   if (FDuplicates == dupIgnore)
      if (Find(Item) != NULL)
         return -1;
   Link *NewLink = CreateLink(Item);
   int pos = 0;
   if (Sorted)
      for (Linker = Begin; Linker != NULL; Linker=Linker->next , pos++)
         //if (Item < Linker->Store)
         if (FCompareFunction(Item, Linker->Store) > 0)
         { //�������� ����� ��������
            Push(Linker, NewLink);
            return pos;
         }
   Push(NULL, NewLink); //������� � �����
   return FCount-1;
}
//---------------------------------------------------------------------------
//AddVector - �������� ������
TEMPLT int LRList IST::AddVector(T** Mas, int count)
{
   if (FDuplicates == dupIgnore)
   {
      for (int i=0; i<count; i++)
         if (Find(Mas[i]) != NULL)
         {
            T* temp = Mas[i];
            count--;
            Mas[i] = Mas[count];
            Mas[count] = temp;
            i--;
            continue;
         }
      if (count == 0)
         return -1;
   }
   Link **NewMas = new Link*[count];
   for (int i=0; i<count; i++)
   {
      NewMas[i] = new Link;
      NewMas[i]->Store = Mas[i];
      if (i != 0)
      {
         NewMas[i]->prev = NewMas[i-1];
         NewMas[i-1]->next = NewMas[i];
      }    
   }
   NewMas[0]->prev = End;
   if (End != NULL)
      End->next = NewMas[0];
   if (Begin == NULL)
      Begin = NewMas[0];
   NewMas[count-1]->next = NULL;
   End = NewMas[count-1];
   FCount += count;
   Mid = FCount / 2;
   Sorted = false;         
   return FCount-count;
}
//---------------------------------------------------------------------------
//operator[] - ������� ������ �� ������� Index. [0..Count-1] (������ � ������ ��������)
TEMPLT inline T* LRList IST::operator[](int Index)
{
   return Get(Index)->Store;
}
/*TEMPLT const T& operator[](int Index) const
{     return Get(Index)->Store;}              */
//---------------------------------------------------------------------------
//IndexOf - ���������� ������ ������� ��������� �������
TEMPLT int LRList IST::IndexOf(T* Item)
{
   int Idx = 0;
   if (FCompareFunction == NULL)
   {
      for (Linker = Begin; Linker != NULL; Linker=Linker->next , Idx++)
         if (Linker->Store == Item)
            return Idx;
   }
   else
   {
      for (Linker = Begin; Linker != NULL; Linker=Linker->next , Idx++)
         if (FCompareFunction(Item, Linker->Store) == 0)
            return Idx;
   }
   return -1;   
}
//---------------------------------------------------------------------------
//Insert - ��������� ������ �� ���� Index, ������� ��� � ��� �����������
TEMPLT void LRList IST::Insert(int Index, T* Item)
{
   if (Index < FCount)
      Push(Get(Index), CreateLink(Item));
   else
      Push(NULL, CreateLink(Item));
   Sorted = false;
}
//---------------------------------------------------------------------------
//SetCompareFunction - ��������� ������������ �������
TEMPLT void LRList IST::SetCompareFunction(TDCLSortCompare rhs)
{
   if (rhs == NULL)
   {
      FSorted = false;
      FDuplicates = dupAccept;
   }
   //��� ��������� ������� ����� ��������� �� ����� if sorted == true
   FCompareFunction = rhs;
}
//---------------------------------------------------------------------------
//SetSorted - ������ ���������� � ��������������
TEMPLT void LRList IST::SetSorted(bool Value)
{
   if (Value)
   {
      if (FCompareFunction == NULL)
      {
         FSorted = false;
         return;
      }
      if (FCount > 1)
      {
         QuickSort(Begin, End);
         Begin = GoBack(Begin, FCount);
      }
   }
   FSorted = Value;
}
//---------------------------------------------------------------------------
//SetDuplicates - ������ � �����������
TEMPLT void LRList IST::SetDuplicates(TDuplicates phs)
{
   if ( (phs == dupIgnore)||(phs == dupError) )
   {
      if (FCompareFunction == NULL)
      {
         FDuplicates = dupAccept;
         return;
      }
      //��� ������ ���� ������ �������� ����������
   }
   FDuplicates = phs;
}
//--------------------------------------------------------------------------- */
//QuickSort - ������� ����������
TEMPLT void LRList IST::QuickSort(Link *pLeft, Link *pRight)
{
   if (FCompareFunction == NULL)
      return;
	Link *pStart;
	Link *pCurrent;
	T* nCopyInteger;
	// ���������� �������� - �����
	if (pLeft == pRight) return;
	// ��������� ���� ������� ���������� - Start � Current
	pStart = pLeft;
	pCurrent = pStart->next;
	// �������� �� ������ ����� �������
	while (1)
	{
		//if (pStart->Store < pCurrent->Store)
      if (FCompareFunction(pStart->Store, pCurrent->Store) > 0) //����� >.
		{
			nCopyInteger = pCurrent->Store;
			pCurrent->Store = pStart->Store;
			pStart->Store = nCopyInteger;
		}	
		
		if (pCurrent == pRight) break;
		pCurrent = pCurrent->next;
	}
	// ������������ First � Current - �������� �������� � ������ ����� ������
   //ShowMessage(IntToStr(pLeft->Store) + " � "+IntToStr(pCurrent->Store));
	nCopyInteger = pLeft->Store;
	pLeft->Store = pCurrent->Store;
	pCurrent->Store = nCopyInteger;
	// ���������� Current
	Link *pOldCurrent = pCurrent;
	// ��������
	pCurrent = pCurrent->prev;
	if (pCurrent != NULL)
	{
		if ((pLeft->prev != pCurrent) && (pCurrent->next != pLeft))
			QuickSort(pLeft, pCurrent);
	}
	pCurrent = pOldCurrent;
	pCurrent = pCurrent->next;
	if (pCurrent != NULL)
	{
		if ((pCurrent->prev != pRight) && (pRight->next != pCurrent))
			QuickSort(pCurrent, pRight);
	}
}
//---------------------------------------------------------------------------
//Clear - ������� ��
TEMPLT void LRList IST::Clear(void)
{
   Link *DelLink, *CurrLink = Begin;
	while (CurrLink != NULL)
	{
		DelLink = CurrLink;
		CurrLink = CurrLink->next;
      if (DelLink->Store != NULL)
      {
      delete DelLink->Store; //new ������ ���� ������� ������!
      DelLink->Store = NULL;
      }
		delete DelLink;
      DelLink = NULL;
	}
	Begin = NULL; End = NULL;
   FCount = 0;   Mid = 0;
   FIterator = NULL;
}
//---------------------------------------------------------------------------
//�oncatenate - ��������� ��� ��������
TEMPLT void LRList IST::Concatenate(Link *parent, Link *Item)
{
   if (parent != NULL)
       parent->next = Item;
   if (Item != NULL)
       Item->prev = parent;
}
//---------------------------------------------------------------------------
//Erase - ������� ������� ������
TEMPLT void LRList IST::Erase(Link *ExcludedLink)
{
   if (ExcludedLink == NULL)
      return;
   if (ExcludedLink == Begin)
      Begin = Begin->next;
   if (ExcludedLink == End)
      End = End->prev;
   Concatenate(ExcludedLink->prev, ExcludedLink->next);
   delete ExcludedLink->Store;
   ExcludedLink->Store = NULL;
   delete ExcludedLink;
   ExcludedLink = NULL;    //???
   FCount--;
   if (MidReveal)
      Mid--;
   MidReveal = !MidReveal;
}
//---------------------------------------------------------------------------
//Delete - ������� ������� � 0
TEMPLT void LRList IST::Delete(int Index)
{
   if ( FCount == 0 )
      return;
   if ( FCount == 1 )
   {
      Clear();
      return;
   }   
   Erase(Get(Index));
}
//---------------------------------------------------------------------------
//Remove - ������� ������ �����, ���������� ������ ������ ���������, ��������� Count
TEMPLT void LRList IST::Remove(T* Item)
{
   Erase(Find(Item));
}
//---------------------------------------------------------------------------
//GetIterator - ���������� ������� ������� � ��������� � ����������
TEMPLT T* LRList IST::GetIterator(void)
{
   if (FIterator == NULL)
   {
      if (Begin == NULL)
      {   return NULL; }
      else
      {   FIterator = Begin;  }
   }
   T* Curr = FIterator->Store;
   FIterator = FIterator->next;
   return Curr;
}  
//---------------------------------------------------------------------------
//SetIterator - ���������� � 0 ����� ������
TEMPLT void LRList IST::InitIterator(T* Item)
{
   if (Item == NULL)
      FIterator = Begin;
   else
      FIterator = Find(Item);
}
//---------------------------------------------------------------------------
//Exchange - �������� ������� ��������
TEMPLT void LRList IST::Exchange(int Index1, int Index2)
{
   if (Index1 == Index2)
      return;
   if ((Index1 >= FCount) || (Index2 >= FCount))
      return;
   Link *A = Get(Index1);
   Link *B = Get(Index2);
   T* One = A->Store;
   A->Store = B->Store;
   B->Store = One;
   Sorted = false;
}
//---------------------------------------------------------------------------
//First - ��������� �� ������
TEMPLT T* LRList IST::First(void)
{
   if (FCount > 0)
      return Begin->Store;
   return NULL;
}
//---------------------------------------------------------------------------
//First - ��������� �� ���������
TEMPLT T* LRList IST::Last(void)
{
   //return operator[](FCount-1);
   if (FCount > 0)
      return End->Store;
   return NULL;
}
//---------------------------------------------------------------------------
//GoForvard - ������� ��������� ������
TEMPLT inline LRList IST::Link* LRList IST::GoForvard(Link* Item, int Pos)
{
   Link *Link = Item;
   for (int i=0 ; i<Pos; i++)
      if (Link->next != NULL)
         Link = Link->next;
      else
         break;
   return Link;
}
//---------------------------------------------------------------------------
//GoBack - ������� ��������� �����
TEMPLT inline LRList IST::Link* LRList IST::GoBack(Link* Item, int Pos)
{
   Link *Link = Item;
   for (int i=0 ; i<Pos; i++)
      if (Link->prev != NULL)
         Link = Link->prev;
      else
         break;
   return Link;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
