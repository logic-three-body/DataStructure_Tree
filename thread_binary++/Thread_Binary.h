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
const TElemType Nil = '#'; /* 字符型以空格符为空 */
typedef struct TBNode
{
	TElemType data;	/* 结点数据 */
    TBNode *lchild, *rchild;	/* 左右孩子指针 */
	PointerTag LTag;
	PointerTag RTag;		/* 左右标志 */
};
class Thread_Binary
{
private:
	TBNode* BiTree_root;
public:
	/* 按前序输入二叉线索树中结点的值,构造二叉线索树T */
 /* 0(整型)/空格(字符型)表示空结点 */
	Thread_Binary();
	Status CreateBiThrTree(TBNode**);
	// 通过中遍历建立中序线索二叉树的主要程序
	void createInThread();
	// 通过中序遍历对二叉树线索化的递归算法：
	void InThread(TBNode *, TBNode *&);
	/* 中序遍历二叉线索树T(头结点)的非递归算法 */
	Status InOrderTraverse_Thr();


 /*https://zhuanlan.zhihu.com/p/134184036*/	
	  //求以p为根的中序线索二叉树中，中序序列下的第一个节点。
	TBNode *First(TBNode*);//存疑
	//求在中序线索二叉树中，节点p在中序下的后继节点。
	TBNode *Next(TBNode*);//存疑
	//中序线索二叉树上执行中序遍历的算法
	void InorderShow();//存疑


};

