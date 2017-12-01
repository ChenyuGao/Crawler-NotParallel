#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include "common.h"
#include "bloomfilter.h"

int main(int argc,char *argv[])
{
	Queue *q = que_init();

	// 将首页地址入队
	char* indexUrl = "/";
	enqueue(q, indexUrl);

	// 构建布隆过滤器
	BF bf = bf_create(VECTORSIZE);
	bf_add(bf, indexUrl);

	char *tempUrl;
	int num;    // DFA函数返回的链接的数量
	int id = 0;
	int n = 0;  // 不重复还能访问的链接的数量
	int m = 0;  // 不重复但是无法访问的链接数量
/*
	if ((resulturl = fopen("url.txt", "wb")) == NULL)
	{
		printf("file result.txt open failed!\n");
		return -1;
	}
*/
	clock_t start, finish;
    start = clock();

    //argv[1] = "10.108.86.80";
	while (!empty(q))
	{
		tempUrl = dequeue(q);
		if (getUrlSourcecode(tempUrl, argv[1]) == 200)    // 有些链接符合抽取条件但是不在服务器内所以需要判断
		{
		    //printf("\n%s\n", tempUrl);

			URLs[n] = tempUrl;
			DFA(sourceCode, q, bf);

			//id++;
			n++;
			printf("n%d\n", n);
			//resultNum++;
		}
		else
		{
			//printf("\n%s\n", tempUrl->urlName);
			m++;
			printf("m%d\n", m);
			free(tempUrl);
		}

	}

	finish = clock();  //终止计时
	double Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", Total_time);

	printf("不重复还能访问的链接的数量： %d\n不重复但是无法访问的链接数量： %d\n\n", n, m);
	//printf("链接关系的数量： %d\n", resultNum);
	//fclose(resulturl);

	return 0;
}


