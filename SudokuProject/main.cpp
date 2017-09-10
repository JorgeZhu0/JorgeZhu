#include<iostream>
#include<ctime>
#include<fstream>
#include"header.h"
using namespace std;
short sudoku[9][9]{ 0 };
Node *LinkedListTail[9];
short num = 1;
bool *row_flag;//�������Ƿ�����ͬ����
bool *column_flag;//�������Ƿ�����ͬ����
short *arr2;
short *arr1;
short *numlocation;
int sudoku_count;
ofstream fcout;
int main(int argc, char*argv[])
{
	if (argc<3 || sscanf_s(argv[2], "%d", &sudoku_count) == 0)//���ڼ������������Ĳ����Ƿ��д�
	{
		cout << "Input error,please re-input again" << endl;
		return 0;
	}
	srand(time(0));//������
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
			if (PutNum(g) == false)//���PutNum���ص�ֵ��false����˵�������������޷�������ɣ���������������
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
			Permutation(9);//���Ѿ�������ɵ��������̽��л����ֲ���
		}
		delete[]arr1;
		delete[]arr2;
	}
	fcout.close();
}
