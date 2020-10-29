#define _CRT_SECURE_NO_WARNINGS //put in first line
#include<iostream>
#include<cstring>
using namespace std;
#define MAX 500
int coun[26]; //频率 
char saveletter[26];//存字母 
char temp[MAX];//暂存被译码串 

typedef struct htnode
{
	int weight;
	int lchild, rchild, parent;
	char data;
	int frequency;//出现频率 
}*huftree;

typedef char **hufcode;

void select(huftree &hf, int x, int &s1, int &s2)//在叶子结点里找最小的两个 
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

void Create(huftree &hf, int n)//叶子为n的哈树有2n-1个结点 
{
	int m = 2 * n - 1, s1 = 0, s2 = 0;

	if (n <= 1) return;

	hf = new htnode[m + 1];//0号单元不用

	for (int i = 1; i <= m; i++)//都初始化为0 
	{
		hf[i].parent = 0;
		hf[i].rchild = 0;
		hf[i].lchild = 0;
		hf[i].data = saveletter[i - 1];//字母
	}

	for (int i = 1; i <= n; i++)
		hf[i].weight = coun[i - 1];//输入权值 

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

void count(char str[], huftree &hf, int &n)//出现频率 ,字母个数 
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
			saveletter[j] = char(i + 97);
			coun[j] = num[i];
			j++;
		}
	}
	n = j;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1)
			cout << saveletter[i] << ":" << coun[i];
		else
			cout << saveletter[i] << ":" << coun[i] << " ";
	}
	cout << endl;
}


void hfcode(huftree &hf, hufcode &hc, int n)
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
			cout << saveletter[j - 1] << ":" << hc[j];
		else
			cout << saveletter[j - 1] << ":" << hc[j] << " ";
	}
	cout << endl;

}


void trans_tonum(huftree &hf, hufcode &hc, int n, char str[])
{
	for (int i = 0; str[i] != '\0'; i++)
		for (int j = 1; j <= n; j++)
			if (str[i] == saveletter[j - 1])
			{
				cout << hc[j];
				strcat(temp, hc[j]);
			}

	cout << endl;

}

void trans_toletter(huftree &hf, hufcode &hc, int n)
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

int main()
{

	while (1)
	{
		huftree hf;
		hufcode hc;
		int n;
		char str[MAX];

		gets_s(str);
		if (str[0] == '0')
			break;

		count(str, hf, n);
		Create(hf, n);
		hfcode(hf, hc, n);
		trans_tonum(hf, hc, n, str);
		trans_toletter(hf, hc, n);

		memset(coun, 0, sizeof(coun));
		memset(saveletter, '\0', sizeof(saveletter));
		memset(temp, '\0', sizeof(temp));

		delete hf;
		delete hc;
	}
	return 0;
}