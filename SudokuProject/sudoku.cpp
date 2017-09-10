#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;
struct Node
{
	short row;
	short column;
	Node *next;
};
void BuildLinkedList();
bool GetRandomValue(short g);
bool PutNum(short g);
void ShowSudoku();
void Permutation(short length);
void Clean();
short sudoku[9][9]{ 0 };
Node *Grid[9];
short blocks[9];
Node *LinkedListTail[9];
short num = 1;
bool *row_flag;//标明行是否有相同数字
bool *column_flag;//标明列是否有相同数字
short *arr2;
short *arr1;
short *numlocation;
int sudoku_count;
bool stop_flag = true;
ofstream fcout;
int main(int argc,char* argv[])
{
	if (argc<3||sscanf_s(argv[2], "%d", &sudoku_count) == 0)//用于检测命令行输入的参数是否有错，
	{
		cout << "Input error,please re-input again" << endl;
		return 0;
	}
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
void BuildLinkedList()//每个九宫格建一个含有9个节点的链表，共建立9个链表
{
	int i, j;
	Node *p1, *p2;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			p2 = new Node;
			p2->row = 3 * (i / 3) + j / 3;
			p2->column = 3 * (i % 3) + j % 3;
			if (j == 0)
			{
				p1 = p2;
				Grid[i] = p2;
			}
			else
				p1->next = p2;
			p1 = p2;
		}
		p2->next = NULL;
		LinkedListTail[i] = p2;
		blocks[i] = 9;
	}
	arr1 = new short[9]{ 0 };
	arr2 = new short[9];
}
bool PutNum(short g)//在每个九宫格中放入相应的数字num
{
	for (;;)
	{
		if (GetRandomValue(g) == true)
		{
			if (g == 8)return true;
			else if (PutNum(g + 1) == false)//如果PutNum(g+1)返回false,则说明第g+1个宫无法放置数字，则在第g个宫尝试可以放置的其他位置，已经尝试过的位置结点则放置到链表后面
			{
				Node *p = new Node;
				p->row = 3 * (g / 3) + numlocation[g] / 3;
				p->column = 3 * (g % 3) + numlocation[g] % 3;
				p->next = NULL;
				LinkedListTail[g]->next = p;
				LinkedListTail[g] = p;
				sudoku[p->row][p->column] = 0;
				row_flag[p->row] = false;
				column_flag[p->column] = false;
				continue;
			}
			else
			{
				blocks[g] = 9 - num;
				return true;
			}
		}
		else
		{
			blocks[g] = 10 - num;
			return false;
		}

	}
}
bool GetRandomValue(short g)//在第g个九宫格中随机选取可用的位置来放入数字
{
	if (blocks[g] == 0)return false;
	int value;
	value = clock() % blocks[g];//因为srand(time(0))中的时间种子精度不够，因此我采用毫秒级的clock()来生成随机数
	int i;
	Node *p1, *p2;
	for (i = 0, p2 = Grid[g], p1 = p2; i < 2 * blocks[g] - 1; i++)//p2即为可放置数字的位置坐标
	{
		if (i >= value&&row_flag[p2->row] == false && column_flag[p2->column] == false)break;
		if (i == blocks[g] - 1)p2 = Grid[g], p1 = p2;
		else
		{
			p1 = p2;
			p2 = p2->next;
		}
	}
	if (i == 2 * blocks[g] - 1)return false;
	sudoku[p2->row][p2->column] = num;//接下来的代码是对被选中的目标位置结点进行删除前的准备操作
	numlocation[g] = 3 * (p2->row % 3) + (p2->column % 3);
	row_flag[p2->row] = true;
	column_flag[p2->column] = true;
	if (p2 == Grid[g])Grid[g] = p2->next;
	if (p2 == LinkedListTail[g])LinkedListTail[g] = p1, p1->next = NULL;
	if (p2 != Grid[g] && p2 != LinkedListTail[g])p1->next = p2->next;
	delete p2;
	blocks[g] = blocks[g] - 1;
	return true;
}
void ShowSudoku()//将数独棋盘输出到文本文件中
{

	int row, column;
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 8; column++)
		{
			fcout << arr2[sudoku[row][column] - 1] << " ";//将随机生成的数独棋盘映射到arr2数组中
		}
		fcout << arr2[sudoku[row][column] - 1] << endl;
	}
	if (--sudoku_count == 0)stop_flag = false;
	else
		fcout << endl;
}
void Clean()//主要用来清理的函数，防止内存泄漏
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (Grid[i]->next != NULL)delete Grid[i]->next;
		delete Grid[i];
		Grid[i] = NULL;
	}
	delete[]numlocation;
	delete[]column_flag;
	delete[]row_flag;
}
void Permutation(short length)//用递归的方法在arr2数组中生成全排列
{
	int i;
	if (length == 10 - sudoku[0][0])
	{
		if (length != 1)Permutation(length - 1);
		else
			ShowSudoku();
		return;
	}
	for (i = 0; i<9 && stop_flag; i++)
	{
		if (arr1[i] == 0)
		{
			arr1[i] = 1;
			arr2[9 - length] = i + 1;
			if (length != 1)Permutation(length - 1);
			else
				ShowSudoku();
			arr1[i] = 0;
		}
	}
}