/* 二叉树 - 根据嵌套括号表示法的字符串生成链式存储的二叉树 */

#include <iostream>
#include <malloc.h>
#include<string>
using namespace std;
const int MaxSize = 50;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 12 /* 存储空间初始分配量 */
const char Nil = '0';//空

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char TElemType;
typedef char ElementType;        //typedef用来给数据类型char起别名(ElementType)
typedef struct bitnode
{
	ElementType data;
	struct bitnode *left, *right;
} bitnode, *bitree;              //bitree为指向bitnode这种自定义数据的指针 


//函数声明 
void CreateTree(bitree &b, char str[]);                //根据嵌套括号表示法的字符串生成链式存储的二叉树
void PrinTree(bitree b);                           //以嵌套括号表示法输出一棵树 
bitree FreeTree(bitree b);                         //释放空间 

//根据嵌套括号表示法的字符串生成链式存储的二叉树
void CreateTree(bitree &b, char str[])
{
	char ch;
	bitree stack[MaxSize], p=nullptr;               //stack[MaxSize]为指针数组，其每一个元素都为指向bitnode这种结构的指针，p为临时指针
	int top = -1, k, j = 0;                   //top为栈顶指针、k决定谁是左、右孩子、j为str指针

	while ((ch = str[j++]) != '\0')
	{
		switch (ch)
		{
		case '(':
			top++;
			stack[top] = p;           //根节点入栈 
			k = 1;                    //1为左孩子 
			break;
		case ',':
			k = 2;                   //2为右孩子 
			break;
		case ')':
			top--;                  //根节点出栈 
			break;
		default:
			p = (bitree)malloc(sizeof(bitnode));
			p->data = ch;
			p->left = p->right = NULL;

			if (b == NULL)        //树为空时 
				b = p;
			else                   //树非空时 
			{
				switch (k)
				{
				case 1:
					stack[top]->left = p;           //根节点的左孩子 
					break;
				case 2:
					stack[top]->right = p;          //根节点的右孩子 
					break;
				}
			}
		}
	}
}
void CreateBiTree(bitree &T)
{
	TElemType ch;

	std::cin >> ch;

	if (ch == Nil)
		T = NULL;
	else
	{
		T = (bitree)malloc(sizeof(bitnode));
		(T)->data = ch; /* 生成根结点 */
		CreateBiTree((T)->left); /* 构造左子树 */
		CreateBiTree((T)->right); /* 构造右子树 */
	}
}

//以嵌套括号表示法输出一棵二叉树 
void PrinTree(bitree b)
{
	if (b)
	{
		cout << b->data;              //访问根节点 
		if (b->left != NULL || b->right != NULL)
		{
			cout << "(";
			PrinTree(b->left);        //递归处理左子树 
			if (b->right != NULL)
				cout << ",";
			PrinTree(b->right);       //递归处理右子树 
			cout << ")";
		}
	}
}

void PrinTree2(bitree b)
{
	if (b)
	{
		cout << b->data;              //访问根节点 
		if (b->left != NULL || b->right != NULL)
		{
			cout << "(";
			PrinTree2(b->left);        //递归处理左子树 
			//if (b->right == NULL)
				cout << ",";
			PrinTree2(b->right);       //递归处理右子树 
			cout << ")";
		}
	}
}

bitree FreeTree(bitree b)
{
	if (b != NULL)
	{
		FreeTree(b->left);        //递归释放左子树 
		FreeTree(b->right);       //递归释放右子树 

		free(b);               //释放根节点 
		b = NULL;              //释放指向根节点的指针 
	}

	return b;                   //return NULL;
}

int main()
{

	//char str[] = "a(b(c),d(e(,f),g))";
	//bitree root = NULL;            //不要忘记初始化 

	//CreateTree(root, str);

	//cout << "str字符串：" << str << endl;
	//cout << "嵌套表示法：";
	//PrinTree(root);
	//cout << endl;

	//root = FreeTree(root);
	//if (root == NULL)
	//	cout << "释放成功" << endl;

	//std::string inp = "";
	//std::cin >> inp;
	while (true)
	{
		bitree root = nullptr;
		//CreateTree(root, inp.c_str);
		CreateBiTree(root);
		if (!root)
		{
			return 0;
		}

		PrinTree2(root);
		cout << endl;
	}




	return 0;
}

//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
