#include <iostream>
#define MaxInputLen 30
using namespace std;

void procE();
void procT();
void procF();
void procNUM();
void error();

char *str;//用于存储输入字符串
int ptr;//读头

int main()
{
	str = new char[MaxInputLen];
	cin >> str;
	ptr = 0;
	procE();
	if (str[ptr] != '\0') {
		error();
	}
	else {
		cout << "分析完成！" << endl;
	}
	system("pause");
}

void procE()
{
	procT();
	cout << "产生式:E->T" << endl;
	if (str[ptr] == '+') {
		++ptr;
		procE();
		cout << "产生式:E->E+T" << endl;
	}
	else if (str[ptr] == '-') {
		++ptr;
		procE();
		cout << "产生式:E->E-T" << endl;
	}
}

void procT()
{
	procF();
	cout << "产生式:T->F" << endl;
	if (str[ptr] == '*') {
		++ptr;
		procT();
		cout << "产生式:T->T*F" << endl;
	}
	else if (str[ptr] == '/') {
		++ptr;
		procT();
		cout << "产生式:T->T/F" << endl;
	}
}

void procF()
{
	if (str[ptr] == '(') {
		++ptr;
		procE();
		if (str[ptr] == ')') {
			++ptr;
			cout << "产生式:F->(E)" << endl;
			return;
		}
	}

	else if (str[ptr] >= '0'&&str[ptr] <= '9')
	{
		procNUM();
		cout << "产生式:F->num"<<endl;
		return;
	}
	else
		error();
		
}

void procNUM()
{
	int m = 0;
	while (str[ptr] >= '0'&&str[ptr] <= '9') {
		m = m * 10 + str[ptr] - '0';
		++ptr;
	}
	cout << "产生式:num->" << m << endl;
}

void error()
{
	cout << "算术表达式不属于本文法" << endl;
}
