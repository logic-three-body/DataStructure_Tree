#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
	int weight;
	struct Node *lchild, *rchild;
	struct Node *next;
}*TreeLink, Link; 
TreeLink creatTree(int n);
void preord(TreeLink link);
TreeLink creatHuffman(TreeLink link);
int WPLD(TreeLink T);
void WPL_PreOrder(TreeLink T, int deep, int &wpl);
TreeLink creatTree(int n)//通过输入的叶子信息，生成一个递增的链表，为哈夫曼树的生成做好准备
{
	if (n <= 1) printf("警告！不能生产哈夫曼树\n");
	TreeLink link = (TreeLink)malloc(sizeof(Link));
	link->lchild = link->rchild = link->next = NULL;
	int i;
	TreeLink s = (TreeLink)malloc(sizeof(Link));
	s->lchild = s->rchild = s->next = NULL;
	printf("请输入第1个权值：\n");
	scanf("%d", &s->weight);
	link->next = s;
	for (i = 2; i <= n; i++)
	{
		s = (TreeLink)malloc(sizeof(Link));
		s->lchild = s->rchild = s->next = NULL;
		printf("请输入第%d个权值：\n", i);
		scanf("%d", &s->weight);
		TreeLink p = link;
		TreeLink q = link->next;
		while (q != NULL)
		{
			if (s->weight < q->weight)
			{
				s->next = q;
				p->next = s;
				break;
			}
			else
			{
				p = q;
				q = q->next;
			}
			if (q == NULL) p->next = s;
		}

	}
	return link;

}
TreeLink creatHuffman(TreeLink link)//将准备好的链表进行合并与生成，转化为哈夫曼树
{
	TreeLink p = NULL, q = NULL, s = NULL;
	int flag = 0;
	while (flag == 0)
	{
		p = link->next;
		q = p->next;
		if (q->next != NULL)
		{
			link->next = q->next;
		}
		else
		{
			flag = 1;
			link->next = NULL;
		}
		s = (TreeLink)malloc(sizeof(Link));
		s->weight = p->weight + q->weight;
		s->lchild = p;
		s->rchild = q;
		s->next = NULL;
		p = link;
		q = p->next;
		while (q != NULL)
		{
			if (s->weight <= q->weight)
			{
				s->next = q;
				p->next = s;
				break;
			}
			else
			{
				p = q;
				q = q->next;
			}
			if (q == NULL)
			{
				p->next = s;
			}
		}
	}
	free(link);
	return s;

}
void preord(TreeLink link)//先序遍历二叉树，作为观测函数
{
	if (link)
	{
		printf("当前节点权值为：%d\n", link->weight);
		preord(link->lchild);
		preord(link->rchild);
	}

}
int WPLD(TreeLink T)//打印WPL值
{
	int wpl = 0;
	WPL_PreOrder(T, 0, wpl);
	printf("WPL值是：%d\n", wpl);
	return wpl;
}
void WPL_PreOrder(TreeLink T, int deep, int &wpl)//核心部分
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
int main()//主函数
{
	int k;
	printf("请输入需要几个叶子：");
	scanf("%d", &k);
	TreeLink L = creatTree(k);
	L = creatHuffman(L);
	preord(L);
	WPLD(L);
	return 0;
}