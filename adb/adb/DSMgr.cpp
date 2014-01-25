#include "DSMgr.h"

int DSMgr::OpenFile(char* filename)		//���ļ�
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

int DSMgr::CloseFile()		//�ر��ļ�
{
	return fclose(currFile);
}

bFrame DSMgr::ReadPage(int page_id)			//��ָ��ҳ
{
	bFrame page;
	fseek(currFile, page_id*FRAMESIZE, SEEK_SET);
	fread(page.field, FRAMESIZE, 1, currFile);
	return page;
}

int DSMgr::WritePage(int page_id, char* field)		//дָ��ҳ
{
	fseek(currFile, page_id*FRAMESIZE, SEEK_SET);
	int count = fwrite(field, FRAMESIZE, 1, currFile);
	return count;
}

int DSMgr::Seek(int offset, int pos)		//Ѱַ�ļ�
{
	return fseek(currFile, offset, pos);
}

FILE* DSMgr::GetFile()			//����ļ�
{
	return currFile;
}

void DSMgr::IncNumPages()		//����ҳ����
{
	numPages++;
}

int DSMgr::GetNumPages()		//���ҳ����
{
	return numPages;
}

void DSMgr::SetUse(int index, int use_bit)		//����ҳ���־λ
{
	pages[index] = use_bit;
}

int DSMgr::GetUse(int index)		//���ҳ���־λ
{
	return pages[index];
}


DSMgr::DSMgr()
{
	currFile = NULL;				//��ʼ��ҳ���־λ
	for (int i = 0; i < MAXPAGES; i++)
	{
		pages[i] = 0;
	}
}

DSMgr::~DSMgr()
{
}