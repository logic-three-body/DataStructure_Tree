#pragma once
#include<iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char TElemType;
typedef enum { Link, Thread } PointerTag;	/* Link==0��ʾָ�����Һ���ָ��, */
typedef struct TBNode
{
	TElemType data;	/* ������� */
    TBNode *lchild, *rchild;	/* ���Һ���ָ�� */
	PointerTag LTag=Link;
	PointerTag RTag=Link;		/* ���ұ�־ */
};
class Thread_Binary
{
private:
	TBNode* BiTree;
public:
	// ͨ���б�������������������������Ҫ����	void createInThread();	// ͨ����������Զ������������ĵݹ��㷨��	void InThread(TBNode *, TBNode *&);	//����pΪ�������������������У����������µĵ�һ���ڵ㡣
	TBNode *First(TBNode*);	//�������������������У��ڵ�p�������µĺ�̽ڵ㡣
	TBNode *Next(TBNode*);	//����������������ִ������������㷨
	void Inorder();
};

