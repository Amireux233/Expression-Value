#include "Calculator.h"
template<class ElemType>
bool Calculator<ElemType>::IsOperator(char ch)
{
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')')
		return true;
	else return false;
}
template<class ElemType>
int Calculator<ElemType>::LeftPri(char op)
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
int Calculator<ElemType>::RightPri(char op)
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
void Calculator<ElemType>::Get2Operands(LinkStack<ElemType>&opnd, ElemType&a1, ElemType&a2)
{
	if (opnd.Pop(a2) == UNDER_FLOW)throw Error("����ʽ�쳣��");
	if (opnd.Pop(a1) == UNDER_FLOW)throw Error("����ʽ�쳣��");
}
template<class ElemType>
void Calculator<ElemType>::DoOperator(LinkStack<ElemType>&opnd, const ElemType&a1, char op, const ElemType&a2)
{
	switch (op)
	{
	case'+':
		opnd.Push(a1 + a2);
		break;
	case'-':
		opnd.Push(a1 - a2);
		break;
	case'*':
		opnd.Push(a1*a2);
		break;
	case'/':
		if (a2 == 0)throw Error("����Ϊ0��");
		opnd.Push(a1 / a2);
		break;
	}
}
template<class ElemType>
void Calculator<ElemType>::PostfixExpression(ofstream&outFile)
//������������������������׺����ʽת��Ϊ��׺����ʽ���ٴ���������ļ�outFile��
{
	LinkStack<char>optr;     //������ջ 
	char ch, optrTop, op;    //������ַ���������ջ��ջ����������������op
	ElemType operand;        //������
	optr.Push('=');
	optr.Top(optrTop);       //ȡ��������ջջ��
	ch = GetChar();          //��������cin�������ո����Ʊ���ȡ��һ���ַ�
	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{	//chΪ���ֻ���ʱ�Ĳ���
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
void Calculator<ElemType>::PostfixExpressionValue(ifstream&inFile)
//����������������ļ�inFile�������׺����ʽ�������׺����ʽ��ֵ
{
	LinkStack<ElemType>opnd;             //������ջ
	char ch;                             //��ǰ�ַ�
	double operand;                      //������

	while (inFile >> ch, ch != '=')
	{
		if (IsOperator(ch))
		{
			ElemType a1, a2;
			Get2Operands(opnd, a1, a2);
			DoOperator(opnd, a1, ch, a2); // ��a1��op��a2���������opndջ
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
void Calculator<ElemType>::Run()
//�����������Ӽ����������׺����ʽֵ֮
{
	ofstream outFile("temp");  //����������ļ�
	PostfixExpression(outFile);
	//���Ӽ������������׺����ʽת��Ϊ��׺����ʽ���������������ļ��У��ԡ�=������
	outFile.close();               //�ر�������ļ�

	ifstream inFile("temp");   //�����������ļ�
	PostfixExpressionValue(inFile);
	//������������ļ�������ĺ�׺����ʽ�����������Ļ����ʾ����
	inFile.close();                //�ر�������ļ� 

	remove("temp");            //ɾ����ʱ�ļ�temp
}