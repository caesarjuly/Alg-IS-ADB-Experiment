#include "LRU.h"



void LRU::insertIntoAO(BCB* bcb)
{
	LRUNode* newnode = (LRUNode*)malloc(sizeof(LRUNode));		//队首插入新结点
	newnode->frame_id = bcb->frame_id;
	newnode->prev = NULL;
	if (accessOnce == NULL)				//AO链表为空直接插入
	{
		accessOnce = newnode;
		tailForAO = newnode;
		newnode->next = NULL;
	}
	else
	{
		newnode->next = accessOnce;
		accessOnce->prev = newnode;
		accessOnce = newnode;
	}
	
}

void LRU::ajustAO(BCB* bcb)
{
	LRUNode* temp = accessOnce;
	LRUNode* temp1 = tailForAO;
	if(temp->next != NULL)					//如果AO中不止有一个结点
	{
		while (temp != NULL && temp1 != NULL)
		{
			if (temp1->frame_id == bcb->frame_id)
			{
				temp = temp1;
			}
			if (temp->frame_id == bcb->frame_id)		//找到AO链表里的要移动的结点
			{
				//移动此结点到队首
				if (temp->prev == NULL)					//此结点为头结点
				{
					//donothing
					
				}
				else if (temp->next == NULL)			//此结点为尾结点
				{
					tailForAO = temp->prev;
					temp->prev->next = NULL;
				}
				else 
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				
				
				//插入队首
				temp->next = accessOnce;
				accessOnce->prev = temp;
				temp->prev = NULL;
				accessOnce = temp;
				break;
			}
			temp = temp->next;
			temp1 = temp1->prev;
		}
	}
	else									//如果AO中只有一个结点
	{
		//donothing
	}
}
int LRU::SelectVictim()
{
	int frame_id;
	LRUNode* temp;
	if (accessOnce != NULL)		//AO队不为空
	{
		frame_id = tailForAO->frame_id;
		temp = tailForAO;
		if (accessOnce == tailForAO)		//只有一个结点
		{
			accessOnce = NULL;
			tailForAO = NULL;
		}
		else
		{
			tailForAO->prev->next = NULL;
			tailForAO = tailForAO->prev;
		}
		
	}


	free(temp);
	return frame_id;
}

LRU::LRU()			//初始化队首和队尾
{
	accessOnce = NULL;
	tailForAO = accessOnce;
}

LRU::~LRU()
{
}