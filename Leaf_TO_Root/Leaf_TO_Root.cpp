// CMP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<string>
#include<queue>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 12 /* 存储空间初始分配量 */


typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef char TElemType;
const TElemType Nil = '0'; /* 字符型以空格符为空 */

Status visit(TElemType e)
{
	printf("%c ", e);
	return OK;
}

typedef struct BiTNode  /* 结点结构 */
{
	TElemType data;		/* 结点数据 */
	struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
}BiTNode, *BiTree;


/* 构造空二叉树T */
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

/* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
void DestroyBiTree(BiTree *T)
{
	if (*T)
	{
		if ((*T)->lchild) /* 有左孩子 */
			DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
		if ((*T)->rchild) /* 有右孩子 */
			DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
		free(*T); /* 释放根结点 */
		*T = NULL; /* 空指针赋0 */
	}
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T)
{
	TElemType ch;


	std::cin >> ch;

	if (ch == Nil)
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = ch; /* 生成根结点 */
		CreateBiTree(&(*T)->lchild); /* 构造左子树 */
		CreateBiTree(&(*T)->rchild); /* 构造右子树 */
	}
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(BiTree T)
{
	if (T)
		return FALSE;
	else
		return TRUE;
}

#define ClearBiTree DestroyBiTree

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(BiTree T)
{
	int i, j;
	if (!T)
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);
	else
		j = 0;
	return i > j ? i + 1 : j + 1;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
