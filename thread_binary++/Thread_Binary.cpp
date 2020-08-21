#include"Thread_Binary.h"
Status visit(TElemType e)
{
	printf("%c ", e);
	return OK;
}

Thread_Binary::Thread_Binary()
{
	std::cout << "�����ַ���,#�����" << std::endl;
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
		(*T)->data = h; /* ���ɸ����(ǰ��) */
		CreateBiThrTree(&(*T)->lchild); /* �ݹ鹹�������� */
		if ((*T)->lchild) /* ������ */
			(*T)->LTag = Link;
		CreateBiThrTree(&(*T)->rchild); /* �ݹ鹹�������� */
		if ((*T)->rchild) /* ���Һ��� */
			(*T)->RTag = Link;
	}
	return OK;
}

void Thread_Binary::createInThread()
{
	TBNode*p = BiTree_root;
	TBNode*pre = BiTree_root;//ǰ���ڵ�ָ��
	InThread(p, pre);
	pre->rchild = BiTree_root;//�ǿն�����������
	pre->RTag = Thread;//�����������һ���ڵ�
}

void Thread_Binary::InThread(TBNode *p, TBNode *&pre)//*&pre,����ֱ��������pre�ĵ�ַ������pre����ÿ�ζ����ָ�����
{
	if (p)
	{
		if (nullptr != p)
		{
			InThread(p->lchild, pre); //�ݹ飬������������
		}
		if (nullptr == p->lchild)
		{
			// ǰ������ 
			p->lchild = pre;
			p->LTag = Thread;
		}
		if (pre != nullptr&nullptr == pre->rchild)
		{
			//����ǰ���ڵ�ĺ������
			pre->rchild = p;
			pre->RTag = Thread;
		}

		pre = p;//preָ��ǰ��p����Ϊp��Ҫָ�����һ���ڵ��ǰ���ڵ���ʾָ��
		InThread(p->rchild, pre);
	}

}

TBNode * Thread_Binary::First(TBNode *p)
{
	while (p->LTag == Link)//��ʾ�����ӣ����Ӳ�Ϊ�գ�
	{
		return First(p->rchild);
	}

	return p;
}

TBNode * Thread_Binary::Next(TBNode *p)
{
	if (p->RTag == Link) //��ʾ���Һ��ӣ��Һ��Ӳ�Ϊ�գ�
	{
		return First(p->rchild);
	}
	else
	{
		return p->rchild; //rtag==1,ֱ�ӷ��غ������
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

/* �����������������T(ͷ���)�ķǵݹ��㷨 */
Status Thread_Binary::InOrderTraverse_Thr()
{
	TBNode* p;
	p = BiTree_root; /* pָ������ */
	while (p != BiTree_root)
	{ /* �������������ʱ,p==T */
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data)) /* ������������Ϊ�յĽ�� */
			return ERROR;
		while (p->RTag == Thread && p->rchild != BiTree_root)
		{
			p = p->rchild;
			visit(p->data); /* ���ʺ�̽�� */
		}
		p = p->rchild;
	}
	return OK;
}
