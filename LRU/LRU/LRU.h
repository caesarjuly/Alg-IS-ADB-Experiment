#ifndef _LRU_H
#define _LRU_H
#include "global.h"

/********************************************************
* ����LRU�㷨��
*********************************************************/
class LRU
{
public:
	LRU();
	~LRU();
	void insertIntoAO(BCB* bcb);
	void ajustAO(BCB* bcb);
	int SelectVictim();

private:
	LRUNode* accessOnce;		//����˫�����洢ֻ���ʹ�һ�εĽ�㣬��һ�η���ʱ�����򣬼�FIFO
	LRUNode* tailForAO;		//�����β���Ӷ�βֱ��ѡ������̭
};
#endif