/*************************************************************\
* Двусвязный список v1.2                                      *
- Заботится об удалении данных, которые в списке
- bg Нельзя добавлять Add дубликаты при dupaccept иначе clear выдаст шибку
- Можно работать с указателем вне класса (который был передан в add
  но нелязя delete его!!!         *
\*************************************************************/
#include <_null.h>
//#include <stdio.h>
//#include <system.hpp>
//#include <Dialogs.hpp>     //для ShowMessage
//#include <dstring.h>
//#include <Classes.hpp>  //для тстринглист
//#include <conio.h>  //*/
#pragma hdrstop       
#include "LarkinList.h"

//---------------------------------------------------------------------------
//Конструктор
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
//Get - Получить список по индексу
TEMPLT LRList IST::Link* LRList IST::Get(int Index) const
{
   if (Index <= 0)
      return Begin;
   else if (Index >= FCount)
      return End;
   Link *linker;
   if ( Index > Mid )
   {  //C конца
      linker = End;
      for (int i=FCount-1; i>Index; i--)
         linker = linker->prev;
   }
   else
   {  //C начала
      linker = Begin;
      for (int i=0; i<Index; i++)
         linker = linker->next;
   }
   return linker;
}
//---------------------------------------------------------------------------
//Find - Ищет элемент списка по объекту. NULL если нету.
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
//Push - Вставляет объекта перед Position, сдвигая тот и все последующие. Count++
TEMPLT void LRList IST::Push(Link* Position, Link* CurrLink)
{
   //Вставка объекта в начало
   if (Position == Begin) //Еще сработает когда begin=NULL и Pos=NULL
   {  //В начало
      CurrLink->next = Begin;
      CurrLink->prev = NULL;
      if (Begin != NULL)
         Begin->prev = CurrLink;
      Begin = CurrLink;
      if (End == NULL)
         End = CurrLink;
   }
   else if (Position == NULL)
   {   //В самый конец после последнего
      CurrLink->next = NULL;
      CurrLink->prev = End;
      if (Begin == NULL)
         Begin = CurrLink;
      else
         End->next = CurrLink;
      End = CurrLink;
   }
   else
   {  //Вставляет объекта перед Position
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
//CreateItem - Создает элемент списка
TEMPLT inline LRList IST::Link* LRList IST::CreateLink(T* Item)
{
   Link *NewLink = new Link;
   NewLink->Store = Item;
   return NewLink;
}
//---------------------------------------------------------------------------
//Add - Добавить элемент в двусвязный список
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
         { //Вставить перед Линкером
            Push(Linker, NewLink);
            return pos;
         }
   Push(NULL, NewLink); //Вставка в конец
   return FCount-1;
}
//---------------------------------------------------------------------------
//AddVector - добавить массив
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
//operator[] - Вернуть объект на позиции Index. [0..Count-1] (чтение и запись работают)
TEMPLT inline T* LRList IST::operator[](int Index)
{
   return Get(Index)->Store;
}
/*TEMPLT const T& operator[](int Index) const
{     return Get(Index)->Store;}              */
//---------------------------------------------------------------------------
//IndexOf - Возвращает индекс первого появление объекта
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
//Insert - Вставляет объект на мето Index, сдвигая тот и все последующие
TEMPLT void LRList IST::Insert(int Index, T* Item)
{
   if (Index < FCount)
      Push(Get(Index), CreateLink(Item));
   else
      Push(NULL, CreateLink(Item));
   Sorted = false;
}
//---------------------------------------------------------------------------
//SetCompareFunction - Установка сравнивающей функции
TEMPLT void LRList IST::SetCompareFunction(TDCLSortCompare rhs)
{
   if (rhs == NULL)
   {
      FSorted = false;
      FDuplicates = dupAccept;
   }
   //При изменении условий нужно запустить по новой if sorted == true
   FCompareFunction = rhs;
}
//---------------------------------------------------------------------------
//SetSorted - Запуск сортировки и автосоритровки
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
//SetDuplicates - Работа с дубликатами
TEMPLT void LRList IST::SetDuplicates(TDuplicates phs)
{
   if ( (phs == dupIgnore)||(phs == dupError) )
   {
      if (FCompareFunction == NULL)
      {
         FDuplicates = dupAccept;
         return;
      }
      //Тут должен быть запуск удаления дубликатов
   }
   FDuplicates = phs;
}
//--------------------------------------------------------------------------- */
//QuickSort - Быстрая сортировка
TEMPLT void LRList IST::QuickSort(Link *pLeft, Link *pRight)
{
   if (FCompareFunction == NULL)
      return;
	Link *pStart;
	Link *pCurrent;
	T* nCopyInteger;
	// сортировка окончена - выход
	if (pLeft == pRight) return;
	// установка двух рабочих указателей - Start и Current
	pStart = pLeft;
	pCurrent = pStart->next;
	// итерация по списку слева направо
	while (1)
	{
		//if (pStart->Store < pCurrent->Store)
      if (FCompareFunction(pStart->Store, pCurrent->Store) > 0) //точно >.
		{
			nCopyInteger = pCurrent->Store;
			pCurrent->Store = pStart->Store;
			pStart->Store = nCopyInteger;
		}	
		
		if (pCurrent == pRight) break;
		pCurrent = pCurrent->next;
	}
	// переключение First и Current - максимум попадает в правый конец списка
   //ShowMessage(IntToStr(pLeft->Store) + " и "+IntToStr(pCurrent->Store));
	nCopyInteger = pLeft->Store;
	pLeft->Store = pCurrent->Store;
	pCurrent->Store = nCopyInteger;
	// сохранение Current
	Link *pOldCurrent = pCurrent;
	// рекурсия
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
//Clear - Очищает всё
TEMPLT void LRList IST::Clear(void)
{
   Link *DelLink, *CurrLink = Begin;
	while (CurrLink != NULL)
	{
		DelLink = CurrLink;
		CurrLink = CurrLink->next;
      if (DelLink->Store != NULL)
      {
      delete DelLink->Store; //new должен быть снаружи класса!
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
//Сoncatenate - Соединяет два элемента
TEMPLT void LRList IST::Concatenate(Link *parent, Link *Item)
{
   if (parent != NULL)
       parent->next = Item;
   if (Item != NULL)
       Item->prev = parent;
}
//---------------------------------------------------------------------------
//Erase - Удаляет элемент списка
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
//Delete - Удаляет элемент с 0
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
//Remove - Удаляет первую копию, возвращает индекс перред удалением, уменьшает Count
TEMPLT void LRList IST::Remove(T* Item)
{
   Erase(Find(Item));
}
//---------------------------------------------------------------------------
//GetIterator - Возвращает текущий элемент и переходит к следующему
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
//SetIterator - Установить в 0 чтобы начать
TEMPLT void LRList IST::InitIterator(T* Item)
{
   if (Item == NULL)
      FIterator = Begin;
   else
      FIterator = Find(Item);
}
//---------------------------------------------------------------------------
//Exchange - Поменять местами элементы
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
//First - Указатель на первый
TEMPLT T* LRList IST::First(void)
{
   if (FCount > 0)
      return Begin->Store;
   return NULL;
}
//---------------------------------------------------------------------------
//First - Указатель на последний
TEMPLT T* LRList IST::Last(void)
{
   //return operator[](FCount-1);
   if (FCount > 0)
      return End->Store;
   return NULL;
}
//---------------------------------------------------------------------------
//GoForvard - Двигать указатель вперед
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
//GoBack - Двигать указатель назад
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
