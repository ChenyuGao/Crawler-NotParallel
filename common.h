#include <stdio.h>
#include "bloomfilter.h"

#define BUF 1000000  // 源码最大长度
char sourceCode[BUF];

FILE *resulturl;
int resultNum;

#define maxq 500000   // 队列最大长度
#define maxu 300000   // 存储的不重复链接最大数量

/*
typedef struct
{
	char urlName[100];
	int id;

}URL, *urlPtr;
*/

char* URLs[maxu];   // 存储所有不重复的链接节点

//***********队列结构***********
typedef struct
{
	char* queue[maxq];
	int head, tail;
} Queue;
//队列初始化
Queue* que_init();
//入队，成功返回1，否则返回0
int enqueue(Queue* q, char* node);
//出队操作
char* dequeue(Queue* q);
//判空操作
int empty(Queue* q);

//***********我的函数**************************
// 获取页面源码，返回状态码
int getUrlSourcecode(char *url, char *arg);
// 从该源码中提取的符合条件的链接全部入栈q
int DFA(char* souceCode, Queue *q, BF bf);
