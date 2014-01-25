#include <iostream>
#include <time.h>
using namespace std;
#define NUM 20
/********************************************************
* ����һЩȫ�ֱ�����������ѷ��䣬��ǰ���䣬���񻨷�ʱ�䣬�����ʱ�䣬ÿ������������ʱ��
*********************************************************/
int bestArrange[NUM];
int arrange[NUM];
int cost[NUM];
int best;
int runtime[10];

/********************************************************
* ��ʼ����������ʱ��
*********************************************************/
void initCost()
{
	srand((int)time(0));
	for (int i = 0; i < NUM; i++)
	{
		cost[i] = rand()%100;
	}	
}

/********************************************************
* ��ʼ����������������ʱ��
*********************************************************/
void initRuntime(int k)
{
	for (int i = 0; i < k; i++)
	{
		runtime[k] = 0;
	}
}

/********************************************************
* ��ȡ��ǰ��������ʱ��
*********************************************************/
int getTotalCost(int k)
{
	int totalCost=0;
	for (int i = 0; i < k; i++)
	{
		if (totalCost<runtime[i])
		{
			totalCost = runtime[i];
		}
	}
	return totalCost;
}

/********************************************************
* ���ݷ���������ѷ�������ʱ��
*********************************************************/
void backtrack(int task, int k)
{
	int temp;
	if (task>=NUM)
	{
		temp = getTotalCost(k);
		if (best>temp)
		{
			best = temp;
			for (int i = 0; i < NUM; i++)
			{
				bestArrange[i] = arrange[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < k; i++)
		{
			if ((getTotalCost(k)+cost[task])<best)		//��֦
			{
				runtime[i]+=cost[task];
				arrange[task] = i;
				backtrack(task+1, k);
				runtime[i]-=cost[task];
			}
		}
	}
}

/********************************************************
* ���������Բ�ͬ��kֵ���л�������ѷ���
*********************************************************/
int main()
{
	initCost();
	cout<<"�������񻨷�ʱ��Ϊ��"<<endl;
	for (int i = 0; i < NUM; i++)
	{
		cout<<i<<" "<<cost[i]<<endl;
	}
	cout<<endl;
	int k=7;
	//for (int k = 3; k <= 10; k++)
	//{
		initRuntime(k);
		best=1000000000;
		backtrack(0, k);
		cout<<"��k����"<<k<<"ʱ��"<<endl;
		cout<<"��ѵ���ʱ��Ϊ��"<<best<<endl;
		cout<<"������䷽��Ϊ��"<<endl;
		for (int i = 0; i < NUM; i++)
		{
			cout<<i<<"-->"<<bestArrange[i]<<endl;
		}
		cout<<endl;
	//}
	getchar();
}