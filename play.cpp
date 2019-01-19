#include"play.h"
#include"conio.h"

IMAGE   wall, people, blank, end, box, darkbox;//IMAGE为图片类型



void DrawMap(int bar);//绘制地图
int PlayGame(int bar, int *flag, int over);//游戏过程
void botton(int bar, char id[12]);


int map[9][9];
int allMap[7][9][9] = { 
		{
		{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 3, 1, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 1, 0, 0, 0 },
		{ 1, 3, 0, 4, 4, 1, 1, 1, 1 },
		{ 1, 1, 1, 5, 0, 4, 0, 3, 1 },
		{ 0, 0, 1, 4, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 3, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0 }
		},

		{
		{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 5, 0, 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 4, 4, 1, 0, 1, 1, 1 },
		{ 1, 0, 4, 0, 1, 0, 1, 3, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 3, 1 },
		{ 0, 1, 1, 0, 0, 0, 0, 3, 1 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 1, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 0, 0 }
		},

		{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 5, 0, 0, 0, 1 },
		{ 1, 0, 0, 4, 0, 4, 0, 0, 1 },
		{ 1, 1, 1, 7, 3, 7, 1, 1, 1 },
		{ 1, 0, 0, 7, 3, 7, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 }
		},

		{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 3, 0, 4, 0, 1, 0, 1 },
		{ 1, 3, 3, 4, 0, 4, 0, 5, 1 },
		{ 1, 3, 3, 0, 4, 0, 4, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }//第四关
		},

		{
		{ 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 5, 1, 0, 0, 0 },
		{ 1, 0, 4, 4, 1, 1, 1, 1, 0 },
		{ 1, 0, 4, 0, 3, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 3, 1, 0, 1, 0 },
		{ 1, 3, 0, 0, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }//第五关
		},


		{
		{ 0, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 5, 0, 0, 0, 1, 1, 0 },
		{ 0, 1, 1, 4, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 0, 3, 0, 0, 1, 0 },
		{ 1, 0, 4, 0, 1, 4, 1, 1, 0 },
		{ 1, 0, 0, 3, 0, 3, 1, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }//第六关
		},

		{
		{ 0, 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 1, 1, 1, 0, 1, 1, 1, 1, 0 },
		{ 1, 0, 0, 4, 0, 3, 0, 1, 0 },
		{ 1, 0, 4, 5, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 1, 1, 3, 0, 1, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 0 }//第七关
		}
	
//0代表空地
//1代表墙
//3代表目的地
//4代表箱子		 
//5代表人
//7代表箱子在目的地(4+3)
//8代表人在目的地(3+5)

};



int num(int bar)
{
	switch(bar)
	{
	case 0: return 4;
	case 1: return 3;
	case 2: return 6;
	case 3: return 5;
	case 4: return 3;
	case 5: return 3;
	case 6: return 2;
	default: return 3;
	}
};



//主程序
int play( int bar, int *flag, char id[12], int(*tanMap)[9])
{
	int over,m,n;
	initgraph(450, 620); //打开窗口
	//加载图片
		loadimage(&wall, "./image/wall.jpg", 50, 50);//保存路径 图片大小
		loadimage(&people, "./image/people.jpg", 50, 50);
		loadimage(&blank,"./image/blank.jpg",50,50); 
	    loadimage(&end, "./image/end.jpg", 50, 50);
	    loadimage(&box, "./image/box.jpg", 50, 50);
	    loadimage(&darkbox, "./image/darkbox.jpg", 50, 50);
	//替换地图，
	for( m = 0; m < 9; m++ )
		for( n = 0; n < 9; n++ )
			map[m][n] = *(*(tanMap+m)+n);
	//找出结束的判断
	over = num(bar);

	while (1)
		{
			DrawMap(bar);
			botton(bar, id);
			bar = PlayGame(bar,flag, over);
			//     标记大于0，表示通过本关
			if(*flag==1) { Sleep(2000); closegraph(); break;}
			if(*flag==2) { 
				for( m = 0; m < 9; m++ )
					for( n = 0; n < 9; n++ )
						 *(*(tanMap+m)+n) = map[m][n]; closegraph(); break;
			}
			if(*flag== 3){
				for( m = 0; m < 9; m++ )
					for( n = 0; n < 9; n++ )
						*(*(tanMap+m)+n) = allMap[bar][m][n]; closegraph(); break;
			}
		}
	return bar;
}



//游戏下方的信息框
void botton(int bar, char id[12])
{
	TCHAR s[5];
	_stprintf(s,_T("%d"),bar+1);
	outtextxy(20, 460, "昵称：");
	outtextxy(80, 460, id);
	outtextxy(20, 480, "关卡：");
	outtextxy(80, 480, s);

	outtextxy(170, 460, "操作方式：");
	outtextxy(190, 480, "↑ ：向上移动");
	outtextxy(190, 500, "↓ ：向下移动");
	outtextxy(190, 520, "← ：向左移动");
	outtextxy(190, 540, "→ ：向右移动");
	outtextxy(190, 560, "r ：重玩本关");
	outtextxy(190, 580, "k ：保存进度");
	outtextxy(190, 600, "t ：退出游戏");
}






