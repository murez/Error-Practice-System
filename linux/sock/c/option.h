/**************************************
 *FILE    :main.c
 *PROJECT :eps
 *AUTHOR  :707wk
 *CREATED :5/19/2013
***************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearpri()                  //调整光标
{
    system("busybox clear");
}

void init(int num)     //记录初始化
{
    FILE* fp;
    int n=0;
    char s[2000];
    fp=fopen("data/ec.db","w");
    while(n<num)
    {
        s[n++]='0';
    }
    for(n=0;n<num;n++)
    	fprintf(fp,"%c",s[n]);
    fclose(fp);
}

void initi(char s[],char m[])
{
	char c,sum[2000];
	int n=0,num=0;
	FILE* fp;
	fp=fopen(s,"r");
	while((c=fgetc(fp))!=EOF)if(c=='^')num++;
	fp=fopen(m,"w");
    while(n<num)
    {
        sum[n++]='0';
    }
    for(n=0;n<num;n++)
    	fprintf(fp,"%c",sum[n]);
    fclose(fp);
}

void inie(int num,int sum)   //存储错题
{
    FILE* fp;
    int n=0;
    char s[2000];
    fp=fopen("data/ec.db","r");
    while(n<sum)
    {
        s[n++]=fgetc(fp);
    }
    s[num-1]='1';
    fclose(fp);
    fp=fopen("data/ec.db","w");
    for(n=0;n<sum;n++)
    	fprintf(fp,"%c",s[n]);
    fclose(fp);
}

void iniee(int num,int sum)   //删除做对的题
{
    FILE* fp;
    int n=0;
    char s[2000];
    fp=fopen("data/ec.db","r");
    while(n<sum)
    {
        s[n++]=fgetc(fp);
    }
    s[num-1]='0';
    fclose(fp);
    fp=fopen("data/ec.db","w");
    for(n=0;n<sum;n++)
    	fprintf(fp,"%c",s[n]);
    fclose(fp);
}

int ud(FILE* fp)   //跳题
{
	int s=0,n,num=0;
	char c;
	clearpri();
	printf("请输入题号:");
	while((c=getch())!='\r')
	{
		if(c>='0'&&c<='9')
		{
			num++;
			printf("%c",c);
			s=s*10+c-'0';
		}
		else if(c==127&&num>0)
		{
				s=s/10;
				printf("\b \b");
				num--;
		}
	}
	scanf("%d",&s);
	rewind(fp);
	n=s;
	if(s==1||s==0)return 1;
	while(s>1)
	{
		if((c=fgetc(fp))=='^')s--;
		if( num>5 || (feof(fp) && s>1) )
		{
			clearpri();
			printf("error!数值超出范围\n按任意键返回第一题");
			getch();
			fseek(fp,0,SEEK_SET);
			return 1;
		}
	}
	fgetc(fp);
	fgetc(fp);
	return n;
}

void uud(FILE* fp,int s)   //无显示跳题
{
	char c;
	rewind(fp);
	if(s==1||s==0)return ;
	while(s>1)
	{
		if((c=fgetc(fp))=='^')s--;
		if(c==EOF&&s>1)
		{
			fseek(fp,0,SEEK_SET);
			return ;
		}
	}
	fgetc(fp);
	fgetc(fp);
	return ;
}

int udd()   //统计题量
{
	char c;
	int n=0;
	FILE* fp;
	fp=fopen("data/select.db","r");
	while((c=fgetc(fp))!=EOF)if(c=='^')n++;
	return n;
}

int ude()   //统计错题量
{
	char c;
	int n=0;
	FILE* fp;
	fp=fopen("data/ec.db","r");
	while((c=fgetc(fp))!=EOF)if(c=='1')n++;
	return n;
}

int uddd(FILE* fp)   //计算当前题号
{
    FILE* fp1;
    int num=1,n;
    n=ftell(fp);
    fp1=fopen("data/select.db","r");
    while(ftell(fp1)<=n)
    {
        if(fgetc(fp1)=='^')num++;
    }
    return num;
}

int Option( char rw , int nb , int n )               //存储设置
{
    int nu[2] ;
    FILE* fp ;
    if( ( fp=fopen( "data/option.ini" , "r" ) ) == NULL )
    {
        fclose( fp ) ;
        printf( "\n< 文件错误:设置文件未找到 >\n" ) ;
        exit(0);
    }
    fscanf( fp , "num = %d\n" , &nu[0] ) ;
    fclose( fp ) ;
    switch( rw )
    {
    case 'r':
        switch( n )
        {
        case 0:
            if( nu[0] == 0 )return 1 ;
            else return nu[0] ;
            break ;
        }
        break ;
    case 'w':
        if( ( fp=fopen( "data/option.ini" , "w" ) ) == NULL )
        {
            fclose( fp ) ;
            printf( "\n< 文件错误:设置文件未能创建成功 >\n" ) ;
            exit( 0 ) ;
        }
        switch( n )
        {
        case 0:
            if( nb == 0 )nu[0] =1 ;
            else nu[0] =nb ;
            break ;
        }
        fprintf( fp , "num = %d\n" , nu[0] ) ;
        fclose( fp ) ;
        return 1 ;
    }
    return 0 ;
}

