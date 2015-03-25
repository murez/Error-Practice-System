/**************************************
 *FILE    :main.c
 *PROJECT :eps
 *AUTHOR  :707wk
 *CREATED :5/19/2013
***************************************/
#include "option.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "checkdate.h"

void date(int year,int mon,int day)  //统计天数
{
    int sum=0;
    int num=year;
    if((mon==6&&day>6)||(mon>6))num=year+1;
    for(;!(year==num&&mon==6);sum=sum+Dayinmonth(mon,year),mon++)if(mon>12){mon=1;year++;}
    printf("                                 |>距%4d年高考还有%3d天<|\r",num,sum+6-day);
}

void opt(int sum)      //正常练习
{
	FILE* fp;
	int n=1;
	char ans,c,tmp;
	clearpri();
	fp=fopen("data/select.db","r");
	n=Option('r',1,0);
	uud(fp,n);
	c=fgetc(fp);
	while(c!=EOF)
	{
		clearpri();
		printf("正常练习：【当前为第%d题】\n",n);
		Option('w',n,0);
		while(c!='^')
		{
			putchar(c);
			c=fgetc(fp);
		}
		c=fgetc(fp);
		printf("请输入答案: ");
		while((tmp=getch())=='\r');
		while(tmp!='\r')
		{
			if( (tmp>='a' && tmp<='z') || (tmp>='A' && tmp<='Z') )
			{
					ans=tmp;
					printf("\b%c",ans);
					break;
			}
			tmp=getch();
		}
		if(ans=='q')return ;
		if(ans=='u')
		{
			n=ud(fp);
			c='\b';
			ans='\b';
			continue;
		}
		if(ans==c||ans==c+32)
		{
			printf("\n答案正确!\n");
			c=fgetc(fp);
			c=fgetc(fp);
			continue;
		}
		else
		{
			printf("\n答案错误,正确答案是:%c\n",c);
			inie(n,sum);
		}
		n++;
		while(getch()!=c+32);
		c=fgetc(fp);
		c=fgetc(fp);
		if(c==EOF)
		{
			c=fgetc(fp);
			clearpri();
			printf("题目已做完,按任意键返回主菜单");
			getch();
			return ;
		}
		clearpri();
	}
	fclose(fp);
}

void opte(int sum)    //错题练习
{
	FILE* fp;
	FILE* fp1;
	char ans,c,tmp;
	int n=0,num=1;
	clearpri();
	fp=fopen("data/ec.db","r");
	fp1=fopen("data/select.db","r");
	c=fgetc(fp);
	clearpri();
	while(c!=EOF)
	{
		n++;
		if(c=='1')
		{
			clearpri();
			printf("错题练习：【当前为第%d题】\n",num++);
			uud(fp1,n);
			c=fgetc(fp1);
			while(c!='^')
			{
				putchar(c);
				c=fgetc(fp1);
			}
			c=fgetc(fp1);
			printf("请输入答案: ");

			tmp=getch();
			while(tmp=='\r')tmp=getch();
			while(tmp!='\r')
			{
				if( (tmp>='a'&&tmp<='z') || (tmp>='A'&&tmp<='Z') )
				{
					ans=tmp;
					printf("\b%c",ans);
				}
				tmp=getch();
			}
			if(ans=='q')return ;
			if(ans==c||ans==c+32)
			{
				printf("\n答案正确!\n");
				iniee(n,sum);
			}
			else
			{
				printf("\n答案错误,正确答案是:%c\n",c);
			}
			while(getch()!='\r');
			fgetc(fp1);
			c=fgetc(fp);
		}
		else {c=fgetc(fp);continue;}
		if(c==EOF)
		{
			clearpri();
			break;
		}
		clearpri();
	}
	printf("题目已做完,按任意键返回主菜单！");
	fclose(fp);
	getch();
}

void optt(int n)     //清空错题
{
	char c,tmp;
	clearpri();
	printf("是否清空错题？ y/n  ");
	while((tmp=getch())=='\r');
	while(tmp!='\r')
	{
		if(tmp=='y'||tmp=='Y'||tmp=='n'||tmp=='N')
		{
			c=tmp;
			printf("\b%c",c);
		}
		tmp=getch();
	}
	if(c=='y'||c=='Y')
	{
		init(n);
		clearpri();
		printf("错题已清空！按任意键返回主菜单\n");
		getch();
	}
}

void abo()  //说明函数
{
	clearpri();
	printf("          说    明:\n");
	printf("输入 q:退出    u:跳题\n导入错题:步骤：将错题文件用本程序打开即可导入错题\n\n          GT-soft studio\n    主页:http://gtsoft.cwsurf.de/\n\n按任意键返回主菜单");
	getch();
}

int eps(int argc,char *argv[])    //主函数
{
	int n;
	time_t rawtime;
    	struct tm* timeinfo;
	char tmp,c;
	n=udd();
	for(;;)
	{
		clearpri();
		time(&rawtime);
        	timeinfo=localtime(&rawtime);
        	date(1900+timeinfo->tm_year,1+timeinfo->tm_mon,timeinfo->tm_mday);
		printf("                选项：\n a:正常练习 (共有%d道题)\n b:错题练习 (共有%d道错题)\n c:清空错题\n d:帮    助\n q:退    出\n   选择： ",n,ude());
		tmp=getch();
		while(tmp=='\r')tmp=getch();
		while(tmp!='\r')
		{
			if(tmp>='a'&&tmp<='z')
			{
				c=tmp;
				printf("%c\b",tmp);
				clearpri();
				break;
			}
			tmp=getch();
		}
		switch(c)
		{
			case 'a':opt(n);break;
			case 'b':opte(n);break;
			case 'c':optt(n);break;
			case 'd':abo();break;
			case 'q':exit(0);
		}
		clearpri();
	}
	return 0;
}
