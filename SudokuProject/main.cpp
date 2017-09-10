#include<iostream>
#include<ctime>
#include<fstream>
#include"header.h"
using namespace std;
short sudoku[9][9]{ 0 };
Node *LinkedListTail[9];
short num = 1;
bool *row_flag;//标明行是否有相同数字
bool *column_flag;//标明列是否有相同数字
short *arr2;
short *arr1;
short *numlocation;
int sudoku_count;
ofstream fcout;
int main(int argc, char*argv[])
{
	if (argc<3 || sscanf_s(argv[2], "%d", &sudoku_count) == 0)//用于检测命令行输入的参数是否有错，
	{
		cout << "Input error,please re-input again" << endl;
		return 0;
	}
	srand(time(0));//播种子
	int g = 0;
	bool flag = true;
	fcout.open(".\\sudoku.txt");
	for (; sudoku_count != 0;)
	{
		num = 1;
		BuildLinkedList();
		for (flag = true; num <= 9; num++)
		{
			row_flag = new bool[9]{ false };
			column_flag = new bool[9]{ false };
			numlocation = new short[9];
			g = 0;
			if (PutNum(g) == false)//如果PutNum返回的值是false，则说明该数独棋盘无法继续完成，抛弃并重新生成
			{
				flag = false;
				Clean();
				break;
			}
			delete[]numlocation;
			delete[]column_flag;
			delete[]row_flag;
		}
		if (flag == true)
		{
			arr1[7] = 1;
			arr2[sudoku[0][0] - 1] = 8;
			Permutation(9);//对已经随机生成的数独棋盘进行换数字操作
		}
		delete[]arr1;
		delete[]arr2;
	}
	fcout.close();
}
