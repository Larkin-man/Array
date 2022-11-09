/**********************************************************************\
*   ���������� ������ � ������������ ���������� � �������� ���������.  *                                       *
\**********************************************************************/
#ifndef LRListH
#define LRListH
#define PATTN
#ifdef PATTN
 #define TEMPLT template <class T>
 #define IST <T>
#else
 #define TEMPLT
 #define IST
 #define T int
#endif
//---------------------------------------------------------------------------
#ifndef ClassesHPP   
enum TDuplicates { dupIgnore, dupAccept, dupError };
#endif   

TEMPLT class LRList
{
private:
   typedef int __fastcall (*TDCLSortCompare)(const T & Item1, const T & Item2); //��������� ��� ����������� �������   > 0 (positive)	Item1 is less than Item20	Item1 is equal to Item2< 0 (negative)	Item1 is greater than Item2//typedef int __fastcall (*TListSortCompare)(void * Item1, void * Item2);
   /*/example for int:  > 0 (positive)	Item1 is less than Item20	Item1 is equal to Item2< 0 (negative)	Item1 is greater than Item2
      int __fastcall CompareFunc(const int &Item1, const int &Item2)
      {  if (Item1.A > Item2.A)
            return 1;
         if (Item1.A < Item2.A)
            return -1;
         return 0;      }     */
   int FCount;
   int Mid;
   struct Data
   {
      T Store;
      Data *next;
      Data *prev;
   }
   *Begin, *End, *Linker, *FIterator;

protected:
   Data* Get(int Index);         //�������� ������� ������ �� �������
   Data* CreateItem(const T& Item);
   Data* Find(const T& Item);    //���� ������� ������ �� �������. NULL ���� ����. |C|
   void Erase(Data *ExcludedItem);
   void SetCount(int NewCount)    { FCount = NewCount; Mid = FCount/2;   }
   void Concatenate(Data *parent, Data *Item);
   void Push(Data* Position, Data* Item); //��������� ������ �� ���� Position, ������� ��� � ��� �����������. Count++
   inline Data* GoForvard(Data* Item, int Pos);
   inline Data* GoBack(Data* Item, int Pos);
   TDCLSortCompare FCompareFunction;
      void SetCompareFunction(TDCLSortCompare phs);
   bool FSorted;                            
      void SetSorted(bool Value);
   TDuplicates FDuplicates;
      void SetDuplicates(TDuplicates phs);
   void QuickSort(Data *pLeft, Data *pRight);

public:
   LRList(); //�����������
   __property int Count = { read=FCount, write=SetCount };
   int Add(const T& Item); //��������� ������ � ����� ������ ��� ���� Sorted �� � �������. ���������� ������. ������ ������� - 0
   int AddVector(T* Mas, int Count);   //AddVector - �������� ������ � �����. Sorted = false
   void Insert(int Index, const T& Item); //��������� ������ �� ���� Index, ������� ��� � ��� �����������
   T& operator[](int Index);    //������� ������ �� ������� Index. [0..Count-1]
   const T& operator[](int Index) const
      {  return Get(Index)->Store;   }
   //__property T Iterator = { read=GetIterator, write=SetIterator} ;
   void InitIterator(int Index);
   T* Iterator(void);
   __property TDCLSortCompare CompareFunction = {read=FCompareFunction, write=SetCompareFunction}; //������������ �������
   __property bool Sorted = { read=FSorted, write=SetSorted }; //������ ����������. ����� ������������ �������
   __property TDuplicates Duplicates = {read=FDuplicates, write=SetDuplicates}; //������ � �����������. ����� ������������ �������
   int IndexOf(const T& Item);   //���������� ������ ������� ��������� �������. -1 ���� ���
   void Exchange(int Index1, int Index2); //������ ������� �������� � ������������� Sorted � false
   T* First(void);
	T* Last(void);
   void Delete(int Index);       //������� � ����. ��������� countf �� 1 �� ���� ������ �� ������� . ������� ������ ��� ���������� Capacity
   void Remove(const T& Item);   //������� ������ �����, ���������� ������ ������ ���������, ��������� Count
   void Clear(void);
   ~LRList(void)  {  Clear(); } 
};
#endif

