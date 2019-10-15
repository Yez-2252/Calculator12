
#include <iostream>
#include <ctime>
#include <fstream>
#include<stack>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
using namespace std;
int question_num;//���û���������������
char option[5] = { '+', '-', '*', '/' };//������������ŷ���option��
int arr[4];//һ���������������������
char op[3];//һ������Ĳ������������
double calculate1(string str4);
void dayin(int op_cnt, ofstream &��������);
bool Judge(int op_cnt);
bool calculate(int num1, char op_1, int num2);
void CreateQuestion(int question_num, ofstream &��������)//����question_num����������
{
	for (int i = 0; i < question_num; )
	{
		int op_cnt = rand() % 2 + 2;//��rand��ѡ��2-3�����ţ�op_cnt�����Ÿ���
		for (int j = 0; j < op_cnt; j++)
		{
			arr[j] = rand() % 100;//��0-99�����ѡ��һ��������arr[j]��
			int temp = rand() % 4;//��0-3��ȡ��һ������Ϊoption���±꣬��һ��ʵ���˻�������˴�����
			op[j] = option[temp];//option[temp]��ķ��Ŵ����op[j]��
		}
		arr[op_cnt] = rand() % 100;//���һ��������Ϊ������ʼ�ձ��ַ�����һ����
		if (Judge(op_cnt) == true)//�ж�������ʽ�Ƿ����㰢����Ҫ��
		{
			dayin(op_cnt, ��������);
			i++;
		}
	}
}
bool Judge(int op_cnt)
{
	for (int i = 0; i < op_cnt; ++i)
	{
		bool judge = calculate(arr[i], op[i], arr[i + 1]);
		if (judge == false)
			return false;
	}
	return true;
}
bool calculate(int num1, char op_1, int num2)//�жϵ������ʽ�Ƿ�����Ҫ��
{
	int ans;
	switch (op_1)
	{
	case '+':
		ans = num1 + num2;
		break;
	case '-':
		ans = num1 - num2;
		if (ans < 0)
			return false;
		break;
	case '*':
		ans = num1 * num2;
		break;
	case '/':
		if (num2 == 0 || num1 % num2 != 0)//�жϷ�ĸ��Ϊ�㲢�����Ƿ��Ƿ���
			return false;
		break;
	default:
		cout << "��������" << endl;
	}
	return true;
}string change(int num0)//�����ʽת��Ϊ�ַ�������
{
	char str[100];
	_itoa_s(num0, str, 10);
	string str1 = str;
	return str1;
}


int judge1(char c1, char c2)//����+.-.*./.(.)�����ȵȼ�
{
	int a1, a2;
	if ('+' == c1 || '-' == c1) a1 = 3;
	if ('*' == c1 || '/' == c1)a1 = 5;
	if ('(' == c1) a1 = 1;
	if (')' == c1) a1 = 7;
	if ('#' == c1) a1 = 0;
	if ('+' == c2 || '-' == c2)a2 = 2;
	if ('*' == c2 || '/' == c2)a2 = 4;
	if ('(' == c2) a2 = 6;
	if (')' == c2) a2 = 1;
	if ('#' == c2) a2 = 0;
	if (a1 > a2) return 1;
	if (a1 == a2) return 0;
	if (a1 < a2) return -1;
}

double run1(char c, double d1, double d2)//������������
{
	switch (c)
	{
	case '+':
		return d1 + d2;
		break;
	case '-':
		return d1 - d2;
		break;
	case'*':
		return d1 * d2;
		break;
	case '/':
		return d1 / d2;
		break;
	default:
		return 0.0;
		break;
	}
}
double calculate1(string str4)//������ʽ��ֵ
{
	char  op1[6] = { "+-*/#" };
	//�����ʽ�ַ���str���'#'������ʶ��
	str4.append(1, '#');
	stack<char> OPTR;//�����ջ
	stack<double> OPND;//������ջ
	int a = -1;
	//�Ƚ�#������ջ
	OPTR.push('#');
	while (true)
	{
		int b = a + 1;
		a = str4.find_first_of(op1, a + 1);
		if (a == string::npos) break;
		if (a != b)
		{
			string ss(str4, b, a - b);
			double d = atof(ss.c_str());
			//��������ջ
			OPND.push(d);
		}
		//��������ȼ��Ƚ�
		int ju = judge1(OPTR.top(), str4[a]);
		if (-1 == ju)//ջ�����ȼ���ֱ����ջ
		{
			OPTR.push(str4[a]);
		}
		if (0 == ju)//ջ�������ȼ�������ջ
		{
			OPTR.pop();
		}
		if (1 == ju)//ջ�����ȼ���,��ջ��������
		{
			double d1 = OPND.top();
			OPND.pop();
			double d2 = OPND.top();
			OPND.pop();
			d1 = run1(OPTR.top(), d2, d1);
			
			OPND.push(d1);
			OPTR.pop();
			a--;
		}
	}
	
	str4.erase(str4.length() - 1, 1);
	return  OPND.top();
}
void dayin(int op_cnt, ofstream &��������)
{
	string str1;
	for (int i = 0; i < op_cnt; i++)
	{
		cout << arr[i];
		cout << op[i];
		�������� << arr[i];
		�������� << op[i];
	}
	if (op_cnt == 2)
	{
		str1 = change(arr[0]) + op[0] + change(arr[1]) + op[1] + change(arr[2]);
	}
	else
	{
		str1 = change(arr[0]) + op[0] + change(arr[1]) + op[1] + change(arr[2]) + op[2] + change(arr[3]);
	}
	cout << arr[op_cnt] << "=" << endl;
	�������� << arr[op_cnt] << "=" << calculate1(str1) << endl;
}
int main()
{
	srand((unsigned int)time(NULL));
	ofstream ��������;
	��������.open("��������.txt");
	cout << "����Ҫ������Ŀ�ĸ���Ϊ";
	cin >> question_num;
	CreateQuestion(question_num, ��������);
	return 0;
}