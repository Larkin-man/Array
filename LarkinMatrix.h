// LarkinMatrix v1.3 (исправленная версия)
// Опции, задаются командами #define:
// Для простых типов (int, double etc):
// #define LRArraySimpleType
//---------------------------------------------------------------------------
#ifndef LARKINMATRIXH
#define LARKINMATRIXH

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

// Динамическая матрица [Row][Col]
TEMPLT class LRMatrix
{
private:
	T **Data;		// Двумерный массив [R][C]
	#ifndef SquareMatrix
	int FColCapacity;	// Размер выделенной памяти (столбцы)
	int FColCount;		// Число элементов в матрице (столбцы)
	int FRowCapacity;	// Размер выделенной памяти (строки)
	int FRowCount;		// Число элементов в матрице (строки)
	#else
	int FCapacity;		// Размер выделенной памяти (квадратная)
	int FSize;			// Число элементов (квадратная)
	#endif

	// Запрещаем копирование без реализации (Rule of Three)
	// LRMatrix(const LRMatrix&);  // Объявлен но не реализован
	// LRMatrix& operator=(const LRMatrix&);  // Объявлен но не реализован

protected:
	// Выделить/изменить размер буфера
	void SetCapacity(int Row, int Col)
	{
		if (Row <= 0 || Col <= 0)
			return;

		if (Data)
		{
			// Расширяем столбцы
			if (Col > FColCapacity)
			{
				for (int i = 0; i < FRowCapacity; ++i)
				{
					if (Data[i])
					{
						T* temp = (T*)realloc(Data[i], Col * sizeof(T));
						if (temp != NULL)
							Data[i] = temp;
					}
					else
					{
						Data[i] = (T*)malloc(Col * sizeof(T));
					}
				}
				FColCapacity = Col;
			}

			// Расширяем строки
			if (Row > FRowCapacity)
			{
				T** tempData = (T**)realloc(Data, Row * sizeof(T*));
				if (tempData != NULL)
				{
					Data = tempData;
					for (int i = FRowCapacity; i < Row; ++i)
					{
						Data[i] = (T*)malloc(FColCapacity * sizeof(T));
						// Инициализируем новые элементы
						for (int j = 0; j < FColCapacity; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
					FRowCapacity = Row;
				}
			}
		}
		else
		{
			// Первое выделение
			Data = (T**)malloc(Row * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < Row; ++i)
				{
					Data[i] = (T*)malloc(Col * sizeof(T));
					if (Data[i])
					{
						for (int j = 0; j < Col; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
				}
				FRowCapacity = Row;
				FColCapacity = Col;
			}
		}
	}

	void SetColCapacity(int Col)
	{
		if (Col <= 0)
			return;

		if (Data)
		{
			if (Col > FColCapacity)
			{
				for (int i = 0; i < FRowCapacity; ++i)
				{
					if (Data[i])
					{
						T* temp = (T*)realloc(Data[i], Col * sizeof(T));
						if (temp != NULL)
							Data[i] = temp;
					}
				}
				FColCapacity = Col;
			}
		}
		else
		{
			Data = (T**)malloc(FRowCapacity * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < FRowCapacity; ++i)
				{
					Data[i] = (T*)malloc(Col * sizeof(T));
				}
				FColCapacity = Col;
			}
		}
	}

	void SetRowCapacity(int Row)
	{
		if (Row <= 0)
			return;

		if (Data)
		{
			if (Row > FRowCapacity)
			{
				T** tempData = (T**)realloc(Data, Row * sizeof(T*));
				if (tempData != NULL)
				{
					Data = tempData;
					for (int i = FRowCapacity; i < Row; ++i)
					{
						Data[i] = (T*)malloc(FColCapacity * sizeof(T));
						if (Data[i])
						{
							for (int j = 0; j < FColCapacity; ++j)
							{
								#ifdef LRArraySimpleType
								Data[i][j] = T();
								#else
								new (&Data[i][j]) T();
								#endif
							}
						}
					}
					FRowCapacity = Row;
				}
			}
		}
		else
		{
			Data = (T**)malloc(Row * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < Row; ++i)
				{
					Data[i] = (T*)malloc(FColCapacity * sizeof(T));
				}
				FRowCapacity = Row;
			}
		}
	}

	void SetColCount(int newColCount)
	{
		if (newColCount < 0)
			newColCount = 0;

		#ifdef LRArraySimpleType
		if (newColCount > FColCount)
			EnsureCapacity(FRowCount, newColCount);
		FColCount = newColCount;
		#else
		if (newColCount < FColCount)
		{
			while (FColCount > newColCount)
				PopBackCol();
		}
		else if (newColCount > FColCount)
		{
			EnsureCapacity(FRowCount, newColCount);
			if (FRowCount > 0)
			{
				for (int i = FColCount; i < newColCount; ++i)
				{
					for (int j = 0; j < FRowCount; ++j)
					{
						#ifdef LRArraySimpleType
						Data[j][i] = T();
						#else
						new (&Data[j][i]) T();
						#endif
					}
				}
			}
			FColCount = newColCount;
		}
		#endif
	}

	void SetRowCount(int newRowCount)
	{
		if (newRowCount < 0)
			newRowCount = 0;

		#ifdef LRArraySimpleType
		if (newRowCount > FRowCount)
			EnsureCapacity(newRowCount, FColCount);
		FRowCount = newRowCount;
		#else
		if (newRowCount < FRowCount)
		{
			while (FRowCount > newRowCount)
				PopBackRow();
		}
		else if (newRowCount > FRowCount)
		{
			EnsureCapacity(newRowCount, FColCount);
			if (FColCount > 0)
			{
				for (int i = FRowCount; i < newRowCount; ++i)
				{
					for (int j = 0; j < FColCount; ++j)
					{
						#ifdef LRArraySimpleType
						Data[i][j] = T();
						#else
						new (&Data[i][j]) T();
						#endif
					}
				}
			}
			FRowCount = newRowCount;
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
	LRMatrix(int Row = 0, int Col = 0)
	{
		Data = NULL;
		FRowCount = 0;
		FColCount = 0;
		FRowCapacity = 0;
		FColCapacity = 0;

		if (Row > 0 && Col > 0)
		{
			Data = (T**)malloc(Row * sizeof(T*));
			if (Data)
			{
				for (int i = 0; i < Row; ++i)
				{
					Data[i] = (T*)malloc(Col * sizeof(T));
					if (Data[i])
					{
						for (int j = 0; j < Col; ++j)
						{
							#ifdef LRArraySimpleType
							Data[i][j] = T();
							#else
							new (&Data[i][j]) T();
							#endif
						}
					}
				}
				FRowCapacity = Row;
				FColCapacity = Col;
			}
		}
	}

	// Конструктор копирования
	LRMatrix(const LRMatrix& CopyBase)
	{
		Data = NULL;
		FRowCount = 0;
		FColCount = 0;
		FRowCapacity = 0;
		FColCapacity = 0;

		if (CopyBase.FRowCount > 0 && CopyBase.FColCount > 0)
		{
			EnsureCapacity(CopyBase.FRowCount, CopyBase.FColCount);
			FRowCount = CopyBase.FRowCount;
			FColCount = CopyBase.FColCount;

			// Копируем данные
			for (int i = 0; i < FRowCount; ++i)
			{
				for (int j = 0; j < FColCount; ++j)
				{
					ConstructCopy(i, j, CopyBase.Data[i][j]);
				}
			}
		}
	}

	// Оператор присваивания
	LRMatrix& operator=(const LRMatrix& rhs)
	{
		if (this == &rhs)
			return *this;

		// Освобождаем текущие данные
		Clear();

		if (rhs.FRowCount > 0 && rhs.FColCount > 0)
		{
			EnsureCapacity(rhs.FRowCount, rhs.FColCount);
			FRowCount = rhs.FRowCount;
			FColCount = rhs.FColCount;

			// Копируем данные
			for (int i = 0; i < FRowCount; ++i)
			{
				for (int j = 0; j < FColCount; ++j)
				{
					ConstructCopy(i, j, rhs.Data[i][j]);
				}
			}
		}

		return *this;
	}

	// Деструктор
	~LRMatrix()
	{
		#ifndef LRArraySimpleType
		for (int i = 0; i < FRowCount; ++i)
		{
			for (int j = 0; j < FColCount; ++j)
			{
				Data[i][j].~T();
			}
		}
		#endif

		FRowCount = 0;
		FColCount = 0;

		if (Data)
		{
			for (int i = 0; i < FRowCapacity; ++i)
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

		FRowCapacity = 0;
		FColCapacity = 0;
	}

	// Свойства
	__property int RowCount = { read = FRowCount, write = SetRowCount };
	__property int ColCount = { read = FColCount, write = SetColCount };
	__property int RowCapacity = { read = FRowCapacity, write = SetRowCapacity };
	__property int ColCapacity = { read = FColCapacity, write = SetColCapacity };

	// Гарантировать минимальную ёмкость
	void EnsureCapacity(int Row, int Col)
	{
		if (Row > FRowCapacity)
		{
			int newRowCapacity = (FRowCapacity == 0) ? 4 : FRowCapacity;
			while (newRowCapacity < Row)
			{
				if (newRowCapacity > (0x7FFFFFFF / 2))
				{
					newRowCapacity = Row;
					break;
				}
				newRowCapacity *= 2;  // ИСПРАВЛЕНО: было = 2
			}
			Row = newRowCapacity;
		}

		if (Col > FColCapacity)
		{
			int newColCapacity = (FColCapacity == 0) ? 4 : FColCapacity;
			while (newColCapacity < Col)
			{
				if (newColCapacity > (0x7FFFFFFF / 2))
				{
					newColCapacity = Col;
					break;
				}
				newColCapacity *= 2;  // ИСПРАВЛЕНО: было = 2
			}
			Col = newColCapacity;
		}

		if ((Row > FRowCapacity) || (Col > FColCapacity))
			SetCapacity(Row, Col);
	}

	// Добавить строку (массив элементов)
	void AppendRow(const T* elements)  // ИСПРАВЛЕНО: было const T elements
	{
		if (elements == NULL)
			return;

		if (FRowCount + 1 > FRowCapacity)
			EnsureCapacity(FRowCount + 1, FColCount);

		for (int i = 0; i < FColCount; ++i)
		{
			ConstructCopy(FRowCount, i, elements[i]);
		}
		FRowCount++;
	}

	// Доступ к ячейке (метод вместо property)
	T& GetCell(int R, int C)
	{
		#ifdef _DEBUG
		if (R < 0 || R >= FRowCount || C < 0 || C >= FColCount)
			__debugbreak();
		#endif
		return Data[R][C];
	}

	void SetCell(int Row, int Col, const T& rhs)
	{
		if (Row < FRowCount && Col < FColCount)
		{
			#ifndef LRArraySimpleType
			Destruct(Row, Col);
			#endif
			ConstructCopy(Row, Col, rhs);
		}
		else
		{
			Expand(Row + 1, Col + 1, rhs);
		}
	}

	// Доступ к строке
	const T* operator[](int Row) const  // ИСПРАВЛЕНО: было const T
	{
		#ifdef _DEBUG
		if (Row < 0 || Row >= FRowCount)
			__debugbreak();
		#endif
		return (Row >= 0 && Row < FRowCount) ? Data[Row] : NULL;
	}

	T* operator[](int Row)
	{
		#ifdef _DEBUG
		if (Row < 0 || Row >= FRowCount)
			__debugbreak();
		#endif
		return (Row >= 0 && Row < FRowCount) ? Data[Row] : NULL;
	}

	// Базовый указатель
	const T** Base() const { return (const T**)Data; }
	T** Base() { return Data; }

	// Расширить матрицу
	void Expand(int Row, int Col, const T& Item)
	{
		if (Row > FRowCapacity || Col > FColCapacity)
			EnsureCapacity(Row, Col);

		// ИСПРАВЛЕНО: правильный порядок циклов (строки внешний, столбцы внутренний)
		if (FRowCount < Row)
		{
			for (int i = FRowCount; i < Row; ++i)
			{
				for (int j = 0; j < FColCount; ++j)
				{
					ConstructCopy(i, j, Item);
				}
			}
			FRowCount = Row;
		}

		if (FColCount < Col)
		{
			for (int i = 0; i < FRowCount; ++i)
			{
				for (int j = FColCount; j < Col; ++j)
				{
					ConstructCopy(i, j, Item);
				}
			}
			FColCount = Col;
		}
	}

	// Обмен строк
	void ExchangeRows(int Row1, int Row2)
	{
		if (Row1 >= FRowCount || Row2 >= FRowCount || Row1 == Row2)
			return;

		T* temp = Data[Row1];  // ИСПРАВЛЕНО: было T temp
		Data[Row1] = Data[Row2];
		Data[Row2] = temp;
	}

	// Обмен столбцов
	void ExchangeCols(int Col1, int Col2)
	{
		if (Col1 >= FColCount || Col2 >= FColCount || Col1 == Col2)
			return;

		for (int i = 0; i < FRowCount; ++i)
		{
			T temp = Data[i][Col1];
			Data[i][Col1] = Data[i][Col2];
			Data[i][Col2] = temp;
		}
	}

	#ifndef LRArraySimpleType
	void DestructRow(int Row)
	{
		if (Row >= 0 && Row < FRowCount)
		{
			for (int Ci = 0; Ci < FColCount; ++Ci)
			{
				Data[Row][Ci].~T();
			}
		}
	}

	void DestructCol(int Col)
	{
		if (Col >= 0 && Col < FColCount)
		{
			for (int R = 0; R < FRowCount; ++R)
			{
				Data[R][Col].~T();
			}
		}
	}
	#endif

	// Удалить последнюю строку
	void PopBackRow()
	{
		if (FRowCount == 0)
			return;

		#ifndef LRArraySimpleType
		for (int C = 0; C < FColCount; ++C)
		{
			Data[FRowCount - 1][C].~T();
		}
		#endif

		FRowCount--;
	}

	// Удалить последний столбец
	void PopBackCol()
	{
		if (FColCount == 0)
			return;

		#ifndef LRArraySimpleType
		for (int R = 0; R < FRowCount; ++R)
		{
			Data[R][FColCount - 1].~T();
		}
		#endif

		FColCount--;
	}

	// Очистить матрицу без освобождения памяти
	void Clear()
	{
		#ifndef LRArraySimpleType
		for (int i = 0; i < FRowCount; ++i)
		{
			for (int j = 0; j < FColCount; ++j)
			{
				Data[i][j].~T();
			}
		}
		#endif

		FRowCount = 0;
		FColCount = 0;
	}

	// Освободить всю память
	void Free()
	{
		Clear();

		if (Data)
		{
			for (int i = 0; i < FRowCapacity; ++i)
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

		FRowCapacity = 0;
		FColCapacity = 0;
	}
};

#endif