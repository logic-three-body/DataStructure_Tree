#include"Thread_Binary.h"
Status visit(TElemType e)
{
	printf("%c ", e);
	return OK;
}

Thread_Binary::Thread_Binary()
{
	std::cout << "输入字符串,#代表空" << std::endl;
	CreateBiThrTree(&BiTree_root);
	createInThread();
}

Status Thread_Binary::CreateBiThrTree(TBNode **T)
{
	TElemType h;
	std::cin.get(h);

	if (h == Nil)
		*T = nullptr;
	else
	{
		*T = new TBNode;
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = h; /* 生成根结点(前序) */
		CreateBiThrTree(&(*T)->lchild); /* 递归构造左子树 */
		if ((*T)->lchild) /* 有左孩子 */
			(*T)->LTag = Link;
		CreateBiThrTree(&(*T)->rchild); /* 递归构造右子树 */
		if ((*T)->rchild) /* 有右孩子 */
			(*T)->RTag = Link;
	}
	return OK;
}

void Thread_Binary::createInThread()
{
	TBNode*p = BiTree_root;
	TBNode*pre = BiTree_root;//前驱节点指针
	InThread(p, pre);
	pre->rchild = BiTree_root;//非空二叉树线索化
	pre->RTag = Thread;//处理中序最后一个节点
}

void Thread_Binary::InThread(TBNode *p, TBNode *&pre)//*&pre,代表直接作用在pre的地址，表明pre不是每次都变的指针变量
{
	if (p)
	{
		if (nullptr != p)
		{
			InThread(p->lchild, pre); //递归，左子树线索化
		}
		if (nullptr == p->lchild)
		{
			// 前驱线索 
			p->lchild = pre;
			p->LTag = Thread;
		}
		if (pre != nullptr&nullptr == pre->rchild)
		{
			//建立前驱节点的后继线索
			pre->rchild = p;
			pre->RTag = Thread;
		}

		pre = p;//pre指向当前的p，作为p将要指向的下一个节点的前驱节点提示指针
		InThread(p->rchild, pre);
	}

}

TBNode * Thread_Binary::First(TBNode *p)
{
	while (p->LTag == Link)//表示有左孩子（左孩子不为空）
	{
		return First(p->rchild);
	}

	return p;
}

TBNode * Thread_Binary::Next(TBNode *p)
{
	if (p->RTag == Link) //表示有右孩子（右孩子不为空）
	{
		return First(p->rchild);
	}
	else
	{
		return p->rchild; //rtag==1,直接返回后继线索
	}

}

void Thread_Binary::Inorder()
{
	for (TBNode *p = First(BiTree_root); p != nullptr; p = Next(p))
	{
		std::cout << p->data<<" ";
	}
	std::cout << std::endl;

}

/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status Thread_Binary::InOrderTraverse_Thr()
{
	TBNode* p;
	p = BiTree_root; /* p指向根结点 */
	while (p != BiTree_root)
	{ /* 空树或遍历结束时,p==T */
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data)) /* 访问其左子树为空的结点 */
			return ERROR;
		while (p->RTag == Thread && p->rchild != BiTree_root)
		{
			p = p->rchild;
			visit(p->data); /* 访问后继结点 */
		}
		p = p->rchild;
	}
	return OK;
}
