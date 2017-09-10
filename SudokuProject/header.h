#ifndef HEADER_H_
#define HEADER_H_
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
#endif
