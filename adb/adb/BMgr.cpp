#include "BMgr.h"
#include "DSMgr.h"
#include "LRU2.h"

int BMgr::FixPage(int page_id)
{
	int frame_id = Hash(page_id);
	BCB* bcb = ptof[frame_id];
	while (bcb != NULL)			//Ѱ�Ҵ�page�Ƿ��ڵ�ǰͰ��
	{
		if (bcb->page_id == page_id)
		{
			if (bcb->stime == -1)	//�ڶ��α����ʣ���AO�ƶ���AT
			{
				bcb->stime = bcb->ftime;
				bcb->ftime = clock();
				//cout<<"get"<<endl;
				lru2.moveAO2AT(bcb);
			}
			else					//�������ϱ����ʣ�������AT�е�λ��
			{
				bcb->stime = bcb->ftime;
				bcb->ftime = clock();
				lru2.ajustAT(bcb);
			}
			return bcb->frame_id;
		}
		bcb = bcb->next;
	}

	//�������Ͱ��
	int i, empty=-1;
	for (i = 0; i < DEFBUFSIZE; i++)	//	���ҿ���buf
	{
		if (ftop[i] == -1)
		{
			empty = i;
			break;
		}
	}
	if (empty == -1)		//���û�ҵ����࣬ʹ��lru2�㷨�滻
	{
		empty = SelectVictim();
	}

	strcpy(buf[empty].field, dsmgr.ReadPage(page_id).field);	//��ҳ��д��buffer
	BCB* newbcb = (BCB*)malloc(sizeof(BCB));
	bcb = ptof[frame_id];			//��Ѱ����λ��
	if (bcb == NULL)				//��ǰͰΪ�գ�ֱ�Ӳ���
	{
		ptof[frame_id] = newbcb;
	}
	else
	{
		while (bcb->next != NULL)		//Ѱַ����β
		{
			bcb = bcb->next;
		}
		bcb->next = newbcb;
	}

	ftop[empty] = page_id;					//����ftop hash
	newbcb->next = NULL;				//��ʼ��newbcb����
	newbcb->count = 0;
	newbcb->dirty = 0;
	newbcb->frame_id = empty;
	newbcb->ftime = clock();
	newbcb->latch = 0;
	newbcb->page_id = page_id;
	newbcb->stime = -1;
	lru2.insertIntoAO(newbcb);
	return empty;
}

int BMgr::SelectVictim()
{
	int frame_id = lru2.SelectVictim();
	int page_id = ftop[frame_id];
	BCB* bcb = ptof[Hash(page_id)];
	while (bcb != NULL)						//����Ҫɾ����bcb
	{
		if (bcb->frame_id == frame_id)
		{
			break;
		}
		bcb = bcb->next;
	}
	RemoveBCB(bcb, page_id);
	return frame_id;
}

void BMgr::RemoveBCB(BCB* ptr, int page_id)
{
	int frame_id = Hash(page_id);
	BCB* bcb = ptof[frame_id];
	if (bcb == ptr)		//�����ǰͰ�ĵ�һ��ΪҪɾ����bcb
	{
		if (bcb->next == NULL)		//���ֻ��һ��Ԫ��
		{
			ptof[frame_id] = NULL;
		}
		else
		{
			ptof[frame_id] = bcb->next;
		}
	}
	else
	{
		while (bcb->next != ptr)				//�ҵ�ɾ��λ�õ�ǰһ��
		{
			bcb = bcb->next;
		}
		bcb->next = ptr->next;
	}

	if (ptr->dirty == 1)
	{
		dsmgr.WritePage(ptr->page_id, buf[ptr->frame_id].field);
	}
	free(ptr);
}

int BMgr::FindFrame(int page_id)
{
	int flag = 0;
	for (int i = 0; i < DEFBUFSIZE; i++)		//���ҵ�ǰҳ�Ƿ���buffer��
	{
		BCB* bcb = ptof[i];
		while (bcb != NULL)
		{
			if (bcb->page_id == page_id)
			{
				flag = 1;
			}
			bcb = bcb->next;
		}
	}
	return flag;
}

void BMgr::SetDirty(int frame_id)		//������λ
{
	int page_id = ftop[frame_id];
	BCB* bcb = ptof[Hash(page_id)];
	while(bcb != NULL)
	{
		if (bcb->frame_id == frame_id)
		{
			bcb->dirty = 1;
		}
		bcb = bcb->next;
	}
}

void BMgr::UnsetDirty(int frame_id)		//ȡ����λ
{
	int page_id = ftop[frame_id];
	BCB* bcb = ptof[Hash(page_id)];
	while(bcb != NULL)
	{
		if (bcb->frame_id == frame_id)
		{
			bcb->dirty = 0;
		}
		bcb = bcb->next;
	}
}

void BMgr::WriteDirtys()			//�������bufд���ļ���
{
	int i = 0;
	BCB* bcb;
	for (i = 0; i < DEFBUFSIZE; i++) {
		bcb = ptof[i];
		while (bcb != NULL) {
			if (bcb->dirty == 1) {
				dsmgr.WritePage(bcb->page_id, buf[bcb->frame_id].field);
			}
			bcb = bcb->next;
		}
	}
}

int BMgr::Hash(int page_id)
{
	return page_id%DEFBUFSIZE;
}


BMgr::BMgr()
{
	buf = (bFrame*)malloc(DEFBUFSIZE*sizeof(bFrame));	//��ʼ��buf��hash��
	for (int i = 0; i < DEFBUFSIZE; i++)
	{
		ftop[i] = -1;
		ptof[i] = NULL;
	}
	dsmgr.OpenFile("data.dbf");

}

BMgr::~BMgr()
{
}