TElemType Root(BiTree T)
{
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

/* 初始条件: 二叉树T存在，p指向T中某个结点 */
/* 操作结果: 返回p所指结点的值 */
TElemType Value(BiTree p)
{
	return p->data;
}

/* 给p所指结点赋值为value */
void Assign(BiTree p, TElemType value)
{
	p->data = value;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
void PreOrderTraverse(const BiTree& T)
{
	if (T == NULL)
		return;
	printf("%c", T->data);/* 显示结点数据，可以更改为其它对结点操作 */
	PreOrderTraverse(T->lchild); /* 再先序遍历左子树 */
	PreOrderTraverse(T->rchild); /* 最后先序遍历右子树 */
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(const BiTree& T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild); /* 中序遍历左子树 */
	printf("%c", T->data);/* 显示结点数据，可以更改为其它对结点操作 */
	InOrderTraverse(T->rchild); /* 最后中序遍历右子树 */
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(const BiTree& T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild); /* 先后序遍历左子树  */
	PostOrderTraverse(T->rchild); /* 再后序遍历右子树  */
	printf("%c", T->data);/* 显示结点数据，可以更改为其它对结点操作 */
}


void DoubleTraverse(const BiTree& T)
{
	if (T == NULL)
		return;
	printf("%c", T->data);/* 显示结点数据，可以更改为其它对结点操作 */
	DoubleTraverse(T->lchild); /* 先后序遍历左子树  */
	printf("%c", T->data);/* 显示结点数据，可以更改为其它对结点操作 */
	DoubleTraverse(T->rchild); /* 再后序遍历右子树  */
}

Status CMP_TREE(const BiTree& T1, const BiTree& T2)//if Equal
{
	if (!T1 && !T2)//Equal if both are NULL
	{
		return OK;
	}
	else if (!T1 || !T2)//Only One is NULL Not Equal
	{
		return ERROR;
	}
	if (T1->data != T2->data)
	{
		return ERROR;
	}
	int left = 0;//Jud left subTree
	int right = 0;//Jud right subTree
	left = CMP_TREE(T1->lchild, T2->lchild);
	right = CMP_TREE(T1->rchild, T2->rchild);
	return right && left;
}

void ChangeLR(BiTree&T)//交换左右子树
{
	BiTree Temp = nullptr;
	if (!T->lchild || !T->rchild)//左右子树某一个为空
	{
		return;
	}
	else
	{
		Temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = Temp;
	}
	ChangeLR(T->lchild);
	ChangeLR(T->rchild);
}

Status LevelTranverse(const BiTree&T)
{
	if (!T)
	{
		return ERROR;
	}
	int max_width = 0, temp_width = 0;
	std::queue<BiTree> Q;
	if (T != nullptr)
		Q.push(T);//根结点进入队列
	while (!Q.empty())//如果队列不为空，就对里面的节点遍历其左右孩子
	{
		std::cout << Q.front()->data << " ";//遍历对头节点

		///++temp_width;//宽度增加

		if (Q.front()->lchild != nullptr)//如果对头节点有左孩子，将左孩子入队
			Q.push(Q.front()->lchild);

		if (Q.front()->rchild != nullptr)//如果对头节点有右孩子，将右孩子入队
			Q.push(Q.front()->rchild);
		Q.pop();//将已经遍历过的节点出队
		///max_width = max_width > temp_width ? max_width : temp_width;//更新最大值		
	}
	std::cout << std::endl;
	return OK;
}

Status Max_Width(const BiTree&T)//method:LevelTranverse
{
	if (!T)
	{
		return ERROR;
	}
	else
	{
		BiTree Q[MAXSIZE] = { nullptr };//Queue,elements : binary tree ptr 
		int front = 0;
		int rear = 0;
		int last = 0;//TO the most right Node
		int temp_width = 0;
		int max_width = 0;
		Q[rear] = T;//Root push into Que
		while (front <= last)
		{
			BiTree p = Q[front++];
			++temp_width;
			if (p->lchild)
			{
				Q[++rear] = p->lchild;
			}
			if (p->rchild)
			{
				Q[++rear] = p->rchild;
			}
			//循环后rear-1总是最右节点
			//front每次循环均增1，而rear不一定增加，依据是否有子树
			//front>last 情况有 ： rear 多次未增加 >> p 无左/右/左右节点 >> 此时以达到一定上限 
			if (front > last)//最右节点的比较
			{
				last = rear;//last point to next most right node
				max_width = max_width > temp_width ? max_width : temp_width;//update
				temp_width = 0;//update
			}//if
		}//while
		return max_width;
	}
}

Status Longest_Path(const BiTree&T)
{
	if (!T)
	{
		return ERROR;
	}
	BiTree p = T;
	BiTree LongPathStack[MAXSIZE] = { nullptr };
	BiTree Stack[MAXSIZE] = { nullptr };
	int tag[MAXSIZE] = { 0 };
	int top = 0;//栈顶指针
	int longest = 0;
	while (p || top > 0)//沿左分支向下
	{
		while (p)
		{
			Stack[++top] = p;
			tag[top] = 0;
			p = p->lchild;
		}
		if (tag[top] == 1)//当前节点右分支已遍历
		{
			if (!Stack[top]->lchild && !Stack[top]->rchild)//到叶子节点查看路径
			{
				if (top > longest)
				{
					for (int i = 1; i <= top; ++i)
					{
						LongPathStack[i] = Stack[i];
					}
					longest = top;
				}//保留当前最长路径到LongPathStack				
			}
			--top;//退栈
		}
		else if (top > 0)//沿右子树向下
		{
			tag[top] = 1;
			p = Stack[top]->rchild;
		}

	}
	std::cout << longest << std::endl;

	for (int i = 1; i <= longest; i++)
	{

		std::cout << LongPathStack[i]->data;
	}
	std::cout << std::endl;
	return OK;
}

void AllPath(const BiTree&T,int path_len,TElemType* path )//pathlen 初始值 0
{
	if (T)
	{
		//叶子节点
		if (!T->lchild&&!T->rchild)
		{
			//输出路径
			std::cout << T->data;
			for (int i = path_len-1; i>=0; --i)
			{
				std::cout << path[i] ;
			}
			std::cout << std::endl;
		}
		//输出路径
		else
		{
			path[path_len] = T->data; //当前节点进入路径
			++path_len; //路径长度增1
			AllPath(T->lchild, path_len, path);//遍历左子树
			AllPath(T->rchild, path_len, path);//遍历右子树
			--path_len;					//恢复环境
		}

	}
}

int main()
{

	while (true)
	{
		BiTree BTree1;
		InitBiTree(&BTree1);
		CreateBiTree(&BTree1);
		if (!BTree1)//仅输入0
		{
			break;
		}
		TElemType Leaf_to_Root[MAXSIZE];
		AllPath(BTree1, 0, Leaf_to_Root);
	}

	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
