#include "LRU2.h"

void LRU2::moveAO2AT(BCB* bcb)
{
	LRUNode* temp = accessOnce;
	if (temp->next != NULL)		//如果AO中不只有一个结点
	{
		while (temp != NULL)
		{
			if (temp->frame_id == bcb->frame_id)		//找到AO链表里的要移动的结点
			{
				//从AO中移除此节点
				if (temp->prev == NULL)					//此结点为头结点
				{
					accessOnce = temp->next;
					temp->next->prev = NULL;
					
				}
				else if (temp->next == NULL)			//此结点为尾结点
				{
					tailForAO = temp->prev;
					temp->prev->next = NULL;
				}
				else									//此结点为中间结点时
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				break;
			}
			temp = temp->next;
		}
	}
	else									//如果只有一个结点
	{
		accessOnce = NULL;
		tailForAO = NULL;
	}
	temp->b2d = bcb->stime-bcb->ftime;	//计算b2d
	insertIntoAT(temp);

}

void LRU2::insertIntoAT(LRUNode* toBeInsert)
{
	if (accessTwice == NULL)	//AT链表为空，直接插入
	{
		accessTwice = toBeInsert;
		tailForAT = toBeInsert;
		toBeInsert->prev = NULL;
		toBeInsert->next = NULL;
	}
	else
	{
		LRUNode* temp = accessTwice;
		while (temp!=NULL && temp->b2d<toBeInsert->b2d)	//找到插入位置
		{
			temp = temp->next;
		}
		if (temp == NULL)		//在队尾
		{
			toBeInsert->prev = tailForAT;
			toBeInsert->next = NULL;
			tailForAT->next = toBeInsert;
			tailForAT = toBeInsert;
		}
		else if (temp->prev == NULL)			//在队首
		{
			toBeInsert->prev = NULL;
			toBeInsert->next = accessTwice;
			accessTwice->prev = toBeInsert;
			accessTwice = toBeInsert;
		}
		else					//在中间
		{
			toBeInsert->prev = temp->prev;
			toBeInsert->next = temp;
			temp->prev->next = toBeInsert;
			temp->prev = toBeInsert;
		}
	}
}

void LRU2::insertIntoAO(BCB* bcb)
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

void LRU2::ajustAT(BCB* bcb)
{
	LRUNode* temp = accessTwice;
	if(temp->next != NULL)					//如果AT中不止有一个结点
	{
		while (temp != NULL)
		{
			if (temp->frame_id == bcb->frame_id)		//找到AT链表里的要移动的结点
			{
				//从AT中移除此节点
				if (temp->prev == NULL)					//此结点为头结点
				{
					accessTwice = temp->next;
					temp->next->prev = NULL;
					
				}
				else if (temp->next == NULL)			//此结点为尾结点
				{
					tailForAT = temp->prev;
					temp->prev->next = NULL;
				}
				else									//此结点为中间结点时
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				
				
				break;
			}
			temp = temp->next;
		}
	}
	else									//如果AT中只有一个结点
	{
		accessTwice = NULL;
		tailForAT = NULL;
	}
	temp->b2d = bcb->ftime-bcb->stime;		//计算b2d
	insertIntoAT(temp);

}

int LRU2::SelectVictim()
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
	else if (accessTwice != NULL)
	{
		frame_id = tailForAT->frame_id;
		temp = tailForAT;
		if (accessTwice == tailForAT)		//只有一个结点
		{
			accessTwice = NULL;
			tailForAT = NULL;
		}
		else
		{
			tailForAT->prev->next = NULL;
			tailForAT = tailForAT->prev;
		}
	}

	free(temp);
	return frame_id;
}

LRU2::LRU2()			//初始化队首和队尾
{
	accessOnce = NULL;
	accessTwice = NULL;
	tailForAO = accessOnce;
	tailForAT = accessTwice;
}

LRU2::~LRU2()
{
}