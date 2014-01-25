#ifndef _LRU2_H
#define _LRU2_H
#include "global.h"

/********************************************************
* 定义LRU2算法类
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
	LRUNode* accessOnce;		//定义双链表，一个存储只访问过一次的结点，以一次访问时间排序，即FIFO，另一个存储访问过两次以上的结点，以b2d时间间隔排序，大的在后
	LRUNode* accessTwice;
	LRUNode* tailForAO;		//定义队尾，从队尾直接选择结点淘汰
	LRUNode* tailForAT;
};
#endif