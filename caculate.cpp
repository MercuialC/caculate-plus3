#include<iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include"caculate.h"
using namespace std;

unordered_map< char, unordered_map < char, char > > Priorities;

void InitPriorities()
{
	Priorities['+']['-'] = '>';
	Priorities['+']['+'] = '>';
	Priorities['+']['*'] = '<';
	Priorities['+']['/'] = '<';
	Priorities['+']['('] = '<';
	Priorities['+'][')'] = '>';

	Priorities['-']['-'] = '>';
	Priorities['-']['+'] = '>';
	Priorities['-']['*'] = '<';
	Priorities['-']['/'] = '<';
	Priorities['-']['('] = '<';
	Priorities['-'][')'] = '>';

	Priorities['*']['-'] = '>';
	Priorities['*']['+'] = '>';
	Priorities['*']['*'] = '>';
	Priorities['*']['/'] = '>';
	Priorities['*']['('] = '<';
	Priorities['*'][')'] = '>';

	Priorities['/']['-'] = '>';
	Priorities['/']['+'] = '>';
	Priorities['/']['*'] = '>';
	Priorities['/']['/'] = '>';
	Priorities['/']['('] = '<';
	Priorities['/'][')'] = '>';

	Priorities['(']['+'] = '<';
	Priorities['(']['-'] = '<';
	Priorities['(']['*'] = '<';
	Priorities['(']['/'] = '<';
	Priorities['(']['('] = '<';
	Priorities['('][')'] = '=';
}

Problem::Problem(string infilepath, string outfilepath)
{
	_InFilePath = infilepath;
	_OutFilePath = outfilepath;
	_ifs.open(_InFilePath.c_str(), ios::in);
	_ofs.open(_OutFilePath.c_str(), ios::out);

	init();
	for (int i = 1; i <= 10; i++)
	{
		num.push_back(i);
	}
	sign.push_back('+');
	sign.push_back('-');
	sign.push_back('*');
	sign.push_back('/');
}

void Problem::init()
{
	answer = 0;
	correctNum = 0;
}

void Problem::scan()//该函数用于与用户交互，获取输入数据
{
	float myans;
	cin >> myans;
	writeFile(myans);
	if (myans == answer)
	{
		cout << "正确" << endl << endl;
		writeFile("正确\n\n");
		//myfile << "正确\n\n";
		correctNum++;
	}
	else
	{
		cout << "错误,";
		writeFile("错误,");
		//myfile << "错误,";
		DisPlayAnswer();
		cout << endl;
	}
}

void Problem::DisPlayAnswer()
{
	cout << "答案是:" << answer << endl;
	writeFile("答案是:");
	writeFile(answer);
	writeFile("\n");
	//myfile << "答案是:" << answer << "\n";
}

void Problem::print()//将统计结果输出给用户
{
	cout << "共作对" << correctNum << "题" << endl << endl;
	writeFile("共作对");
	writeFile(correctNum);
	writeFile("题\n\n");
	//myfile << "共作对" << correctNum << "题\n\n";
}

//生成算式部分----------------------------------------------------------------------
int Problem::randomNumber()//用于随机生成数字
{
	return num[rand() % num.size()];
}
char Problem::randomOperation()//用于随机生成运算符
{
	return sign[rand() % sign.size()];
}

template<typename T>//模板
string Problem::Tostring(T i)
{
	stringstream ss;
	string s;
	ss << i;
	ss >> s;
	return s;
}

void Problem::generateExpression()//用于生成运算式
{
	expression = Tostring(randomNumber()) + Tostring(randomOperation()) + Tostring(randomNumber());
	int len = rand() % 5 + 2;
	for (int i = 0; i < len; i++)//add '(' and ')'
	{
		int rdnum = rand() % 10 + 1;
		if (rdnum<2)//10% 加左边 加括号
		{
			expression = Tostring(randomNumber()) + Tostring(randomOperation()) + "(" + Tostring(expression) + ")";
		}
		else if (rdnum>8)//10% 加右边 加括号
		{
			expression = "(" + Tostring(expression) + ")" + Tostring(randomOperation()) + Tostring(randomNumber());
		}
		else if (rdnum<4)//20% 加左边 不加括号
		{
			expression = Tostring(randomNumber()) + Tostring(randomOperation()) + Tostring(expression);
		}
		else if (rdnum>6)//20% 加右边 不加括号
		{
			expression = Tostring(expression) + Tostring(randomOperation()) + Tostring(randomNumber());
		}
		//30% 不加
	}
	cout << expression << " = ";
	writeFile(expression);
	writeFile(" = ");
	//myfile << expression << " = ";
	answer = calculateResult();
}
//----------------------------------------------------------------------------------

//算式计算部分----------------------------------------------------------------------
float Problem::calculateResult()
{
	vector<float> Operands;
	vector<char> Operators;
	float OperandTemp = 0;
	char LastOperator = 0;

	for (int i = 0; i < expression.size(); i++)
	{
		char ch = expression[i];
		if ('0' <= ch && ch <= '9')
		{
			OperandTemp = OperandTemp * 10 + ch - '0';
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		{
			if (ch != '(' && LastOperator != ')')
			{
				Operands.push_back(OperandTemp);
				OperandTemp = 0;
			}
			char Opt2 = ch;
			for (; Operators.size() > 0;)
			{
				char Opt1 = Operators.back();
				char CompareRet = Priorities[Opt1][Opt2];
				if (CompareRet == '>')
				{
					float Operand2 = Operands.back();
					Operands.pop_back();
					float Operand1 = Operands.back();
					Operands.pop_back();
					Operators.pop_back();
					float Ret = caculate(Operand1, Operand2, Opt1);
					Operands.push_back(Ret);
				}
				else if (CompareRet == '<')
				{
					break;
				}
				else if (CompareRet == '=')
				{
					Operators.pop_back();
					break;
				}
			}
			if (Opt2 != ')')
			{
				Operators.push_back(Opt2);
			}
			LastOperator = Opt2;
		}
	}
	if (LastOperator != ')')
	{
		Operands.push_back(OperandTemp);
	}
	for (; Operators.size() > 0;)
	{
		float Operand2 = Operands.back();
		Operands.pop_back();
		float Operand1 = Operands.back();
		Operands.pop_back();
		char Opt = Operators.back();
		Operators.pop_back();
		float Ret = caculate(Operand1, Operand2, Opt);
		Operands.push_back(Ret);
	}
	return (float)((int)(Operands.back() * 100)) / 100;
}

float Problem::caculate(float Operand1, float Operand2, char Operator)
{
	if (Operator == '+') return Operand1 + Operand2;
	if (Operator == '-') return Operand1 - Operand2;
	if (Operator == '*') return Operand1 * Operand2;
	if (Operator == '/') return Operand1 / Operand2;
}
//----------------------------------------------------------------------------------


int Problem::readFile()
{
	int n = 0;
	_ifs >> n;
	return n;
}

template <typename T>
void Problem::writeFile(T t)
{
	_ofs << t;
}
