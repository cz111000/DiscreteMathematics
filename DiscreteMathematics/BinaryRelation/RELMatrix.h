#pragma once
#include "Set.h"
#include <iostream>
using namespace std;
#define MAX_SIZE 100

template<class DataType>
class RELMatrix
{
public:
	RELMatrix();
	~RELMatrix();
	bool isReflexive();
	bool isIrreflexive();
	bool isSymmetrical();
	bool isDissymmetrical();
	bool isTransitive();
	bool isEquivalent();
	Set<Set<DataType>> getQuotientSet();
	RELMatrix<DataType> pow(int n);
	template<class DataType>
	friend istream& operator>>(istream& in, RELMatrix<DataType>& matrix);
	template<class DataType>
	friend ostream& operator<<(ostream& out, RELMatrix<DataType>& matrix);
private:
	int matrix[MAX_SIZE][MAX_SIZE];
	DataType data[MAX_SIZE];
	int count;
};

template<class DataType>
RELMatrix<DataType>::RELMatrix()
{
	count = 0;
}

template<class DataType>
RELMatrix<DataType>::~RELMatrix()
{
}

template<class DataType>
bool RELMatrix<DataType>::isReflexive()
{
	for (int i = 0;i < count;i++)
		if (matrix[i][i] == 0)
			return false;
	return true;
}

template<class DataType>
bool RELMatrix<DataType>::isIrreflexive()
{
	for (int i = 0;i < count;i++)
		if (matrix[i][i] == 1)
			return false;
	return true;
}

template<class DataType>
bool RELMatrix<DataType>::isSymmetrical()
{
	for (int i = 0;i < count;i++)
		for (int j = 0;j < i;j++)
			if (matrix[i][j] != matrix[j][i])
				return false;
	return true;
}

template<class DataType>
bool RELMatrix<DataType>::isDissymmetrical()
{
	for (int i = 0;i < count;i++)
		for (int j = 0;j < i;j++)
			if (matrix[i][j] == matrix[j][i])
				if (matrix[i][j] == 1)
					return false;
	return true;
}

template<class DataType>
bool RELMatrix<DataType>::isTransitive()
{
	RELMatrix temp = pow(2);
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (temp.matrix[i][j] == 1 && matrix[i][j] == 0)
				return false;
	return true;
}

template<class DataType>
bool RELMatrix<DataType>::isEquivalent()
{
	if (isReflexive() && isSymmetrical() && isTransitive())
		return true;
	return false;
}

template<class DataType>
Set<Set<DataType>> RELMatrix<DataType>::getQuotientSet()
{
	Set<Set<DataType>> result;
	bool visited[MAX_SIZE] = { false };
	for (int i = 0; i < count; i++)
		if (visited[i] == false)
		{
			Set<DataType> temp;
			temp.insert(data[i]);
			visited[i] = true;
			for (int j = 0; j < count; j++)
				if (visited[j] == false && matrix[j][i] == 1)
				{
					temp.insert(data[j]);
					visited[j] = true;
				}
			result.insert(temp);
		}
	return result;
}

template<class DataType>
RELMatrix<DataType> RELMatrix<DataType>::pow(int n)
{
	RELMatrix<DataType> result;
	result.count = count;
	RELMatrix<DataType> temp = *this;
	while (--n)
	{
		for (int k = 0; k < count; k++)
			for (int i = 0; i < count; i++)
			{
				result.matrix[k][i] = 0;
				for (int j = 0; j < count; j++)
					result.matrix[k][i] += temp.matrix[k][j] * matrix[j][i];
				if (result.matrix[k][i] > 1)
					result.matrix[k][i] = 1;
			}
		temp = result;
	}
	return result;
}

template<class DataType>
istream& operator>>(istream& in, RELMatrix<DataType>& matrix)
{
	cout << "输入元素个数:" << endl;
	in >> matrix.count;
	cout << "输入元素:" << endl;
	for (int i = 0; i < matrix.count; i++)
		in >> matrix.data[i];
	cout << "输入关系矩阵:" << endl;
	for (int i = 0; i < matrix.count; i++)
		for (int j = 0; j < matrix.count; j++)
			in >> matrix.matrix[i][j];
	return in;
}

template<class DataType>
ostream& operator<<(ostream& out, RELMatrix<DataType>& matrix)
{
	for (int i = 0; i < matrix.count; i++)
	{
		out << '[' << ' ';
		for (int j = 0; j < matrix.count; j++)
			out << matrix.matrix[i][j] << ' ';
		out << ']';
		out << endl;
	}
	return out;
}
