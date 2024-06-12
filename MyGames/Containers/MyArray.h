#pragma once


#include <list>

/*
* �𸮾����� TArray�� ���� �߽��ϴ�
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

		//����
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

	//	// ���� ���� ������
	//	iterator& operator++() { ++ptr_; return *this; }
	//	// ���� ���� ������
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
	//my_base�� nullptr����
	//������� ĳ�۽�Ƽ�� 0�̹Ƿ� ���Ҹ� �߰��Ҷ� Reserve()�Լ����� �Ҵ��� �̷����ϴ�
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

	//operator= �־�� &(���۷���)Ÿ������ ���� �� ����
	//operator= ������ �̻��� �����͸� ������
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

	//ĳ�۽�Ƽ�� �ø� �� ������ ���� ���ٸ� �ش� ����ŭ �ø��ϴ�
	size_t additive_capacity = 32;
public:
	Data& operator[] (const size_t index)
	{
		//�ε����� ��ȿ�ϸ� �ε��� ��ġ�� ������ �ڷḦ ��ȯ�ϼ���.
		this->CheckValidIndex(index);

		//�����͸� ��ȯ�մϴ�
		//��ȯ ������ ���� �������� �����ϼ���.
		return this->my_base[index];
	}

	// ũ�⸦ �����ϴ� �޼���
	void Resize(size_t new_size, const Data& value = Data())
	{
		if (new_size > this->my_capacity)
		{
			Reserve(new_size);
		}

		// ���� �߰��� ��Ҹ� �ʱ�ȭ�մϴ�.
		for (size_t i = this->my_size; i < new_size; ++i)
		{
			this->my_base[i] = value;
		}

		this->my_size = new_size;
	}

	//�����̳��� ������ ���� �����մϴ�
	void Reserve(size_t capacity)
	{
		//���� ĳ�۽�Ƽ�� �� ũ�ٸ� ���Ҵ��� ���� �ʽ��ϴ�
		if (this->my_capacity > capacity)
			return;

		Data* temp = new Data[capacity];
		this->my_capacity = capacity;

		//�����̳ʿ� ���Ұ� �ִٸ� ���� �Ҵ��� �ּҷ� �Ű��ݴϴ�
		if (this->my_size >= 1)
		{
			for (size_t i = 0; i < this->my_size; i++)
			{
				//temp[i] = my_base[i];
				//std::move�� ���� ���簡 �ƴ� �̵��� �ϱ� ������ �� �����ϴ�.
				temp[i] = std::move(this->my_base[i]);
			}
			delete[] this->my_base;

		}

		this->my_base = temp;
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	//���� ���Խ� ���� ��ġ�� ���Һ��� ���������ұ��� ���� �ε����� +1�� �и��� ������
	//���Ұ� ���� 0�� �������ġ�� ���Եɼ��� ������ �� �ֽ��ϴ�
	void Insert(const size_t insert_index, const Data& data)
	{
		//�����̳ʿ� ����ִ� �ڸ��� �ִ��� Ȯ��
		if (this->my_size == this->my_capacity)
		{
			//���ڸ� ����. ���Ҵ��� �õ��մϴ�
			this->Reserve(this->my_capacity + this->additive_capacity);
		}


		//�����̳� �߰��� ���Ұ� ���ٸ� ���Ҹ� �ش� �������� ��ĭ�� �ڷ� �̵���ŵ�ϴ�.
		for (size_t i = this->my_size; i > insert_index; --i)
		{
			this->my_base[i] = this->my_base[i - 1];
		}


		//�߰��մϴ�
		this->my_base[insert_index] = data;
		++this->my_size;
	}

	//������ ��ġ�� ���Ҹ� �߰��մϴ�
	void Add(const Data& data)
	{
		Insert(this->Num(), data);
	}

	

	//�ش� ��ġ�� ���Ҹ� �����մϴ�
	void RemoveAt(const size_t index)
	{
		this->CheckValidIndex(index);

		--this->my_size;
		for (size_t i = index; i < this->my_size; ++i)
		{
			this->my_base[i] = this->my_base[i + 1];
		}
	}

	//�����̵��� ���ϸ� ���̱� ���� ������ ���ҿ� ������ ������ ��ġ�� �����ϰ� �����մϴ�
	//������ ���Ұ� ������ ������ ��ġ�� ���� ������ ������ ������ ������� �ʽ��ϴ�
	void RemoveAtSwap(const size_t index)
	{
		--this->my_size;
		this->my_base[index] = this->my_base[this->my_size];
	}

	//�迭�� ���Ҹ� ���������ʰ� ����� 0���� ����ϴ�
	//ĳ�۽�Ƽ�� �ǵ��� �ʰ� �ʱ�ȭ�� �� ���˴ϴ�
	//Clear()�Լ��Ŀ� ���ҷ� �߰��ϸ� ������ �ִ� ���Ҹ� �����ϴ�
	//�𸮾����� Reset()�� ��������Դϴ�
	void Clear()
	{
		this->my_size = 0;
	}

	//�����̳��� ���Ұ����Դϴ�
	size_t Num()
	{
		return this->my_size;
	}

	//�����̳��� ĳ�۽�Ƽ�����Դϴ�
	size_t Max()
	{
		return this->my_capacity;
	}

	//�ε��� ��ȿ���˻縦 �մϴ�
//��ȿ���� ������ throw
	bool CheckValidIndex(const size_t index)
	{
		if ((index >= 0) && (index < this->my_size))
		{
			return true;
		}
		else
		{
			throw printf("������ ��� �ε����� ����Ͽ����ϴ�. �����Ϸ��� �ε���: %zd, �迭ũ��: %zd", index, this->Num());
		}
	}





};