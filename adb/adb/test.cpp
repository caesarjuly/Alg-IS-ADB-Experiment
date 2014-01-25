#include "global.h"
#include <iomanip>
#include <fstream>
#include <string>
#include "BMgr.h"
using namespace std;

/********************************************************
* 测试程序
*********************************************************/
int main()
{
	ofstream dbf("data.dbf");				//初始化文件
	for (int i = 0; i < 50000; i++)
	{
		for (int j = 0; j < 4096; j++)
		{
			dbf<<"1";
		}
	}
	FILE* f = fopen("data-5w-50w-zipf.txt", "r");		//打开页面操作文件
	char line[20];
	int ICount, OCount, pages, starttime, endtime;
	double ratio, runtime;
	ICount = 0;
	OCount = 0;
	pages = 0;
	BMgr bm;
	starttime = clock();
	while (!feof(f))				//逐个执行操作
	{
		fgets(line, 20, f);
		char* temp1 = strtok(line, ",");		//分割字符串
		char* temp2 = strtok(NULL, ",");
		int mode = atoi(temp1);
		int page_id = atoi(temp2);
		//cout<<mode<<" "<<page_id;
		if (mode == 1)					//读操作
		{
			if (!bm.FindFrame(page_id))
			{
				ICount++;
			}
		}
		else							//写操作
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
	cout<<"buffer大小："<<DEFBUFSIZE<<endl;
	cout<<"总读写页数："<<pages<<endl;
	cout<<"总IO："<<ICount+OCount<<endl;
	cout<<"运行时间："<<runtime<<"s"<<endl;
	cout<<"命中率："<<ratio<<"%"<<endl;
	bm.WriteDirtys();						//把脏页写入
	getchar();
	return 0;
}
