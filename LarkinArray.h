//Опции, задаются командами #define:
//Для простых типов (int, double etc):
//#define LRArraySimpleType
//Автосортировка для простых типов:
//#define LRArrayAutoSort
//Создание коллекции (игнорируется добавление дубликата):
//#define LRArrayCollection
//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
#define TYPED
#ifdef TYPED
	#define TEMPLT template< class T >
	#define T T
#else
	#define TEMPLT
	#define T int
#endif
#include <alloc.h>
#include <mem.h>

// Динамический массив
TEMPLT class LARKINARRAY
{
private:
	T *Data;		// Одномерный массив
	int FCapacity;	// Размер выделенной памяти
	int FCount;		// Число элементов в массиве
	#ifdef LRArrayAutoSort
		#ifdef LRArraySimpleType
		bool FSortingAccordIncrease;
		#endif
	#endif

protected:
	// Выделить/изменить размер буфера
	// ВАЖНО: для сложных типов НЕ используется realloc (не вызывает конструкторы)
	void SetCapacity(int newCapacity)
	{
		if (newCapacity < 0)
			return;
		if (newCapacity == FCapacity)
			return;

		#ifdef LRArraySimpleType
			// Для POD-типов можно использовать realloc
			if (Data)
				Data = (T*)realloc(Data, newCapacity * sizeof(T));
			else
				Data = (T*)malloc(newCapacity * sizeof(T));
		#else
			// Для сложных типов: выделяем новый буфер и копируем элементы вручную
			T* newData = nullptr;
			if (newCapacity > 0) {
				newData = (T*)malloc(newCapacity * sizeof(T));
				if (!newData) {
					// Ошибка выделения — сохраняем старое состояние
					return;
				}
				// Копируем существующие элементы через конструктор копирования
				for (int i = 0; i < FCount; ++i) {
					new (&newData[i]) T(Data[i]);
					Data[i].~T();
				}
			}
			// Освобождаем старый буфер
			if (Data) {
				free(Data);
			}
			Data = newData;
		#endif
		FCapacity = newCapacity;
	}

	void SetCount(int newCount)
	{
		#ifdef LRArraySimpleType
		if (newCount > FCount)
			EnsureCapacity(newCount);
		else if (newCount < 0)
			newCount = 0;
		FCount = newCount;
		#else
		if (newCount < FCount) {
			if (newCount < 0) newCount = 0;
			while (FCount > newCount)
				PopBack();
		}
		else if (newCount > FCount) {
			EnsureCapacity(newCount);
			// Инициализируем новые элементы дефолтным конструктором
			for (int i = FCount; i < newCount; ++i)
				new (&Data[i]) T();
			FCount = newCount;
		}
		#endif
	}

	// Сдвиг элементов: только для простых типов! Для сложных — ручное перемещение
	void MoveElements(int idx, int num)
	{
		#ifdef LRArraySimpleType
		int numBytes = (FCount - idx) * sizeof(T);
		if (numBytes > 0)
			memmove(&Data[idx + num], &Data[idx], numBytes);
		#else
		// Для сложных типов: поэлементное перемещение с конструкторами
		if (num > 0) {
			// Сдвиг вправо
			for (int i = FCount - 1; i >= idx; --i) {
				new (&Data[i + num]) T(Data[i]);
				Data[i].~T();
			}
		} else if (num < 0) {
			// Сдвиг влево
			int shift = -num;
			for (int i = idx; i < FCount; ++i) {
				if (i + shift < FCount) {
					new (&Data[i]) T(Data[i + shift]);
					Data[i + shift].~T();
				}
			}
		}
		#endif
	}

public:
	// Конструктор
	// ВНИМАНИЕ: убрано значение по умолчанию у capacity, чтобы избежать
	// неоднозначности с параметром сортировки при LRArrayAutoSort
	#ifdef LRArrayAutoSort
	LARKINARRAY(bool sortingAccordingIncrease, int capacity)
	{
		FSortingAccordIncrease = sortingAccordingIncrease;
	#else
	LARKINARRAY(int capacity = 0)
	{
	#endif
		Data = nullptr;
		FCount = 0;
		FCapacity = 0;
		if (capacity > 0)
			SetCapacity(capacity);
	}

	// Конструктор по умолчанию (только для режима без авто-сортировки)
	#ifndef LRArrayAutoSort
	LARKINARRAY() : Data(nullptr), FCount(0), FCapacity(0) {}
	#endif

	// Конструктор копирования
	LARKINARRAY(const LARKINARRAY& Array)
	{
		#ifdef LRArrayAutoSort
		FSortingAccordIncrease = Array.FSortingAccordIncrease;
		#endif

		FCount = Array.FCount;
		FCapacity = Array.FCapacity;

		if (FCapacity > 0 && FCount > 0) {
			Data = (T*)malloc(FCapacity * sizeof(T));
			if (Data) {
				for (int i = 0; i < FCount; ++i)
					ConstructCopy(i, Array.Data[i]);
			} else {
				FCapacity = 0;
				FCount = 0;
			}
		} else {
			Data = nullptr;
			FCapacity = 0;
			FCount = 0;
		}
	}

	// Оператор присваивания
	LARKINARRAY& operator=(const LARKINARRAY& rhs)
	{
		if (this == &rhs)
			return *this;

		// Освобождаем текущие данные
		Free();

		#ifdef LRArrayAutoSort
		FSortingAccordIncrease = rhs.FSortingAccordIncrease;
		#endif

		FCount = rhs.FCount;
		FCapacity = rhs.FCapacity;

		if (FCapacity > 0 && FCount > 0) {
			Data = (T*)malloc(FCapacity * sizeof(T));
			if (Data) {
				for (int i = 0; i < FCount; ++i)
					ConstructCopy(i, rhs.Data[i]);
			} else {
				FCapacity = 0;
				FCount = 0;
			}
		} else {
			Data = nullptr;
		}

		return *this;
	}

	~LARKINARRAY()
	{
		Free();
	}

	#ifdef LRArrayAutoSort
	// Добавить элемент с сохранением порядка сортировки
	void Add(const T& el)
	{
		// Пустой массив — просто добавляем
		if (FCount == 0) {
			EnsureCapacity(1);
			ConstructCopy(0, el);
			FCount = 1;
			return;
		}

		int Pos = 0;
		if (FSortingAccordIncrease) {
			for (; Pos < FCount; Pos++) {
				#ifdef LRArrayCollection
				if (Data[Pos] == el)
					return;
				#endif
				if (Data[Pos] > el)
					break;
			}
		} else {
			for (; Pos < FCount; Pos++) {
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
	// Добавить элемент в конец
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

	// Свойства
	__property int Count = { read = FCount, write = SetCount };
	__property int Capacity = { read = FCapacity, write = SetCapacity };

	// Гарантировать минимальную ёмкость
	void EnsureCapacity(int capacity)
	{
		if (capacity > FCapacity) {
			int newCapacity = (FCapacity == 0) ? 4 : FCapacity;
			// Защита от переполнения int
			while (newCapacity < capacity) {
				if (newCapacity > (0x7FFFFFFF / 2)) {
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
			__debugbreak(); // Или выброс исключения, если используется RTL
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

	// Базовый указатель
	const T* Base() const { return Data; }

	#ifdef LRArrayBasic
	T& First()
	{
		#ifdef _DEBUG
		if (FCount == 0) __debugbreak();
		#endif
		return Data[0];
	}
	T& Last()
	{
		#ifdef _DEBUG
		if (FCount == 0) __debugbreak();
		#endif
		return Data[FCount - 1];
	}
	#endif

	const T& First() const
	{
		#ifdef _DEBUG
		if (FCount == 0) __debugbreak();
		#endif
		return Data[0];
	}
	const T& Last() const
	{
		#ifdef _DEBUG
		if (FCount == 0) __debugbreak();
		#endif
		return Data[FCount - 1];
	}

	bool Empty() const { return FCount == 0; }

	// Инверсия порядка элементов
	// ВНИМАНИЕ: не меняет флаг сортировки, так как инверсия нарушает порядок
	// Если нужен обратный порядок сортировки — создайте новый массив с другим флагом
	void Invert()
	{
		T temp;
		for (int i = 0; i < FCount / 2; ++i) {
			temp = Data[i];
			Data[i] = Data[FCount - i - 1];
			Data[FCount - i - 1] = temp;
		}
		// FSortingAccordIncrease НЕ инвертируется — это нарушило бы логику Add()
	}

	#ifdef LRArrayAutoSort
	__property bool SortingAccordIncrease = { read = FSortingAccordIncrease };
	protected:
	#endif

	// Конструирующее копирование в указанный индекс
	void ConstructCopy(int i, const T& el)
	{
		#ifdef LRArraySimpleType
		Data[i] = el;
		#else
		new (&Data[i]) T(el);
		#endif
	}

	#ifdef LRArrayAutoSort
	public:
	#endif

	#ifndef LRArraySimpleType
	void Destruct(int i) { Data[i].~T(); }
	#endif

	// Вставка в произвольную позицию (только без авто-сортировки)
	#ifndef LRArrayAutoSort
	void Insert(int idx, const T& el)
	{
		#ifdef LRArrayCollection
		if (Find(el) != -1)
			return;
		#endif
		if (idx < 0) idx = 0;
		else if (idx > FCount) idx = FCount;

		EnsureCapacity(FCount + 1);
		MoveElements(idx, 1);
		ConstructCopy(idx, el);
		FCount++;
	}
	#endif

	// Линейный поиск
	int Find(const T& el) const
	{
		for (int i = 0; i < FCount; i++) {
			if (Data[i] == el)
				return i;
		}
		return -1;
	}

	// Удаление последнего элемента
	void PopBack()
	{
		if (FCount == 0)
			return;
		#ifndef LRArraySimpleType
		Destruct(FCount - 1);
		#endif
		FCount--;
	}

	// Удаление по индексу
	void Delete(int idx)
	{
		if (FCount <= 0 || idx < 0 || idx >= FCount)
			return;
		#ifndef LRArraySimpleType
		Destruct(idx);
		#endif
		MoveElements(idx + 1, -1);
		FCount--;
	}

	// Найти и удалить
	void Remove(const T& el)
	{
		int idx = Find(el);
		if (idx != -1)
			Delete(idx);
	}

	// Очистка без освобождения буфера
	void Clear()
	{
		SetCount(0);
	}

	// Полное освобождение памяти
	void Free()
	{
		#ifdef LRArraySimpleType
		FCount = 0;
		#else
		while (FCount > 0)
			PopBack();
		#endif
		if (Data) {
			free(Data);
		}
		Data = nullptr;
		FCapacity = 0;
		FCount = 0;
	}
};
#endif

#undef LRArraySimpleType
#undef LRArrayAutoSort
#undef LRArrayCollection
#undef LRArrayBasic