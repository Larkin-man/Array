// LarkinSquareMatrix v1.3
// Опции, задаются командами #define:
// Для простых типов (int, double etc):
// #define LRArraySimpleType
//---------------------------------------------------------------------------
#ifndef LARKINSQUAREMATRIXH
#define LARKINSQUAREMATRIXH

#include <alloc.h>
#include <mem.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
#define TYPED
#ifdef TYPED
	#define TEMPLT template< class T >
	#define T T
#else
	#define TEMPLT
	#define T int
#endif

// Квадратная матрица [Size][Size]
TEMPLT class LRSquareMatrix
{
private:
	T **Data;		// Двумерный массив [R][C]
	int FCapacity;	// Размер выделенной памяти
	int FSize;		// Число элементов (размер матрицы)

	// Запрещаем копирование без реализации (Rule of Three)
	LRSquareMatrix(const LRSquareMatrix&);
	LRSquareMatrix& operator=(const LRSquareMatrix&);

protected:
	// Выделить/изменить размер буфера
	void SetCapacity(int newCapacity)
	{
		if (newCapacity < FCapacity)
			return;
		if (newCapacity <= 0)
			return;

		if (Data)
		{
			// Расширяем существующие строки
			for (int i = 0; i < FCapacity; ++i)
			{
				if (Data[i])
				{
					T* temp = (T*)realloc(Data[i], newCapacity * sizeof(T));
					if (temp != NULL)
						Data[i] = temp;
				}
				else
				{
					Data[i] = (T*)malloc(newCapacity * sizeof(T));
				}
			}

			// Расширяем массив указателей
			T** tempData = (T**)realloc(Data, newCapacity * sizeof(T*));
			if (tempData != NULL)
			{
				Data = tempData;
				// Инициализируем новые строки
				for (int i = FCapacity; i < newCapacity; ++i)
				{
					Data[i] = (T*)malloc(newCapacity * sizeof(T));
					if (Data[i])
					{
						for (int j = 0; j < newCapacity; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
				}
			}
		}
		else
		{
			// Первое выделение
			Data = (T**)malloc(newCapacity * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < newCapacity; ++i)
				{
					Data[i] = (T*)malloc(newCapacity * sizeof(T));
					if (Data[i])
					{
						for (int j = 0; j < newCapacity; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
				}
			}
		}
		FCapacity = newCapacity;
	}

	void SetSize(int newSize)
	{
		if (newSize < 0)
			newSize = 0;

		#ifdef LRArraySimpleType
		if (newSize > FSize)
			EnsureCapacity(newSize);
		FSize = newSize;
		#else
		if (newSize < FSize)
		{
			Compress(FSize - newSize);
		}
		else if (newSize > FSize)
		{
			EnsureCapacity(newSize);
			// Инициализируем новые элементы дефолтным конструктором
			for (int i = FSize; i < newSize; ++i)
			{
				for (int j = 0; j < newSize; ++j)
				{
					#ifdef LRArraySimpleType
					Data[i][j] = T();
					#else
					new (&Data[i][j]) T();
					#endif
				}
			}
			FSize = newSize;
		}
		#endif
	}

	// Конструирующее копирование в указанную ячейку
	void ConstructCopy(int Row, int Col, const T& Item)
	{
		#ifdef LRArraySimpleType
		Data[Row][Col] = Item;
		#else
		new (&Data[Row][Col]) T(Item);
		#endif
	}

	#ifndef LRArraySimpleType
	void Destruct(int Row, int Col)
	{
		Data[Row][Col].~T();
	}
	#endif

public:
	// Конструктор
	LRSquareMatrix(int capacity = 0)
	{
		Data = NULL;
		FSize = 0;
		FCapacity = 0;

		if (capacity > 0)
		{
			Data = (T**)malloc(capacity * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < capacity; ++i)
				{
					Data[i] = (T*)malloc(capacity * sizeof(T));
					if (Data[i])
					{
						for (int j = 0; j < capacity; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
				}
				FCapacity = capacity;
				FSize = capacity;  // ИСПРАВЛЕНО: устанавливаем FSize
			}
		}
	}

	// Конструктор копирования
	LRSquareMatrix(const LRSquareMatrix& CopyBase)
	{
		Data = NULL;
		FSize = 0;
		FCapacity = 0;

		if (CopyBase.FSize > 0)
		{
			EnsureCapacity(CopyBase.FSize);
			FSize = CopyBase.FSize;

			// Копируем данные
			for (int i = 0; i < FSize; ++i)
			{
				for (int j = 0; j < FSize; ++j)
				{
					ConstructCopy(i, j, CopyBase.Data[i][j]);
				}
			}
		}
	}

	// Оператор присваивания
	LRSquareMatrix& operator=(const LRSquareMatrix& rhs)
	{
		if (this == &rhs)
			return *this;

		// Освобождаем текущие данные
		Clear();

		if (rhs.FSize > 0)
		{
			EnsureCapacity(rhs.FSize);
			FSize = rhs.FSize;

			// Копируем данные
			for (int i = 0; i < FSize; ++i)
			{
				for (int j = 0; j < FSize; ++j)
				{
					ConstructCopy(i, j, rhs.Data[i][j]);
				}
			}
		}

		return *this;
	}

	// Деструктор
	~LRSquareMatrix()
	{
		Free();
	}

	// Свойства
	__property int Size = { read = FSize, write = SetSize };
	__property int Capacity = { read = FCapacity, write = SetCapacity };

	// Гарантировать минимальную ёмкость
	void EnsureCapacity(int size)
	{
		if (size <= FCapacity)
			return;

		int newCapacity = (FCapacity == 0) ? 4 : FCapacity;
		while (newCapacity < size)
		{
			if (newCapacity > (0x7FFFFFFF / 2))  // Защита от переполнения
			{
				newCapacity = size;
				break;
			}
			newCapacity *= 2;  // ИСПРАВЛЕНО: было = 2
		}
		SetCapacity(newCapacity);
	}

	// Установить строку (массив элементов)
	void SetRow(int Row, const T* elements)  // ИСПРАВЛЕНО: const T*
	{
		if (elements == NULL || Row >= FSize)  // Добавлена проверка NULL
			return;

		for (int i = 0; i < FSize; ++i)
		{
			#ifndef LRArraySimpleType
			Destruct(Row, i);
			#endif
			ConstructCopy(Row, i, elements[i]);
		}
	}

	// Установить столбец (массив элементов)
	void SetCol(int Col, const T* elements)
	{
		if (elements == NULL || Col >= FSize)  // Добавлена проверка NULL
			return;

		for (int i = 0; i < FSize; ++i)
		{
			#ifndef LRArraySimpleType
			Destruct(i, Col);
			#endif
			ConstructCopy(i, Col, elements[i]);
		}
	}

	// Доступ к ячейке (метод вместо property)
	T& GetCell(int R, int C)
	{
		#ifdef _DEBUG
		if (R < 0 || R >= FSize || C < 0 || C >= FSize)
			__debugbreak();
		#endif
		return Data[R][C];
	}

	void SetCell(int Row, int Col, const T& rhs)
	{
		if (Row < 0 || Col < 0)
			return;

		// Авто-расширение при записи за границы
		if (Row >= FSize || Col >= FSize)
		{
			int newSize = (Row > Col) ? (Row + 1) : (Col + 1);
			EnsureCapacity(newSize);
			// Инициализируем новые элементы
			for (int i = FSize; i < newSize; ++i)
			{
				for (int j = 0; j < newSize; ++j)
				{
					#ifdef LRArraySimpleType
					Data[i][j] = T();
					#else
					new (&Data[i][j]) T();
					#endif
				}
			}
			FSize = newSize;
		}

		#ifndef LRArraySimpleType
		Destruct(Row, Col);
		#endif
		ConstructCopy(Row, Col, rhs);
	}

	// Доступ к строке
	const T* operator[](int Row) const  // ИСПРАВЛЕНО: const T*
	{
		#ifdef _DEBUG
		if (Row < 0 || Row >= FSize)
			__debugbreak();
		#endif
		return (Row >= 0 && Row < FSize) ? Data[Row] : NULL;
	}

	T* operator[](int Row)
	{
		#ifdef _DEBUG
		if (Row < 0 || Row >= FSize)
			__debugbreak();
		#endif
		return (Row >= 0 && Row < FSize) ? Data[Row] : NULL;
	}

	// Базовый указатель
	const T** Base() const { return (const T**)Data; }  // ИСПРАВЛЕНО: const-correctness
	T** Base() { return Data; }

	// Расширить матрицу
	void Expand(int size, const T& Item)
	{
		if (size > FCapacity)
			EnsureCapacity(size);

		if (size > FSize)
		{
			// ИСПРАВЛЕНО: правильный порядок циклов (строки внешний, столбцы внутренний)
			for (int i = FSize; i < size; ++i)
			{
				for (int j = 0; j < FSize; ++j)
				{
					ConstructCopy(i, j, Item);
				}
			}
			for (int i = 0; i < size; ++i)
			{
				for (int j = FSize; j < size; ++j)
				{
					ConstructCopy(i, j, Item);
				}
			}
			FSize = size;
		}
	}

	// Сжать матрицу
	void Compress(int size)
	{
		if (size > FSize)
			size = FSize;
		if (size <= 0)
			return;

		// ИСПРАВЛЕНО: уничтожаем каждый элемент только один раз
		for (int i = FSize - size; i < FSize; ++i)
		{
			for (int j = 0; j < FSize; ++j)  // Вся строка
			{
				#ifndef LRArraySimpleType
				Data[i][j].~T();
				#endif
			}
		}

		FSize -= size;
	}

	// Обмен строк
	void ExchangeRows(int Row1, int Row2)
	{
		if (Row1 >= FSize || Row2 >= FSize || Row1 == Row2)
			return;

		T* temp = Data[Row1];  // ИСПРАВЛЕНО: T* вместо T
		Data[Row1] = Data[Row2];
		Data[Row2] = temp;
	}

	// Обмен столбцов
	void ExchangeCols(int Col1, int Col2)
	{
		if (Col1 >= FSize || Col2 >= FSize || Col1 == Col2)
			return;

		for (int i = 0; i < FSize; ++i)
		{
			T temp = Data[i][Col1];
			Data[i][Col1] = Data[i][Col2];
			Data[i][Col2] = temp;
		}
	}

	#ifndef LRArraySimpleType
	void DestructRow(int Row)
	{
		if (Row >= 0 && Row < FSize)
		{
			for (int Ci = 0; Ci < FSize; ++Ci)
			{
				Data[Row][Ci].~T();
			}
		}
	}

	void DestructCol(int Col)
	{
		if (Col >= 0 && Col < FSize)
		{
			for (int R = 0; R < FSize; ++R)
			{
				Data[R][Col].~T();
			}
		}
	}
	#endif

	// Очистить матрицу без освобождения памяти
	void Clear()
	{
		#ifndef LRArraySimpleType
		for (int i = 0; i < FSize; ++i)
		{
			for (int j = 0; j < FSize; ++j)
			{
				Data[i][j].~T();
			}
		}
		#endif

		FSize = 0;
	}

	// Освободить всю память
	void Free()
	{
		Clear();

		if (Data)
		{
			for (int i = 0; i < FCapacity; ++i)
			{
				if (Data[i])
				{
					free(Data[i]);
					Data[i] = NULL;
				}
			}
			free(Data);
			Data = NULL;
		}

		FCapacity = 0;
		FSize = 0;
	}
};

#endif