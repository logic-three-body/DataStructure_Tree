// WPL2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 12 /* 存储空间初始分配量 */
const int Nil = 0;//空

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int TElemType;
typedef struct Node
{
	int weight;
	struct Node *lchild, *rchild;
}*TreeLink, Link;

/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(TreeLink &T)
{
	TElemType ch;

	std::cin >> ch;

	if (ch == Nil)
		T = NULL;
	else
	{
		T = (TreeLink)malloc(sizeof(Node));
		(T)->weight = ch; /* 生成根结点 */
		CreateBiTree((T)->lchild); /* 构造左子树 */
		CreateBiTree((T)->rchild); /* 构造右子树 */
	}
}
void WPL_PreOrder(TreeLink& T, int deep, int &wpl)
{
	if (T->lchild == NULL && T->rchild == NULL)
	{
		wpl += deep * (T->weight);
		return;
	}
	if (T->lchild)
	{
		deep++;
		WPL_PreOrder(T->lchild, deep, wpl);
		deep--;
	}
	if (T->rchild)
	{
		deep++;
		WPL_PreOrder(T->rchild, deep, wpl);
		deep--;
	}

}
int WPLrec(TreeLink& lbt, int n)
{
	int wpl = 0;
	if (lbt != NULL)
	{
		if (lbt->lchild == NULL && lbt->rchild == NULL)
			wpl += n * lbt->weight;
		wpl += WPLrec(lbt->lchild, n + 1);
		wpl += WPLrec(lbt->rchild, n + 1);
	}
	return wpl;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(TreeLink& T)
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

int main()
{
	while (true)
	{
		TreeLink Bitree = nullptr;
		CreateBiTree(Bitree);
		if (!Bitree)
		{
			break;
		}
		int deep = BiTreeDepth(Bitree);
		int WPL = WPLrec(Bitree, 0 );
		std::cout << WPL << std::endl;
	}

	//WPL_PreOrder(Bitree, deep, WPL);
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
