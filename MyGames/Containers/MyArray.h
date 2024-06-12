#pragma once


#include <list>

/*
* 언리얼엔진의 TArray를 참고 했습니다
*/

template <typename Data>
class MyArray
{

public:

	class iterator
	{
	private:
		Data* pos = nullptr;
	public:
		iterator(Data* pos = nullptr)
			:pos(pos)
		{
			
		}
		Data& operator* ()const
		{
			return *pos;
		}

		//int operator-(const iterator& iter)const
		//{
		//	return pos - iter.pos;
		//}

		bool operator!=(const iterator& iter)const
		{
			return pos != iter.pos;
		}
		bool operator==(const iterator& iter)const
		{
			return pos == iter.pos;
		}

		//전위
		iterator& operator++()
		{
			++pos;
			return (*this);
		}
	};

	//class iterator
	//{
	//public:
	//	using iterator_category = std::random_access_iterator_tag;
	//	using value_type = Data;
	//	using difference_type = std::ptrdiff_t;
	//	using pointer = Data*;
	//	using reference = Data&;

	//	iterator(pointer ptr) : ptr_(ptr) {}

	//	reference operator*() const { return *ptr_; }
	//	pointer operator->() { return ptr_; }

	//	// 전위 증가 연산자
	//	iterator& operator++() { ++ptr_; return *this; }
	//	// 후위 증가 연산자
	//	iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }

	//	iterator& operator--() { --ptr_; return *this; }
	//	iterator operator--(int) { iterator temp = *this; --(*this); return temp; }

	//	iterator& operator+=(difference_type offset) { ptr_ += offset; return *this; }
	//	iterator operator+(difference_type offset) const { iterator temp = *this; return temp += offset; }

	//	iterator& operator-=(difference_type offset) { ptr_ -= offset; return *this; }
	//	iterator operator-(difference_type offset) const { iterator temp = *this; return temp -= offset; }

	//	difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }

	//	bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
	//	bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
	//	bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
	//	bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
	//	bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
	//	bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

	//private:
	//	pointer ptr_;
	//};

	iterator begin()
	{
		iterator iter(this->my_base);
		return iter;
	}
	iterator end()
	{
		iterator iter(this->my_base + this->my_size);
		return iter;
	}

public:
	//my_base가 nullptr지만
	//사이즈및 캐퍼시티가 0이므로 원소를 추가할때 Reserve()함수에서 할당이 이뤄집니다
	MyArray()
		: my_base(nullptr), my_capacity(0), my_size(0)
	{
		
	}

	//MyArray<int> my_vector({ 1, 2, 3, 4 })
	MyArray(std::initializer_list<Data> list)
		:MyArray()
	{
		this->Reserve(list.size());
		for (auto& element : list)
		{
			this->my_base[this->my_size++] = element;
		}
	}

	//MyArray<int> my_vector(3,Struct);
	MyArray(const size_t count, Data data)
		:MyArray()
	{
		this->Reserve(count);
		for (size_t i = 0; i < count; ++i)
		{
			this->my_base[this->my_size++] = data;
		}
	}

	//operator= 있어야 &(레퍼런스)타입으로 받을 수 있음
	//operator= 없으면 이상한 데이터를 가져옴
	MyArray& operator=(const MyArray& other)
	{
		if (this != &other)
		{
			delete[] my_base;
			my_base = nullptr;
			my_capacity = my_size = 0;

			Reserve(other.my_capacity);
			for (size_t i = 0; i < other.my_size; ++i) {
				my_base[i] = other.my_base[i];
			}
			my_size = other.my_size;
		}
		return *this;
	}

	//MyArray(MyArray&& other) noexcept : my_base(other.my_base), my_capacity(other.my_capacity), my_size(other.my_size)
	//{
	//	other.my_base = nullptr;
	//	other.my_capacity = 0;
	//	other.my_size = 0;
	//}

	//MyArray& operator=(MyArray&& other) noexcept
	//{
	//	if (this != &other)
	//	{
	//		delete[] my_base;
	//		my_base = other.my_base;
	//		my_capacity = other.my_capacity;
	//		my_size = other.my_size;

	//		other.my_base = nullptr;
	//		other.my_capacity = 0;
	//		other.my_size = 0;
	//	}
	//	return *this;
	//}

	~MyArray()
	{
		if (this->my_base)
		{
			delete[] this->my_base;
		}
	}
protected:
	Data* my_base = nullptr;
	size_t my_capacity = 0;
	size_t my_size = 0;

