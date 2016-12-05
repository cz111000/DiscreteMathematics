#pragma once
#include <iostream>
using namespace std;

#define MAX_SIZE 100

template<class DataType>
class ASystem
{
public:
	ASystem();
	~ASystem();
	DataType operate(const DataType a, const DataType b);
	bool isGroup();
	template<class DataType>
	friend istream& operator>>(istream& in, ASystem<DataType>& aSystem);
	template<class DataType>
	friend ostream& operator<<(ostream& out, const ASystem<DataType>& aSystem);
private:
	DataType algebra[MAX_SIZE];
	DataType operation[MAX_SIZE][MAX_SIZE];
	int count;
};

template<class DataType>
ASystem<DataType>::ASystem()
{
	count = 0;
}

template<class DataType>
ASystem<DataType>::~ASystem()
{
}

template<class DataType>
inline DataType ASystem<DataType>::operate(const DataType a, const DataType b)
{
	int i, j;
	for (i = 0; i < count; i++)
		if (algebra[i] == a)
			break;
	for (j = 0; j < count; j++)
		if (algebra[j] == b)
			break;
	return operation[i][j];
}

template<class DataType>
inline bool ASystem<DataType>::isGroup()
{
	//单位元判断
	bool exist = false;
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (operation[i][j] == algebra[j] && operation[j][i] == algebra[j])
			{
				exist = true;
				break;
			}
	if (!exist)
		return false;
	//结合性判断
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			for (int k = 0; k < count; k++)
				if (operate(operation[i][j], algebra[k]) != operate(algebra[i], operation[j][k]))
					return false;
	//X^-1∈G判断
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (operation[i][j] != operation[j][i])
				return false;
	return true;
}

template<class DataType>
istream& operator>>(istream& in, ASystem<DataType>& aSystem)
{
	in >> aSystem.count;
	for (int i = 0; i < aSystem.count; i++)
		in >> aSystem.algebra[i];
	for (int i = 0; i < aSystem.count; i++)
		for (int j = 0; j < aSystem.count; j++)
			in >> aSystem.operation[i][j];
	return in;
}

template<class DataType>
ostream& operator<<(ostream& out, const ASystem<DataType>& aSystem)
{
	out << "G:";
	for (int i = 0; i < aSystem.count; i++)
		out << aSystem.algebra[i] << ' ';
	out << endl;
	out << "Opration:" << endl;
	for (int i = 0; i < aSystem.count; i++)
	{
		for (int j = 0; j < aSystem.count; j++)
			out << aSystem.operation[i][j] << ' ';
		out << endl;
	}
	return out;
}
