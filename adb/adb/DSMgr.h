#ifndef _DSMGR_H
#define _DSMGR_H
#include "global.h"

#define MAXPAGES 50000

using namespace std;

/********************************************************
* ∂®“ÂDiskManager¿‡
*********************************************************/
class DSMgr
{
public:
  DSMgr();
  ~DSMgr();
  int OpenFile(char* filename);
  int CloseFile();
  bFrame ReadPage(int page_id);
  int WritePage(int page_id, char* field);
  int Seek(int offset, int pos);
  FILE * GetFile();
  void IncNumPages();
  int GetNumPages();
  void SetUse(int index, int use_bit);
  int GetUse(int index);

private:
  FILE *currFile;
  int numPages;
  int pages[MAXPAGES];

};

#endif
