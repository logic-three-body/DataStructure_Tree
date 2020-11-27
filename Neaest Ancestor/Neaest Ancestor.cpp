#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 12 /* 存储空间初始分配量 */
const char Nil = '#';//空

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char TElemType;
typedef struct Node
{
	TElemType data;
	struct Node *lchild, *rchild;
}*TreeLink, Link;

/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(TreeLink &T)
{
	TElemType ch;

	std::cin >> ch;
	if (ch=='0')
	{
		return;
	}
	if (ch == Nil)
		T = NULL;
	else
	{
		T = (TreeLink)malloc(sizeof(Node));
		(T)->data = ch; /* 生成根结点 */
		CreateBiTree((T)->lchild); /* 构造左子树 */
		CreateBiTree((T)->rchild); /* 构造右子树 */
	}
}

TreeLink CheckNode(TreeLink&root,TElemType& D)
{
	if(root)
	{
		if (root->data == D)
		{
			return root;
		}
		TreeLink LRoot = CheckNode(root->lchild, D);
		TreeLink RRoot = CheckNode(root->rchild, D);
		return LRoot == nullptr ? RRoot : LRoot;
	}
	return nullptr;
}


TreeLink lowestCommonAncestor(TreeLink root, TreeLink p, TreeLink q) {
	// 两种情况的 base case
	if (root == nullptr) return nullptr;
	if (root == p || root == q) return root;

	TreeLink left = lowestCommonAncestor(root->lchild, p, q);
	TreeLink right = lowestCommonAncestor(root->rchild, p, q);

	// 情况 1
	if (left != nullptr && right != nullptr) {
		return root;
	}
	// 情况 2
	if (left == nullptr && right == nullptr) {
		return nullptr;
	}
	// 情况 3
	return left == nullptr ? right : left;

}

int main()
{
	while (true)
	{
		TreeLink T = nullptr;
		CreateBiTree(T);
		if (!T)
		{
			break;
		}
		TElemType Son1, Son2;
		std::cin >> Son1 >> Son2;
		TreeLink P = CheckNode(T, Son1);
		TreeLink q = CheckNode(T, Son2);
		TreeLink Ancestor = lowestCommonAncestor(T, P, q);
		std::cout << Ancestor->data << std::endl;
	}
	return 0;

}