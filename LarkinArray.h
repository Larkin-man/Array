#ifndef LARKINARRAY_OPTIONS_H
#define LARKINARRAY_OPTIONS_H

// Опции, задаются командами #define:
// Для простых типов (int, double etc):
// #define LRArraySimpleType
// Автосортировка для простых типов:
// #define LRArrayAutoSort
// Создание коллекции (игнорируется добавление дубликата):
// #define LRArrayCollection

#undef LARKINARRAY
#undef LRArrayBasic

#ifdef LRArrayAutoSort
	#ifndef LRArraySimpleType
		#error This version does not contain sorting for compound types. Define LRArraySimpleType
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
			#define LRArrayBasic
		#endif
	#endif
#endif

#ifdef LARKINARRAY
	#ifndef LRArraySimpleType
		#include <new>
	#endif

	#include <alloc.h>
	#include <mem.h>
	#include <System.Classes.hpp> // Для TPersistent

	//---------------------------------------------------------------------------
	#define TYPED
	#ifdef TYPED
		#define TEMPLT template< class T >
		#define T T
	#else
		#define TEMPLT
		#define T int
	#endif

// Динамический массив
TEMPLT class LARKINARRAY : public TPersistent
{
private:
	T *Data;               // Одномерный массив
	int FCapacity;         // Размер выделенной памяти
	int FCount;            // Число элементов в массиве
	#ifdef LRArrayAutoSort
		bool FSortingAccordIncrease; // Направление сортировки
	#endif

protected:
	// Выделить/изменить размер буфера
	void SetCapacity(int newCapacity)
	{
		if (newCapacity < 0 || newCapacity == FCapacity)
			return;

		#ifdef LRArraySimpleType
			if (Data)
				Data = (T*)realloc(Data, newCapacity * sizeof(T));
			else
				Data = (T*)malloc(newCapacity * sizeof(T));
		#else
			T* newData = nullptr;
			if (newCapacity > 0)
			{
				newData = (T*)malloc(newCapacity * sizeof(T));
				if (!newData) return;
				for (int i = 0; i < FCount; ++i)
				{
					new (&newData[i]) T(Data[i]);
					Data[i].~T();
				}
			}
			if (Data) free(Data);
			Data = newData;
		#endif
		FCapacity = newCapacity;
	}

	// Установить количество элементов
	void SetCount(int newCount)
	{
		#ifdef LRArraySimpleType
			if (newCount > FCount)
				EnsureCapacity(newCount);
			else if (newCount < 0)
				newCount = 0;
			FCount = newCount;
		#else
			if (newCount < FCount)
			{
				if (newCount < 0) newCount = 0;
				while (FCount > newCount)
					PopBack();
			}
			else if (newCount > FCount)
			{
				EnsureCapacity(newCount);
				for (int i = FCount; i < newCount; ++i)
					new (&Data[i]) T();
				FCount = newCount;
			}
		#endif
	}

	// Сдвиг элементов
	void MoveElements(int idx, int num)
	{
		#ifdef LRArraySimpleType
			int numBytes = (FCount - idx) * sizeof(T);
			if (numBytes > 0)
				memmove(&Data[idx + num], &Data[idx], numBytes);
		#else
			if (num > 0)
			{
				for (int i = FCount - 1; i >= idx; --i)
				{
					new (&Data[i + num]) T(Data[i]);
					Data[i].~T();
				}
			}
			else if (num < 0)
			{
				int shift = -num;
				for (int i = idx; i < FCount; ++i)
				{
					if (i + shift < FCount)
					{
						new (&Data[i]) T(Data[i + shift]);
						Data[i + shift].~T();
					}
				}
			}
		#endif
	}

	// Конструирующее копирование
	void ConstructCopy(int i, const T& el)
	{
		#ifdef LRArraySimpleType
			Data[i] = el;
		#else
			new (&Data[i]) T(el);
		#endif
	}

public:
	// Конструктор
	#ifdef LRArrayAutoSort
		LARKINARRAY(bool sortingAccordingIncrease, int capacity = 0) : TPersistent()
	#else
		LARKINARRAY(int capacity = 0) : TPersistent()
	#endif
	{
		#ifdef LRArrayAutoSort
			FSortingAccordIncrease = sortingAccordingIncrease;
		#endif
		Data = nullptr;
		FCount = 0;
		FCapacity = 0;
		if (capacity > 0)
			SetCapacity(capacity);
	}

	// Конструктор по умолчанию (только для режима без авто-сортировки)
	#ifndef LRArrayAutoSort
		LARKINARRAY() : TPersistent(), Data(nullptr), FCount(0), FCapacity(0) {}
	#endif

	// Конструктор копирования
	LARKINARRAY(const LARKINARRAY& Array) : TPersistent()
	{
		#ifdef LRArrayAutoSort
			FSortingAccordIncrease = Array.FSortingAccordIncrease;
		#endif
		FCount = Array.FCount;
		FCapacity = Array.FCapacity;
		if (FCapacity > 0 && FCount > 0)
		{
			Data = (T*)malloc(FCapacity * sizeof(T));
			if (Data)
			{
				for (int i = 0; i < FCount; ++i)
					ConstructCopy(i, Array.Data[i]);
			}
			else
			{
				FCapacity = 0;
				FCount = 0;
			}
		}
		else
		{
			Data = nullptr;
		}
	}

	// Оператор присваивания
	LARKINARRAY& operator=(const LARKINARRAY& rhs)
	{
		if (this == &rhs)
			return *this;
		Free();
		#ifdef LRArrayAutoSort
			FSortingAccordIncrease = rhs.FSortingAccordIncrease;
		#endif
		FCount = rhs.FCount;
		FCapacity = rhs.FCapacity;
		if (FCapacity > 0 && FCount > 0)
		{
			Data = (T*)malloc(FCapacity * sizeof(T));
			if (Data)
			{
				for (int i = 0; i < FCount; ++i)
					ConstructCopy(i, rhs.Data[i]);
			}
			else
			{
				FCapacity = 0;
				FCount = 0;
			}
		}
		else
		{
			Data = nullptr;
		}
		return *this;
	}

	// Деструктор
	virtual ~LARKINARRAY()
	{
		Free();
	}

	// Освобождение памяти
	void Free()
	{
		#ifndef LRArraySimpleType
			while (FCount > 0)
				PopBack();
		#endif
		if (Data) free(Data);
		Data = nullptr;
		FCount = FCapacity = 0;
	}

	// Добавление элемента
	#ifdef LRArrayAutoSort
		void Add(const T& el)
		{
			if (FCount == 0)
			{
				EnsureCapacity(1);
				ConstructCopy(0, el);
				FCount = 1;
				return;
			}
			int Pos = 0;
			if (FSortingAccordIncrease)
			{
				for (; Pos < FCount; Pos++)
				{
					#ifdef LRArrayCollection
						if (Data[Pos] == el)
							return;
					#endif
					if (Data[Pos] > el)
						break;
				}
			}
			else
			{
				for (; Pos < FCount; Pos++)
				{
					#ifdef LRArrayCollection
						if (Data[Pos] == el)
							return;
					#endif
					if (Data[Pos] < el)
						break;
				}
			}
			EnsureCapacity(FCount + 1);
			if (Pos < FCount)
				MoveElements(Pos, 1);
			ConstructCopy(Pos, el);
			FCount++;
		}
	#else
		void PushBack(const T& el)
		{
			#ifdef LRArrayCollection
				if (Find(el) != -1)
					return;
			#endif
			EnsureCapacity(FCount + 1);
			ConstructCopy(FCount, el);
			FCount++;
		}
	#endif

	// Гарантирование минимальной ёмкости
	void EnsureCapacity(int capacity)
	{
		if (capacity > FCapacity)
		{
			int newCapacity = (FCapacity == 0) ? 4 : FCapacity;
			while (newCapacity < capacity)
			{
				if (newCapacity > (0x7FFFFFFF / 2))
				{
					newCapacity = capacity;
					break;
				}
				newCapacity *= 2;
			}
			SetCapacity(newCapacity);
		}
	}

	// Доступ к элементам
	#ifdef LRArrayBasic
		T& operator[](int i)
		{
			#ifdef _DEBUG
				if (i < 0 || i >= FCount)
					__debugbreak();
			#endif
			return Data[i];
		}
	#endif

	const T& operator[](int i) const
	{
		#ifdef _DEBUG
			if (i < 0 || i >= FCount)
				__debugbreak();
		#endif
		return Data[i];
	}

	// Свойства для Object Inspector
	__property int Count = { read = FCount, write = SetCount, nodefault };
	__property int Capacity = { read = FCapacity, write = SetCapacity, nodefault };

	#ifdef LRArrayAutoSort
		__property bool SortAscending = { read = FSortingAccordIncrease, write = FSortingAccordIncrease, default = true };
	#endif

	// Удаление последнего элемента
	void PopBack()
	{
		if (FCount == 0)
			return;
		#ifndef LRArraySimpleType
			Data[FCount - 1].~T();
		#endif
		FCount--;
	}

	// Удаление по индексу
	void Delete(int idx)
	{
		if (FCount <= 0 || idx < 0 || idx >= FCount)
			return;
		#ifndef LRArraySimpleType
			Data[idx].~T();
		#endif
		MoveElements(idx + 1, -1);
		FCount--;
	}

	// Линейный поиск
	int Find(const T& el) const
	{
		for (int i = 0; i < FCount; i++)
		{
			if (Data[i] == el)
				return i;
		}
		return -1;
	}

	// Удаление по значению
	void Remove(const T& el)
	{
		int idx = Find(el);
		if (idx != -1)
			Delete(idx);
	}

	// Очистка
	void Clear()
	{
		SetCount(0);
	}

	// Инверсия порядка
	void Invert()
	{
		T temp;
		for (int i = 0; i < FCount / 2; ++i)
		{
			temp = Data[i];
			Data[i] = Data[FCount - i - 1];
			Data[FCount - i - 1] = temp;
		}
	}
};

#undef LRArraySimpleType
#undef LRArrayAutoSort
#undef LRArrayCollection
#undef LRArrayBasic
#endif // LARKINARRAY