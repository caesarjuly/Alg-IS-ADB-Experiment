#ifndef _BMGR_H
#define _BMGR_H

#include <iostream>
#include "global.h"
#include "DSMgr.h"
#include "LRU2.h"


using namespace std;

/********************************************************
* ∂®“ÂBufferManager
*********************************************************/
class BMgr
{
public:
  BMgr();
  ~BMgr();
  // Interface functions
  int FixPage(int page_id);
  void FixNewPage();
  int UnfixPage(int page_id);
  int NumFreeFrames();
  int FindFrame(int page_id);

  // Internal Functions
  int SelectVictim();
  int Hash(int page_id);
  void RemoveBCB(BCB * ptr, int page_id);
  void RemoveLRUEle(int frid);
  void SetDirty(int frame_id);
  void UnsetDirty(int frame_id);
  void WriteDirtys();
  void PrintFrame(int frame_id);
  bFrame* buf;

  private:
  // Hash Table
  int ftop[DEFBUFSIZE];
  BCB* ptof[DEFBUFSIZE];
  DSMgr dsmgr;
  LRU2 lru2;
 

}; 
#endif