//������������ ������. v1.0 ��� �������� ��������� ������������ �� ����������!
//�����, �������� ��������� #define:
//��� ������� ����� (int, double etc):
//#define LRArraySimpleType
//�������������� ��� ������� �����:
//#define LRArrayAutoSort
//�������� ��������� (������������ ���������� ���������):
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

// ������������ ������
TEMPLT class LARKINARRAY
{
private:
	T *Data;    //���������� ������
	int FCapacity; //������ ���������� ������
	int FCount; //����� ��������� � ������� (����� ���� ������ ������� ���������� ������)
   //������ �� �����������
   LARKINARRAY(const LARKINARRAY&) ;
   LARKINARRAY&operator=(const LARKINARRAY&) ;
   #ifdef LRArrayAutoSort
      #ifdef LRArraySimpleType
      bool SortingAccordIncrease;
      #endif
   #endif
                          
protected:
   //�������� ������
	void SetCapacity(int newCapacity)
	{                
		if ( Data )
			Data = (T*)realloc( Data, newCapacity * sizeof(T) );
		else
			Data = (T*)malloc( newCapacity * sizeof(T) );
      //Data = new T[newCapacity];
		FCapacity = newCapacity;
	}

	//����������� ����� ������� ����� idx �� num : �������+ ������-
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
   //����������� ��� LRDynArray � LRCollection � ����� ����������
   //����������� ��� LRDynArraySort � LRCollectionSort � ����� �����������. ���������� �������� � ����� ������
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
   
	// ������ � ���������
	T& operator[]( int i ) { return Data[i]; }
	const T& operator[]( int i ) const { return Data[i]; }
	// ������� ���������
	T *Base() { return Data; }
	const T *Base() const { return Data; }
	// ������ � ��������� ��������
	T& First() { return Data[0]; }
	T& Last() { return Data[FCount-1]; }
	const T& First() const { return Data[0]; }
	const T& Last() const { return Data[FCount-1]; }
	bool Empty() const { return FCount == 0; } // ������?

   #ifdef LRArrayAutoSort
   void Add(const T& el)
	{
		EnsureCapacity(FCount+1);
		ConstructCopy(FCount, el);
		FCount++;
	}
   #else
	//�������� ������� � ����� �������
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
      new  (&Data[i]) T( el );  //����������� �� ����������
      #endif
	}
	void PopBack() // ������� ��������� �������
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
   //�������� ������� � ������������ �����
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

	// ������� ������������ �������
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

	//��������!
	void Erase()
	{
		while (FCount > 0)
			PopBack();
	}            

	//����� ������ ��������
	int Find(const T& el) const
	{
		for (int i=0; i < FCount; i++)
		{
			if (Data[i] == el)
				return i;
		}
		return -1;
	}  

	//����� � ����������!
	void RemoveElement(const T& el)
	{
		int idx = Find( el );
		if (idx >= 0)
			Remove( idx );
	}         

	//��������, ��� ������ ������ ��� �������� �� ������� ���� ����� ����� ���������.
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
