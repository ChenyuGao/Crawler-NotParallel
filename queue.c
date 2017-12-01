#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "common.h"

//存储节点的队列
Queue* que_init()
{
	Queue* q;
	if ((q = malloc(sizeof(Queue))) == NULL)
		return NULL;
	memset(q, 0, sizeof(Queue));
	q->head = 0;
	q->tail = 0;
	return q;
}
//队列判空
int empty(Queue* q)
{
	if (q->head == q->tail)
		return 1;
	return 0;
}

//入队，成功返回1，否则返回0
int enqueue(Queue* q, char* node)
{
	if ((q->head - q->tail + maxq) % maxq == 1)
		return 0;
	else
	{
		q->queue[q->tail] = node;
		q->tail = (q->tail + 1) % maxq;
		return 1;
	}
}
//出队，返回出队节点或NULL（队空）
char* dequeue(Queue* q)
{
	if (q->head == q->tail)
		return NULL;
	else
	{
		int head = q->head;
		q->head = (head + 1) % maxq;
		return q->queue[head];
	}
}

