#ifndef _LRU_H
#define _LRU_H
#include "global.h"

/********************************************************
* 定义LRU算法类
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
	LRUNode* accessOnce;		//定义双链表，存储只访问过一次的结点，以一次访问时间排序，即FIFO
	LRUNode* tailForAO;		//定义队尾，从队尾直接选择结点淘汰
};
#endif