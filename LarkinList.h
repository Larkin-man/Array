/**********************************************************************\
*   Двусвязный список с возможностью сортировки и создания коллекций.  *                                       *
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
   typedef int __fastcall (*TDCLSortCompare)(T* Item1, T* Item2); //Параметры для сортирующей функции   > 0 (positive)	Item1 is less than Item20	Item1 is equal to Item2< 0 (negative)	Item1 is greater than Item2//typedef int __fastcall (*TListSortCompare)(void * Item1, void * Item2);
   /*/example for int:  > 0 (positive)	Item1 is less than Item20	Item1 is equal to Item2< 0 (negative)	Item1 is greater than Item2
      int __fastcall CompareFunc(int *Item1, int *Item2)
      {  if (Item1.A > Item2.A)
            return 1;
         if (Item1.A < Item2.A)
            return -1;
         return 0;      }     */
   int FCount;
   int Mid;
   struct Link
   {
      T *Store;
      Link *next;
      Link *prev;
   }
   *Begin, *End, *Linker, *FIterator;

protected:
   Link* Get(int Index) const;         //Получить элемент списка по индексу
   Link* CreateLink(T* Item);
   Link* Find(T* Item);    //Ищет элемент списка по объекту. NULL если нету. |C|
   void Erase(Link *ExcludedLink);
   void SetCount(int NewCount)    { FCount = NewCount; Mid = FCount/2;   }
   void Concatenate(Link *ParentLink, Link *CurrLink);
   void Push(Link* Position, Link* CurrLink); //Вставляет объект на мето Position, сдвигая тот и все последующие. Count++
   inline Link* GoForvard(Link* CurrLink, int Pos);
   inline Link* GoBack(Link* CurrLink, int Pos);
   TDCLSortCompare FCompareFunction;
      void SetCompareFunction(TDCLSortCompare rhs);
   bool FSorted;                            
      void SetSorted(bool Value);
   TDuplicates FDuplicates;
      void SetDuplicates(TDuplicates phs);
   void QuickSort(Link *pLeft, Link *pRight);
   bool MidReveal;
   void InitIterator(T* Item);
   T* GetIterator(void);
                                                        //TList
public:
   LRList(); //Конструктор
   __property int Count = { read=FCount };
   int Add(T* Item); //Добавляет в конец списка или если Sorted то в позицию. Возвращает индекс. Индекс первого - 0
   int AddVector(T** Mas, int count);   //AddVector - добавить массив в конец. Sorted = false
   int CreateCopyOf(T& Item);
   void Insert(int Index, T* Item); //Вставляет объект на мето Index, сдвигая тот и все последующие
   T* operator[](int Index);    //Вернуть объект на позиции Index. [0..Count-1]
   const T* operator[](int Index) const
      {  return Get(Index)->Store;   }
   __property T* Iterator = {read=GetIterator, write=InitIterator}; //Авто инкремент при обращении. Задать NULL - начало списка
   __property TDCLSortCompare CompareFunction = {read=FCompareFunction, write=SetCompareFunction}; //Сравнивающая функция
   __property bool Sorted = { read=FSorted, write=SetSorted }; //Запуск сортировки. Нужна сравнивающая функция
   __property TDuplicates Duplicates = {read=FDuplicates, write=SetDuplicates}; //Работа с дубликатами. Нужна сравнивающая функция
   int IndexOf(T* Item);   //Возвращает индекс первого появление объекта. -1 если нет. Если CompareFunction не NULL то вызывается она
   void Exchange(int Index1, int Index2); //Меняет местами элементы и устанавливает Sorted в false
   T* First(void);
	T* Last(void);
   void Delete(int Index);       //Удаляет с нуля. уменьшает countf на 1 по идее память не очищает . очистка памяти это уменьшение Capacity
   void Remove(T* Item);   //Удаляет первую копию, возвращает индекс перед удалением, уменьшает Count
   void Clear(void);
   ~LRList(void)  {  Clear(); } 
};
#endif

