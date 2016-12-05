// Graph.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ALGraph.cpp"
#include <iostream>
using namespace std;

int main()
{
	ALGraph<int> alGraph;
	cout << "isEulerianGraph:" << boolalpha << alGraph.isEulerianGraph() << endl;
	if (alGraph.isEulerianGraph())
	{
		cout << "ŷ��ͨ·(Fleury�㷨(DFS+STACK)):" << endl;
		alGraph.fleury(0);
		cout << endl;
	}
	cout << "Kruskal�㷨:" << endl;
	alGraph.kruskal();

	return 0;
}

/*
6 18
0 1 2 3 4 5
0 1 34
0 2 46
0 5 19
1 0 34
1 4 12
2 0 46
2 3 17
2 5 25
3 2 17
3 4 38
3 5 25
4 1 12
4 3 38
4 5 26
5 0 19
5 2 25
5 3 25
5 4 26
*/