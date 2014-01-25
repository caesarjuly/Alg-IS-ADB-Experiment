#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define Length 1000000

/********************************************************
* �����������
*********************************************************/
void generateRandomArray(int *copy){
	srand((int)time(0));
	for (int i = 0; i < Length; i++)
	{
		copy[i] = rand();
	}
}

/********************************************************
* ����������ӡ����
*********************************************************/
void printArray(int *toBePrint){
	for (int i = 0; i < Length; i++)
	{
		printf("%d\n",toBePrint[i]);
	}
}

/********************************************************
* ����x��y��ֵ
*********************************************************/
void exchange(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/********************************************************
* �������飬��֤ÿ�ν�����������鶼��ͬ�����������
*********************************************************/
void copyArray(int *source, int *destination){
	for (int i = 0; i < Length; i++)
	{
		destination[i] = source[i];
	}
}

/********************************************************
* ��������
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
* �������λ�ã����ڲ����������Ԫ
*********************************************************/
int randP(int p, int r){
	int i;
	srand((int)time(0));
	return rand()%(r-p)+p;
}

/********************************************************
* һ�λ���
*********************************************************/
int partition(int *toBePartition,int p, int r){
	int x,i,j,temp;
	//�����������Ԫ
	//x = toBePartition[randP(p ,r)];    

	//ȡ���һ����Ϊ����Ԫ
	x = toBePartition[r];                

	//ȡ�м�ֵΪ����Ԫ
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
* ��������
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
* ȡ��ͬ��kֵ�����Ż�����ƽ������ʱ��
*********************************************************/
void differentNumOptimizeTest(int *toBeSort,int *copy){
	clock_t  startTime, endTime;
	long average;
	for (int numUseInsert = 0; numUseInsert < 200; numUseInsert += 5)
	{
		average = 0;
		printf("��k=%dʱ:\n", numUseInsert);
		for (int i = 0; i < 10; i++)
		{
			copyArray(copy, toBeSort);
			startTime = clock();
			quickSort(toBeSort, 0, Length-1, numUseInsert);
			insertSort(toBeSort);
			endTime = clock();
			//printf("k=%dʱ��%d������ʱ��Ϊ��%ld\n", numUseInsert, i+1, endTime-startTime);
			average += endTime-startTime;
		}
		printf("k=%dʱƽ������ʱ��Ϊ��%ld\n\n", numUseInsert, average/10);

	}
}

/********************************************************
* �������������������ı��ݲ������Ż����Ժ���
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