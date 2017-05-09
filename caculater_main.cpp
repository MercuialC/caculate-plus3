#include <iostream>
#include <ctime>
#include"caculate.h"
using namespace std;


int main(int argc,char **argv)
{
	string infilepath, outfilepath;
	if (argc == 3)//判断主函数参数个数（避免直接打开报错）
	{
		infilepath = argv[1];
		outfilepath = argv[2];
	}
	else cin >> infilepath >> outfilepath;//从命令行中输入路径和输出路径
	srand(time(0));
	InitPriorities();

	Problem p(infilepath, outfilepath);
	p.writeFile("计算结果如有小数请保留2位,只舍不入");//写入文件
	p.writeFile("请输入题目数目\n");
	p.writeFile("------------------------------------------------\n");
	int proNum=p.readFile();//读入文件
	p.writeFile(proNum);
	cout << "计算结果如有小数请保留2位,只舍不入" << endl;
	cout << "请输入题目数目:";
	cout << proNum << endl;
	cout << "------------------------------------------------" << endl;
	
	for (int i = 1; i <= proNum; i++)
	{
		p.generateExpression();//生成运算式
		p.scan();//与用户交互输入数据
	}
	p.print();//将统计结果输出给用户

	return 0;
}

 
