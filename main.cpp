#include"shuju.h"
#include"play.h"
int ssinitMap[9][9] ={
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 3, 1, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 1, 0, 0, 0 },
	{ 1, 3, 0, 4, 4, 1, 1, 1, 1 },
	{ 1, 1, 1, 5, 0, 4, 0, 3, 1 },
	{ 0, 0, 1, 4, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 1, 3, 1, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 0, 0, 0 }
};

void replay(int bar);
void pass(int bar);

void main()
{
	char id[12]={'0'};
	int bar=0,flag = 0;//���Ϊ1��ʾͨ���ؿ�   //��¼�ؿ�
	bar = data(id, ssinitMap);					
	while(1)
	{
		bar = play(bar, &flag, id, ssinitMap);//ͨ�غ����¿�ʼ
		if(flag == 1) {system("cls"); pass(bar); getch(); flag =0;}
		if(flag == 2) {saveData(id,bar,ssinitMap); system("cls"); pass(bar); getch(); flag =0;}
		if(flag == 3) {saveData(id,bar,ssinitMap); system("cls"); pass(bar); getch(); flag =0;}
	}
}

void pass(int bar)//���ؽ���
{
	int i;
	printf("___________________________________\n");
	for(i = 0; i <7; i++ )
	{
		printf("|                                  |\n");
	}
	printf("|    ��ϲ����!                     |\n");
	printf("|    ��enter������:                |\n");
	printf("|    ��һ��:��%d��                  |",bar+1);
	for(i = 0; i <7; i++ )
	{
		printf("\n|                                  |");
	}
	printf("\n|__________________________________|\n");
}









