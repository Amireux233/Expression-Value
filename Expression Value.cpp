// Expression Value.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "utility.h"
#include "Calculator.h"


int main()
{
	try {
		bool bYes;

		do {
			cout << "��������ʽ��" << endl;
			Calculator <double>::Run();
			cout << "�Ƿ����������ʽ";
			bYes = UserSaysYes();
		} while (bYes);
	}
	catch (Error err) {
		err.Show();
	}

	system("PAUSE");
	return 0;
}

