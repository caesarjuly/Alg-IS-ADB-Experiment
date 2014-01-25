#include "global.h"
#include <iomanip>
#include <fstream>
#include <string>
#include "BMgr.h"
using namespace std;

/********************************************************
* ���Գ���
*********************************************************/
int main()
{
	ofstream dbf("data.dbf");				//��ʼ���ļ�
	for (int i = 0; i < 50000; i++)
	{
		for (int j = 0; j < 4096; j++)
		{
			dbf<<"1";
		}
	}
	FILE* f = fopen("data-5w-50w-zipf.txt", "r");		//��ҳ������ļ�
	char line[20];
	int ICount, OCount, pages, starttime, endtime;
	double ratio, runtime;
	ICount = 0;
	OCount = 0;
	pages = 0;
	BMgr bm;
	starttime = clock();
	while (!feof(f))				//���ִ�в���
	{
		fgets(line, 20, f);
		char* temp1 = strtok(line, ",");		//�ָ��ַ���
		char* temp2 = strtok(NULL, ",");
		int mode = atoi(temp1);
		int page_id = atoi(temp2);
		//cout<<mode<<" "<<page_id;
		if (mode == 1)					//������
		{
			if (!bm.FindFrame(page_id))
			{
				ICount++;
			}
		}
		else							//д����
		{
			if (!bm.FindFrame(page_id))
			{
				OCount++;
			}
		}
		bm.FixPage(page_id);
		pages++;
	}
	endtime = clock();
	runtime = ((double)endtime-(double)starttime)/1000;
	ratio = (double)(pages-ICount-OCount)/(double)pages*100;
	cout<<"buffer��С��"<<DEFBUFSIZE<<endl;
	cout<<"�ܶ�дҳ����"<<pages<<endl;
	cout<<"��IO��"<<ICount+OCount<<endl;
	cout<<"����ʱ�䣺"<<runtime<<"s"<<endl;
	cout<<"�����ʣ�"<<ratio<<"%"<<endl;
	bm.WriteDirtys();						//����ҳд��
	getchar();
	return 0;
}
