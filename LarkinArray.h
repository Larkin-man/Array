//Динамический массив.
#ifndef LARKINARRAY
#define LARKINARRAY

//Память, которая может увеличиваться в 2 раза
template< class T >
class DMemory
{
public:
	// Конструктор
	DMemory( int initialSize = 0 )
	{
		mData = 0;
		mSize = 0;

		if ( initialSize )
		{
			SetSize( initialSize );
		}
	}

	// Деструктор
	~DMemory()
	{
		if ( mData )
		{
			free( mData );
		}
	}

	// Доступ к элементам
	T& operator[]( int i )
	{
		return mData[i];
	}
	const T& operator[]( int i ) const
	{
		return mData[i];
	}

	// Базовый указатель
	T *Base()
	{
		return mData;
	}
	const T *Base() const
	{
		return mData;
	}

	// Получить текущий размер
	int Size() const
	{
		return mSize;
	}

	// Убедимся, что памяти хватит для хранения по
	// крайней мере этого числа элементов.
	void EnsureCapacity( int capacity )
	{
		if ( capacity > mSize )
		{
			int newSize = mSize;
			if ( newSize == 0 )
				newSize = 1;
			while ( newSize < capacity )
				newSize *= 2;

			SetSize( newSize );
		}
	}

	// Увеличить размер ровно в два раза
	void Swell()
	{
		int newSize = mSize;
		if ( newSize == 0 )
			newSize = 1;
		newSize *= 2;

		SetSize( newSize );
	}

private:
	// Установить новый размер куска памяти
	void SetSize( int newSize )
	{
		if ( mData )
			mData = (T*)realloc( mData, newSize * sizeof(T) );
		else
			mData = (T*)malloc( newSize * sizeof(T) );

		mSize = newSize;
	}

	// Собственно данные
	T *mData;

	// Размер выделенной памяти
	int mSize;
};

// Динамический массив
template< class T >
class LARKINARRAY
{
	enum
	{
		DEFAULT_RESERVE = 64
	};

public:
	// Конструктор
	LARKINARRAY( int reserveMemory = DEFAULT_RESERVE )
		: mMemory( reserveMemory )
	{
		mCount = 0;
	}
	// Деструктор
	~LARKINARRAY()
	{
		Erase();
	}

	// Доступ к элементам
	T& operator[]( int i ) { return mMemory[i]; }
	const T& operator[]( int i ) const { return mMemory[i]; }
	T& Element( int i ) { return mMemory[i]; }
	const T& Element( int i ) const { return mMemory[i]; }

	// Базовый указатель
	T *Base() { return mMemory.Base(); }
	const T *Base() const { return mMemory.Base(); }

	// Первый и последний элементы
	T& First() { return mMemory[0]; }
	T& Last() { return mMemory[mCount-1]; }
	const T& First() const { return mMemory[0]; }
	const T& Last() const { return mMemory[mCount-1]; }

	// Число элементов в массиве
	int Count() const { return mCount; }

	// Пустой?
	bool IsEmpty() const { return Count() == 0; }

	// Добавить элемент в конец массива
	void PushBack( const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		ConstructCopy( mCount, c );
		mCount++;
	}

	// Удалить последний элемент
	void PopBack()
	{
		Destruct( mCount-1 );
		mCount--;
	}

	// Добавить элемент в произвольное место
	void Insert( int idx, const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		MoveElementsRight( idx, 1 );
		ConstructCopy( idx, c );
		mCount++;
	}

	// Удалить произвольный элемент
	void Remove( int idx )
	{
		Destruct( idx );
		MoveElementsLeft( idx+1, 1 );
		mCount--;
	}

	// Очистить!
	void Erase()
	{
		while ( mCount > 0 )
			PopBack();
	}

	// Размер выделенной памяти
	int MemSize() const
	{
		return mMemory.Size();
	}

	// Гарантирует выделение памяти для указанного
	// числа элементов.
	void EnsureCapacity( int capacity )
	{
		mMemory.EnsureCapacity( capacity );
	}

	// Увеличивает размер выделенной памяти в два раза
	void Swell()
	{
		mMemory.Swell();
	}

	// Найти
	int Find( const T& c, int startIndex = 0 )
	{
		for ( int i = startIndex; i < mCount; i++ )
		{
			if ( mMemory[i] == c )
				return i;
		}
		return -1;
	}

	// Найти и уничтожить! >)
	void RemoveElement( const T& c )
	{
		int i = Find( c );
		if ( i >= 0 )
			Remove( i );
	}

private:
	void ConstructCopy( int i, const T& c )
	{
		new ( &mMemory[i] ) T( c );
	}
	void Destruct( int i )
	{
		mMemory[i].~T();
	}

	// Подвинуть хвост направо
	void MoveElementsRight( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx+num], &mMemory[idx], numBytesToCopy );
		}
	}

	// Подвинуть хвост налево
	void MoveElementsLeft( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx-num], &mMemory[idx], numBytesToCopy );
		}
	}

	// Память, где мы храним данные
	DMemory<T> mMemory;

	// Число элементов в массиве (может быть меньше размера выделенной памяти!)
	int mCount;
};

#endif
