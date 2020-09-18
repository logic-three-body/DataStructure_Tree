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


#define Nil 123432//��ʾ��
#define ElemType int

/* ���ڹ��������********************************** */
int index = 0;
constexpr int NodeArray[] = { 3,5, 6, Nil, Nil, 2, 7, Nil, Nil, 4 ,Nil, Nil, 1, 0, Nil, Nil, 8, Nil, Nil };
constexpr int NodeArray2[] = {0};
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
		//���rootΪ�գ��϶��÷���null�����root��������p����q��
		//����˵root����p�ڵ�ɣ����q��������rootΪ�������У���Ȼroot��������������ȣ���ʹq����������rootΪ�������У�
		//������� 3 �Ķ��壬ҲӦ�÷���root�ڵ㡣
		if (root == nullptr) return nullptr;
		if (root == p || root == q) return root;

		TreeNode *left = lowestCommonAncestor(root->left, p, q);//��root���Ѱ��Ŀ�� ������NULL˵��δ�ҵ�
		TreeNode *right = lowestCommonAncestor(root->right, p, q);//��root�Ҳ�Ѱ��Ŀ�� ������NULL˵��δ�ҵ�

		//�൱�ں���

		// ��� 1 ���p��q������rootΪ�������У���ôleft��rightһ���ֱ���p��q���� base case �������ģ�
		if (left != nullptr && right != nullptr) {
			return root;
		}
		// ��� 2 ���p��q��������rootΪ�������У�ֱ�ӷ���null��
		if (left == nullptr && right == nullptr) {
			return nullptr;
		}
		// ��� 3 ���p��qֻ��һ��������rootΪ�������У��������ظýڵ㡣 
		/*
		�൱����̾��룬p�Ѿ��������root���������������q��root��Զ������ν
		*/

		return left == nullptr ? right : left;//���ҽڵ�˭��Ϊ�շ���˭  ������/�ҽڵ�������һ��δ�ҵ���˵��q/p�϶�����һ�ࣨ�ų�����
	
	}
	//��ǰ������������н���ֵ
	/* #��ʾ�������������������ʾ������T�� */
	void createBinary(TreeNode**T) {//T=&Binary_Tree *T=Binary_Tree,����ָ�����������BinaryTreeͷָ�뱾����һ��ָ���BinaryTREEͬ�����޷�������BinaryTreeָ��
		ElemType elem;
		//std::cin>>elem;
		elem = NodeArray[index++];

		if (Nil==elem)
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
			createBinary(&(*T)->left);/* ���������� */
			createBinary(&(*T)->right);/* ���������� */
		}
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
	//TreeNode Node8(NULL);
	//TreeNode Node9(NULL);
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

	TreeNode*Result,*Result2,*Result3,*Result4;
	Result=test.lowestCommonAncestor(Binary_Tree,&Node2,&Node3);
	Result2 = test.lowestCommonAncestor(Binary_Tree, &Node2, &Node4);
	Result3 = test.lowestCommonAncestor(Binary_Tree, &Node10, &Node7);
	Result4 = test.lowestCommonAncestor(Binary_Tree, &Node4, &Node7);
	Result4 = test.lowestCommonAncestor(Binary_Tree, &Node11, &Node5);

	
	TreeNode*binary_tree2=nullptr;
	test.createBinary(&binary_tree2);
	
	system("pause");
}
/*3 5 6 123432 123432 2 7 123432 123432 4 123432 123432 1 0 123432 123432 8 123432 123432*/