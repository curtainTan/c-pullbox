#include"shuju.h"



#define FilePath "userInfo.txt"  //玩家数据文件的位置
UseNode *useHead;



int initMap[9][9];
int i,j;
void display();
void display1();
void createNewFile(char *path,char id[12]);							 //创建初始数据文件
UseNode *importData(FILE *fp);						 //导入数据文件中的数据
void SaveData(UseNode *head);						 //保存数据到文件中
int findById(UseNode *head,char id[12]);
UseNode *initData(char id[12]);
void addUse(UseNode *head,char id[12]);                   //增加一个玩家
void displayAll(UseNode *head);                           //显示玩家信息


int data(char id[12],int (*dataMap)[9])
{
	int choice=234;
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			initMap[i][j] = *(*(dataMap+i)+j);
	while(choice)
	{
		system("cls");
		display1();
		scanf("%d",&choice);
		if(choice < 1 || choice > 2){ exit(0);  }
		if(choice == 1)
		{
			system("cls");
			useHead = initData(id);
			displayAll(useHead);
		}
		if(choice == 2)
		{
			system("cls");
			display();
			scanf("%s",id);
			useHead = initData(id);     //初始化系统数据，导入学生信息
			//判断是否为新用户
			choice = findById(useHead,id);
			for(i =0; i < 9; i++)
				for(j = 0; j < 9; j++)
					*(*(dataMap+i)+j)=initMap[i][j]; break;
		}
	}
	return choice;
	
}


//修改数据的函数
void saveData(char id[12],int bar,int (*dataMap)[9])
{
	UseNode *p;
	p = useHead;
	while (p != NULL && strcmp(p->use.id, id) != 0)
		p = p->next;
	p->use.num = bar;
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			p->use.imap[i][j] = *(*(dataMap+i)+j);
	SaveData(useHead);
}




//初始化数据函数
UseNode *initData(char id[12])
{
	FILE *fp;
	if ((fp = fopen(FilePath, "rb")) == NULL)		//如果第一次使用系统时，存储数据的文件不存在，可新建一个数据文件
	{    
		createNewFile(FilePath, id);					//新建一个初始的数据文件
		if ((fp = fopen(FilePath, "rb")) == NULL)   //如果新建的数据文件不成功，退出系统   
		{
			printf("\n无法初始化数据，退出系统！\n");
			exit(1);
		}
	}
	useHead = importData(fp);       //导入文件数据
	fclose(fp);                     //关闭文件
	return useHead;                 //返回存储数据的单链表表头
}
//初始化创用户
void createNewFile(char *path, char id[12])
{
	FILE *fp;
	User use;
	if ((fp = fopen(path, "wb")) == NULL)    //以写的方式打开数据文件
	{
		printf("\n无法建立新文件！\n");
		return;
	}
	strcpy(use.id,id);
	use.num = 0;                            //初始关卡为0
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			use.imap[i][j] = initMap[i][j];
	fwrite(&use,sizeof(User),1,fp)      ;  //写入数据到文件、
	fclose(fp);
}


//导入数据
UseNode *importData(FILE *fp)
{
	UseNode *head=NULL, *p, *q;  //head指向链表头；p指向新节点；q指向链表尾节点
	User use;                       //用来存储学生信息的临时变量
	fread(&use, sizeof(User), 1, fp);  //从数据文件中读取一条记录（一个学生信息）
	while (!feof(fp))                  //如果文件没有结束，继续循环
	{
		if (head == NULL)              //单链表的第一个节点的处理
		{
			head = (UseNode *)malloc(sizeof(UseNode));  //分配节点空间
			head->use = use;           //把从文件中读入的记录，赋给链表第一个节点
			head->next = NULL;         //把节点的后继指针置NULL
			q = head;
		}
		else                           //非第一个节点的处理
		{
			p = (UseNode *)malloc(sizeof(UseNode));
			p->use = use;
			p->next = NULL;
			q->next = p;               //链接新节点到表尾
			q = p;                     //把q指针指向新节点
		}
		 fread(&use, sizeof(User), 1, fp)    ;    //从数据文件中读取下一条记录
	}
	if(head==NULL)  printf("\n链表建立错误\n");
	return head;                       //返回单链表的表头指针
}





int findById(UseNode *head, char id[12])
{
	UseNode *p = head;
	while (p != NULL && strcmp(p->use.id, id) != 0)
		p = p->next;
	if(p==NULL){ addUse(head,id);  return 0;}
			for(i =0; i < 9; i++)
				for(j = 0; j < 9; j++)
					initMap[i][j] = p->use.imap[i][j];
	return p->use.num;
}


//增加新用户
void addUse(UseNode *head,char id[12])
{
	User use;
	UseNode *p = head;
	while (p->next!= NULL) //找到最后一个节点
		p = p->next;
	p->next = (UseNode *)malloc(sizeof(UseNode));
	p = p->next;
	strcpy(use.id,id);
	use.num = 0;
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			use.imap[i][j] = initMap[i][j];
	p->use = use;                        //结构体赋值
	p->next = NULL;
	SaveData(head);
}


//保存数据到文件中
void SaveData(UseNode *head)
{
	UseNode *p = head;
	FILE *fp;
	if ((fp = fopen(FilePath, "wb")) == NULL)       //以写方式打开文件
	{
		printf("\n创建文件错误，无法保存修改！\n");
		return;
	}
	while (  p!=NULL   )
	{
		fwrite(&p->use,   sizeof(User) , 1, fp);//将一条记录写入数据文件
		p=p->next   ;
	}
	fclose(fp); 
}





//显示所有玩家信息
void displayAll(UseNode *head)
{
	UseNode *p = head;
	system("cls");
	if (head == NULL)
	{
		printf("\n没有玩家信息！\n");
		system("pause");
		return;
	}
	printf("\n所有玩家的信息：\n=================\n");
	printf("昵称           关卡\n");
	printf("---------------------------------------\n");
	while (p!= NULL)    //循环输出单链表中的所有数据
	{
		printf("%-15s%-7d\n", p->use.id, p->use.num);
		p = p->next;    //移向下一个节点
	}
	printf("---------------------------------------\n");
	system("pause");
}






//显示界面
void display1()
{
	printf("|___________________________________|\n");
	printf("|欢迎来到推箱子游戏                 |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|    1.显示所有玩家信息             |\n");
	printf("|    2.开始游戏                     |\n");
	printf("|    3.退出游戏                     |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
}









//显示界面
void display()
{
	printf("|___________________________________|\n");
	printf("|欢迎来到推箱子游戏                 |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|            推箱子                 |\n");
	printf("|                                   |\n");
	printf("|            请输入昵称 :           |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
}














