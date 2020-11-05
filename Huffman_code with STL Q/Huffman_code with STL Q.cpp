#include<queue>
#include<map> 
#include<iostream>
#include<algorithm>
#include<string>
#define MaxSize 64
using namespace std;
priority_queue<int, vector<int>, greater<int> >q; // 定义优先队列，最前面的值最小
map<char, int> mapp;
struct character {
	char ch;   // 字符 
	int fre;  // 频率 
};
struct huffmanTree {
	char ch;  // 字符 
	string str;  // 编码 
};


// 建树
int bulidTree(int n, character c[]) {
	int weight = 0;
	// 入队 
	for (int i = 0; i < n; i++)
		q.push((c[i].fre));
	while (q.size() > 1) {
		// 取出堆顶元素 
		int x = q.top();
		// 弹出堆顶元素 
		q.pop();
		int y = q.top();
		q.pop();
		// 入堆 
		q.push(x + y);
		weight += x + y;  // 得到编码长度 
		// 小权值会不断被加 
	}
	q.pop();
	return weight;
}
bool cmp(huffmanTree a, huffmanTree b) {
	return a.str.size() < b.str.size();
}

// 判断是否为前缀
bool isPrefix(huffmanTree code[], int n) {
	// 按字符串长度从小到大排序 
	sort(code, code + n, cmp);
	for (int i = 0; i < n; i++) {
		string str = code[i].str;
		for (int j = i + 1; j < n; j++) { // 查找之后全部字符
			// 如果短字符串与长字符串截取相同长度相等，即为前缀 
			if (code[j].str.substr(0, str.size()) == str)
				return true;
		}
	}
	return false;
}

void judge(int n, character c[], int weight) {
	// 返回 WPL 
	huffmanTree code[MaxSize];
	int codelen = 0;
	for (int i = 0; i < n; i++) {
		cin >> code[i].ch >> code[i].str;
		// 编码长度等于编码长度*频率总和 
		codelen += mapp[code[i].ch] * code[i].str.size();
	}
	if (codelen != weight || isPrefix(code, n))
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
}

int main() {
	int n;
	int m;
	cin >> n;
	character c[MaxSize];
	for (int i = 0; i < n; i++) {
		cin >> c[i].ch >> c[i].fre;
		mapp[c[i].ch] = c[i].fre;
	}
	int weight = bulidTree(n, c);
	cin >> m;
	for (int i = 0; i < m; i++)
		judge(n, c, weight);
	system("pause");
	return 0;
}