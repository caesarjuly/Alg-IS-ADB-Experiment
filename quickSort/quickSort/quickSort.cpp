#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define Length 1000000

/********************************************************
* 产生随机数组
*********************************************************/
void generateRandomArray(int *copy){
	srand((int)time(0));
	for (int i = 0; i < Length; i++)
	{
		copy[i] = rand();
	}
}

/********************************************************
* 辅助函数打印数组
*********************************************************/
void printArray(int *toBePrint){
	for (int i = 0; i < Length; i++)
	{
		printf("%d\n",toBePrint[i]);
	}
}

/********************************************************
* 交换x和y的值
*********************************************************/
void exchange(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/********************************************************
* 复制数组，保证每次进行排序的数组都是同样的随机数组
*********************************************************/
void copyArray(int *source, int *destination){
	for (int i = 0; i < Length; i++)
	{
		destination[i] = source[i];
	}
}

/********************************************************
* 插入排序
*********************************************************/
void insertSort(int *allMostSort){
	int key, j, i;
	for (i = 1; i < Length; i++)
	{
		key = allMostSort[i];
		j = i-1;
		while (j>=0 && allMostSort[j]>key)
		{
			allMostSort[j+1] = allMostSort[j];
			j = j-1;
		}
		allMostSort[j+1] = key;
	}
}

/********************************************************
* 产生随机位置，用于产生随机划分元
*********************************************************/
int randP(int p, int r){
	int i;
	srand((int)time(0));
	return rand()%(r-p)+p;
}

/********************************************************
* 一次划分
*********************************************************/
int partition(int *toBePartition,int p, int r){
	int x,i,j,temp;
	//随机产生划分元
	//x = toBePartition[randP(p ,r)];    

	//取最后一个数为划分元
	x = toBePartition[r];                

	//取中间值为划分元
	//int middle = (p+r)/2;             
	//if ((toBePartition[p] < toBePartition[middle] && toBePartition[p] > toBePartition[r]) || 
	//		(toBePartition[p] > toBePartition[middle] && toBePartition[p] < toBePartition[r]))
	//{
	//	x = toBePartition[p];
	//}
	//else if ((toBePartition[middle] < toBePartition[p] && toBePartition[middle] > toBePartition[r]) || 
	//		(toBePartition[middle] > toBePartition[p] && toBePartition[middle] < toBePartition[r]))
	//{
	//	x = toBePartition[middle];
	//}
	//else
	//{
	//	x = toBePartition[r];
	//}
	i = p-1;
	for (j = p; j < r; j++)
	{
		if ( toBePartition[j] <= x)
		{
			i = i+1;
			exchange(&toBePartition[i], &toBePartition[j]);
		}
	}
	exchange(&toBePartition[i+1], &toBePartition[r]);
	return i+1;
}

/********************************************************
* 快速排序
*********************************************************/
void quickSort(int *toBeSort, int p, int r, int numUseInsert){
	int q;
	if ( (r-p)>numUseInsert )
	{
		q = partition(toBeSort, p, r);
		quickSort(toBeSort, p, q-1, numUseInsert);
		quickSort(toBeSort, q+1, r, numUseInsert);
	}
}

/********************************************************
* 取不同的k值进行优化并求平均运行时间
*********************************************************/
void differentNumOptimizeTest(int *toBeSort,int *copy){
	clock_t  startTime, endTime;
	long average;
	for (int numUseInsert = 0; numUseInsert < 200; numUseInsert += 5)
	{
		average = 0;
		printf("当k=%d时:\n", numUseInsert);
		for (int i = 0; i < 10; i++)
		{
			copyArray(copy, toBeSort);
			startTime = clock();
			quickSort(toBeSort, 0, Length-1, numUseInsert);
			insertSort(toBeSort);
			endTime = clock();
			//printf("k=%d时第%d次运行时间为：%ld\n", numUseInsert, i+1, endTime-startTime);
			average += endTime-startTime;
		}
		printf("k=%d时平均运行时间为：%ld\n\n", numUseInsert, average/10);

	}
}

/********************************************************
* 主函数，生成随机数组的备份并调用优化测试函数
*********************************************************/
int main(){
	int *toBeSort, *copy;
	toBeSort = (int *)malloc(Length*sizeof(int));
	copy = (int *)malloc(Length*sizeof(int));
	generateRandomArray(copy);
	//printArray(toBeSort);
	differentNumOptimizeTest(toBeSort, copy);
	getchar();
}