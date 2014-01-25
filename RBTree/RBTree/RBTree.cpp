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
	bool color;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
}RBNode;
RBNode *nil;
RBNode *root;

/********************************************************
* ���һ��������Ϣ
*********************************************************/
void printCurrentNode(RBNode *t){
	puts("================================");
	printf("��ǰ����ֵΪ��%d\n", t->key);

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
* ǰ�������
*********************************************************/
void preorderTraversal(RBNode *t){
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
RBNode* leftRotate(RBNode *root, RBNode *RotateNode){
	RBNode *y = RotateNode->right;				//y��ΪRotateNode�Һ���
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
RBNode* rightRotate(RBNode* root, RBNode *RotateNode)
{
	RBNode *x = RotateNode->left;					//x��ΪRotateNode������
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
RBNode* RBInsertFixup(RBNode *root, RBNode *FixupNode){
	RBNode *Uncle;
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
RBNode* RBInsert(RBNode *root, RBNode *InsertNode){

	RBNode *y = nil;
	RBNode *x = root;
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
	return RBInsertFixup(root, InsertNode);		//������ǰ���
}

/********************************************************
* ���������������β���ָ�������
*********************************************************/
RBNode* buildRBTree(){
	srand((int)time(0));
	root = nil;
	for (int i = 0; i < NUM; i++)
	{
		RBNode *InsertNode = (RBNode*)malloc(sizeof(RBNode));
		InsertNode->key = rand()%1000; 
		root = RBInsert(root, InsertNode);
		//printf("����key=%d�Ľ���\n", InsertNode->key);
		//preorderTraversal(root);
	}
	return root;
}

/********************************************************
* ��ӡ�ڸ�
*********************************************************/
void printBlackHeight(RBNode *root){
	int i = 1;
	RBNode *x = root;
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
int getHeight(RBNode *root){
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
void printHeight(RBNode *root){
	printf("����Ϊ��%d\n", getHeight(root));
}

/********************************************************
* ����������ʼ��nil��㣬������Ȼ���ӡ���ߺͺڸ�
*********************************************************/
int main(){
	nil = (RBNode*)malloc(sizeof(RBNode));
	nil->key = -1;
	nil->color = BLACK;
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	root = buildRBTree();
	printHeight(root);
	printBlackHeight(root);
	getchar();
}