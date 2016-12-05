// Logic.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

template<typename DataType>
class Stack
{
private:
	DataType data[100];
	int top;
public:
	Stack() { top = -1; }
	~Stack() {}
	void push(DataType data);
	DataType pop();
	DataType get();
	bool empty();
	void clear();
};

template<typename DataType>
void Stack<DataType>::push(DataType data)
{
	if (top == 100)throw string("Stack Full");
	this->data[++top] = data;
}

template<typename DataType>
DataType Stack<DataType>::pop()
{
	if (top == -1)throw string("None");
	return data[top--];
}

template<typename DataType>
DataType Stack<DataType>::get()
{
	if (top == -1)throw string("None");
	return data[top];
}

template<typename DataType>
bool Stack<DataType>::empty()
{
	return top == -1 ? true : false;
}

template<typename DataType>
void Stack<DataType>::clear()
{
	top = -1;
}

double squareRoot(double a);
double absol(double number);
bool high(char a, char b);
string symLowToHigh(string str);
double calculate(double a, char operate, double b);
template<typename DataType1, typename DataType2>
void judge(Stack<DataType1>& number, Stack<DataType2>& symbol, string str);
template<typename DataType1, typename DataType2>
void logicalOperate(Stack<DataType1>& number, Stack<DataType2>& symbol, string origin, string str, int begin);
void print(string str);

enum Operate {
	add = '+', minus = '-', multiply = '*', divide = '/', factorial = '!', square = ';', power = '^', absolute = ':',
	logicalNOT = '~', logicalAND = '@', logicalOR = '#', logicalIF = '$', logicalIFF = '&'
};

int main()
{
	string str;
	Stack<char> symbol;
	Stack<double> number;
	cout << "                 " << "��ѧ������ V1.2" << endl;
	cout << "===============================================" << endl;
	cout <<
		"��:" << (char)Operate::add <<
		" ��:" << (char)Operate::minus <<
		" ��:" << (char)Operate::multiply <<
		" ��:" << (char)Operate::divide <<
		" ȡ��:" << (char)Operate::absolute <<
		" �׳�:" << (char)Operate::factorial <<
		" ����:" << (char)Operate::square <<
		" �η�:" << (char)Operate::power
		<< endl;
	cout << "                   " << "֧������()" << endl;
	cout << "===============================================" << endl;
	while (true) {
		symbol.clear();number.clear();
		cout << "input string:";
		cin >> str;
		if (str == "exit")
			break;
		str = symLowToHigh(str) + "=";
		try
		{
			cout << "1.����ģʽ 2.����ģʽ" << endl;
			int n;cin >> n;
			if (n == 2)
			{
				string temp = str;
				logicalOperate(number, symbol, temp, str, 0);
			}
			else
			{
				judge(number, symbol, str);
				cout << "result:" << number.pop() << endl;
			}
		}
		catch (string& e) { cout << e << endl; }
	}

	return 0;
}

string symLowToHigh(string str)
{
	for (int i = 0;i < str.length();i++) {
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, "(");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, ")");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, ".");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, ":");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, ";");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, "~");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, "@");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, "#");
		if (str.compare(i, 2, "��") == 0)
			str.replace(i, 2, "$");
		if (str.compare(i, 2, "?") == 0)
			str.replace(i, 2, "&");
	}
	return str;
}

bool high(char a, char b) {
	if (b == ')')
		return true;
	if (b == '=')
		return true;
	if (a == Operate::absolute)
		return true;
	if (a == Operate::square)
		return true;
	if (a == Operate::factorial)
		if (b != Operate::square)
			return true;
		else
			return false;
	if (a == Operate::power)
		if (b != Operate::square && b != Operate::factorial)
			return true;
		else
			return false;
	if (a == Operate::multiply || a == Operate::divide)
		if (b != Operate::factorial && b != Operate::square)
			return true;
		else
			return false;
	if (a == Operate::add || a == Operate::minus)
		if (b == Operate::add || b == Operate::minus)
			return true;
		else
			return false;
	//logical
	if (a == Operate::logicalNOT)
		return true;
	if (a == Operate::logicalAND)
		if (b != Operate::logicalNOT)
			return true;
		else
			return false;
	if (a == Operate::logicalOR)
		if (b != Operate::logicalNOT && b != Operate::logicalAND)
			return true;
		else
			return false;
	if (a == Operate::logicalIF)
		if (b != Operate::logicalNOT && b != Operate::logicalAND && b != Operate::logicalOR)
			return true;
		else
			return false;
	if (a == Operate::logicalIFF)
		if (b != Operate::logicalNOT && b != Operate::logicalAND && b != Operate::logicalOR && b != Operate::logicalIF)
			return true;
		else
			return false;
	return false;
}

double squareRoot(double a)		//ţ�ٵ����������㷽����ѯ�԰ٶ�֪����
{
	double result, last;
	if (a == 0)		//��ƽ���е������������ֹ��ĸΪ0
		return 0;
	result = a;
	while (true)
	{
		last = result;
		result = (result + a / result) / 2.0;		//����a/resultʹ�̲��ϱƽ���0���̼���result�ٳ���2ȡ�м��������ϱƽ�׼ȷ��ƽ����
		if (absol(last - result) < 0.00000001)
			break;		//��ȷ����9λ��
	}
	return result;
}

double absol(double number)		//����ֵ(С����)
{
	return number < 0 ? -number : number;
}

