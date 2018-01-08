// ExpressionEvaluation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

char compare(char ch, char top);

int main()
{
	/*char s = '9';
	int i = s-48;
	cout << i;*/
	char n = 'y';
	while (n == 'y')
	{
		cout << "输入表达式，以 #号 结尾" << endl;
		stack<char> optr;
		optr.push('#');
		stack<double> opnu;
		int i = 0;
		char ch;
		double op;
		bool flag = false;
		cin >> ch;
		while (optr.top() != '#' || ch != '#')
		{
			if (flag == true)
			{
				flag = false;
				while (!opnu.empty())
					opnu.pop();
				break;
			}
			if (ch >= '0'&&ch <= '9')
			{
				cin.putback(ch);
				cin >> op;
				opnu.push(op);
				cin >> ch;
			}
			else
			{
				switch (compare(ch, optr.top()))
				{
				case '<':
				{
					double a, b, c;
					char c1 = optr.top();
					if (opnu.empty())
					{
						optr.push('#');
						cout << "表达式错误，没有足够的操作数" << endl;
						flag = true;
						break;
					}
					b = opnu.top();
					opnu.pop();
					if (opnu.empty())
					{
						optr.push('#');
						cout << "表达式错误，没有足够的操作数" << endl;
						flag = true;
						break;
					}
					a = opnu.top();
					opnu.pop();
					optr.pop();
					switch (c1)
					{
					case '+':
						c = a + b;
						opnu.push(c);
						break;
					case '-':
						c = a - b;
						opnu.push(c);
						break;
					case '*':
						c = a * b;
						opnu.push(c);
						break;
					case '/':
						if (b == 0)
						{
							cout << "表达式错误，除数不能为0" << endl;
							flag = true;
							break;
						}
						c = a / b;
						opnu.push(c);
						break;
					}

					break;
				}
				case '>':
					optr.push(ch);
					cin >> ch;
					break;
				case '=':
					optr.pop();
					cin >> ch;
					break;
				default:
					optr.push('#');
					cout << "表达式错误，括号不匹配" << endl;
					cin.clear();
					flag = true;
					break;
				}
			}
		}
		if (!opnu.empty())
			cout << "表达式的值为:" << opnu.top() << endl;

		cout << "继续计算输入 y ，输入其他键退出" << endl;
		cin.clear();
		cin >> n;
		while (!optr.empty())
			optr.pop();
		optr.push('#');
	}
	return 0;
}


char compare(char ch, char top)
{
	switch (ch) {
	case '+':
	case '-':
		if (top == '+' || top == '-' || top == '*' || top == '/')
			return '<';  //扫描的小于栈顶  
		else
			return '>';  //扫描的大于栈顶  
		break;
	case '*':
	case '/':
		if (top == '*' || top == '/')
			return '<';
		else
			return '>';
		break;
	case '(':
		if (top == ')') {
			return '0';
		}
		return '>';
		break;
	case ')':
		if (top == '(')
			return '=';
		else if (top == '#') {
			return '0';
		}
		else {
			return '<';
		}
		break;
	case '#':
		return '<';
	default:
		return '0';
	}
}