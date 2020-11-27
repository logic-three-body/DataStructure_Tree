// WPL2.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//


#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 12 /* �洢�ռ��ʼ������ */
const int Nil = 0;//��

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int TElemType;
typedef struct Node
{
	int weight;
	struct Node *lchild, *rchild;
}*TreeLink, Link;

/* #��ʾ������������������ʾ������T�� */
void CreateBiTree(TreeLink &T)
{
	TElemType ch;

	std::cin >> ch;

	if (ch == Nil)
		T = NULL;
	else
	{
		T = (TreeLink)malloc(sizeof(Node));
		(T)->weight = ch; /* ���ɸ���� */
		CreateBiTree((T)->lchild); /* ���������� */
		CreateBiTree((T)->rchild); /* ���������� */
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

/* ��ʼ����: ������T���ڡ��������: ����T����� */
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

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
