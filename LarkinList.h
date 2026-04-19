/**********************************************************************\
  Двусвязный список с поддержкой сортировки и управления дубликатами.
  Версия 1.3
\**********************************************************************/
#ifndef LRListH
#define LRListH

#define PATTN
#ifdef PATTN
	#define TEMPLT template <class T>
	#define IST
#else
	#define TEMPLT
	#define IST
	#define T int
#endif

//---------------------------------------------------------------------------
#ifndef ClassesHPP
enum TDuplicates { dupIgnore, dupAccept, dupError };
#endif

typedef int __fastcall (*TDCLSortCompare)(T* Item1, T* Item2);
// Возвращает: >0 если Item1 > Item2, 0 если равны, <0 если Item1 < Item2

TEMPLT class LRList
{
private:
	struct Link
	{
		T* Store;
		Link* next;
		Link* prev;
	};

	Link* Begin;
	Link* End;
	Link* FIterator;
	int FCount;
	int Mid;
	bool MidReveal;
	TDCLSortCompare FCompareFunction;
	bool FSorted;
	TDuplicates FDuplicates;

	// Запрещаем копирование (Rule of Three)
	LRList(const LRList&);
	LRList& operator=(const LRList&);

protected:
	Link* Get(int Index) const;
	Link* CreateLink(T* Item);
	Link* Find(T* Item);
	void Erase(Link* ExcludedLink);
	void Concatenate(Link* ParentLink, Link* CurrLink);
	void Push(Link* Position, Link* CurrLink);
	Link* GoForward(Link* CurrLink, int Pos);
	Link* GoBack(Link* CurrLink, int Pos);
	void QuickSort(Link* pLeft, Link* pRight);
	void SetCompareFunction(TDCLSortCompare rhs);
	void SetSorted(bool Value);
	void SetDuplicates(TDuplicates phs);
	void InitIterator(T* Item);
	T* GetIterator(void);

public:
	LRList();
	~LRList();

	__property int Count = { read = FCount };
	int Add(T* Item);
	int AddVector(T** Mas, int count);
	void Insert(int Index, T* Item);
	T* operator[](int Index);
	const T* operator[](int Index) const;
	__property T* Iterator = { read = GetIterator, write = InitIterator };
	__property TDCLSortCompare CompareFunction = { read = FCompareFunction, write = SetCompareFunction };
	__property bool Sorted = { read = FSorted, write = SetSorted };
	__property TDuplicates Duplicates = { read = FDuplicates, write = SetDuplicates };
	int IndexOf(T* Item);
	void Exchange(int Index1, int Index2);
	T* First(void);
	T* Last(void);
	void Delete(int Index);
	void Remove(T* Item);
	void Clear(void);
};

#endif