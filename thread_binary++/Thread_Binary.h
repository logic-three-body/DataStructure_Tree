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
const TElemType Nil = '#'; /* �ַ����Կո��Ϊ�� */
typedef struct TBNode
{
	TElemType data;	/* ������� */
    TBNode *lchild, *rchild;	/* ���Һ���ָ�� */
	PointerTag LTag;
	PointerTag RTag;		/* ���ұ�־ */
};
class Thread_Binary
{
private:
	TBNode* BiTree_root;
public:
	/* ��ǰ����������������н���ֵ,�������������T */
 /* 0(����)/�ո�(�ַ���)��ʾ�ս�� */
	Thread_Binary();
	Status CreateBiThrTree(TBNode**);
	// ͨ���б�������������������������Ҫ����
	void createInThread();
	// ͨ����������Զ������������ĵݹ��㷨��
	void InThread(TBNode *, TBNode *&);
	/* �����������������T(ͷ���)�ķǵݹ��㷨 */
	Status InOrderTraverse_Thr();


 /*https://zhuanlan.zhihu.com/p/134184036*/	
	  //����pΪ�������������������У����������µĵ�һ���ڵ㡣
	TBNode *First(TBNode*);//����
	//�������������������У��ڵ�p�������µĺ�̽ڵ㡣
	TBNode *Next(TBNode*);//����
	//����������������ִ������������㷨
	void InorderShow();//����


};

