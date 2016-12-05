// BinaryRelation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RELMatrix.h"
#include <iostream>
using namespace std;

int main()
{
	RELMatrix<char> relMatrix;
	cin >> relMatrix;
	cout << "M:" << endl << relMatrix;
	cout << "isReflexive:" << boolalpha << relMatrix.isReflexive() << endl;
	cout << "isIrreflexive:" << boolalpha << relMatrix.isIrreflexive() << endl;
	cout << "isSymmetrical:" << boolalpha << relMatrix.isSymmetrical() << endl;
	cout << "isDissymmetrical:" << boolalpha << relMatrix.isDissymmetrical() << endl;
	cout << "isTransitive:" << boolalpha << relMatrix.isTransitive() << endl;
	cout << "isEquivalent:" << boolalpha << relMatrix.isEquivalent() << endl;
	cout << "pow(2):" << endl << relMatrix.pow(2);
	if (relMatrix.isEquivalent())
		cout << "R=" << relMatrix.getQuotientSet() << endl;

	return 0;
}
