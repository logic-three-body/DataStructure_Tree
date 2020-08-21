#pragma once
#include<iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char TElemType;
typedef enum { Link, Thread } PointerTag;	/* Link==0表示指向左右孩子指针, */
typedef struct TBNode
{
	TElemType data;	/* 结点数据 */
    TBNode *lchild, *rchild;	/* 左右孩子指针 */
	PointerTag LTag=Link;
	PointerTag RTag=Link;		/* 左右标志 */
};
class Thread_Binary
{
private:
	TBNode* BiTree;
public:
	// 通过中遍历建立中序线索二叉树的主要程序	void createInThread();	// 通过中序遍历对二叉树线索化的递归算法：	void InThread(TBNode *, TBNode *&);	//求以p为根的中序线索二叉树中，中序序列下的第一个节点。
	TBNode *First(TBNode*);	//求在中序线索二叉树中，节点p在中序下的后继节点。
	TBNode *Next(TBNode*);	//中序线索二叉树上执行中序遍历的算法
	void Inorder();
};

