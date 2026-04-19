/*************************************************************\
  Двусвязный список v1.3
  Исправлены критические ошибки управления памятью и логикой
\*************************************************************/
#include <_null.h>
#pragma hdrstop
#include "LarkinList.h"

//---------------------------------------------------------------------------
// Конструктор
TEMPLT LRList<T>::LRList()
{
	FCount = 0;
	Mid = 0;
	Begin = NULL;
	End = NULL;
	FIterator = NULL;
	FCompareFunction = NULL;
	FSorted = false;
	FDuplicates = dupAccept;
	MidReveal = true;
}

//---------------------------------------------------------------------------
// Деструктор
TEMPLT LRList<T>::~LRList()
{
	Clear();
}

//---------------------------------------------------------------------------
// Get - получение узла по индексу
TEMPLT typename LRList<T>::Link* LRList<T>::Get(int Index) const
{
	if (FCount == 0)
		return NULL;
	if (Index <= 0)
		return Begin;
	if (Index >= FCount)
		return End;

	Link* currentLink;
	if (Index > Mid && Mid > 0)
	{
		// С конца
		currentLink = End;
		for (int i = FCount - 1; i > Index; i--)
			currentLink = currentLink->prev;
	}
	else
	{
		// С начала
		currentLink = Begin;
		for (int i = 0; i < Index; i++)
			currentLink = currentLink->next;
	}
	return currentLink;
}

//---------------------------------------------------------------------------
// Find - поиск узла по значению
TEMPLT typename LRList<T>::Link* LRList<T>::Find(T* Item)
{
	if (Item == NULL)
		return NULL;

	Link* currentLink;
	if (FCompareFunction == NULL)
	{
		for (currentLink = Begin; currentLink != NULL; currentLink = currentLink->next)
			if (currentLink->Store == Item)
				return currentLink;
	}
	else
	{
		for (currentLink = Begin; currentLink != NULL; currentLink = currentLink->next)
			if (FCompareFunction(Item, currentLink->Store) == 0)
				return currentLink;
	}
	return NULL;
}

//---------------------------------------------------------------------------
// Push - вставка узла перед Position
TEMPLT void LRList<T>::Push(Link* Position, Link* CurrLink)
{
	if (CurrLink == NULL)
		return;

	if (Position == Begin)
	{
		// В начало
		CurrLink->next = Begin;
		CurrLink->prev = NULL;
		if (Begin != NULL)
			Begin->prev = CurrLink;
		Begin = CurrLink;
		if (End == NULL)
			End = CurrLink;
	}
	else if (Position == NULL)
	{
		// В конец
		CurrLink->next = NULL;
		CurrLink->prev = End;
		if (Begin == NULL)
			Begin = CurrLink;
		else
			End->next = CurrLink;
		End = CurrLink;
	}
	else
	{
		// Между узлами
		CurrLink->next = Position;
		CurrLink->prev = Position->prev;
		if (Position->prev != NULL)
			Position->prev->next = CurrLink;
		Position->prev = CurrLink;
	}
	FCount++;
	
	// Обновляем Mid
	Mid = FCount / 2;
	FSorted = false;
}

//---------------------------------------------------------------------------
// CreateLink - создание нового узла
TEMPLT typename LRList<T>::Link* LRList<T>::CreateLink(T* Item)
{
	Link* NewLink = new Link;
	NewLink->Store = Item;
	NewLink->next = NULL;
	NewLink->prev = NULL;
	return NewLink;
}

//---------------------------------------------------------------------------
// Add - добавление элемента
TEMPLT int LRList<T>::Add(T* Item)
{
	if (Item == NULL)
		return -1;

	if (FDuplicates == dupIgnore)
		if (Find(Item) != NULL)
			return -1;

	Link* NewLink = CreateLink(Item);
	int pos = 0;

	if (FSorted && FCompareFunction != NULL)
	{
		Link* currentLink;
		for (currentLink = Begin; currentLink != NULL; currentLink = currentLink->next, pos++)
		{
			// Если Item < currentLink->Store, вставляем перед
			if (FCompareFunction(Item, currentLink->Store) < 0)
			{
				Push(currentLink, NewLink);
				return pos;
			}
		}
	}

	Push(NULL, NewLink);
	return FCount - 1;
}

