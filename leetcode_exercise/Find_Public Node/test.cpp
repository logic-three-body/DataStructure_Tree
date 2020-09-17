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

typedef struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};

/*
��� 1�����p��q������rootΪ�������У���ôleft��rightһ���ֱ���p��q���� base case �������ģ���

��� 2�����p��q��������rootΪ�������У�ֱ�ӷ���null��

��� 3�����p��qֻ��һ��������rootΪ�������У��������ظýڵ㡣
*/

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// ��������� base case
		if (root == nullptr) return nullptr;
		if (root == p || root == q) return root;

		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);

		// ��� 1
		if (left != nullptr && right != nullptr) {
			return root;
		}
		// ��� 2
		if (left == nullptr && right == nullptr) {
			return nullptr;
		}
		// ��� 3
		return left == nullptr ? right : left;
	
	}
};

int main()
{
	Solution test;
	TreeNode* Binary_Tree;//����binary tree
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
	system("pause");


}
