﻿#define _CRT_SECURE_NO_WARNINGS //put in first line

#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include<map>
#define HeapCapacity 64
#define MinData 0
typedef struct TreeNode *HuffmanTree;
typedef struct Heap *MinHeap;
struct Heap {   // 堆 
	HuffmanTree *data;  // 存哈夫曼树 
	int size; // 堆的当前大小 
};
struct TreeNode {   // 哈夫曼树 
	int weight;  // 频率
	HuffmanTree left;
	HuffmanTree right;
};
using namespace std;

MinHeap createHeap();   // 建堆 
HuffmanTree createHuffman();  // 建哈夫曼树 
void sortHeap(MinHeap H, int i); // 调整子最小堆 
void adjust(MinHeap H);  // 调整堆 
MinHeap InitHeap(int n); // 初始化堆 
HuffmanTree Delete(MinHeap H); // 堆的删除 
void Insert(MinHeap H, HuffmanTree Huff); // 堆的插入 
HuffmanTree Huffman(MinHeap H);  // 哈夫曼树的构造 
int WPL(HuffmanTree Huff, int depth); // 计算 HuffmanTree 的编码长度 


map<char, int> mappp;  // 保存字符到频率的映射关系 

// 建堆 
MinHeap createHeap() {
	MinHeap H;
	H = (MinHeap)malloc(sizeof(struct Heap));
	H->data = (HuffmanTree *)malloc(sizeof(struct TreeNode) * HeapCapacity);
	H->size = 0;
	// 设置哨兵
	HuffmanTree Huff = createHuffman();
	H->data[0] = Huff;
	return H;
}

// 建哈夫曼树 
HuffmanTree createHuffman() {
	HuffmanTree Huff;
	Huff = (HuffmanTree)malloc(sizeof(struct TreeNode));
	Huff->weight = MinData;   // 初始化成频率最小 
	Huff->left = NULL;
	Huff->right = NULL;
	return Huff;
}

// 调整子最小堆 
void sortHeap(MinHeap H, int i) {
	int parent, child;
	HuffmanTree Huff = H->data[i]; // 拿到当前根结点的哈夫曼树
	for (parent = i; parent * 2 <= H->size; parent = child) {
		// 左右儿子中挑小的 
		child = parent * 2;
		if ((child != H->size) && (H->data[child + 1]->weight < H->data[child]->weight))
			child++;
		// 没有更小的了，结束循环 
		if (Huff->weight <= H->data[child]->weight)
			break;
		// 否则把儿子结点拿上来
		H->data[parent] = H->data[child];
	}
	H->data[parent] = Huff;
}


// 调整堆 
void adjust(MinHeap H) {
	// 从第一个有孩子结点的结点开始调整 
	for (int i = H->size / 2; i > 0; i--)
		sortHeap(H, i);
}

// 初始化堆 
MinHeap InitHeap(int n) {
	MinHeap H = createHeap();
	HuffmanTree Huff;
	char c;  // 临时保存字符 
	int f;  //  临时保存频率 
	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c %d", &c, &f);
		mappp.insert(pair<char, int>(c, f));  // 把字符和频率的映射关系存进map 
		Huff = createHuffman();
		Huff->weight = f;
		H->data[++H->size] = Huff;
	}
	// 调整最小堆 
	adjust(H);
	return H;
}

// 堆的删除 
HuffmanTree Delete(MinHeap H) {
	int parent, child;
	HuffmanTree T = H->data[1]; // 拿到根结点的哈夫曼树 
	HuffmanTree Huff = H->data[H->size--];  // 拿到最后一个位置的哈夫曼树 
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		// 左右儿子中挑小的 
		child = parent * 2;
		if ((child != H->size) && (H->data[child + 1]->weight < H->data[child]->weight))
			child++;
		// 没有更小的了，结束循环 
		if (Huff->weight <= H->data[child]->weight)
			break;
		// 否则把儿子结点拿上来
		H->data[parent] = H->data[child];
	}
	H->data[parent] = Huff;
	return T;
}

// 堆的插入
void Insert(MinHeap H, HuffmanTree Huff) {
	int i = ++H->size;
	for (; Huff->weight < H->data[i / 2]->weight; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = Huff;
}

// 哈夫曼树的构造 
HuffmanTree Huffman(MinHeap H) {
	HuffmanTree Huff;
	int times = H->size;
	for (int i = 1; i < times; i++) {
		Huff = createHuffman();
		Huff->left = Delete(H);  // 从堆中删除一个结点，作为新 T 的左子结点 
		Huff->right = Delete(H);  // 从堆中删除一个结点，作为新 T 的右子结点 
		Huff->weight = Huff->left->weight + Huff->right->weight; // 重新计算权值 
		Insert(H, Huff);   // 再加进堆中 
	}
	Huff = Delete(H);
	return Huff;
}

// 计算 HuffmanTree 的编码长度 
int WPL(HuffmanTree Huff, int depth) {
	// 如果是叶结点，返回编码长度 
	if (Huff->left == NULL && Huff->right == NULL)
		return depth * Huff->weight;
	else  // 否则返回其左右子结点的编码长度 
		return (WPL(Huff->left, depth + 1) + WPL(Huff->right, depth + 1));
}

// 提交 
void submit(int n, int codeLen) {
	HuffmanTree Huff = createHuffman();
	HuffmanTree pre;
	int counter = 1;
	bool flag = true;
	char ch;
	string code;
	for (int i = 0; i < n; i++) {
		getchar();
		pre = Huff;
		// 读入每行 
		scanf("%c", &ch);
		cin >> code;
		// 遍历编码 
		for (int j = 0; j < code.size(); j++) {
			if (code[j] == '0') {  // 如果当前编码为 0，左分支 
				if (pre->left == NULL) {   // 如果左子树不存在，创建 
					pre->left = createHuffman();
					counter++;
				}
				if (pre->weight != 0)
					flag = false;
				pre = pre->left;
			}
			else if (code[j] == '1') { // 如果当前编码为 0，左分支 
				if (pre->right == NULL) {   // 如果左子树不存在，创建 
					pre->right = createHuffman();
					counter++;
				}
				if (pre->weight != 0)
					flag = false;
				pre = pre->right;
			}
		}
		if (pre->left || pre->right)
			flag = false;
		pre->weight = mappp[ch];   // 从 mapp 取出存的频率
	}
	if (counter != 2 * n - 1 || !flag || WPL(Huff, 0) != codeLen) { // 如果结点不是 2n-1 个  或者编码长度不相等 
		printf("No\n");
		return;
	}
	else {
		printf("Yes\n");
		return;
	}
}


int main() {
	int n, m;
	scanf("%d", &n);
	// 初始化最小堆 
	MinHeap H = InitHeap(n);
	// 初始化哈夫曼树 
	HuffmanTree Huff = Huffman(H);
	// 计算该哈夫曼树的编码长度 
	int codeLen = WPL(Huff, 0);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		submit(n, codeLen);
	}
	system("pause");
	return 0;
}