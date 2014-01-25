#include <stdio.h>
#include <iostream>
#include <queue>
#include <time.h>
using namespace std;
#define NUM 10

/********************************************************
* 定义结点结构
*********************************************************/
typedef struct Node
{
	char c;
	int freq;
	char code[5];
	struct Node* left;
	struct Node* right;
}HFNode;

/********************************************************
* 定义优先队列比较函数
*********************************************************/
struct ComHFNode
{
	bool operator()(HFNode* a, HFNode* b){
		return a->freq > b->freq;
	}
};

/********************************************************
* 对生成的哈夫曼树编码
*********************************************************/
void encodeHFTree(HFNode* z){
	if (z != NULL)
	{
		if (z->left!=NULL && z->right!=NULL)
		{
				strcpy(z->left->code, z->code);
				strcat(z->left->code, "0");
				strcpy(z->right->code, z->code);
				strcat(z->right->code, "1");
		}
		encodeHFTree(z->left);
		encodeHFTree(z->right);
	}

	
}

/********************************************************
* 打印哈夫曼树
*********************************************************/
void printHFTree(HFNode* z){
	if (z != NULL)
	{
		if (z->left==NULL && z->right==NULL)
		{
			printf("%c %d %s\n", z->c, z->freq, z->code);
		}
		printHFTree(z->left);
		printHFTree(z->right);
	}
	
}

/********************************************************
* 建树
*********************************************************/
HFNode* buildHFTree(){
	priority_queue<HFNode*, vector<HFNode*>, ComHFNode> pqueue_HFNode;
	srand((int)time(0));
	for (int i = 0; i < NUM; i++)		//初始化所有结点
	{
		HFNode* z = (HFNode*)malloc(sizeof(HFNode));
		z->code[0] = '\0';
		z->c = 'a'+i;
		z->freq = rand()%100;
		z->left = NULL;
		z->right = NULL;
		pqueue_HFNode.push(z);

	}

	for (int i = 0; i < NUM-1; i++)			//生成中间结点，建立树
	{
		HFNode* z = (HFNode*)malloc(sizeof(HFNode));
		z->code[0] = '\0';
		z->left = pqueue_HFNode.top();
		pqueue_HFNode.pop();
		z->right = pqueue_HFNode.top();
		pqueue_HFNode.pop();
		z->freq = z->left->freq + z->right->freq;
		pqueue_HFNode.push(z);
	}
	return pqueue_HFNode.top();

}

/********************************************************
* 主函数
*********************************************************/
int main(){
	HFNode* root = (HFNode*)malloc(sizeof(HFNode));
	root = buildHFTree();
	encodeHFTree(root);
	printHFTree(root);
	getchar();
}
