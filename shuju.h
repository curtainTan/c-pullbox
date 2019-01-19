#include"stdio.h"
#include "malloc.h" 
#include "string.h" 
#include "stdlib.h" 
#include "conio.h"  

typedef struct Use
{
	char id[12];		
	int num;         //关卡	
	int imap[9][9];
}User;
//存储玩家信息单链表节点类型
typedef struct Node
{
	User use;           //玩家信息域
	struct Node *next;  //链表的后继指针
}UseNode;


int data(char id[12],int (*dataMap)[9]);
void saveData(char id[12],int bar,int (*dataMap)[9]);	//保存玩家信息信息




