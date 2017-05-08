#include<vector>
#include<string>
#include<fstream>
using namespace std;

void InitPriorities();

class Problem
{
public:
	Problem(string infilepath, string outfilepath);
	void init();				//初始化
	void scan();				//该函数用于与用户交互，获取输入数据
	void DisPlayAnswer();		//输出正确答案
	void print();				//将统计结果输出给用户

	//生成算式部分----------------------------------------------------------------------
	int randomNumber();			//用于随机生成数字
	char randomOperation();		//用于随机生成运算符
	template<typename T> string Tostring(T i);
	void generateExpression();	//用于生成运算式
	//----------------------------------------------------------------------------------

	//算式计算部分----------------------------------------------------------------------
	float calculateResult();	//计算结果 
	float caculate(float Operand1, float Operand2, char Operator);
	//----------------------------------------------------------------------------------

	//文件读写
	int readFile();
	template <typename T> void writeFile(T t);

private:
	vector<char> sign;
	vector<int> num;
	string expression;
	float answer;
	int correctNum;
	
	string _InFilePath;
	string _OutFilePath;
	ifstream _ifs;
	ofstream _ofs;
};