	//캐퍼시티를 늘릴 때 지정된 값이 없다면 해당 값만큼 늘립니다
	size_t additive_capacity = 32;
public:
	Data& operator[] (const size_t index)
	{
		//인덱스가 유효하면 인덱스 위치에 보관한 자료를 반환하세요.
		this->CheckValidIndex(index);

		//데이터를 반환합니다
		//반환 형식이 참조 형식임을 주의하세요.
		return this->my_base[index];
	}

	// 크기를 조정하는 메서드
	void Resize(size_t new_size, const Data& value = Data())
	{
		if (new_size > this->my_capacity)
		{
			Reserve(new_size);
		}

		// 새로 추가된 요소를 초기화합니다.
		for (size_t i = this->my_size; i < new_size; ++i)
		{
			this->my_base[i] = value;
		}

		this->my_size = new_size;
	}

	//컨테이너의 공간을 새로 생성합니다
	void Reserve(size_t capacity)
	{
		//기존 캐퍼시티가 더 크다면 재할당을 하지 않습니다
		if (this->my_capacity > capacity)
			return;

		Data* temp = new Data[capacity];
		this->my_capacity = capacity;

		//컨테이너에 원소가 있다면 새로 할당한 주소로 옮겨줍니다
		if (this->my_size >= 1)
		{
			for (size_t i = 0; i < this->my_size; i++)
			{
				//temp[i] = my_base[i];
				//std::move는 값을 복사가 아닌 이동을 하기 때문에 더 빠릅니다.
				temp[i] = std::move(this->my_base[i]);
			}
			delete[] this->my_base;

		}

		this->my_base = temp;
	}

	//정해진 위치에 원소를 추가합니다
	//원소 삽입시 기존 위치의 원소부터 마지막원소까지 전부 인덱스가 +1씩 밀리기 때문에
	//원소가 많고 0의 가까운위치에 삽입될수록 느려질 수 있습니다
	void Insert(const size_t insert_index, const Data& data)
	{
		//컨테이너에 비어있는 자리가 있는지 확인
		if (this->my_size == this->my_capacity)
		{
			//빈자리 없음. 재할당을 시도합니다
			this->Reserve(this->my_capacity + this->additive_capacity);
		}


		//컨테이너 중간에 원소가 들어간다면 원소를 해당 지점부터 한칸씩 뒤로 이동시킵니다.
		for (size_t i = this->my_size; i > insert_index; --i)
		{
			this->my_base[i] = this->my_base[i - 1];
		}


		//추가합니다
		this->my_base[insert_index] = data;
		++this->my_size;
	}

	//마지막 위치에 원소를 추가합니다
	void Add(const Data& data)
	{
		Insert(this->Num(), data);
	}

	

	//해당 위치의 원소를 삭제합니다
	void RemoveAt(const size_t index)
	{
		this->CheckValidIndex(index);

		--this->my_size;
		for (size_t i = index; i < this->my_size; ++i)
		{
			this->my_base[i] = this->my_base[i + 1];
		}
	}

	//원소이동의 부하를 줄이기 위해 삭제될 원소와 마지막 원소의 위치만 변경하고 삭제합니다
	//마지막 원소가 삭제된 원소의 위치로 오기 때문에 원소의 순서는 보장되지 않습니다
	void RemoveAtSwap(const size_t index)
	{
		--this->my_size;
		this->my_base[index] = this->my_base[this->my_size];
	}

	//배열의 원소를 삭제하지않고 사이즈를 0으로 만듭니다
	//캐퍼시티를 건들지 않고 초기화할 때 사용됩니다
	//Clear()함수후에 원소룰 추가하면 기존에 있던 원소를 덮어씌웁니다
	//언리얼엔진의 Reset()과 같은기능입니다
	void Clear()
	{
		this->my_size = 0;
	}

	//컨테이너의 원소개수입니다
	size_t Num()
	{
		return this->my_size;
	}

	//컨테이너의 캐퍼시티개수입니다
	size_t Max()
	{
		return this->my_capacity;
	}

	//인덱스 유효성검사를 합니다
//유효하지 않으면 throw
	bool CheckValidIndex(const size_t index)
	{
		if ((index >= 0) && (index < this->my_size))
		{
			return true;
		}
		else
		{
			throw printf("범위를 벗어난 인덱스를 사용하였습니다. 접근하려는 인덱스: %zd, 배열크기: %zd", index, this->Num());
		}
	}





};