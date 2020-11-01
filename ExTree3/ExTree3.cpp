
#include <iostream>
#include <string>
#include <cstring>
#define MAX 1005

using namespace std;
/*************************************************************************************************************
		表达式树：将一个四则运算表达式（含括号）转化成二叉树并计算结果
		创建树(递归)：
		1，找到“最后运算”的运算符（一定为树的根），然后递归创建
		2，利用 p == 0 时找到最右出现的 + - 和 * / 运算符,分别用 c1 c2保存位置
		   p != 0时该操作符一定在括号内，且括号一定不是最后计算，只有 p == 0才考虑当前字符
		3，当 c1 < 0时，说明没有 + - 操作符出现在最右，则需考虑 * /运算符。（c1 = c2）
		   若 c2 也小于 0，说明整个算式最右无 + - * /，即整个算式都在一个大括号内
		   去掉括号递归调用即可 build_tree(x+1,y-1);
		4，递归创建左右子树即可
		5，计算表达式的结果，递归遍历树即可，碰到叶子结点即非操作符结点 return 即可；
		Input:
			a+b
			a+b*(f-a)-d/b
			(a+b*c)
		OutPut:
			3
			9
			7
		PS:这里写的是一个一般化的程序，如果输入数字，将字母改成数字即可
*************************************************************************************************************/
string expression;
int NodeNum;     //结点编号
int lchild[MAX], rchild[MAX];	//左右孩子结点编号
char op[MAX];		//结点的操作字符
int result = 0;		//计算结果

int BuildExpTree(int x, int y) {
	int c1 = -1, c2 = -1, p = 0;
	int u;		//结点编号
	if (y - x == 1) {
		u = ++NodeNum;
		lchild[u] = rchild[u] = 0;
		op[u] = expression[x];
		return u;
	}
	for (int i = x; i < y; i++) {
		if (expression[i] == '(')	p++;
		if (expression[i] == ')')	p--;
		if (!p && (expression[i] == '+' || expression[i] == '-'))
			c1 = i;
		if (!p && (expression[i] == '*' || expression[i] == '/'))
			c2 = i;
	}

	if (c1 < 0 && c2 < 0)		//找不到最后出现的四则运算符号，即整个算式被大括号括着
		return BuildExpTree(x + 1, y - 1);
	if (c1 < 0)		//找不到 + || - 运算，就用 * || / 运算
		c1 = c2;

	u = ++NodeNum;
	lchild[u] = BuildExpTree(x, c1);
	rchild[u] = BuildExpTree(c1 + 1, y);
	op[u] = expression[c1];

	return u;
}

int DFS(int id) {
	if (isdigit(op[id]))	return (int)(op[id] - '0' );

	if (op[id] == '+')
		return DFS(lchild[id]) + DFS(rchild[id]);
	if (op[id] == '-')
		return DFS(lchild[id]) - DFS(rchild[id]);
	if (op[id] == '*')
		return DFS(lchild[id]) * DFS(rchild[id]);
	if (op[id] == '/')
		return DFS(lchild[id]) / DFS(rchild[id]);
}
int main()
{
	while (cin >> expression) {
		if (expression=="=")
		{
			break;
		}

		NodeNum = 0;     //每次重置结点编号从0开始

		int length = expression.size();
		BuildExpTree(0, length-1);
		/*for(int i = 1;i <= nc;i ++)       //可利用输出查看树的构建情况，包括根节点，左右孩子结点
			cout<<"op: "<<op[i]<<"  lch: "<<lch[i]<<"  rch: "<<rch[i]<<endl;*/
		result = DFS(1);
		cout << result << endl;
	}
	return 0;
}