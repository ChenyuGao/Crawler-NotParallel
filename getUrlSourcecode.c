#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> // for close()
#include "common.h"

#define buf 1024

// 获取页面源码，返回状态码
int getUrlSourcecode(char *url, char *arg)
{
	char myurl[BUFSIZ];
	char *pHost = 0, *pGET = 0;
	char host[BUFSIZ], GET[BUFSIZ];
	char header[BUFSIZ] = "";
	static char text[buf];
	int i;
	memset(sourceCode, 0, BUF);

	/*
	* 分离url中的主机地址和相对路径
	*/
	char *server = arg;   // 10.108.86.80   127.0.0.1
	strcpy(myurl, server);
	strcat(myurl, url);
	for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost);
	if ((int)(pHost - myurl) == strlen(myurl))
		strcpy(GET, "/");
	else
		strcpy(GET, pHost);
	*pHost = '\0';
	strcpy(host, myurl);
	/*
	* 设定socket参数,并未真正初始化
	*/
    int sockfd;
    if ( -1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)) )   // 穿件套接字
    {
        printf("sockfd open error!\n");
        return 0;
    }

    struct sockaddr_in addr;
	int sock_len = sizeof(struct sockaddr);
	bzero(&addr, sock_len);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(server); // 按照网络字节顺序存储IP地址
	addr.sin_port = htons(80);
	/*
	* 组织发送到web服务器的信息
	* 为何要发送下面的信息请参考HTTP协议的约定
	*/
	strcat(header, "GET ");
	strcat(header, GET);
	strcat(header, " HTTP/1.1\r\n");
	strcat(header, "HOST: ");
	strcat(header, host);
	strcat(header, "\r\nConnection: Close\r\n\r\n");
	/*
	* 连接到服务器，发送请求header，并接受反馈（即网页源代码）
	*/
	int conct;
	if (conct = connect(sockfd, (struct sockaddr *)(&addr), sock_len))
    {
        printf("connect fail! try again...\n");
        return 0;
    }

	send(sockfd, header, strlen(header), 0);
	while (recv(sockfd, text, buf - 1, 0) > 0)     // text定义为static并且buf-1，源码里才没有奇怪的东西
	{
		strcat(sourceCode, text);
		memset(text, '\0', buf);
	}
	close(sockfd);
	// 输出状态码
	char *s = sourceCode;
	s += 9;
	char d[3];
	memcpy(d, s, 3);
	return atoi(d);
}
