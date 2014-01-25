#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************************************************
* 定义红绿属性和结点数
*********************************************************/
#define RED true
#define BLACK false
#define NUM 1000

/********************************************************
* 结点结构，定义树根和nil结点
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
* 输出一个结点的信息
*********************************************************/
void printCurrentNode(RBNode *t){
	puts("================================");
	printf("当前结点键值为：%d\n", t->key);

	if (t->color)
	{
		printf("颜色为RED\n");
	}
	else
	{
		printf("颜色为BLACK\n");
	}

	if (t->parent != nil)
	{
		printf("他的父结点键值为：%d\n", t->parent->key);
	}
	else
	{
		printf("他的父结点为nil结点\n");
	}

	if (t->left != nil)
	{
		printf("他的左孩子结点键值为：%d\n", t->left->key);
	}
	else
	{
		printf("他的左孩子结点为nil结点\n");
	}

	if (t->right != nil)
	{
		printf("他的右孩子结点键值为：%d\n", t->right->key);
	}
	else
	{
		printf("他的右孩子结点为nil结点\n");
	}

	puts("================================\n");
}

/********************************************************
* 前序遍历树
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
* 左旋函数
*********************************************************/
RBNode* leftRotate(RBNode *root, RBNode *RotateNode){
	RBNode *y = RotateNode->right;				//y设为RotateNode右孩子
	RotateNode->right = y->left;				//y左孩子设为RotateNode右孩子
	if (y->left != nil)							//如果y左孩子不为空
	{
		y->left->parent = RotateNode;			//y左孩子父结点设为RotateNode
	}
	y->parent = RotateNode->parent;				//y的父结点设为RotateNode父结点
	if (RotateNode->parent == nil)				//如果RotateNode的父结点为空
	{
		root = y;								//y即为根节点
	}
	else if(RotateNode == RotateNode->parent->left)		//如果RotateNode为其父结点的左孩子
	{
		RotateNode->parent->left = y;					//将y设为RotateNode父结点的左孩子
	}
	else
	{
		RotateNode->parent->right = y;					//否则设为右孩子
	}		
	y->left = RotateNode;								//RotateNode设为y的左孩子
	RotateNode->parent = y;								//y设为RotateNode的父结点
	return root;

}

/********************************************************
* 右旋函数
*********************************************************/
RBNode* rightRotate(RBNode* root, RBNode *RotateNode)
{
	RBNode *x = RotateNode->left;					//x设为RotateNode的左孩子
	RotateNode->left = x->right;					//x的右孩子设为RotateNode的左孩子
	if (x->right != nil)							//如果x的右孩子不为空
	{
		x->right->parent = RotateNode;				//设置RotateNode为x的右孩子的父亲
	}
	x->parent = RotateNode->parent;					//将x的父结点设为RotateNode的父结点
	if (RotateNode->parent == nil)					//如果RotateNode的父结点为空
	{
		root = x;									//x即为根节点
	}
	else if(RotateNode == RotateNode->parent->left)	//如果RotateNode为其父结点的
	{
		RotateNode->parent->left = x;				//x设为RotateNode父结点的左孩子
	}
	else
	{
		RotateNode->parent->right = x;				//否则设为右孩子
	}
	x->right = RotateNode;							//RotateNode设为x的右孩子
	RotateNode->parent = x;							//RotateNode的父结点设为x
	return root;
}

