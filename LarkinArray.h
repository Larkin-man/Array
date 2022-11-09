//Динамический массив. v1.0 При создании элементов конструкторы не вызываются!
//Опции, задаются командами #define:
//Для простых типов (int, double etc):
//#define LRArraySimpleType
//Автосортировка для простых типов:
//#define LRArrayAutoSort
//Создание коллекции (игнорируются добавление дубликата):
//Define LRArrayCollection
//---------------------------------------------------------------------------
#undef LARKINARRAY
#ifdef LRArrayAutoSort
   #ifndef LRArraySimpleType
      #error Version 1.0 does not contain sorting for compound types. Define LRArraySimpleType
   #endif
   #ifdef LRArrayCollection
      #ifndef LarkinCollectionSortH
         #define LarkinCollectionSortH
         #define LARKINARRAY LRCollectionSort
      #endif
   #else
      #ifndef LarkinArraySortH
         #define LarkinArraySortH
         #define LARKINARRAY LRArraySort
      #endif
   #endif
#else
   #ifdef LRArrayCollection
      #ifndef LarkinCollectionH
         #define LarkinCollectionH
         #define LARKINARRAY LRCollection
      #endif
   #else
      #ifndef LarkinArrayH
         #define LarkinArrayH
         #define LARKINARRAY LRDynArray
      #endif
   #endif
#endif

#ifdef LARKINARRAY
   #ifndef LRArraySimpleType
      #include <new>
   #endif
#include <alloc.h>
#include <mem.h>        
//---------------------------------------------------------------------------
#define TYPEDf
#ifdef TYPED
 #define TEMPLT template< class T >
 #define T T
#else
 #define TEMPLT
 #define T int
#endif

