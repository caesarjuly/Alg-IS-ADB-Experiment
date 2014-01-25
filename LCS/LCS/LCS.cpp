#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10001
char x[NUM], y[NUM], b[NUM][NUM];
int c[NUM][NUM];

/********************************************************
* ��������ַ����У������Ϊ����������a-z��ż��������A-Z
*********************************************************/
void generateXY(){
	int temp1, temp2;
	srand((int)time(0));
	y[0] = x[0] = ' ';		//��y��x�ĵ�һ���ַ�����Ϊ�գ��ӵڶ����ַ���ʼƥ�䣬����c��b��x��y����������С����
	for (int i = 1; i < NUM; i++)
	{
		temp1 = rand();
		temp2 = rand();
		x[i] = temp1%2==0? (65+(temp1%26)) : (97+(temp1%26));
		y[i] = temp2%2==0? (65+(temp2%26)) : (97+(temp2%26));
	}
}

/********************************************************
* ��ӡ����
*********************************************************/
void printXY(){
	puts(x);
	puts(y);
}

/********************************************************
* �����������������
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

	for (i = 1; i < m; i++)				//��x��y�ĵڶ����ַ���ʼƥ��
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
* ��ӡ�����������
*********************************************************/
void print_LCS(int i, int j){
	int length = c[NUM-1][NUM-1];
	char result[NUM];			//�洢����������
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
	printf("\n����Ϊ��%d\n", c[NUM-1][NUM-1]);
}

/********************************************************
* ����������ʼ��x��y���У�����ʱ
*********************************************************/
int main(){
	clock_t  startTime, endTime;
	generateXY();
	startTime = clock();
	LCS_Length();
	endTime = clock();
	printf("����ʱ��Ϊ��%ldms\n", endTime-startTime);
	//printXY();
	printf("�����������Ϊ��\n");
	print_LCS(NUM-1, NUM-1);
	getchar();
}