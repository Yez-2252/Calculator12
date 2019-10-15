
#include <iostream>
#include <ctime>
#include <fstream>
#include<stack>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
using namespace std;
int question_num;//从用户端输入的问题个数
char option[5] = { '+', '-', '*', '/' };//将四则运算符号放在option里
int arr[4];//一个存放四则运算数字数组
char op[3];//一个存放四册运算符号数组
double calculate1(string str4);
void dayin(int op_cnt, ofstream &四则运算);
bool Judge(int op_cnt);
bool calculate(int num1, char op_1, int num2);
void CreateQuestion(int question_num, ofstream &四则运算)//创造question_num个四则运算
{
	for (int i = 0; i < question_num; )
	{
		int op_cnt = rand() % 2 + 2;//从rand中选出2-3个符号，op_cnt即符号个数
		for (int j = 0; j < op_cnt; j++)
		{
			arr[j] = rand() % 100;//从0-99中随机选出一个数放在arr[j]里
			int temp = rand() % 4;//从0-3中取出一个数作为option的下标，这一步实现了化简减少了代码量
			op[j] = option[temp];//option[temp]里的符号存放在op[j]里
		}
		arr[op_cnt] = rand() % 100;//最后一个数（因为数字数始终比字符数大一个）
		if (Judge(op_cnt) == true)//判断这个表达式是否满足阿超的要求
		{
			dayin(op_cnt, 四则运算);
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
bool calculate(int num1, char op_1, int num2)//判断单个表达式是否满足要求
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
		if (num2 == 0 || num1 % num2 != 0)//判断分母不为零并计算是否是分数
			return false;
		break;
	default:
		cout << "发生错误" << endl;
	}
	return true;
}string change(int num0)//将表达式转换为字符串类型
{
	char str[100];
	_itoa_s(num0, str, 10);
	string str1 = str;
	return str1;
}


int judge1(char c1, char c2)//设置+.-.*./.(.)的优先等级
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

double run1(char c, double d1, double d2)//计算四则运算
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
double calculate1(string str4)//计算表达式的值
{
	char  op1[6] = { "+-*/#" };
	//给表达式字符串str添加'#'结束标识符
	str4.append(1, '#');
	stack<char> OPTR;//运算符栈
	stack<double> OPND;//操作数栈
	int a = -1;
	//先将#符号入栈
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
			//数据先入栈
			OPND.push(d);
		}
		//运算符优先级比较
		int ju = judge1(OPTR.top(), str4[a]);
		if (-1 == ju)//栈外优先级大直接入栈
		{
			OPTR.push(str4[a]);
		}
		if (0 == ju)//栈内外优先级相等则出栈
		{
			OPTR.pop();
		}
		if (1 == ju)//栈内优先级大,出栈进行运算
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
void dayin(int op_cnt, ofstream &四则运算)
{
	string str1;
	for (int i = 0; i < op_cnt; i++)
	{
		cout << arr[i];
		cout << op[i];
		四则运算 << arr[i];
		四则运算 << op[i];
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
	四则运算 << arr[op_cnt] << "=" << calculate1(str1) << endl;
}
int main()
{
	srand((unsigned int)time(NULL));
	ofstream 四则运算;
	四则运算.open("四则运算.txt");
	cout << "你需要产生题目的个数为";
	cin >> question_num;
	CreateQuestion(question_num, 四则运算);
	return 0;
}