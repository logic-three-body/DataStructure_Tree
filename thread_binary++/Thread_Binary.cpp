#include "Thread_Binary.h"

void Thread_Binary::createInThread()
{
	TBNode*pre = nullptr;//前驱节点指针
	InThread(BiTree, pre);
	pre->rchild = nullptr;//非空二叉树线索化
	pre->RTag = Thread;//处理中序最后一个节点

}

void Thread_Binary::InThread(TBNode *p, TBNode *&pre)
{
	if (nullptr!=p)
	{
		InThread(p->lchild, pre); //递归，左子树线索化
	}
	if (nullptr==p->lchild)
	{
		// 前驱线索 
		p->lchild = pre;
		p->LTag = Thread;
	}
	if (pre!=nullptr&nullptr==pre->rchild)
	{
		//建立前驱节点的后继线索
		pre->rchild = p;
		pre->RTag = Thread;
	}

	pre = p;//pre指向当前的p，作为p将要指向的下一个节点的前驱节点提示指针
	InThread(p->rchild, pre);
}

TBNode * Thread_Binary::First(TBNode *p)
{
	while (p->LTag == Link)//表示有左孩子（左孩子不为空）	{		return First(p->rchild);	}
	return p;
}

TBNode * Thread_Binary::Next(TBNode *p)
{
	if (p->RTag == Link) //表示有右孩子（右孩子不为空）	{		return First(p->rchild);	}	else	{		return p->rchild; //rtag==1,直接返回后继线索	}
}

void Thread_Binary::Inorder()
{
	for (TBNode *p = First(BiTree); p != nullptr; p = Next(p))	{
		std::cout << p->data<<" ";
	}
	std::cout << std::endl;
}
