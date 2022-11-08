//������������ ������.
#ifndef LARKINARRAY
#define LARKINARRAY

//������, ������� ����� ������������� � 2 ����
template< class T >
class DMemory
{
public:
	// �����������
	DMemory( int initialSize = 0 )
	{
		mData = 0;
		mSize = 0;

		if ( initialSize )
		{
			SetSize( initialSize );
		}
	}

	// ����������
	~DMemory()
	{
		if ( mData )
		{
			free( mData );
		}
	}

	// ������ � ���������
	T& operator[]( int i )
	{
		return mData[i];
	}
	const T& operator[]( int i ) const
	{
		return mData[i];
	}

	// ������� ���������
	T *Base()
	{
		return mData;
	}
	const T *Base() const
	{
		return mData;
	}

	// �������� ������� ������
	int Size() const
	{
		return mSize;
	}

	// ��������, ��� ������ ������ ��� �������� ��
	// ������� ���� ����� ����� ���������.
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

	// ��������� ������ ����� � ��� ����
	void Swell()
	{
		int newSize = mSize;
		if ( newSize == 0 )
			newSize = 1;
		newSize *= 2;

		SetSize( newSize );
	}

private:
	// ���������� ����� ������ ����� ������
	void SetSize( int newSize )
	{
		if ( mData )
			mData = (T*)realloc( mData, newSize * sizeof(T) );
		else
			mData = (T*)malloc( newSize * sizeof(T) );

		mSize = newSize;
	}

	// ���������� ������
	T *mData;

	// ������ ���������� ������
	int mSize;
};

// ������������ ������
template< class T >
class LARKINARRAY
{
	enum
	{
		DEFAULT_RESERVE = 64
	};

public:
	// �����������
	LARKINARRAY( int reserveMemory = DEFAULT_RESERVE )
		: mMemory( reserveMemory )
	{
		mCount = 0;
	}
	// ����������
	~LARKINARRAY()
	{
		Erase();
	}

	// ������ � ���������
	T& operator[]( int i ) { return mMemory[i]; }
	const T& operator[]( int i ) const { return mMemory[i]; }
	T& Element( int i ) { return mMemory[i]; }
	const T& Element( int i ) const { return mMemory[i]; }

	// ������� ���������
	T *Base() { return mMemory.Base(); }
	const T *Base() const { return mMemory.Base(); }

	// ������ � ��������� ��������
	T& First() { return mMemory[0]; }
	T& Last() { return mMemory[mCount-1]; }
	const T& First() const { return mMemory[0]; }
	const T& Last() const { return mMemory[mCount-1]; }

	// ����� ��������� � �������
	int Count() const { return mCount; }

	// ������?
	bool IsEmpty() const { return Count() == 0; }

	// �������� ������� � ����� �������
	void PushBack( const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		ConstructCopy( mCount, c );
		mCount++;
	}

	// ������� ��������� �������
	void PopBack()
	{
		Destruct( mCount-1 );
		mCount--;
	}

	// �������� ������� � ������������ �����
	void Insert( int idx, const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		MoveElementsRight( idx, 1 );
		ConstructCopy( idx, c );
		mCount++;
	}

	// ������� ������������ �������
	void Remove( int idx )
	{
		Destruct( idx );
		MoveElementsLeft( idx+1, 1 );
		mCount--;
	}

	// ��������!
	void Erase()
	{
		while ( mCount > 0 )
			PopBack();
	}

	// ������ ���������� ������
	int MemSize() const
	{
		return mMemory.Size();
	}

	// ����������� ��������� ������ ��� ����������
	// ����� ���������.
	void EnsureCapacity( int capacity )
	{
		mMemory.EnsureCapacity( capacity );
	}

	// ����������� ������ ���������� ������ � ��� ����
	void Swell()
	{
		mMemory.Swell();
	}

	// �����
	int Find( const T& c, int startIndex = 0 )
	{
		for ( int i = startIndex; i < mCount; i++ )
		{
			if ( mMemory[i] == c )
				return i;
		}
		return -1;
	}

	// ����� � ����������! >)
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

	// ��������� ����� �������
	void MoveElementsRight( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx+num], &mMemory[idx], numBytesToCopy );
		}
	}

	// ��������� ����� ������
	void MoveElementsLeft( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx-num], &mMemory[idx], numBytesToCopy );
		}
	}

	// ������, ��� �� ������ ������
	DMemory<T> mMemory;

	// ����� ��������� � ������� (����� ���� ������ ������� ���������� ������!)
	int mCount;
};

#endif
