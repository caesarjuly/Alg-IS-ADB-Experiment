#include "LRU2.h"

void LRU2::moveAO2AT(BCB* bcb)
{
	LRUNode* temp = accessOnce;
	if (temp->next != NULL)		//���AO�в�ֻ��һ�����
	{
		while (temp != NULL)
		{
			if (temp->frame_id == bcb->frame_id)		//�ҵ�AO�������Ҫ�ƶ��Ľ��
			{
				//��AO���Ƴ��˽ڵ�
				if (temp->prev == NULL)					//�˽��Ϊͷ���
				{
					accessOnce = temp->next;
					temp->next->prev = NULL;
					
				}
				else if (temp->next == NULL)			//�˽��Ϊβ���
				{
					tailForAO = temp->prev;
					temp->prev->next = NULL;
				}
				else									//�˽��Ϊ�м���ʱ
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				break;
			}
			temp = temp->next;
		}
	}
	else									//���ֻ��һ�����
	{
		accessOnce = NULL;
		tailForAO = NULL;
	}
	temp->b2d = bcb->stime-bcb->ftime;	//����b2d
	insertIntoAT(temp);

}

void LRU2::insertIntoAT(LRUNode* toBeInsert)
{
	if (accessTwice == NULL)	//AT����Ϊ�գ�ֱ�Ӳ���
	{
		accessTwice = toBeInsert;
		tailForAT = toBeInsert;
		toBeInsert->prev = NULL;
		toBeInsert->next = NULL;
	}
	else
	{
		LRUNode* temp = accessTwice;
		while (temp!=NULL && temp->b2d<toBeInsert->b2d)	//�ҵ�����λ��
		{
			temp = temp->next;
		}
		if (temp == NULL)		//�ڶ�β
		{
			toBeInsert->prev = tailForAT;
			toBeInsert->next = NULL;
			tailForAT->next = toBeInsert;
			tailForAT = toBeInsert;
		}
		else if (temp->prev == NULL)			//�ڶ���
		{
			toBeInsert->prev = NULL;
			toBeInsert->next = accessTwice;
			accessTwice->prev = toBeInsert;
			accessTwice = toBeInsert;
		}
		else					//���м�
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
	LRUNode* newnode = (LRUNode*)malloc(sizeof(LRUNode));		//���ײ����½��
	newnode->frame_id = bcb->frame_id;
	newnode->prev = NULL;
	if (accessOnce == NULL)				//AO����Ϊ��ֱ�Ӳ���
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
	if(temp->next != NULL)					//���AT�в�ֹ��һ�����
	{
		while (temp != NULL)
		{
			if (temp->frame_id == bcb->frame_id)		//�ҵ�AT�������Ҫ�ƶ��Ľ��
			{
				//��AT���Ƴ��˽ڵ�
				if (temp->prev == NULL)					//�˽��Ϊͷ���
				{
					accessTwice = temp->next;
					temp->next->prev = NULL;
					
				}
				else if (temp->next == NULL)			//�˽��Ϊβ���
				{
					tailForAT = temp->prev;
					temp->prev->next = NULL;
				}
				else									//�˽��Ϊ�м���ʱ
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				
				
				break;
			}
			temp = temp->next;
		}
	}
	else									//���AT��ֻ��һ�����
	{
		accessTwice = NULL;
		tailForAT = NULL;
	}
	temp->b2d = bcb->ftime-bcb->stime;		//����b2d
	insertIntoAT(temp);

}

int LRU2::SelectVictim()
{
	int frame_id;
	LRUNode* temp;
	if (accessOnce != NULL)		//AO�Ӳ�Ϊ��
	{
		frame_id = tailForAO->frame_id;
		temp = tailForAO;
		if (accessOnce == tailForAO)		//ֻ��һ�����
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
		if (accessTwice == tailForAT)		//ֻ��һ�����
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

LRU2::LRU2()			//��ʼ�����׺Ͷ�β
{
	accessOnce = NULL;
	accessTwice = NULL;
	tailForAO = accessOnce;
	tailForAT = accessTwice;
}

LRU2::~LRU2()
{
}