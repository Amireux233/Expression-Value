#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "LinkStack.h"
template<class ElemType>
class Calculator {
private:
	static bool IsOperator(char ch);
	static int LeftPri(char op);
	static int RightPri(char op);
	static void Get2Operands(LinkStack<ElemType>&opnd, ElemType &a1, ElemType &a2);
	static void DoOperator(LinkStack<ElemType>&opnd, const ElemType &a1, char op, const ElemType &a2);
	static void TransExpression(ofstream &outFile);
	static void ExpressionValue(ifstream &inFile);
public:
	Calculator() {};
	virtual ~Calculator() {};
	static void Run();
};
template<class ElemType>
bool Calculator<ElemType>::IsOperator(char ch) //�ж��Ƿ�Ϊ�����
{
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')')
		return true;
	else return false;
}
template<class ElemType>
int Calculator<ElemType>::LeftPri(char op) //����������ʱ�����ȼ�
{
	int result;
	if (op == '=')result = 0;
	else if (op == '(')result = 1;
	else if (op == '*' || op == '/')result = 5;
	else if (op == '+' || op == '-')result = 3;
	else if (op == ')')result = 6;
	return result;
}
template<class ElemType>
int Calculator<ElemType>::RightPri(char op)//��������Ҳ�ʱ�����ȼ�
{
	int result;
	if (op == '=')result = 0;
	else if (op == '(')result = 6;
	else if (op == '*' || op == '/')result = 4;
	else if (op == '+' || op == '-')result = 2;
	else if (op == ')')result = 1;
	return result;
}
template<class ElemType>
void Calculator<ElemType>::Get2Operands(LinkStack<ElemType>&opnd, ElemType&left, ElemType&right)//�Ӳ�����ջ���˳�����������
{
	if (opnd.Pop(right) == UNDER_FLOW)throw Error("���ʽ�쳣��");
	if (opnd.Pop(left) == UNDER_FLOW)throw Error("���ʽ�쳣��");
}
template<class ElemType>
void Calculator<ElemType>::DoOperator(LinkStack<ElemType>&opnd, const ElemType&left, char op, const ElemType&right)//ִ������(left)op(right)
{
	switch (op)
	{
	case'+':
		opnd.Push(left + right);
		break;
	case'-':
		opnd.Push(left - right);
		break;
	case'*':
		opnd.Push(left * right);
		break;
	case'/':
		if (right == 0)throw Error("����Ϊ0��");
		opnd.Push(left / right);
		break;
	}
}
template<class ElemType>
void Calculator<ElemType>::TransExpression(ofstream&outFile)//���������������׺���ʽת��Ϊ��׺���ʽ���ٴ���������ļ�outFile��
{
	LinkStack<char>optr;     
	char ch, optrTop, op;    
	ElemType operand;        
	optr.Push('=');
	optr.Top(optrTop);       
	ch = GetChar();          
	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{	
			cin.putback(ch);
			cin >> operand;
			outFile << operand << " ";
			ch = GetChar();
		}
		else if (!IsOperator(ch))
		{
			throw Error("�Ƿ��ַ���");
		}
		else
		{

			if (LeftPri(optrTop)<RightPri(ch))
			{

				optr.Push(ch);
				ch = GetChar();

			}
			else if (LeftPri(optrTop)>RightPri(ch))
			{

				optr.Pop(op);
				outFile << op << " ";
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{
				optr.Pop(ch);          //��optrջ�˳�ջ����'('
				ch = GetChar();
			}
		}
		optr.Top(optrTop);    // ȡ��������ջջ��     
	}
	outFile << '=';           //������ļ�outFile��'='����
}
template<class ElemType>
void Calculator<ElemType>::ExpressionValue(ifstream&inFile)//�������ļ�inFile�������׺���ʽ�������׺���ʽ��ֵ
{
	LinkStack<ElemType>opnd;            
	char ch;                            
	double operand;                      

	while (inFile >> ch, ch != '=')
	{
		if (IsOperator(ch))
		{
			ElemType left, right;
			Get2Operands(opnd, left, right);
			DoOperator(opnd, left , ch, right); 
		}
		else
		{
			inFile.putback(ch);
			inFile >> operand;
			opnd.Push(operand);
		}
	}
	opnd.Top(operand);
	cout << operand << endl;
}
template<class ElemType>
void Calculator<ElemType>::Run()//��Ӽ����������׺���ʽֵ֮
{
	ofstream outFile("temp.txt");  
	TransExpression(outFile);
	outFile.close();              

	ifstream inFile("temp.txt");  
	ExpressionValue(inFile);
	inFile.close();                

	remove("temp.txt");            
}

#endif // !__CALCULATOR_H_