// Динамический массив
TEMPLT class LARKINARRAY
{
private:
	T *Data;    //Одномерный массив
	int FCapacity; //Размер выделенной памяти
	int FCount; //Число элементов в массиве (может быть меньше размера выделенной памяти)
   //Защита от копирования
   LARKINARRAY(const LARKINARRAY&) ;
   LARKINARRAY&operator=(const LARKINARRAY&) ;
   #ifdef LRArrayAutoSort
      #ifdef LRArraySimpleType
      bool SortingAccordIncrease;
      #endif
   #endif
                          
protected:
   //Выделить память
	void SetCapacity(int newCapacity)
	{                
		if ( Data )
			Data = (T*)realloc( Data, newCapacity * sizeof(T) );
		else
			Data = (T*)malloc( newCapacity * sizeof(T) );
      //Data = new T[newCapacity];
		FCapacity = newCapacity;
	}

	//Скопировать часть массива после idx на num : направо+ налево-
	void MoveElements(int idx, int num)
	{
		int numBytesToCopy = (FCount-idx) * sizeof(T);
		if (numBytesToCopy > 0)
			memmove(&Data[idx+num], &Data[idx], numBytesToCopy);
	}
         
   int AddCheck(const T& el)
   {
      if (FCount == 0)
         return 0;
      int Pos = 0;
      if (AutoSort)
      {
         #ifdef LRArraySimpleType
         if (SortingAccordIncrease)
         {
            for (; Pos < FCount; Pos++)
               if (Data[Pos] >= el)
                  break;
         }
         else
         {
            for (; Pos < FCount; Pos++)
               if (Data[Pos] <= el)
                  break;
         }
         #endif
      }
      if (Duplicates != dupAccept)
      {
         
      }
      if ( (AutoSort)&&(Duplicates != dupAccept) )
      {
         for (int i=0; i < FCount; i++)
         {
            if (Data[i] == el)
               return i;
         }

      }
   }
   //*/

public:
   //Конструктор для LRDynArray и LRCollection с одним параметром
   //Конструктор для LRDynArraySort и LRCollectionSort с двумя параметрами. Сортировка задается в самом начале
   #ifdef LRArrayAutoSort
   LARKINARRAY(bool sortingAccordingIncrease, int capacity = 0)
   {
      SortingAccordIncrease = sortingAccordingIncrease;
   #else
	LARKINARRAY(int capacity = 0)
	{
   #endif
		Data = 0;
      FCount = 0;
		if (capacity > 0)
		   SetCapacity(capacity);   
      else
         FCapacity = 0;
	}

   ~LARKINARRAY()
	{
      #ifdef LRArraySimpleType
      FCount = 0;
      #else
      Erase();
      #endif
      if ( Data )
		{
			free( Data );
         //delete [] Data;
		}

	}
   __property int Capacity = { read=FCapacity, write=SetCapacity };
   __property int Count = { read=FCount };
   
	// Доступ к элементам
	T& operator[]( int i ) { return Data[i]; }
	const T& operator[]( int i ) const { return Data[i]; }
	// Базовый указатель
	T *Base() { return Data; }
	const T *Base() const { return Data; }
	// Первый и последний элементы
	T& First() { return Data[0]; }
	T& Last() { return Data[FCount-1]; }
	const T& First() const { return Data[0]; }
	const T& Last() const { return Data[FCount-1]; }
	bool Empty() const { return FCount == 0; } // Пустой?

   #ifdef LRArrayAutoSort
   void Add(const T& el)
	{
		EnsureCapacity(FCount+1);
		ConstructCopy(FCount, el);
		FCount++;
	}
   #else
	//Добавить элемент в конец массива
	void PushBack(const T& el)
	{
		EnsureCapacity(FCount+1);
		ConstructCopy(FCount, el);
		FCount++;
	}
   #endif

   void ConstructCopy(int i, const T& el)
	{
      #ifdef LRArraySimpleType
      Data[i] = el;
      #else
      new  (&Data[i]) T( el );  //Конструктор не вызывается
      #endif
	}
	void PopBack() // Удалить последний элемент
	{
      #ifndef LRArraySimpleType
      Destruct(FCount-1);
      #endif
		FCount--;
	}
   #ifndef LRArraySimpleType
   void Destruct(int i)
	{
		Data[i].~T();
	}
   #endif
   //Добавить элемент в произвольное место
   #ifndef LRArrayAutoSort
	void Insert(int idx, const T& el)
	{
      if (idx < 0)
         idx = 0;
      else if (idx > FCount)
         idx = FCount;
		EnsureCapacity(FCount+1);
		MoveElements(idx, 1);
      //Data[idx] = el;
		ConstructCopy(idx, el);
		FCount++;
	}
   #endif

	// Удалить произвольный элемент
	void Remove(int idx)
	{
      if (FCount <= 0)
      {
         FCount = 0;
         return;
      }
      if (idx < 0)
         idx = 0;
      else if (idx > FCount)
         idx = FCount;
		Destruct(idx);
		MoveElements(idx+1, -1);
		FCount--;
	}

	//Очистить!
	void Erase()
	{
		while (FCount > 0)
			PopBack();
	}            

	//Найти индекс элемента
	int Find(const T& el) const
	{
		for (int i=0; i < FCount; i++)
		{
			if (Data[i] == el)
				return i;
		}
		return -1;
	}  

	//Найти и уничтожить!
	void RemoveElement(const T& el)
	{
		int idx = Find( el );
		if (idx >= 0)
			Remove( idx );
	}         

	//Убедимся, что памяти хватит для хранения по крайней мере этого числа элементов.
	inline void EnsureCapacity(int capacity)
	{
		if ( capacity > FCapacity )
		{
			int newCapacity = FCapacity;
			if ( newCapacity == 0 )
				newCapacity = 4;
			while ( newCapacity < capacity )
				newCapacity *= 2;    
			SetCapacity( newCapacity );
		}
	}

};
#endif
#undef LRArraySimpleType
#undef LRArrayAutoSort
#undef LRArrayCollection