double calculate(double a, char operate, double b) {
	if (operate == Operate::multiply)
		return a*b;
	if (operate == Operate::divide)
		if (b == 0)throw string("��������Ϊ0");
		else
			return a / b;
	if (operate == Operate::add)
		return a + b;
	if (operate == Operate::minus)
		return a - b;
	if (operate == Operate::absolute)
		return absol(a);
	if (operate == Operate::square)
		if (a < 0)throw string("������������Ϊ����");
		else
			return squareRoot(a);
	if (operate == Operate::factorial) {
		if (a < 0 || a != (int)a)throw string("�׳˸�ʽ����");
		double sum = 1;
		for (int i = (int)a;i > 1;i--)
			sum *= i;
		return sum;
	}
	if (operate == Operate::power)
		return pow(a, b);
	if (operate == Operate::logicalNOT)
		return a == 0 ? 1 : 0;
	if (operate == Operate::logicalAND)
		if (a == 1 && b == 1)
			return 1;
		else
			return 0;
	if (operate == Operate::logicalOR)
		if (a == 0 && b == 0)
			return 0;
		else
			return 1;
	if (operate == Operate::logicalIF)
		if (a == 1 && b == 0)
			return 0;
		else
			return 1;
	if (operate == Operate::logicalIFF)
		return a == b ? 1 : 0;
	return 0;
}

void print(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == Operate::logicalNOT)
			cout << "��";
		else if (str[i] == Operate::logicalAND)
			cout << "��";
		else if (str[i] == Operate::logicalOR)
			cout << "��";
		else if (str[i] == Operate::logicalIF)
			cout << "��";
		else if (str[i] == Operate::logicalIFF)
			cout << "?";
		else
			cout << str[i];
}

template<typename DataType1, typename DataType2>
void judge(Stack<DataType1>& number, Stack<DataType2>& symbol, string str)
{
	double temp = -1;
	bool point = false;
	int position = 0;
	for (int i = 0;i < str.length();i++) {
		//get numbers
		if (str[i] == '.' || str[i] >= '0' && str[i] <= '9') {
			if (temp == -1)temp = 0;
			if (str[i] == '.')
				point = true;
			else if (point) {
				double right = 1;
				position++;
				for (int i = 0;i < position;i++)
					right *= 1.0 / 10;
				temp += (str[i] - '0')*right;
			}
			else
				temp = temp * 10 + (str[i] - '0');
		}
		//get stmbols
		else {
			//������
			if (str[i] == Operate::minus) {
				if (i == 0 || str[i - 1] == '(')
					number.push(0);
			}
			//������ջ
			if (temp >= 0) {
				number.push(temp);
				temp = -1;position = 0;point = false;
			}
			//���㴦��
			if (str[i] == '(') {
				symbol.push('(');
			}
			else {
				while (!symbol.empty() && !number.empty() && symbol.get() != '(' && high(symbol.get(), str[i])) {
					try {
						if (symbol.get() == Operate::logicalNOT)
							number.push(calculate(number.pop(), symbol.pop(), 0));
						else if (symbol.get() == Operate::absolute)
							number.push(calculate(number.pop(), symbol.pop(), 0));
						else if (symbol.get() == Operate::factorial)
							number.push(calculate(number.pop(), symbol.pop(), 0));
						else if (symbol.get() == Operate::square)
							number.push(calculate(number.pop(), symbol.pop(), 0));
						else
							number.push(calculate(number.pop(), symbol.pop(), number.pop()));
					}
					catch (string& e) { throw e; }
				}
				//������ջ
				if (str[i] == ')')
					symbol.pop();
				else
					symbol.push(str[i]);
			}
		}
	}
}

template<typename DataType1, typename DataType2>
void logicalOperate(Stack<DataType1>& number, Stack<DataType2>& symbol, string origin, string str, int begin)
{
	Stack<int> stack;
	if (begin == str.length())
	{
		symbol.clear();number.clear();
		judge(number, symbol, str);
		print(str);
		cout << number.pop() << endl;
	}
	else if (str[begin] >= 'a' && str[begin] <= 'z')
	{
		for (int i = begin + 1;i < str.length(); i++)
			if (str[i] == str[begin])
			{
				stack.push(i);
				str[i] = '0';
			}
		str[begin] = '0';
		logicalOperate(number, symbol, origin, str, begin + 1);
		while (!stack.empty())
			str[stack.pop()] = origin[begin];
		str[begin] = origin[begin];
		for (int i = begin + 1;i < str.length(); i++)
			if (str[i] == str[begin])
			{
				stack.push(i);
				str[i] = '1';
			}
		str[begin] = '1';
		logicalOperate(number, symbol, origin, str, begin + 1);
		while (!stack.empty())
			str[stack.pop()] = origin[begin];
		str[begin] = origin[begin];
	}
	else
		logicalOperate(number, symbol, origin, str, begin + 1);
}

//a��(��p��q)
//��(p��q)��q��p

/*
(2)ץ��������ʽ:
(��t����s)��(��s��r)��(p����r)��(p��q)
p:��͵����̨�����
q:��͵����̨�����
r:����ʱ�䷢������ҹǰ
s:��˵�����滰
t:��ҹʱ����ĵƻ�����
��ȻtӦȡ0������ʽ���Ϊ1ʱ�۲�q��ֵ
*/