//---------------------------------------------------------------------------
// AddVector - добавление массива элементов
TEMPLT int LRList<T>::AddVector(T** Mas, int count)
{
	if (Mas == NULL || count <= 0)
		return -1;

	int addedCount = 0;
	for (int i = 0; i < count; i++)
	{
		if (Mas[i] == NULL)
			continue;

		if (FDuplicates == dupIgnore)
			if (Find(Mas[i]) != NULL)
				continue;

		Link* NewLink = CreateLink(Mas[i]);
		Push(NULL, NewLink);
		addedCount++;
	}

	if (addedCount == 0)
		return -1;

	return FCount - addedCount;
}

//---------------------------------------------------------------------------
// operator[] - доступ по индексу
TEMPLT T* LRList<T>::operator[](int Index)
{
	#ifdef _DEBUG
	if (Index < 0 || Index >= FCount)
		__debugbreak();
	#endif
	Link* node = Get(Index);
	return (node != NULL) ? node->Store : NULL;
}

TEMPLT const T* LRList<T>::operator[](int Index) const
{
	#ifdef _DEBUG
	if (Index < 0 || Index >= FCount)
		__debugbreak();
	#endif
	Link* node = Get(Index);
	return (node != NULL) ? node->Store : NULL;
}

//---------------------------------------------------------------------------
// IndexOf - поиск индекса элемента
TEMPLT int LRList<T>::IndexOf(T* Item)
{
	Link* foundLink = Find(Item);
	if (foundLink == NULL)
		return -1;

	// Вычисляем индекс
	int idx = 0;
	Link* currentLink;
	for (currentLink = Begin; currentLink != NULL; currentLink = currentLink->next, idx++)
		if (currentLink == foundLink)
			return idx;
	return -1;
}

//---------------------------------------------------------------------------
// Insert - вставка по индексу
TEMPLT void LRList<T>::Insert(int Index, T* Item)
{
	if (Item == NULL)
		return;

	if (Index < 0)
		Index = 0;
	if (Index > FCount)
		Index = FCount;

	if (Index < FCount)
		Push(Get(Index), CreateLink(Item));
	else
		Push(NULL, CreateLink(Item));
}

//---------------------------------------------------------------------------
// SetCompareFunction - установка функции сравнения
TEMPLT void LRList<T>::SetCompareFunction(TDCLSortCompare rhs)
{
	if (rhs == NULL)
	{
		FSorted = false;
		FDuplicates = dupAccept;
	}
	FCompareFunction = rhs;
}

//---------------------------------------------------------------------------
// SetSorted - установка режима сортировки
TEMPLT void LRList<T>::SetSorted(bool Value)
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
			// После сортировки Begin может измениться
			Begin = GoBack(Begin, FCount - 1);
		}
	}
	FSorted = Value;
}

//---------------------------------------------------------------------------
// SetDuplicates - установка режима дубликатов
TEMPLT void LRList<T>::SetDuplicates(TDuplicates phs)
{
	if ((phs == dupIgnore || phs == dupError) && FCompareFunction == NULL)
	{
		// Требуется функция сравнения для проверки дубликатов
		FDuplicates = dupAccept;
		return;
	}
	FDuplicates = phs;
}

//---------------------------------------------------------------------------
// QuickSort - быстрая сортировка списка
TEMPLT void LRList<T>::QuickSort(Link* pLeft, Link* pRight)
{
	if (FCompareFunction == NULL || pLeft == NULL || pRight == NULL)
		return;
	if (pLeft == pRight)
		return;
	if (pLeft->next == pRight)
	{
		// Два элемента
		if (FCompareFunction(pLeft->Store, pRight->Store) > 0)
		{
			T* temp = pLeft->Store;
			pLeft->Store = pRight->Store;
			pRight->Store = temp;
		}
		return;
	}

	Link* pPivot = pLeft;
	Link* pCurrent = pLeft->next;
	Link* pLastLess = pLeft;

	while (pCurrent != NULL && pCurrent != pRight->next)
	{
		if (FCompareFunction(pCurrent->Store, pPivot->Store) < 0)
		{
			pLastLess = pLastLess->next;
			T* temp = pCurrent->Store;
			pCurrent->Store = pLastLess->Store;
			pLastLess->Store = temp;
		}
		pCurrent = pCurrent->next;
	}

	// Меняем местами pivot и последний меньший
	T* temp = pPivot->Store;
	pPivot->Store = pLastLess->Store;
	pLastLess->Store = temp;

	// Рекурсия
	if (pLastLess->prev != NULL && pLastLess->prev != pLeft)
		QuickSort(pLeft, pLastLess->prev);
	if (pLastLess->next != NULL && pLastLess->next != pRight)
		QuickSort(pLastLess->next, pRight);
}

