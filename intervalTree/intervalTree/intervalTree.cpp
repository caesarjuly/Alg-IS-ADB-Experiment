#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************************************************
* ����������Ժͽ����
*********************************************************/
#define RED true
#define BLACK false
#define NUM 1000

/********************************************************
* ���ṹ������������nil���
*********************************************************/
typedef struct Node
{
	int key;
	int high;
	int max;
	bool color;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
}intervalNode;
intervalNode *nil;
intervalNode *root;

/********************************************************
* ���һ��������Ϣ
*********************************************************/
void printCurrentNode(intervalNode *t){
	puts("================================");
	printf("��ǰ���������˵�ֵΪ��%d\n", t->key);
	printf("��ǰ��������Ҷ˵�ֵΪ��%d\n", t->high);
	printf("��ǰ���maxֵΪ��%d\n", t->max);

	if (t->color)
	{
		printf("��ɫΪRED\n");
	}
	else
	{
		printf("��ɫΪBLACK\n");
	}

	if (t->parent != nil)
	{
		printf("���ĸ�����ֵΪ��%d\n", t->parent->key);
	}
	else
	{
		printf("���ĸ����Ϊnil���\n");
	}

	if (t->left != nil)
	{
		printf("�������ӽ���ֵΪ��%d\n", t->left->key);
	}
	else
	{
		printf("�������ӽ��Ϊnil���\n");
	}

	if (t->right != nil)
	{
		printf("�����Һ��ӽ���ֵΪ��%d\n", t->right->key);
	}
	else
	{
		printf("�����Һ��ӽ��Ϊnil���\n");
	}

	puts("================================\n");
}