/********************************************************
* 插入调整函数
*********************************************************/
RBNode* RBInsertFixup(RBNode *root, RBNode *FixupNode){
	RBNode *Uncle;
	while (FixupNode->parent->color == RED)		//如果待调整结点的父结点不为空，且父结点为红，则需要调整
	{
		if (FixupNode->parent == FixupNode->parent->parent->left)		//如果父结点为祖父结点的左孩子
		{
			Uncle = FixupNode->parent->parent->right;					//获取叔结点
			if (Uncle->color == RED)					//如果叔结点不为nil且叔结点为红
			{
				FixupNode->parent->color = BLACK;						//父结点设为黑
				Uncle->color = BLACK;									//叔结点设为黑
				FixupNode->parent->parent->color = RED;					//祖父结点设为红
				FixupNode = FixupNode->parent->parent;					//当前结点设为祖父结点
				continue;
			}
			else														//如果叔结点为黑
			{
				if(FixupNode == FixupNode->parent->right)				//如果当前结点是右孩子
				{
					FixupNode = FixupNode->parent;						//当前结点设为父结点
					root = leftRotate(root, FixupNode);			 		//左旋
				}

				FixupNode->parent->color = BLACK;						//设置父结点为黑
				FixupNode->parent->parent->color = RED;				//祖父结点设为红	
				root = rightRotate(root, FixupNode->parent->parent);	//右旋
			}
		}
		else
		{
			Uncle = FixupNode->parent->parent->left;					//叔结点为祖父结点的左孩子
			if (Uncle->color == RED)					//如果叔结点不为空且颜色为红
			{
				FixupNode->parent->color = BLACK;						//父结点设为黑	
				Uncle->color = BLACK;									//叔结点设为黑
				FixupNode->parent->parent->color = RED;					//祖父结点设为红
				FixupNode = FixupNode->parent->parent;					//当前结点设为祖父结点
				continue;
			}
			else														//如果叔结点为黑
			{
				if(FixupNode == FixupNode->parent->left)				//当前结点为父结点的左孩子
				{
					FixupNode = FixupNode->parent;						//当前结点设为父结点
					root = rightRotate(root, FixupNode);				//右旋
				}

				FixupNode->parent->color = BLACK;						//父结点设为黑
				FixupNode->parent->parent->color = RED;				//祖父结点设为红
				root = leftRotate(root, FixupNode->parent->parent);	//左旋
			}

		}
	}
	root->color = BLACK;
	return root;
}

/********************************************************
* 插入结点函数
*********************************************************/
RBNode* RBInsert(RBNode *root, RBNode *InsertNode){

	RBNode *y = nil;
	RBNode *x = root;
	while (x != nil)	//寻找插入位置
	{
		y = x;	//y记录当前位置父结点位置
		if (InsertNode->key < x->key)	//插入结点key小于当前结点则往左走
		{
			x = x->left;
		}
		else							//大于就往右走
		{
			x = x->right;
		}
	}
	InsertNode->parent = y;				//当前结点父节点设置为y
	if (y == nil)						//如果y结点是nil，则当前结点为root结点
	{
		root = InsertNode;
	}
	else if(InsertNode->key < y->key)	//插入结点key小于y则为y的左孩子
	{
		y->left = InsertNode;
	}
	else								//反之为右孩子
	{
		y->right = InsertNode;
	}

	InsertNode->left = nil;				//设置结点信息
	InsertNode->right = nil;
	InsertNode->color = RED;	
	return RBInsertFixup(root, InsertNode);		//调整当前结点
}

/********************************************************
* 构造树函数，依次插入指定结点数
*********************************************************/
RBNode* buildRBTree(){
	srand((int)time(0));
	root = nil;
	for (int i = 0; i < NUM; i++)
	{
		RBNode *InsertNode = (RBNode*)malloc(sizeof(RBNode));
		InsertNode->key = rand()%1000; 
		root = RBInsert(root, InsertNode);
		//printf("插入key=%d的结点后：\n", InsertNode->key);
		//preorderTraversal(root);
	}
	return root;
}

/********************************************************
* 打印黑高
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
	printf("树的黑高为：%d\n", i);
}

/********************************************************
* 获得树高
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
		return (i>j?i:j)+1;			//返回左右子树中的大者+1
	}
}

/********************************************************
* 打印树高
*********************************************************/
void printHeight(RBNode *root){
	printf("树高为：%d\n", getHeight(root));
}

/********************************************************
* 主函数，初始化nil结点，构造树然后打印树高和黑高
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