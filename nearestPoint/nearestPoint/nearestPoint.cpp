#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <cmath>

using namespace std;

#define NUM 3
#define DIV 100

/********************************************************
�㷨˼·��
* �����ṹ
* ��ʼ���㼯P
* ��x�����P��������X����
* ��y�����P��������Y����
* �ݹ�Ѱ��������
* ��ӡ���
*********************************************************/



/********************************************************
* �����ṹ
*********************************************************/
typedef struct 
{
	int index;
	float x;
	float y;
} point;

/********************************************************
* ���������ṹ
*********************************************************/
typedef struct 
{
	point pl;
	point pr;
	float dis;
} nearestpair;


/********************************************************
* ��ӡ�㼯
*********************************************************/
void printPoint(point *p){
	for (int i = 0; i < NUM; i++)
	{
		printf("[%.2f, %.2f] ", p[i].x, p[i].y);
	}
	printf("\n");
}

/********************************************************
* ��x������п��ŵıȽϺ���
*********************************************************/
bool compareX(point a, point b){
        return b.x>a.x;
}

/********************************************************
* ��y������п��ŵıȽϺ���
*********************************************************/
bool compareY(point a, point b){
        return b.y>a.y;
}

/********************************************************
* ��ʼ������ֵ
*********************************************************/
void initAll(point *x, point *y){
	float tempX, tempY;
	srand((int)time(0));
	for (int i = 0; i < NUM; i++)
	{
		tempX = rand()%DIV;
		tempY = rand()%DIV;
		tempX += tempX/100;
		tempY += tempY/100;
		x[i].index = i;
		x[i].x = tempX;
		x[i].y = tempY;
		y[i].index = i;
		y[i].x = tempX;
		y[i].y = tempY;
	}
}

/********************************************************
* ���������ľ���
*********************************************************/
float dist(point x, point y){
	float distx, disty;
	distx = abs(x.x - y.x);
	disty = abs(x.y - y.y);
	return sqrt(distx*distx + disty*disty);
}

/********************************************************
* �ݹ�Ѱ�������
*********************************************************/
nearestpair findNearestPair(point *x, point *y, int low, int high){
	nearestpair pair, pairLeft, pairRight;
	int middle, i, j, k;
	float dis, dis1, dis2, dis3;
	pair.dis = 100;
	if (high-low == 1)				//�����ֻ�������㣬ֱ�ӱȽϷ���
	{
		dis = dist(x[low], x[high]);
		pair.pl = x[low];
		pair.pr = x[high];
		pair.dis = dis;
	}
	if(high-low ==2)				//�����㣬�ȽϷ���
	{
		dis1 = dist(x[low], x[low+1]);
		dis2 = dist(x[low], x[high]);
		dis3 = dist(x[low+1], x[high]);
		dis = min(dis1, dis2);
		dis = min(dis3, dis);
		if(dis == dis1)
		{
			pair.pl = x[low];
			pair.pr = x[low+1];
		}
		if(dis == dis2)
		{
			pair.pl = x[low];
			pair.pr = x[high];
		}
		if(dis == dis3)
		{
			pair.pl = x[low+1];
			pair.pr = x[high];
		}
		pair.dis = dis;
	}

	if(high-low > 2)				//����������
	{
		middle = (high-low)/2;
		point *yl = (point *)malloc((middle+1)*sizeof(point));
		point *yr = (point *)malloc((middle)*sizeof(point));
		middle += low;
		j = k = 0;

		for (i = 0; i <= high-low; i++) //��������y����
		{
			if (y[i].index <= middle)
			{
				yl[j++] = y[i];
			}
			else
			{
				yr[k++] = y[i];
			}
		}


		pairLeft = findNearestPair(x, yl, low, middle);		//�����Ҿ����е�Сֵ
		pairRight = findNearestPair(x, yr, middle+1, high);


		if (pairLeft.dis < pairRight.dis)
		{
			pair = pairLeft;
		}
		else
		{
			pair = pairRight;
		}

		k = 0;											//����y'����
		point *yi = (point *)malloc((high-low+1)*sizeof(point));
		for (i = 0; i <= high-low; i++)
		{
			dis = abs(x[middle].x - y[i].x);
			if (dis < pair.dis)
			{
				yi[k++] = y[i];
			}
		}

		for (i = 0; i < k; i++)			//���м�������С���
		{
			for (j= i+1; j<k && j<(i+5); j++)
			{
				dis = dist(yi[i], yi[j]);
				if (dis < pair.dis)
				{
					pair.pl = yi[i];
					pair.pr = yi[j];
					pair.dis = dis;
				}
			}
		}

	}
	return pair;
}

/********************************************************
* ����������ʼ��x��y�㼯������x��y�����Ѱ�������Բ����
*********************************************************/
int main(){
	point x[NUM], y[NUM];
	nearestpair pair;
	initAll(x, y);
	sort(x, x+NUM, compareX);
	sort(y, y+NUM, compareY);
	printPoint(x);

	pair = findNearestPair(x, y, 0, NUM-1);
	printf("���ҵ�����С���Ϊ��[%.2f, %.2f]��[%.2f, %.2f]\n", pair.pl.x, pair.pl.y, pair.pr.x, pair.pr.y);
	printf("��С����Ϊ%.2f", pair.dis);

	getchar();
	return 1;
}