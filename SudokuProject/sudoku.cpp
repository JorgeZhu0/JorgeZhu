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
bool *row_flag;//�������Ƿ�����ͬ����
bool *column_flag;//�������Ƿ�����ͬ����
short *arr2;
short *arr1;
short *numlocation;
int sudoku_count;
bool stop_flag = true;
ofstream fcout;
int main(int argc,char* argv[])
{
	if (argc<3||sscanf_s(argv[2], "%d", &sudoku_count) == 0)//���ڼ������������Ĳ����Ƿ��д�
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
void BuildLinkedList()//ÿ���Ź���һ������9���ڵ������������9������
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
bool PutNum(short g)//��ÿ���Ź����з�����Ӧ������num
{
	for (;;)
	{
		if (GetRandomValue(g) == true)
		{
			if (g == 8)return true;
			else if (PutNum(g + 1) == false)//���PutNum(g+1)����false,��˵����g+1�����޷��������֣����ڵ�g�������Կ��Է��õ�����λ�ã��Ѿ����Թ���λ�ý������õ��������
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
bool GetRandomValue(short g)//�ڵ�g���Ź��������ѡȡ���õ�λ������������
{
	if (blocks[g] == 0)return false;
	int value;
	value = clock() % blocks[g];//��Ϊsrand(time(0))�е�ʱ�����Ӿ��Ȳ���������Ҳ��ú��뼶��clock()�����������
	int i;
	Node *p1, *p2;
	for (i = 0, p2 = Grid[g], p1 = p2; i < 2 * blocks[g] - 1; i++)//p2��Ϊ�ɷ������ֵ�λ������
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
	sudoku[p2->row][p2->column] = num;//�������Ĵ����ǶԱ�ѡ�е�Ŀ��λ�ý�����ɾ��ǰ��׼������
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
void ShowSudoku()//����������������ı��ļ���
{

	int row, column;
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 8; column++)
		{
			fcout << arr2[sudoku[row][column] - 1] << " ";//��������ɵ���������ӳ�䵽arr2������
		}
		fcout << arr2[sudoku[row][column] - 1] << endl;
	}
	if (--sudoku_count == 0)stop_flag = false;
	else
		fcout << endl;
}
void Clean()//��Ҫ��������ĺ�������ֹ�ڴ�й©
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
void Permutation(short length)//�õݹ�ķ�����arr2����������ȫ����
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