//---------------------------------------------------------------------------
// Clear - очистка списка
TEMPLT void LRList<T>::Clear(void)
{
	Link* currentLink = Begin;
	while (currentLink != NULL)
	{
		Link* delLink = currentLink;
		currentLink = currentLink->next;
		// НЕ удаляем Store - класс не владеет этой памятью!
		delLink->Store = NULL;
		delete delLink;
	}
	Begin = NULL;
	End = NULL;
	FCount = 0;
	Mid = 0;
	FIterator = NULL;
}

//---------------------------------------------------------------------------
// Concatenate - соединение двух узлов
TEMPLT void LRList<T>::Concatenate(Link* ParentLink, Link* CurrLink)
{
	if (ParentLink != NULL)
		ParentLink->next = CurrLink;
	if (CurrLink != NULL)
		CurrLink->prev = ParentLink;
}

//---------------------------------------------------------------------------
// Erase - удаление узла
TEMPLT void LRList<T>::Erase(Link* ExcludedLink)
{
	if (ExcludedLink == NULL)
		return;

	if (ExcludedLink == Begin)
		Begin = Begin->next;
	if (ExcludedLink == End)
		End = End->prev;

	Concatenate(ExcludedLink->prev, ExcludedLink->next);
	
	// НЕ удаляем Store - класс не владеет этой памятью!
	ExcludedLink->Store = NULL;
	delete ExcludedLink;

	FCount--;
	Mid = FCount / 2;
}

//---------------------------------------------------------------------------
// Delete - удаление по индексу
TEMPLT void LRList<T>::Delete(int Index)
{
	if (FCount == 0)
		return;
	if (Index < 0 || Index >= FCount)
		return;

	Erase(Get(Index));
}

//---------------------------------------------------------------------------
// Remove - удаление по значению
TEMPLT void LRList<T>::Remove(T* Item)
{
	if (Item == NULL)
		return;
	Erase(Find(Item));
}

//---------------------------------------------------------------------------
// GetIterator - получение следующего элемента итератора
TEMPLT T* LRList<T>::GetIterator(void)
{
	if (FIterator == NULL)
	{
		if (Begin == NULL)
			return NULL;
		FIterator = Begin;
	}
	else
	{
		FIterator = FIterator->next;
	}

	if (FIterator == NULL)
		return NULL;
	return FIterator->Store;
}

//---------------------------------------------------------------------------
// InitIterator - инициализация итератора
TEMPLT void LRList<T>::InitIterator(T* Item)
{
	if (Item == NULL)
		FIterator = Begin;
	else
		FIterator = Find(Item);
}

//---------------------------------------------------------------------------
// Exchange - обмен двух элементов
TEMPLT void LRList<T>::Exchange(int Index1, int Index2)
{
	if (Index1 == Index2)
		return;
	if (Index1 < 0 || Index1 >= FCount || Index2 < 0 || Index2 >= FCount)
		return;

	Link* A = Get(Index1);
	Link* B = Get(Index2);
	if (A == NULL || B == NULL)
		return;

	T* temp = A->Store;
	A->Store = B->Store;
	B->Store = temp;
	FSorted = false;
}

//---------------------------------------------------------------------------
// First - первый элемент
TEMPLT T* LRList<T>::First(void)
{
	if (FCount > 0 && Begin != NULL)
		return Begin->Store;
	return NULL;
}

//---------------------------------------------------------------------------
// Last - последний элемент
TEMPLT T* LRList<T>::Last(void)
{
	if (FCount > 0 && End != NULL)
		return End->Store;
	return NULL;
}

//---------------------------------------------------------------------------
// GoForward - переход вперёд на Pos узлов
TEMPLT typename LRList<T>::Link* LRList<T>::GoForward(Link* Item, int Pos)
{
	if (Item == NULL)
		return NULL;
	Link* currentLink = Item;
	for (int i = 0; i < Pos; i++)
	{
		if (currentLink->next != NULL)
			currentLink = currentLink->next;
		else
			break;
	}
	return currentLink;
}

//---------------------------------------------------------------------------
// GoBack - переход назад на Pos узлов
TEMPLT typename LRList<T>::Link* LRList<T>::GoBack(Link* Item, int Pos)
{
	if (Item == NULL)
		return NULL;
	Link* currentLink = Item;
	for (int i = 0; i < Pos; i++)
	{
		if (currentLink->prev != NULL)
			currentLink = currentLink->prev;
		else
			break;
	}
	return currentLink;
}