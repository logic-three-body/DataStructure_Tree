#include "Thread_Binary.h"

void Thread_Binary::createInThread()
{
	TBNode*pre = nullptr;//ǰ���ڵ�ָ��
	InThread(BiTree, pre);
	pre->rchild = nullptr;//�ǿն�����������
	pre->RTag = Thread;//�����������һ���ڵ�

}

void Thread_Binary::InThread(TBNode *p, TBNode *&pre)
{
	if (nullptr!=p)
	{
		InThread(p->lchild, pre); //�ݹ飬������������
	}
	if (nullptr==p->lchild)
	{
		// ǰ������ 
		p->lchild = pre;
		p->LTag = Thread;
	}
	if (pre!=nullptr&nullptr==pre->rchild)
	{
		//����ǰ���ڵ�ĺ������
		pre->rchild = p;
		pre->RTag = Thread;
	}

	pre = p;//preָ��ǰ��p����Ϊp��Ҫָ�����һ���ڵ��ǰ���ڵ���ʾָ��
	InThread(p->rchild, pre);
}

TBNode * Thread_Binary::First(TBNode *p)
{
	while (p->LTag == Link)//��ʾ�����ӣ����Ӳ�Ϊ�գ�	{		return First(p->rchild);	}
	return p;
}

TBNode * Thread_Binary::Next(TBNode *p)
{
	if (p->RTag == Link) //��ʾ���Һ��ӣ��Һ��Ӳ�Ϊ�գ�	{		return First(p->rchild);	}	else	{		return p->rchild; //rtag==1,ֱ�ӷ��غ������	}
}

void Thread_Binary::Inorder()
{
	for (TBNode *p = First(BiTree); p != nullptr; p = Next(p))	{
		std::cout << p->data<<" ";
	}
	std::cout << std::endl;
}