void DrawMap(int bar)//绘制地图
{
	//遍历二维数组
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(i * 50, j * 50, &blank);//输出图片
				break;
			case 1:
				putimage(i * 50, j * 50, &wall);
				break;
			case 3:
				putimage(i * 50, j * 50, &end);
				break;
			case 4:
				putimage(i * 50, j * 50, &box);
				break;
			case 5:
				putimage(i * 50, j * 50, &people);
				break;
			case 7:
				putimage(i * 50, j * 50, &darkbox);
				break;
			case 8:
				putimage(i * 50, j * 50, &people);
				break;
			}
		}
		printf("\n");
	}
}

//玩游戏过程
int PlayGame(int bar,int *flag, int over)
{
	/*
	    通过按键去改变二维数组的元素------控制人和箱子的移动
	    游戏规则:
		          需要去改变的情况有:
	                  1.人的前面是空地
	                  2.人的前面是目的地
	                  3.人的前面是箱子(不一定,需要判断箱子前面是什么)
	                     3.1 箱子的前面是空地
	                     3.2 箱子的前面是目的地
	*********************************************************/

	char move;  //接收键盘
	//要改变的是人周围的元素
	     //人的位置，标志为5 人和8 人在目的地
	int r, c, i, j, tan = 0; //人的行和列
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
			{
				r = i;
				c = j;
			}
		}
	}
	//map[r][c]为人的位置

	move = getch(); 
	switch (move)
	{
	case '↑': //上
	case 72:  //键值 72 80 75 77
		//1.人的前面是空地 2.人的前面是目的地
		if (map[r][c - 1] == 0 || map[r][c - 1] == 3)
		{
			map[r][c - 1] += 5;
			map[r][c] -= 5;
		}
		//3.人的前面是箱子.(不一定)3.1 箱子的前面是空地.3.2 箱子的前面是目的地.
		else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)  //人的前面是箱子
		{
			if (map[r][c - 2] == 0 || map[r][c - 2] == 3)  //箱子的前面是空地或者目的地
			{
				map[r][c - 2] += 4;
				map[r][c - 1] += 1;
				map[r][c] -= 5;
			}
		}

		
		break;
	case '↓'://下
	case 80:
		//1.人的前面是空地 2.人的前面是目的地
		if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
		{
			map[r][c + 1] += 5;
			map[r][c] -= 5;
		}
		//3.人的前面是箱子 3.1 箱子的前面是空地 3.2 箱子的前面是目的地
		else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)  //人的前面是箱子
		{
		 	 if (map[r][c + 2] == 0 || map[r][c + 2] == 3)  //箱子的前面是空地或者目的地
			{
				map[r][c + 2] += 4;
				map[r][c + 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;

	case '←'://左
	case 75:
		//1.人的前面是空地 2.人的前面是目的地
		if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
		{
			map[r - 1][c] += 5;
			map[r][c] -= 5;
		}
		//3.人的前面是箱子 3.1 箱子的前面是空地 3.2 箱子的前面是目的地
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)  //人的前面是箱子
		{
			 if (map[r - 2][c] == 0 || map[r - 2][c] == 3)  //箱子的前面是空地或者目的地
			{
				map[r - 2][c] += 4;
				map[r - 1][c] += 1;
				map[r][c] -= 5;
			}
		}
		break;

	case '→'://右
	case 77:
		//1.人的前面是空地 2.人的前面是目的地
		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)
		{
			map[r + 1][c] += 5;
			map[r][c] -= 5;
		}
		//3.人的前面是箱子 3.1 箱子的前面是空地  箱子的前面是目的地
		else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)  //人的前面是箱子
		{
			 if (map[r + 2][c] == 0 || map[r + 2][c] == 3)  //箱子的前面是空地或者目的地
			{
				map[r + 2][c] += 4;
				map[r + 1][c] += 1;
				map[r][c] -= 5;
			}
		}
		break;


	case 'r':           //重新玩本关
		*flag = 1; break;
	case 'k':
		*flag = 2; break;
	case 't':           //退出游戏
		system("cls"); exit(0);
	}


	//           计算到达目的地的箱子
	for(i=0; i< 9; i++)
	{
		for(j=0; j< 9; j++)
			if(map[i][j]==7) tan++;
	}
	//  判断是否全部入库   如果是，关卡加一， 标记变成一
	if(tan == over)
	{	
		*flag = 3; 
		++bar;
		if(bar >= 7)  bar = 0;
	}
	return bar; 
}