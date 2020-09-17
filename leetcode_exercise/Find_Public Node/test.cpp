#include<iostream>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Help:https://mp.weixin.qq.com/s?__biz=MzAxODQxMDM0Mw==&mid=2247485561&idx=1&sn=a394ba978283819da1eb34a256f6915b&chksm=9bd7f671aca07f6722f0bc1e946ca771a0a40fd8173cc1227a7e0eabfe4e2fcc57b9ba464547&scene=21#wechat_redirect

*/


#define Nil 123432//表示空
#define ElemType int

/* 用于构造二叉树********************************** */
int index = 0;
constexpr int NodeArray[] = { 3,5, 6, Nil, Nil, 2, 7, Nil, Nil, 4 ,Nil, Nil, 1, 0, Nil, Nil, 8, Nil, Nil };
typedef struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};

/*
情况 1，如果p和q都在以root为根的树中，那么left和right一定分别是p和q（从 base case 看出来的）。

情况 2，如果p和q都不在以root为根的树中，直接返回null。

情况 3，如果p和q只有一个存在于root为根的树中，函数返回该节点。
*/

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// 两种情况的 base case
		if (root == nullptr) return nullptr;
		if (root == p || root == q) return root;

		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);

		//相当于后序

		// 情况 1
		if (left != nullptr && right != nullptr) {
			return root;
		}
		// 情况 2
		if (left == nullptr && right == nullptr) {
			return nullptr;
		}
		// 情况 3
		return left == nullptr ? right : left;
	
	}
	//按前序输入二叉树中结点的值
	/* #表示空树，构造二叉链表表示二叉树T。 */
	void createBinary(TreeNode*T) {
		ElemType elem;
		//std::cin>>elem;
		elem = NodeArray[index++];

		if (Nil==elem)
		{
			T = nullptr;
		}
		else
		{
			T = new TreeNode(elem);
			if (!T)
			{
				exit(OVERFLOW);
			}
			createBinary(T->left);/* 构造左子树 */
			createBinary(T->right);/* 构造右子树 */
		}
	}
};

int main()
{
	Solution test;
	TreeNode* Binary_Tree;//构造binary tree
	TreeNode Node1(3);
	TreeNode Node2(5);
	TreeNode Node3(1);
	TreeNode Node4(6);
	TreeNode Node5(2);
	TreeNode Node6(0);
	TreeNode Node7(8);
	TreeNode Node8(NULL);
	TreeNode Node9(NULL);
	TreeNode Node10(7);
	TreeNode Node11(4);
	Binary_Tree = &Node1;
	Node1.left = &Node2;
	Node1.right = &Node3;
	Node2.left = &Node4;
	Node2.right = &Node5;
	Node5.left = &Node10;
	Node5.right = &Node11;
	Node3.left = &Node6;
	Node3.right = &Node7;

	TreeNode*Result;
	Result=test.lowestCommonAncestor(Binary_Tree,&Node2,&Node3);

	TreeNode*binary_tree2=nullptr;
	test.createBinary(binary_tree2);
	
	system("pause");
}
/*3 5 6 123432 123432 2 7 123432 123432 4 123432 123432 1 0 123432 123432 8 123432 123432*/