#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

/*

https://blog.csdn.net/wyyzsl212328/article/details/8216536 C/C++ STL MAP���������ļ����ظ�����ͬ��һ�����ݵ����� ���ʴ�Ƶͳ�ƣ���ĩ��

https://blog.csdn.net/hyqsong/article/details/46053981     ��ջ Cookie �������⵽���ڶ�ջ�Ļ��������

*/


class HTNode {
private:
	int weight;
	int parent;
	int lchild;
	int rchild;
public:
	HTNode() {
		this->weight = 0;
		this->parent = 0;
		this->lchild = 0;
		this->rchild = 0;
	}
	int getWeight() {
		return weight;
	}
	int getParent() {
		return parent;
	}
	int getLchild() {
		return lchild;
	}
	int getRchild() {
		return rchild;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}
	void setParent(int parent) {
		this->parent = parent;
	}
	void setLchild(int lchild) {
		this->lchild = lchild;
	}
	void setRchild(int rchild) {
		this->rchild = rchild;
	}

};

class HuffmanTree {
private:
	HTNode* node;

public:
	HuffmanTree() {}
	void select(HTNode* node, int num, int& s1, int& s2) {
		int minindex = 0;
		s1 = -1;
		s2 = -1;
		for (int i = 0; i < 2; i++) {
			for (int k = 1; k <= num; k++) {//ѭ��Ѱ����С�±�
				if (!(node[k].getParent()) && (k != s1)) {
					if (minindex == 0) {
						minindex = k;
						continue;
					}
					if (node[minindex].getWeight() > node[k].getWeight()) {
						minindex = k;
					}
				}
			}
			if (s1 == -1) {//s1==-1������s1δ��ֵ
				s1 = minindex;//��ֵs1
				s2 = s1;//��s1��С�±긳ֵ��s2��ֹ�ظ��ж�
			}
			if (s2 == s1) {//s2==s1������s1δ��ֵ
				s2 = minindex;
			}
			minindex = 0;
		}
	}
	void init(map<char, int> word_count) {
		if (word_count.size() <= 1) {//map��������Ԫ��
			return;
		}
		int m = word_count.size() * 2 - 1;//Huffman���ڵ�����
		node = new HTNode[m + 1];
		map<char, int>::iterator it;
		int i = 1;
		for (it = word_count.begin(); it != word_count.end(); it++) {
			node[i].setWeight(it->second);
			i++;
		}
	}
	void creat(int n) {//��ϸ�����������ġ����ݽṹC��P138
		int s1 = 0;
		int s2 = 0;
		for (int i = n + 1; i <= n * 2 - 1; i++) {
			select(node, i - 1, s1, s2);
			node[s1].setParent(i);
			node[s2].setParent(i);
			node[i].setLchild(s1);
			node[i].setRchild(s2);
			node[i].setWeight(node[s1].getWeight() + node[s2].getWeight());
		}
	}
	void showNode(int n) {
		for (int i = 1; i <= n * 2 - 1; i++) {
			cout << i << " " << node[i].getWeight() << " " << node[i].getParent() << " " << node[i].getLchild() << " " << node[i].getRchild() << endl;
		}
	}
	void code(map<char, int> word_count, map<char, string>& huffmancode, int n) {
		string code = "";
		int parent = 0;
		int child = 0;
		map<char, int>::iterator it = word_count.begin();
		for (int i = 1; i <= n; i++) {//��Ҷ�ӽڵ������Ϸ���
			parent = node[i].getParent();
			child = i;
			while (parent != 0) {//�ɴ�ʱ��Ҷ�ӽڵ�i���ϱ���
				if (node[parent].getLchild() == child) {
					code += '0';
				}
				else {
					code += '1';
				}
				parent = node[parent].getParent();//�ҵ�Ҷ�ӽڵ��˫��
				child = parent;//Ϊ�´η���˫����׼��
			}
			//��Ҷ����������0011��Ȼ����ȷ˳��Ӧ����1100
			reverse(code.begin(), code.end());//���ڴ�Ҷ�ӽڵ����ϻ��ݣ��ʱ���Ϊ������Ҫ�ٴ���������Ϊ��
			huffmancode.insert(pair<char, string>(it->first, code));//����ǰ׺���
			it++;
			code = "";//���code
		}
	}
	void clear() {
		node = NULL;
	}

};

class Huffman {
private:
	string words;
	map<char, int> word_count;
	HuffmanTree huffmantree;
	map<char, string> huffmancode;
public:
	Huffman() {}
	Huffman(string s) {
		this->words = s;
	}

	void set_words(string s) {
		this->words = s;
	}

	//ͳ�ƴ�Ƶ
	void countWords() {
		for (int i = 0; i < words.length(); i++) {
			if (word_count.count(words[i])) {//���map���Ѿ�������Ƶ�ʼ�һ
				//ʹ��count�����ص��Ǳ�����Ԫ�صĸ���������У�����1�����򣬷���0��ע�⣬map�в�������ͬԪ�أ����Է���ֵֻ����1��0��
				map<char, int>::iterator it = word_count.find(words[i]);//ʹ��find�����ص��Ǳ�����Ԫ�ص�λ�ã�û���򷵻�map.end()��
				it->second++;
			}
			else {//�����map��δ���������
				word_count.insert(pair<char, int>(words[i], 1));
			}
		}
	}

	void showWord_count() {
		map<char, int>::iterator it = word_count.begin();
		cout << it->first << ":" << it->second;
		it++;
		for (; it != word_count.end(); it++) {
			cout << " " << it->first << ":" << it->second;
		}
		cout << endl;
	}

	void creatHuffmanTree() {
		huffmantree.init(word_count);
		huffmantree.creat(word_count.size());
	}

	void showHuffmanTree() {
		huffmantree.showNode(word_count.size());
	}

	void creatHuffmanCode() {
		huffmantree.code(word_count, huffmancode, word_count.size());
	}

	void showHuffmanCode() {
		map<char, string>::iterator it = huffmancode.begin();
		cout << it->first << ":" << it->second;
		it++;
		for (; it != huffmancode.end(); it++) {
			cout << " " << it->first << ":" << it->second;
		}
		cout << endl;
	}

	void codeWords() {
		map<char, string>::iterator it;
		for (int i = 0; i < words.length(); i++) {
			it = huffmancode.find(words[i]);
			cout << it->second;
		}
		cout << endl;
	}

	void clean() {
		words = "";
		word_count.clear();
		huffmantree.clear();
		huffmancode.clear();
	}
};


int main() {
	Huffman huffman;
	string s;
	while (1) {
		cin >> s;
		if (s == "0") {
			break;
		}
		huffman.set_words(s);
		huffman.countWords();
		huffman.showWord_count();
		huffman.creatHuffmanTree();
		huffman.showHuffmanTree();
		huffman.creatHuffmanCode();
		huffman.showHuffmanCode();
		huffman.codeWords();
		cout << s << endl;
		huffman.clean();	
	}
	return 0;
}