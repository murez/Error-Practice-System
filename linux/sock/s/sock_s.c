/*******
socket server example
*******/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVPORT 1707		/*服务器监听端口号 */
#define BACKLOG 1024		/* 最大同时连接请求数 */
#define MAXDATASIZE 1024	/*每次最大数据传输量 */

#define BUFLEN 255   

struct user_data {
	int name;
	int passwd;
	int active;
	struct user_data *next;
};

void clearpri()			//清屏
{
	system("busybox clear");
}

void work_place(char *place)
{
	char *p;
	char *str;
	p = str = (char *)malloc(sizeof(char) * (strlen(place)));
	strcpy(str, place);
	for (; *p; p++) ;
	for (; *p != '/'; p--) ;
	p++;
	*p = '\0';
	chdir(str);
}

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

/*
int user_num()
{
	FILE *fpin;
	int sum;
	int temp[2];
	if((fpin=fopen("data/user.db","r"))==NULL)
	{
		printf("未找到数据库文件！\n");
		exit(0);
	}
	for(sum=0;!feof(fpin);sum++)
	{
		fscanf(fpin,"%d %d\n",&temp[0],&temp[1]);
	}
	fclose(fpon);
	return sum;
}
*/

struct user_data *read_user_data()
{
	FILE *fpin;
	struct user_data *head;
	struct user_data *p;
	struct user_data *q;
	if ((fpin = fopen("data/user.db", "r")) == NULL) {
		printf("not find the user data！\n");
		exit(0);
	}
	printf("loading user data\n");
	q=head = p = (struct user_data *)malloc(sizeof(struct user_data));
	fscanf(fpin, "%d %d %d\n", &p->name,&p->passwd, &p->active);
	p->next = NULL;
	for (; !feof(fpin);) {
		q = p;
		p = (struct user_data *)malloc(sizeof(struct user_data));
		fscanf(fpin, "%d %d %d\n", &p->name,&p->passwd, &p->active);
		q->next = p;
	}
	printf("Finished loading\n");
	return head;
}

int find(struct user_data *head, int username,int userpasswd)
{
	while (head != NULL) {
		if (head->name == username&&head->passwd==userpasswd) {
			return head->active;
		}
		head = head->next;
	}
	return -1;
}

void put_data(struct user_data *head)
{
	while (head != NULL) {
		printf("%d %d %d\n", head->name,head->passwd, head->active);
		head = head->next;
	}
}

int main(int argc, char *argv[])
{
	char str[MAXDATASIZE];
	struct user_data *head;
	int temp;
	int tempusername;
	int tempuserpasswd;
	int sin_size;
	int sockfd, client_fd;	/*sockfd:监听socket;client_fd:数据传输socket */
	struct sockaddr_in my_addr;	/* 本机地址信息 */
	struct sockaddr_in remote_addr;	/* 客户端地址信息 */

	time_t t ;   
	char tmpBuf[BUFLEN];
	
	clearpri();
	work_place(argv[0]);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket set up error !\n");
		exit(1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERVPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind error !\n");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen error !\n");
		exit(1);
	}
	head = read_user_data();
	put_data(head);
	printf("startover monitoring service\n");
	while (1) {
		sin_size = sizeof(struct sockaddr_in);
		if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, (socklen_t *)&sin_size)) == -1) {
			perror("accept error \n");
			continue;
		}
		t= time( 0 );
		strftime(tmpBuf, BUFLEN, "[%Y/%m/%d %H:%M:%S]", localtime(&t)); 
		printf("%s Client %s insert\n",tmpBuf,
		       (char *)inet_ntoa(remote_addr.sin_addr));
		if ((temp = recv(client_fd, str, MAXDATASIZE, 0)) == -1) {
			perror("recv error !\n");
			exit(1);
		}
		sscanf(str,"%d %d",&tempusername,&tempuserpasswd);
		str[temp] = 0;
		sprintf(str,"%d",find(head,tempusername,tempuserpasswd));
		if (send(client_fd, str, MAXDATASIZE, 0) == -1)
			perror("send error !\n");
		close(client_fd);
	}
	return 0;
}
