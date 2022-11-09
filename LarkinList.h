/**********************************************************************\
*   Äâóñâÿçíûé ñïèñîê ñ âîçìîæíîñòüþ ñîðòèðîâêè è ñîçäàíèÿ êîëëåêöèé.  *                                       *
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
   typedef int __fastcall (*TDCLSortCompare)(const T & Item1, const T & Item2); //Ïàðàìåòðû äëÿ ñîðòèðóþùåé ôóíêöèè   > 0 (positive)	Item1 is less than Item20	Item1 is equal to Item2< 0 (negative)	Item1 is greater than Item2//typedef int __fastcall (*TListSortCompare)(void * Item1, void * Item2);
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
   Data* Get(int Index);         //Ïîëó÷èòü ýëåìåíò ñïèñêà ïî èíäåêñó
   Data* CreateItem(const T& Item);
   Data* Find(const T& Item);    //Èùåò ýëåìåíò ñïèñêà ïî îáúåêòó. NULL åñëè íåòó. |C|
   void Erase(Data *ExcludedItem);
   void SetCount(int NewCount)    { FCount = NewCount; Mid = FCount/2;   }
   void Concatenate(Data *parent, Data *Item);
   void Push(Data* Position, Data* Item); //Âñòàâëÿåò îáúåêò íà ìåòî Position, ñäâèãàÿ òîò è âñå ïîñëåäóþùèå. Count++
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
   LRList(); //Êîíñòðóêòîð
   __property int Count = { read=FCount, write=SetCount };
   int Add(const T& Item); //Äîáàâëÿåò îáúåêò â êîíåö ñïèñêà èëè åñëè Sorted òî â ïîçèöèþ. Âîçâðàùàåò èíäåêñ. Èíäåêñ ïåðâîãî - 0
   int AddVector(T* Mas, int Count);   //AddVector - äîáàâèòü ìàññèâ â êîíåö. Sorted = false
   void Insert(int Index, const T& Item); //Âñòàâëÿåò îáúåêò íà ìåòî Index, ñäâèãàÿ òîò è âñå ïîñëåäóþùèå
   T& operator[](int Index);    //Âåðíóòü îáúåêò íà ïîçèöèè Index. [0..Count-1]
   const T& operator[](int Index) const
      {  return Get(Index)->Store;   }
   //__property T Iterator = { read=GetIterator, write=SetIterator} ;
   void InitIterator(int Index);
   T* Iterator(void);
   __property TDCLSortCompare CompareFunction = {read=FCompareFunction, write=SetCompareFunction}; //Ñðàâíèâàþùàÿ ôóíêöèÿ
   __property bool Sorted = { read=FSorted, write=SetSorted }; //Çàïóñê ñîðòèðîâêè. Íóæíà ñðàâíèâàþùàÿ ôóíêöèÿ
   __property TDuplicates Duplicates = {read=FDuplicates, write=SetDuplicates}; //Ðàáîòà ñ äóáëèêàòàìè. Íóæíà ñðàâíèâàþùàÿ ôóíêöèÿ
   int IndexOf(const T& Item);   //Âîçâðàùàåò èíäåêñ ïåðâîãî ïîÿâëåíèå îáúåêòà. -1 åñëè íåò
   void Exchange(int Index1, int Index2); //Ìåíÿåò ìåñòàìè ýëåìåíòû è óñòàíàâëèâàåò Sorted â false
   T* First(void);
	T* Last(void);
   void Delete(int Index);       //Óäàëÿåò ñ íóëÿ. óìåíüøàåò countf íà 1 ïî èäåå ïàìÿòü íå î÷èùàåò . î÷èñòêà ïàìÿòè ýòî óìåíüøåíèå Capacity
   void Remove(const T& Item);   //Óäàëÿåò ïåðâóþ êîïèþ, âîçâðàùàåò èíäåêñ ïåððåä óäàëåíèåì, óìåíüøàåò Count
   void Clear(void);
   ~LRList(void)  {  Clear(); } 
};
#endif