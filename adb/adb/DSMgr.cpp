#include "DSMgr.h"

int DSMgr::OpenFile(char* filename)		//打开文件
{
	currFile = fopen(filename, "r+");
	if (currFile != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int DSMgr::CloseFile()		//关闭文件
{
	return fclose(currFile);
}

bFrame DSMgr::ReadPage(int page_id)			//读指定页
{
	bFrame page;
	fseek(currFile, page_id*FRAMESIZE, SEEK_SET);
	fread(page.field, FRAMESIZE, 1, currFile);
	return page;
}

int DSMgr::WritePage(int page_id, char* field)		//写指定页
{
	fseek(currFile, page_id*FRAMESIZE, SEEK_SET);
	int count = fwrite(field, FRAMESIZE, 1, currFile);
	return count;
}

int DSMgr::Seek(int offset, int pos)		//寻址文件
{
	return fseek(currFile, offset, pos);
}

FILE* DSMgr::GetFile()			//获得文件
{
	return currFile;
}

void DSMgr::IncNumPages()		//增加页面数
{
	numPages++;
}

int DSMgr::GetNumPages()		//获得页面数
{
	return numPages;
}

void DSMgr::SetUse(int index, int use_bit)		//设置页面标志位
{
	pages[index] = use_bit;
}

int DSMgr::GetUse(int index)		//获得页面标志位
{
	return pages[index];
}


DSMgr::DSMgr()
{
	currFile = NULL;				//初始化页面标志位
	for (int i = 0; i < MAXPAGES; i++)
	{
		pages[i] = 0;
	}
}

DSMgr::~DSMgr()
{
}