/********************************************************
* �����ص�����
*********************************************************/
intervalNode *intervalSearch(intervalNode *root, intervalNode *toBeSearch){
	intervalNode *x = root;
	while (x != nil && !(x->key <= toBeSearch->key && x->high >= toBeSearch->high))
	{
		if (x->left != nil && x->left->max >= toBeSearch->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	return x;
}

/********************************************************
* ������С�Ͷ˵��ص�����
*********************************************************/
intervalNode *minIntervalSearch(intervalNode *root, intervalNode *toBeSearch){
	intervalNode *x = intervalSearch(root, toBeSearch);
	intervalNode *y = x;

	while (y != nil && y->left->max >= toBeSearch->key)
	{
		y = x->left;

		while (y != nil && !(y->key <= toBeSearch->key && y->high >= toBeSearch->high))
		{
			if (y->left != nil && y->left->max >= toBeSearch->key)
			{
				y = y->left;
			}
			else
			{
				y = y->right;
			}
		}

		if (y != nil)
		{
			x = y;
		}
	}

	return x;

}

/********************************************************
* ��maxֵ
*********************************************************/
int max(intervalNode *x){
	int maxIn2 = x->high > x->left->max ? x->high : x->left->max;
	int maxIn3 = x->right->max > maxIn2 ? x->right->max : maxIn2;
	return maxIn3;
}

/********************************************************
* ����������maxֵ
*********************************************************/
void fixupMax(intervalNode *t){
	if (t != nil)
	{
		fixupMax(t->left);
		fixupMax(t->right);
		t->max = max(t);
	}
}

/********************************************************
* ǰ�������
*********************************************************/
void preorderTraversal(intervalNode *t){
	if (t != nil)
	{
		printCurrentNode(t);
		preorderTraversal(t->left);
		preorderTraversal(t->right);
	}
}


/********************************************************
* ��������
*********************************************************/
intervalNode* leftRotate(intervalNode *root, intervalNode *RotateNode){
	intervalNode *y = RotateNode->right;				//y��ΪRotateNode�Һ���
	RotateNode->right = y->left;				//y������ΪRotateNode�Һ���
	if (y->left != nil)							//���y���Ӳ�Ϊ��
	{
		y->left->parent = RotateNode;			//y���Ӹ������ΪRotateNode
	}
	y->parent = RotateNode->parent;				//y�ĸ������ΪRotateNode�����
	if (RotateNode->parent == nil)				//���RotateNode�ĸ����Ϊ��
	{
		root = y;								//y��Ϊ���ڵ�
	}
	else if(RotateNode == RotateNode->parent->left)		//���RotateNodeΪ�丸��������
	{
		RotateNode->parent->left = y;					//��y��ΪRotateNode����������
	}
	else
	{
		RotateNode->parent->right = y;					//������Ϊ�Һ���
	}		
	y->left = RotateNode;								//RotateNode��Ϊy������
	RotateNode->parent = y;								//y��ΪRotateNode�ĸ����
	
	return root;

}

/********************************************************
* ��������
*********************************************************/
intervalNode* rightRotate(intervalNode* root, intervalNode *RotateNode)
{
	intervalNode *x = RotateNode->left;					//x��ΪRotateNode������
	RotateNode->left = x->right;					//x���Һ�����ΪRotateNode������
	if (x->right != nil)							//���x���Һ��Ӳ�Ϊ��
	{
		x->right->parent = RotateNode;				//����RotateNodeΪx���Һ��ӵĸ���
	}
	x->parent = RotateNode->parent;					//��x�ĸ������ΪRotateNode�ĸ����
	if (RotateNode->parent == nil)					//���RotateNode�ĸ����Ϊ��
	{
		root = x;									//x��Ϊ���ڵ�
	}
	else if(RotateNode == RotateNode->parent->left)	//���RotateNodeΪ�丸����
	{
		RotateNode->parent->left = x;				//x��ΪRotateNode����������
	}
	else
	{
		RotateNode->parent->right = x;				//������Ϊ�Һ���
	}
	x->right = RotateNode;							//RotateNode��Ϊx���Һ���
	RotateNode->parent = x;							//RotateNode�ĸ������Ϊx

	return root;
}

/********************************************************
* �����������
*********************************************************/
intervalNode* intervalInsertFixup(intervalNode *root, intervalNode *FixupNode){
	intervalNode *Uncle;
	while (FixupNode->parent->color == RED)		//������������ĸ���㲻Ϊ�գ��Ҹ����Ϊ�죬����Ҫ����
	{
		if (FixupNode->parent == FixupNode->parent->parent->left)		//��������Ϊ�游��������
		{
			Uncle = FixupNode->parent->parent->right;					//��ȡ����
			if (Uncle->color == RED)					//������㲻Ϊnil������Ϊ��
			{
				FixupNode->parent->color = BLACK;						//�������Ϊ��
				Uncle->color = BLACK;									//������Ϊ��
				FixupNode->parent->parent->color = RED;					//�游�����Ϊ��
				FixupNode = FixupNode->parent->parent;					//��ǰ�����Ϊ�游���
				continue;
			}
			else														//�������Ϊ��
			{
				if(FixupNode == FixupNode->parent->right)				//�����ǰ������Һ���
				{
					FixupNode = FixupNode->parent;						//��ǰ�����Ϊ�����
					root = leftRotate(root, FixupNode);			 		//����
				}

				FixupNode->parent->color = BLACK;						//���ø����Ϊ��
				FixupNode->parent->parent->color = RED;				//�游�����Ϊ��	
				root = rightRotate(root, FixupNode->parent->parent);	//����
			}
		}
		else
		{
			Uncle = FixupNode->parent->parent->left;					//����Ϊ�游��������
			if (Uncle->color == RED)					//������㲻Ϊ������ɫΪ��
			{
				FixupNode->parent->color = BLACK;						//�������Ϊ��	
				Uncle->color = BLACK;									//������Ϊ��
				FixupNode->parent->parent->color = RED;					//�游�����Ϊ��
				FixupNode = FixupNode->parent->parent;					//��ǰ�����Ϊ�游���
				continue;
			}
			else														//�������Ϊ��
			{
				if(FixupNode == FixupNode->parent->left)				//��ǰ���Ϊ����������
				{
					FixupNode = FixupNode->parent;						//��ǰ�����Ϊ�����
					root = rightRotate(root, FixupNode);				//����
				}

				FixupNode->parent->color = BLACK;						//�������Ϊ��
				FixupNode->parent->parent->color = RED;				//�游�����Ϊ��
				root = leftRotate(root, FixupNode->parent->parent);	//����
			}

		}
	}
	root->color = BLACK;
	return root;
}

/********************************************************
* �����㺯��
*********************************************************/
intervalNode* intervalInsert(intervalNode *root, intervalNode *InsertNode){

	intervalNode *y = nil;
	intervalNode *x = root;
	while (x != nil)	//Ѱ�Ҳ���λ��
	{
		y = x;	//y��¼��ǰλ�ø����λ��
		if (InsertNode->key < x->key)	//������keyС�ڵ�ǰ�����������
		{
			x = x->left;
		}
		else							//���ھ�������
		{
			x = x->right;
		}
	}
	InsertNode->parent = y;				//��ǰ��㸸�ڵ�����Ϊy
	if (y == nil)						//���y�����nil����ǰ���Ϊroot���
	{
		root = InsertNode;
	}
	else if(InsertNode->key < y->key)	//������keyС��y��Ϊy������
	{
		y->left = InsertNode;
	}
	else								//��֮Ϊ�Һ���
	{
		y->right = InsertNode;
	}

	InsertNode->left = nil;				//���ý����Ϣ
	InsertNode->right = nil;
	InsertNode->color = RED;
	return intervalInsertFixup(root, InsertNode);		//������ǰ���
}

/********************************************************
* ���������������β���ָ�������
*********************************************************/
intervalNode* buildIntervalTree(){
	srand((int)time(0));
	root = nil;
	for (int i = 0; i < NUM; i++)
	{
		intervalNode *InsertNode = (intervalNode*)malloc(sizeof(intervalNode));
		InsertNode->key = rand()%1000; 
		InsertNode->high = InsertNode->key + rand()%200 +1;
		InsertNode->max = InsertNode->high;
		root = intervalInsert(root, InsertNode);
		//printf("����key=%d�Ľ���\n", InsertNode->key);
		//preorderTraversal(root);
	}
	return root;
}

/********************************************************
* ��ӡ�ڸ�
*********************************************************/
void printBlackHeight(intervalNode *root){
	int i = 1;
	intervalNode *x = root;
	while (x != nil)
	{
		if (x->color == BLACK)
			i++;
		x = x->left;
	} 
	printf("���ĺڸ�Ϊ��%d\n", i);
}

/********************************************************
* �������
*********************************************************/
int getHeight(intervalNode *root){
	int i, j;
	if (root == nil)
	{
		return 0;
	}
	else 
	{
		i = getHeight(root->left);
		j = getHeight(root->right);
		return (i>j?i:j)+1;			//�������������еĴ���+1
	}
}

/********************************************************
* ��ӡ����
*********************************************************/
void printHeight(intervalNode *root){
	printf("����Ϊ��%d\n", getHeight(root));
}

/********************************************************
* ����������ʼ��nil��㣬������Ȼ���ӡ���ߺͺڸ�
*********************************************************/
int main(){
	intervalNode *	result;
	nil = (intervalNode*)malloc(sizeof(intervalNode));
	intervalNode *	toBeSearch = (intervalNode*)malloc(sizeof(intervalNode));
	nil->key = -1;
	nil->color = BLACK;
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->high = -1;
	nil->max = -1;

	srand((int)time(0));
	toBeSearch->key = rand()%1000;
	toBeSearch->high = toBeSearch->key + rand()%100 + 1;
	printf("��ʼ����������\n");
	root = buildIntervalTree();
	printf("������������ɣ�\n");
	fixupMax(root);
	printf("Ҫ���ҵ��������Ϊ[%d, %d]\n", toBeSearch->key, toBeSearch->high);
	result = intervalSearch(root, toBeSearch);
	if (result != nil)
	{
		printf("���ҵ��ĵ�һ���ص�����Ϊ[%d, %d]\n", result->key, result->high);
	}
	else
	{
		printf("δ�ҵ��ص�����\n");
	}
	result = minIntervalSearch(root, toBeSearch);
	if (result != nil)
	{
		printf("���ҵ��ĵͶ˵���С���ص�����Ϊ[%d, %d]\n", result->key, result->high);
	}
	else
	{
		printf("δ�ҵ��ص�����\n");
	}

	//preorderTraversal(root);
	//printHeight(root);
	//printBlackHeight(root);
	getchar();
}