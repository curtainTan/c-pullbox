#include"shuju.h"



#define FilePath "userInfo.txt"  //��������ļ���λ��
UseNode *useHead;



int initMap[9][9];
int i,j;
void display();
void display1();
void createNewFile(char *path,char id[12]);							 //������ʼ�����ļ�
UseNode *importData(FILE *fp);						 //���������ļ��е�����
void SaveData(UseNode *head);						 //�������ݵ��ļ���
int findById(UseNode *head,char id[12]);
UseNode *initData(char id[12]);
void addUse(UseNode *head,char id[12]);                   //����һ�����
void displayAll(UseNode *head);                           //��ʾ�����Ϣ


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
			useHead = initData(id);     //��ʼ��ϵͳ���ݣ�����ѧ����Ϣ
			//�ж��Ƿ�Ϊ���û�
			choice = findById(useHead,id);
			for(i =0; i < 9; i++)
				for(j = 0; j < 9; j++)
					*(*(dataMap+i)+j)=initMap[i][j]; break;
		}
	}
	return choice;
	
}


//�޸����ݵĺ���
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




//��ʼ�����ݺ���
UseNode *initData(char id[12])
{
	FILE *fp;
	if ((fp = fopen(FilePath, "rb")) == NULL)		//�����һ��ʹ��ϵͳʱ���洢���ݵ��ļ������ڣ����½�һ�������ļ�
	{    
		createNewFile(FilePath, id);					//�½�һ����ʼ�������ļ�
		if ((fp = fopen(FilePath, "rb")) == NULL)   //����½��������ļ����ɹ����˳�ϵͳ   
		{
			printf("\n�޷���ʼ�����ݣ��˳�ϵͳ��\n");
			exit(1);
		}
	}
	useHead = importData(fp);       //�����ļ�����
	fclose(fp);                     //�ر��ļ�
	return useHead;                 //���ش洢���ݵĵ������ͷ
}
//��ʼ�����û�
void createNewFile(char *path, char id[12])
{
	FILE *fp;
	User use;
	if ((fp = fopen(path, "wb")) == NULL)    //��д�ķ�ʽ�������ļ�
	{
		printf("\n�޷��������ļ���\n");
		return;
	}
	strcpy(use.id,id);
	use.num = 0;                            //��ʼ�ؿ�Ϊ0
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			use.imap[i][j] = initMap[i][j];
	fwrite(&use,sizeof(User),1,fp)      ;  //д�����ݵ��ļ���
	fclose(fp);
}


//��������
UseNode *importData(FILE *fp)
{
	UseNode *head=NULL, *p, *q;  //headָ������ͷ��pָ���½ڵ㣻qָ������β�ڵ�
	User use;                       //�����洢ѧ����Ϣ����ʱ����
	fread(&use, sizeof(User), 1, fp);  //�������ļ��ж�ȡһ����¼��һ��ѧ����Ϣ��
	while (!feof(fp))                  //����ļ�û�н���������ѭ��
	{
		if (head == NULL)              //������ĵ�һ���ڵ�Ĵ���
		{
			head = (UseNode *)malloc(sizeof(UseNode));  //����ڵ�ռ�
			head->use = use;           //�Ѵ��ļ��ж���ļ�¼�����������һ���ڵ�
			head->next = NULL;         //�ѽڵ�ĺ��ָ����NULL
			q = head;
		}
		else                           //�ǵ�һ���ڵ�Ĵ���
		{
			p = (UseNode *)malloc(sizeof(UseNode));
			p->use = use;
			p->next = NULL;
			q->next = p;               //�����½ڵ㵽��β
			q = p;                     //��qָ��ָ���½ڵ�
		}
		 fread(&use, sizeof(User), 1, fp)    ;    //�������ļ��ж�ȡ��һ����¼
	}
	if(head==NULL)  printf("\n����������\n");
	return head;                       //���ص�����ı�ͷָ��
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


//�������û�
void addUse(UseNode *head,char id[12])
{
	User use;
	UseNode *p = head;
	while (p->next!= NULL) //�ҵ����һ���ڵ�
		p = p->next;
	p->next = (UseNode *)malloc(sizeof(UseNode));
	p = p->next;
	strcpy(use.id,id);
	use.num = 0;
	for(i =0; i < 9; i++)
		for(j = 0; j < 9; j++)
			use.imap[i][j] = initMap[i][j];
	p->use = use;                        //�ṹ�帳ֵ
	p->next = NULL;
	SaveData(head);
}


//�������ݵ��ļ���
void SaveData(UseNode *head)
{
	UseNode *p = head;
	FILE *fp;
	if ((fp = fopen(FilePath, "wb")) == NULL)       //��д��ʽ���ļ�
	{
		printf("\n�����ļ������޷������޸ģ�\n");
		return;
	}
	while (  p!=NULL   )
	{
		fwrite(&p->use,   sizeof(User) , 1, fp);//��һ����¼д�������ļ�
		p=p->next   ;
	}
	fclose(fp); 
}





//��ʾ���������Ϣ
void displayAll(UseNode *head)
{
	UseNode *p = head;
	system("cls");
	if (head == NULL)
	{
		printf("\nû�������Ϣ��\n");
		system("pause");
		return;
	}
	printf("\n������ҵ���Ϣ��\n=================\n");
	printf("�ǳ�           �ؿ�\n");
	printf("---------------------------------------\n");
	while (p!= NULL)    //ѭ������������е���������
	{
		printf("%-15s%-7d\n", p->use.id, p->use.num);
		p = p->next;    //������һ���ڵ�
	}
	printf("---------------------------------------\n");
	system("pause");
}






//��ʾ����
void display1()
{
	printf("|___________________________________|\n");
	printf("|��ӭ������������Ϸ                 |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|    1.��ʾ���������Ϣ             |\n");
	printf("|    2.��ʼ��Ϸ                     |\n");
	printf("|    3.�˳���Ϸ                     |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
}









//��ʾ����
void display()
{
	printf("|___________________________________|\n");
	printf("|��ӭ������������Ϸ                 |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|            ������                 |\n");
	printf("|                                   |\n");
	printf("|            �������ǳ� :           |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
}














