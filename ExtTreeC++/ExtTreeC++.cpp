#include <iostream>
#include <stack>
#include<string>//后序遍历：样本：(4+5)*9->45+9*->81
//用来表示二叉树
struct treenode {
	char data;//由于表达式中有数字字每，所以这里用一个字节来表达
	treenode* left;//左结点
	treenode* right;//右结点
	treenode(int value) :data(value), left(nullptr), right(nullptr) {}
};

class BET {
	treenode* root;
public:
	BET() : root(nullptr) {}
	//解析表达式为树形结构
	void parse(const char exp[]) {
		const char* p = exp;
		std::stack<treenode*> s;
		while (*p != '\0') {
			if (*p=='=')
			{
				++p;
				continue;
			}
			if (*p >= '0' && *p <= '9') {
				s.push(new treenode(*p));
			}
			else {
				treenode* new_node = new treenode(*p);
				new_node->right = s.top();
				s.pop();
				new_node->left = s.top();
				s.pop();
				s.push(new_node);
			}
			p++;
		}
		if (s.size() != 1) {
			std::cout << "Illegal Expression:";
			root = nullptr;
		}
		else {
			root = s.top();
		}
	}

	//求值
	int evaluate() {
		if (root == nullptr)
			return std::numeric_limits<int>::max();
		return evaluate(root);
	}
private:
	int evaluate(treenode* node) {
		switch (node->data) {
		case '-': return evaluate(node->left) - evaluate(node->right);
		case '+': return evaluate(node->left) + evaluate(node->right);
		case '*': return evaluate(node->left) * evaluate(node->right);
		default: return node->data - '0';
		}
	}
};

int main()
{
	BET T;
	char  expression[100];
	while (std::cin>>expression)
	{
		if (expression[0]=='0')
		{
			break;
		}
			T.parse(expression);
			std::cout<<T.evaluate()<<std::endl;
	}
	
}