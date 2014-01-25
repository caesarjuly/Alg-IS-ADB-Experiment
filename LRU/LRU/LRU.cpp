#include "LRU.h"



void LRU::insertIntoAO(BCB* bcb)
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

void LRU::ajustAO(BCB* bcb)
{
	LRUNode* temp = accessOnce;
	LRUNode* temp1 = tailForAO;
	if(temp->next != NULL)					//���AO�в�ֹ��һ�����
	{
		while (temp != NULL && temp1 != NULL)
		{
			if (temp1->frame_id == bcb->frame_id)
			{
				temp = temp1;
			}
			if (temp->frame_id == bcb->frame_id)		//�ҵ�AO�������Ҫ�ƶ��Ľ��
			{
				//�ƶ��˽�㵽����
				if (temp->prev == NULL)					//�˽��Ϊͷ���
				{
					//donothing
					
				}
				else if (temp->next == NULL)			//�˽��Ϊβ���
				{
					tailForAO = temp->prev;
					temp->prev->next = NULL;
				}
				else 
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				
				
				//�������
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
	else									//���AO��ֻ��һ�����
	{
		//donothing
	}
}
int LRU::SelectVictim()
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


	free(temp);
	return frame_id;
}

LRU::LRU()			//��ʼ�����׺Ͷ�β
{
	accessOnce = NULL;
	tailForAO = accessOnce;
}

LRU::~LRU()
{
}