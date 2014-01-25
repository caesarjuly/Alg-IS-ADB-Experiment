#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10001
char x[NUM], y[NUM], b[NUM][NUM];
int c[NUM][NUM];

/********************************************************
* 随机生成字符序列，随机数为奇数则生成a-z，偶数则生成A-Z
*********************************************************/
void generateXY(){
	int temp1, temp2;
	srand((int)time(0));
	y[0] = x[0] = ' ';		//将y和x的第一个字符均设为空，从第二个字符开始匹配，这样c、b与x、y行数列数大小即可
	for (int i = 1; i < NUM; i++)
	{
		temp1 = rand();
		temp2 = rand();
		x[i] = temp1%2==0? (65+(temp1%26)) : (97+(temp1%26));
		y[i] = temp2%2==0? (65+(temp2%26)) : (97+(temp2%26));
	}
}

/********************************************************
* 打印序列
*********************************************************/
void printXY(){
	puts(x);
	puts(y);
}

/********************************************************
* 动归求最长公共子序列
*********************************************************/
void LCS_Length(){
	int m, n, i, j;
	m = n = NUM;
	for (i = 1;	i < m; i++)
	{
		c[i][0] = 0;
	}
	for (j = 0; j < n; j++)
	{
		c[0][j] = 0;
	}

	for (i = 1; i < m; i++)				//从x、y的第二个字符开始匹配
	{
		for (j = 1; j < n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = '\\';
			}
			else if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i][j] = '|';
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i][j] = '-';
			}
		}
	}
}

/********************************************************
* 打印最长公共子序列
*********************************************************/
void print_LCS(int i, int j){
	int length = c[NUM-1][NUM-1];
	char result[NUM];			//存储公共子序列
	while (i*j != 0)
	{
		if (b[i][j] == '\\')
		{
			result[length-1] = x[i];
			i--;
			j--;
			length--;
		}
		else if (b[i][j] == '|')
		{
			i--;
		}
		else
		{
			j--;
		}
	}
	result[c[NUM-1][NUM-1]] = '\0';
	puts(result);
	printf("\n长度为：%d\n", c[NUM-1][NUM-1]);
}

/********************************************************
* 主函数，初始化x、y序列，并计时
*********************************************************/
int main(){
	clock_t  startTime, endTime;
	generateXY();
	startTime = clock();
	LCS_Length();
	endTime = clock();
	printf("运行时间为：%ldms\n", endTime-startTime);
	//printXY();
	printf("最长公共子序列为：\n");
	print_LCS(NUM-1, NUM-1);
	getchar();
}