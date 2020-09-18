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


#define Nil 123432//��ʾ��
#define ElemType int

 /* ���ڹ��������********************************** */
int index = 0;
constexpr int NodeArray[] = { 3,5, 6, Nil, Nil, 2, 7, Nil, Nil, 4 ,Nil, Nil, 1, 0, Nil, Nil, 8, Nil, Nil };
constexpr int NodeArray2[] = { 0 };
typedef struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};

// ���壺���� root Ϊ��������ƽΪ����
class Solution {
public:
	void flatten(TreeNode*root)
	{
		// base case
		if (root == nullptr) return;

		flatten(root->left);
		flatten(root->right);

		/**** �������λ�� ****/
		// 1�����������Ѿ�����ƽ��һ������
		TreeNode* left = root->left;
		TreeNode* right = root->right;

		// 2������������Ϊ������
		root->left = nullptr;
		root->right = left;

		// 3����ԭ�ȵ��������ӵ���ǰ��������ĩ��
		TreeNode* p = root;
		while (p->right != nullptr) {
			p = p->right;
		}
		p->right = right;
	}

	//help���� ����Ա�ڹ����� ��pdf P157
	TreeNode* Conver(TreeNode*head)//ת˫������
	{
		if (!head)
		{
			return head;
		}
		TreeNode *leftE = Conver(head->left);
		TreeNode *rightE = Conver(head->right);
		
		//�������
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
			head->right = head;//Ϊ71-72�д������
			return head;
		}

	}

	//��ǰ������������н���ֵ
/* #��ʾ������������������ʾ������T�� */
	void createBinary(TreeNode**T) {//T=&Binary_Tree *T=Binary_Tree,����ָ�����������BinaryTreeͷָ�뱾���һ��ָ���BinaryTREEͬ�����޷�������BinaryTreeָ��
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
			createBinary(&(*T)->left);/* ���������� */
			createBinary(&(*T)->right);/* ���������� */
		}
	}

};
int main()
{
	TreeNode* Binary_Tree;//����binary tree
	TreeNode* Binary_Tree2;//����binary tree
	Solution test1;
	test1.createBinary(&Binary_Tree);
	index = 0;
	test1.createBinary(&Binary_Tree2);
	test1.flatten(Binary_Tree);
	test1.Conver(Binary_Tree2);
	system("pause");
	return 0;

}