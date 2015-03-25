/**************************************
 *FILE    :main.c
 *PROJECT :eps
 *AUTHOR  :707wk
 *CREATED :5/19/2013
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "getch.h"
#include "main.h"

#define SERVPORT 1777
#define MAXDATASIZE 1024 /*每次最大数据传输量 */

int ELFHash(char str[])		//字符串hash转换 
{
	int hash = 0;
	int x = 0;
	int i;
	for (i = 0; i < strlen(str); i++) {
		hash = (hash << 4) + str[i];
		if ((x = (int)(hash & 0xF0000000L)) != 0) {
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
	return (hash & 0x7FFFFFFF);
}

void logo_user_password(char* password)
{
	char* p;
	printf("密码:");
	for(p=password;(*p=getch())!=13;)
	{
		if(*p==127)
		{
			if(p>password)
			{
				*p--='\0';
				printf("\b \b");
			}
		}
		else if(p-password<100)
		{
			printf("*");
			p++;
		}
	}
	*p='\0';
}

int check_socket()
{
	int sockfd;
	int recvbytes;
	char buf[MAXDATASIZE];
	char host_name[1000]="wangk";
	char user_name[100];
	char password[100];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	clearpri();
	printf("请输入服务器名:");
	scanf("%s",host_name);
_TRY_AGAIN:
	printf("用户名:");//printf("%d %d\n",ELFHash("wangk"),ELFHash("123"));
	scanf("%s",user_name);
	getchar();
	logo_user_password(password);
	sprintf(buf,"%d %d",ELFHash(user_name),ELFHash(password));
	if((host=gethostbyname(host_name))==NULL)
	{
		herror("\n服务器连接失败，错误代码：0001!\n");
		exit(1);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\n服务器连接失败，错误代码：0002!\n");
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero( &(serv_addr.sin_zero),8);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("\n服务器连接失败，错误代码：0003!\n");
		exit(1);
	}
	if (send(sockfd, buf, MAXDATASIZE, 0) == -1)
	{
		perror( "\n服务器连接失败，错误代码：0004!\n");
		exit(1);
	}
	if ((recvbytes=recv(sockfd, buf, MAXDATASIZE, 0)) ==-1)
	{
		perror("\n服务器连接失败，错误代码：0005!\n");
		exit(1);
	}
	buf[recvbytes] = '\0';
	clearpri();
	switch(atoi(buf))
	{
		case -1:
		printf("用户名或密码错误!\n");
		close(sockfd);
		goto _TRY_AGAIN;
		break;
		case 0:
		printf("账户未激活!\n");
		close(sockfd);
		return 1;
		break;
		case 1:
		printf("登录成功!\n");
		break;
	}
	close(sockfd);
	return 0;
}

void work_place(char *place)
{
	char* p;
	char* str;
	p=str=(char *)malloc(sizeof(char)*(strlen(place)));
	strcpy(str,place);
	for(;*p;p++);
	for(;*p!='/';p--);
	p++;
	*p='\0';
	chdir(str);
}

int main(int argc,char *argv[])
{
	//if(0)
	if(check_socket())
	{
		return 1;
	}
	work_place(argv[0]);
	eps(argc,argv);
	return 0;
}
