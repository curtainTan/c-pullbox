#include"stdio.h"
#include "malloc.h" 
#include "string.h" 
#include "stdlib.h" 
#include "conio.h"  

typedef struct Use
{
	char id[12];		
	int num;         //�ؿ�	
	int imap[9][9];
}User;
//�洢�����Ϣ������ڵ�����
typedef struct Node
{
	User use;           //�����Ϣ��
	struct Node *next;  //����ĺ��ָ��
}UseNode;


int data(char id[12],int (*dataMap)[9]);
void saveData(char id[12],int bar,int (*dataMap)[9]);	//���������Ϣ��Ϣ




