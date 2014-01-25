#include <iostream>
#include <time.h>
using namespace std;
#define NUM 20
/********************************************************
* 定义一些全局变量，包括最佳分配，当前分配，任务花费时间，最佳总时间，每个机器的运行时间
*********************************************************/
int bestArrange[NUM];
int arrange[NUM];
int cost[NUM];
int best;
int runtime[10];

/********************************************************
* 初始化任务所需时间
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
* 初始化各个机器的运行时间
*********************************************************/
void initRuntime(int k)
{
	for (int i = 0; i < k; i++)
	{
		runtime[k] = 0;
	}
}

/********************************************************
* 获取当前最大的运行时间
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
* 回溯法，计算最佳分配和最佳时间
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
			if ((getTotalCost(k)+cost[task])<best)		//剪枝
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
* 主函数，对不同的k值进行回溯求最佳分配
*********************************************************/
int main()
{
	initCost();
	cout<<"各个任务花费时间为："<<endl;
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
		cout<<"当k等于"<<k<<"时："<<endl;
		cout<<"最佳调度时间为："<<best<<endl;
		cout<<"任务分配方案为："<<endl;
		for (int i = 0; i < NUM; i++)
		{
			cout<<i<<"-->"<<bestArrange[i]<<endl;
		}
		cout<<endl;
	//}
	getchar();
}