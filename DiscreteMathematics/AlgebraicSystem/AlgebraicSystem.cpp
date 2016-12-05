// AlgebraicSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ASystem.h"

int main()
{
	ASystem<char> aSystem;
	cin >> aSystem;
	cout << aSystem;
	cout << "isGroup:" << boolalpha << aSystem.isGroup() << endl;

	return 0;
}

/*
4
e a b c
e a b c
a e c b
b c e a
c b a e
*/