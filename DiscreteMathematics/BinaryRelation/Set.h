#pragma once
#include <iostream>
using namespace std;

template<class DataType>
class Set
{
public:
	Set() { length = 0; }
	Set(DataType data[], int length);
	Set(const Set<DataType>& set);
	~Set() {}
	void clear();
	void insert(DataType data, bool check = true);
	void remove(DataType data);
	bool exsit(DataType data);
	int size();
	Set<DataType> sort(bool up = true);
	Set<DataType>& unionSet(const Set<DataType>& set);
	Set<DataType>& intersectionSet(const Set<DataType>& set);
	Set<DataType>& differenceSet(const Set<DataType>& set);
	Set<Set<DataType>>& powerSet();
	Set<DataType>& sysmmetricDifferenceSet(const Set<DataType>& set);
	Set<Set<DataType>>& cartesianProductSet(const Set<DataType>& set);
	bool operator==(const Set<DataType>& set);
	bool operator>(const Set<DataType>& set);
	template<class DataType>
	friend istream& operator>>(istream& in, Set<DataType>& set);
	template<class DataType>
	friend ostream& operator<<(ostream& out, const Set<DataType>& set);
private:
	Set<Set<DataType>>& powerSet(Set<Set<DataType>>& set, int begin = 0, int top = -1);
	DataType data[100];
	int length;
};

template<class DataType>
Set<DataType>::Set(DataType data[], int length)
{
	this->length = length;
	for (int i = 0;i < length;i++)
		this->data[i] = data[i];
}

template<class DataType>
Set<DataType>::Set(const Set<DataType>& set)
{
	length = set.length;
	for (int i = 0;i < length;i++)
		data[i] = set.data[i];
}

template<class DataType>
void Set<DataType>::clear()
{
	length = 0;
}

template<class DataType>
void Set<DataType>::insert(DataType data, bool check)
{
	if (!check || !exsit(data))
		this->data[length++] = data;
}

template<class DataType>
bool Set<DataType>::exsit(DataType data)
{
	for (int i = 0;i < length;i++)
		if (this->data[i] == data)
			return true;
	return false;
}

template<class DataType>
int Set<DataType>::size()
{
	return length;
}

template<class DataType>
void Set<DataType>::remove(DataType data)
{
	for (int i = 0;i < length;i++)
		if (this->data[i] == data)
		{
			length--;
			for (int j = i--;j < length;j++)
				this->data[j] = this->data[j + 1];
		}
}

template<class DataType>
Set<DataType> Set<DataType>::sort(bool up)
{
	DataType temp;
	for (int i = 0;i < length;i++)
		for (int j = 0;j < length - 1 - i;j++)
			if (up ? (data[j] > data[j + 1]) : !(data[j] > data[j + 1]))
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}

	return *this;
}

template<class DataType>
Set<DataType>& Set<DataType>::unionSet(const Set<DataType>& set)
{
	Set<DataType> *temp = new Set<DataType>;
	for (int i = 0;i < set.length;i++)
		if (exsit(set.data[i]))
			temp->insert(set.data[i]);
	return *temp;
}

template<class DataType>
Set<DataType>& Set<DataType>::intersectionSet(const Set<DataType>& set)
{
	Set<DataType> *temp = new Set<DataType>(*this);
	for (int i = 0;i < set.length;i++)
		temp->insert(set.data[i]);
	return *temp;

}

template<class DataType>
Set<DataType>& Set<DataType>::differenceSet(const Set<DataType>& set)
{
	Set<DataType> *temp = new Set<DataType>(*this);
	for (int i = 0;i < set.length;i++)
		if (exsit(set.data[i]))
			temp->remove(set.data[i]);
	return *temp;
}

template<class DataType>
Set<DataType>& Set<DataType>::sysmmetricDifferenceSet(const Set<DataType>& set)
{
	Set<DataType> *temp = new Set<DataType>(*this);
	for (int i = 0;i < set.length;i++)
		if (exsit(set.data[i]))
			temp->remove(set.data[i]);
		else
			temp->insert(set.data[i]);

	return *temp;
}

template<class DataType>
Set<Set<DataType>>& Set<DataType>::powerSet()
{
	Set<Set<DataType>> *set = new Set<Set<DataType>>(new Set<DataType>(), 1);
	powerSet(*set);
	return *set;
}

template<class DataType>
Set<Set<DataType>>& Set<DataType>::powerSet(Set<Set<DataType>>& set, int begin, int top)
{
	static DataType stack[100];
	for (int i = begin;i < length;i++)
	{
		stack[++top] = data[i];
		Set<DataType> temp(stack, top + 1);set.insert(temp);
		powerSet(set, ++begin, top);
		top--;
	}

	return set;
}

template<class DataType>
Set<Set<DataType>>& Set<DataType>::cartesianProductSet(const Set<DataType>& set)
{
	Set<Set<DataType>> *result = new Set<Set<DataType>>;
	for (int i = 0;i < length;i++)
		for (int j = 0;j < set.length;j++)
		{
			Set<DataType> temp;
			temp.insert(data[i]);
			temp.insert(set.data[j], false);
			result->insert(temp);
		}

	return *result;
}

template<class DataType>
bool Set<DataType>::operator==(const Set<DataType>& set)
{
	if (length != set.length)
		return false;
	for (int i = 0;i < length;i++)
		if (data[i] != set.data[i])
			return false;
	return true;
}

template<class DataType>
bool Set<DataType>::operator>(const Set<DataType>& set)
{
	if (length == set.length)
		for (int i = 0;i < length;i++)
			if (data[i] > set.data[i])
				return true;
	return length > set.length ? true : false;
}

template<class DataType>
istream& operator>>(istream& in, Set<DataType>& set)
{
	int length;
	DataType temp;
	cout << "输入集合元素个数：";
	in >> length;
	for (int i = 0;i < length;i++)
	{
		cout << "输入第" << i + 1 << "个元素：";
		in >> temp;
		set.insert(temp);
	}

	return in;
}

template<class DataType>
ostream& operator<<(ostream& out, const Set<DataType>& set)
{
	if (set.length == 0)
		out << "Φ";
	else
	{
		out << "{";
		for (int i = 0;i < set.length - 1;i++)
			out << set.data[i] << ",";
		out << set.data[set.length - 1] << "}";
	}

	return out;
}
