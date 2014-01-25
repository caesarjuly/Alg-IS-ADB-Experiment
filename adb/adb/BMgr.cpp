#include "BMgr.h"
#include "DSMgr.h"
#include "LRU2.h"

int BMgr::FixPage(int page_id)
{
	int frame_id = Hash(page_id);
	BCB* bcb = ptof[frame_id];
	while (bcb != NULL)			//寻找此page是否在当前桶中
	{
		if (bcb->page_id == page_id)
		{
			if (bcb->stime == -1)	//第二次被访问，从AO移动到AT
			{
				bcb->stime = bcb->ftime;
				bcb->ftime = clock();
				//cout<<"get"<<endl;
				lru2.moveAO2AT(bcb);
			}
			else					//二次以上被访问，调整在AT中的位置
			{
				bcb->stime = bcb->ftime;
				bcb->ftime = clock();
				lru2.ajustAT(bcb);
			}
			return bcb->frame_id;
		}
		bcb = bcb->next;
	}

	//如果不在桶中
	int i, empty=-1;
	for (i = 0; i < DEFBUFSIZE; i++)	//	查找空余buf
	{
		if (ftop[i] == -1)
		{
			empty = i;
			break;
		}
	}
	if (empty == -1)		//如果没找到空余，使用lru2算法替换
	{
		empty = SelectVictim();
	}

	strcpy(buf[empty].field, dsmgr.ReadPage(page_id).field);	//读页并写入buffer
	BCB* newbcb = (BCB*)malloc(sizeof(BCB));
	bcb = ptof[frame_id];			//找寻插入位置
	if (bcb == NULL)				//当前桶为空，直接插入
	{
		ptof[frame_id] = newbcb;
	}
	else
	{
		while (bcb->next != NULL)		//寻址到队尾
		{
			bcb = bcb->next;
		}
		bcb->next = newbcb;
	}

	ftop[empty] = page_id;					//设置ftop hash
	newbcb->next = NULL;				//初始化newbcb参数
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
	while (bcb != NULL)						//查找要删除的bcb
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
	if (bcb == ptr)		//如果当前桶的第一个为要删除的bcb
	{
		if (bcb->next == NULL)		//如果只有一个元素
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
		while (bcb->next != ptr)				//找到删除位置的前一个
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
	for (int i = 0; i < DEFBUFSIZE; i++)		//查找当前页是否在buffer中
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

void BMgr::SetDirty(int frame_id)		//设置脏位
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

void BMgr::UnsetDirty(int frame_id)		//取消脏位
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

void BMgr::WriteDirtys()			//所有脏的buf写入文件内
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
	buf = (bFrame*)malloc(DEFBUFSIZE*sizeof(bFrame));	//初始化buf和hash表
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