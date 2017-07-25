#pragma once
template<class T>
class IndirectList 
{
public:
	IndirectList(int MaxListSize = 10);
	~IndirectList();
	bool IsEmpty() const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	IndirectList<T>& Delete(int k, T& x);
	IndirectList<T>& Insert(int k, const T& x);
	void Output(ostream& out) const;
private:
	T **table; //һάT����ָ������
	int length, MaxSize;
};

template<class T>
IndirectList<T>::IndirectList(int MaxListSize)
{
	//���캯��
	MaxSize = MaxListSize;
	table = new T *[MaxSize];
	length = 0;
};

template<class T>
IndirectList<T>::~IndirectList()
{
	//ɾ����
	for (int i = 0; i < length; i++)
		delete table[i];
	delete[] table;
};

template<class T>
bool IndirectList<T>::Find(int k, T& x) const
{
	//ȡ��k��Ԫ����x
	//��������ڵ�k��Ԫ�أ���������false�����򷵻�true
	if (k < 1 || k > length) return false; //�����ڵ�k��Ԫ��
	x = *table[k - 1];
	return true;
};

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k, T& x)
{ 
	//�ѵ�k��Ԫ�ش�����x��Ȼ��ɾ����k��Ԫ��
	// ��������ڵ�k��Ԫ�أ��������쳣OutOfBounds
	if (Find(k, x)) 
	{
		//��ǰ�ƶ�ָ��k+l, ...
		for (int i = k; i < length; i++)
			table[i - l] = table[i];
		length--;
		return *this;
	}
	else throw OutOfBounds();
};

template<class T>
IndirectList<T>& IndirectList<T>::Insert(int k, const T& x)
{
	// �ڵ�k��Ԫ��֮�����x
	// ��������ڵ�k��Ԫ�أ��������쳣OutOfBounds
	// ���û���㹻�Ŀռ䣬�򴫵�NoMem�쳣
	if (k < 0 || k > length) throw OutOfBounds();
	if (length == MaxSize) throw NoMem();
	// ����ƶ�һ��λ��
	for (int i = length - 1; i >= k; i--)
		table[i + 1] = table[i];
	table[k] = new T;
	*table[k] = x;
	length++;
	return *this;
}