#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <iostream>
#include <time.h>

/********************************************************
* 定义全局结构体和宏
*********************************************************/
#define FRAMESIZE  4096
#define DEFBUFSIZE 1024

struct bFrame 
{
	char field[FRAMESIZE];
};


struct BCB
{
  int page_id;
  int frame_id;
  int latch;
  int count;
  int ftime;
  int stime;
  int dirty;
  BCB * next;
};

struct LRUNode
{
	int frame_id;
	LRUNode* prev;
	LRUNode* next;

};


#endif

