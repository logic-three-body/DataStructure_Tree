#define _CRT_SECURE_NO_WARNINGS //put in first line
#include<iostream>
#include<cstring>
#include<string>
#include <cstdlib>
#include <iomanip>
using namespace std;
#define MAX 500
int FrencyTank[26]; //频率 
char LetterTank[26];//存字母 
char temp[MAX];//暂存被译码串 

typedef struct htnode
{
	int weight;
	int lchild, rchild, parent;
	char data;
	int frequency;//出现频率 
}*Huffman_tree;

typedef char **Huffman_code;

void select(Huffman_tree &hf, int x, int &s1, int &s2)//在叶子结点里找最小的两个 
{
	int min = 999, cmin = 999;//最小值和次小值 
	int i = 1;
	while (i <= x)
	{
		if (hf[i].parent == 0)
		{
			if (hf[i].weight < min)//寻找权值最小 
			{
				min = hf[i].weight;
				s1 = i;
			}
			i++;
		}
		else
			i++;
	}
	int flag = s1;
	i = 1;
	while (i <= x)
	{
		if (hf[i].parent == 0)
		{
			if ((hf[i].weight > min && hf[i].weight < cmin) || (hf[i].weight == min && flag != i))//找次小值 
			{
				cmin = hf[i].weight;
				s2 = i;
			}
			i++;
		}
		else
			i++;
	}

}

void CreateHuffmanTree(Huffman_tree &hf, int n)//叶子为n的Huffman树有2n-1个结点 
{
	int m = 2 * n - 1, s1 = 0, s2 = 0;

	if (n <= 1) return;

	hf = new htnode[m + 1];//0号单元不用

	for (int i = 1; i <= m; i++)//都初始化为0 
	{
		hf[i].parent = 0;
		hf[i].rchild = 0;
		hf[i].lchild = 0;
		hf[i].data = LetterTank[i - 1];//字母
	}

	for (int i = 1; i <= n; i++)
		hf[i].weight = FrencyTank[i - 1];//输入权值 

	for (int i = n + 1; i <= m; i++)//前n个为叶子，后面需要构建 
	{
		select(hf, i - 1, s1, s2);//选择最小的两个节点,返回序号 
		hf[s1].parent = i;
		hf[s2].parent = i;//结点双亲变为i
		hf[i].lchild = s1;
		hf[i].rchild = s2;//i的左右孩子
		hf[i].weight = hf[s1].weight + hf[s2].weight;
		//i权值更改 
	}

}

void count(string& str, Huffman_tree &hf, int &times)//出现频率 ,字母个数 
{
	int i = 0, j = 0;
	int num[26];
	char ch;
	memset(num, 0, sizeof(num));

	while (str[i] != '\0')
	{
		j = str[i] - 97;
		num[j]++;
		i++;
	}
	j = 0;
	for (i = 0; i < 26; i++)
	{
		if (num[i] != 0)
		{
			LetterTank[j] = char(i + 97);
			FrencyTank[j] = num[i];
			j++;
		}
	}
	times = j;
	for (int i = 0; i < times; i++)
	{
		if (i == times - 1)
			cout << LetterTank[i] << ":" << FrencyTank[i];
		else
			cout << LetterTank[i] << ":" << FrencyTank[i] << " ";
	}
	cout << endl;
}


void HuffmanCode(Huffman_tree &hf, Huffman_code &hc, int n)
{
	int start = 0, c, f;
	char *cd;

	hc = new char*[n + 1];//编码表 
	cd = new char[n];//每个字符的编码一定小于n 
	cd[n - 1] = '\0';

	for (int i = 1; i <= n; i++)
	{
		start = n - 1;
		c = i;
		f = hf[i].parent;

		while (f != 0)//不是根节点
		{
			start--;

			if (hf[f].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';

			c = f;//向上回溯 
			f = hf[f].parent;
		}
		hc[i] = new char[n - start];
		strcpy(hc[i], &cd[start]);//把临时空间的编码复制到编码表中 
	}
	delete cd;

	int i, j, z = 0;
	for (j = 1; j <= n; j++)//输出字母编码 
	{
		if (j == n)
			cout << LetterTank[j - 1] << ":" << hc[j];
		else
			cout << LetterTank[j - 1] << ":" << hc[j] << " ";
	}
	cout << endl;
}


void letter_to_code(Huffman_tree &hf, Huffman_code &hc, int n, string& str)
{
	for (int i = 0; str[i] != '\0'; i++)
		for (int j = 1; j <= n; j++)
			if (str[i] == LetterTank[j - 1])
			{
				cout << hc[j];
				strcat(temp, hc[j]);
			}

	cout << endl;

}

void code_to_letter(Huffman_tree &hf, Huffman_code &hc, int n)
{
	int i = 2 * n - 1;
	int j = 0;

	while (temp[j] != '\0')
	{
		if (temp[j] == '0')
			i = hf[i].lchild;   //左孩子
		else if (temp[j] == '1')
			i = hf[i].rchild;    //右孩子
		if (hf[i].lchild == 0)
		{
			cout << hf[i].data;
			i = 2 * n - 1;
		}
		j++;   //无论是否找到叶子节点都读取下一个编码串字符
	}
	cout << endl;
}

//打印HT
void PrintState(Huffman_tree& HT, int n)
{
	int m = 2 * n - 1;  //总结点数
	
	for (int i = 1; i <= m; i++)
	{
		cout << i << " ";
		cout << HT[i].weight << " ";
		cout << HT[i].parent << " ";
		cout << HT[i].lchild << " ";
		cout << HT[i].rchild << " " << endl;
	}
}

int main()
{

	while (true)
	{
		Huffman_tree huffman_tree;
		Huffman_code huffman_code;
		int frequency;
		string str = "";

		
		getline(cin, str);
		
		if (str[0] == '0')
			break;

		//统计频率
		count(str, huffman_tree, frequency);



		//创造HuffmanTree
		CreateHuffmanTree(huffman_tree, frequency);

		//TODO输出HuffmanTree
		PrintState(huffman_tree, frequency);


		//输出编码格式
		HuffmanCode(huffman_tree, huffman_code, frequency);

		//打印编码
		letter_to_code(huffman_tree, huffman_code, frequency, str);

		//打印字符
		code_to_letter(huffman_tree, huffman_code, frequency);

		memset(FrencyTank, 0, sizeof(FrencyTank));
		memset(LetterTank, '\0', sizeof(LetterTank));
		memset(temp, '\0', sizeof(temp));

		delete huffman_tree;
		delete huffman_code;
	}
	return 0;
}