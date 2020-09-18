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
 Help:https://mp.weixin.qq.com/s/izZ5uiWzTagagJec6Y7RvQ

 */


#define Nil 123432//表示空
#define ElemType int

 /* 用于构造二叉树********************************** */
int index = 0;
constexpr int NodeArray[] = { 3,5, 6, Nil, Nil, 2, 7, Nil, Nil, 4 ,Nil, Nil, 1, 0, Nil, Nil, 8, Nil, Nil };
constexpr int NodeArray2[] = { 0 };
typedef struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};

// 定义：将以 root 为根的树拉平为链表
class Solution {
public:
	void flatten(TreeNode*root)
	{
		// base case
		if (root == nullptr) return;

		flatten(root->left);
		flatten(root->right);

		/**** 后序遍历位置 ****/
		// 1、左右子树已经被拉平成一条链表
		TreeNode* left = root->left;
		TreeNode* right = root->right;

		// 2、将左子树作为右子树
		root->left = nullptr;
		root->right = left;

		// 3、将原先的右子树接到当前右子树的末端
		TreeNode* p = root;
		while (p->right != nullptr) {
			p = p->right;
		}
		p->right = right;
	}

	//help：《 程序员内功修炼 》pdf P157
	TreeNode* Conver(TreeNode*head)//转双向链表
	{
		if (!head)
		{
			return head;
		}
		TreeNode *leftE = Conver(head->left);
		TreeNode *rightE = Conver(head->right);
		
		//后序遍历
		TreeNode*leftB = leftE != nullptr ? leftE->right : nullptr;
		TreeNode*rightB = rightE != nullptr ? rightE->right : nullptr;

		if (leftE&&rightE)
		{
			leftE->right = head;//next
			head->left = leftE;//last
			head->right = rightB;
			rightB->left = head;//next
			rightE->right = leftB;//last
			return rightE;
		}
		else if (leftE)
		{
			leftE->right = head;
			head->left = leftE;
			head->right = leftB;
			return head;
		}
		else if (rightE)
		{
			head->right = rightB;
			rightB->left = head;
			rightE->right = head;
			return rightE;
		}
		else
		{
			head->right = head;//为71-72行代码服务
			return head;
		}

	}

	//按前序输入二叉树中结点的值
/* #表示空树，构造二叉链表表示二叉树T。 */
	void createBinary(TreeNode**T) {//T=&Binary_Tree *T=Binary_Tree,二级指针可以作用于BinaryTree头指针本身而一级指针和BinaryTREE同级，无法作用于BinaryTree指针
		ElemType elem;
		//std::cin>>elem;
		elem = NodeArray[index++];

		if (Nil == elem)
		{
			*T = nullptr;
		}
		else
		{
			*T = new TreeNode(elem);
			if (!*T)
			{
				exit(OVERFLOW);
			}
			createBinary(&(*T)->left);/* 构造左子树 */
			createBinary(&(*T)->right);/* 构造右子树 */
		}
	}

};
int main()
{
	TreeNode* Binary_Tree;//构造binary tree
	TreeNode* Binary_Tree2;//构造binary tree
	Solution test1;
	test1.createBinary(&Binary_Tree);
	index = 0;
	test1.createBinary(&Binary_Tree2);
	test1.flatten(Binary_Tree);
	test1.Conver(Binary_Tree2);
	system("pause");
	return 0;

}