#ifndef _LRU2_H
#define _LRU2_H
#include "global.h"

/********************************************************
* ����LRU2�㷨��
*********************************************************/
class LRU2
{
public:
	LRU2();
	~LRU2();
	void moveAO2AT(BCB* bcb);
	void insertIntoAT(LRUNode* toBeInsert);
	void ajustAT(BCB* bcb);
	void insertIntoAO(BCB* bcb);
	int SelectVictim();

private:
	LRUNode* accessOnce;		//����˫����һ���洢ֻ���ʹ�һ�εĽ�㣬��һ�η���ʱ�����򣬼�FIFO����һ���洢���ʹ��������ϵĽ�㣬��b2dʱ�������򣬴���ں�
	LRUNode* accessTwice;
	LRUNode* tailForAO;		//�����β���Ӷ�βֱ��ѡ������̭
	LRUNode* tailForAT;
};
#endif