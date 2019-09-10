/* uva 817: According to Bartjens
 * 题意：n个数字（0～9) 排成一个序列，在序列种插入+，-，×运算符，使得表达式值为2000。要求数不能有前导0，运算符按四则
 *       运算优先级计算。
 *       要求输出所有的解，多个解按照字典序从大到小排列。
 * 分析：9个数字，最多8个位置可以插入，每个位置可以插入+，-，×三种符号，最多有pow(4,8) = 65536种排列。
 * 思路：1.按字典序dfs
 * 	 2.前导0要剪枝
 * 	 3.在递归过程中，要计算中间结果，否则等递归完成再计算，重复计算量太大，会超时！
 */
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stack>
#include <queue>
using namespace std;

int n;
bool solve;
char p[11];
char a[8];

struct Rec
{
	int a;
	char e;
	int b;
	bool m;
	int c;

	void calc()
	{
		if (m)
			b *= c;
		if ('+' == e)
			a += b;
		else
			a -= b;
		b = 0;
		c = 0;
		e = '+';
		m = false;
	}
	Rec(int a_, char e_, int b_, bool m_, int c_) : a(a_) , e(e_), b(b_), m(m_), c(c_) {}
};

void printans(Rec rec)
{
	rec.calc();
	if (rec.a == 2000)
	{
		solve = true;
		char t[20];
		int j = 0;
		for(int i = 0; i < n; i++)
		{
			t[j++] = p[i];
			if (a[i] != '_')
				t[j++] = a[i];
		}
		t[j++] = p[n];
		t[j] = 0;
		cout<<"  "<<t<<"="<<endl;
	}
}

const char *ins = "*+-_";
void dfs(int d, bool c, Rec rec)
{
	if (d == n)
		printans(rec);
	else
	{
		for(int i = 0 ; i < (c ? 4 : 3); i++)
		{
			Rec nrec = rec;
			a[d] = ins[i];
			if (3 == i)
			{
				if (nrec.m)
					nrec.c = nrec.c*10+p[d+1]-'0';
				else
					nrec.b = nrec.b*10+p[d+1]-'0';
			}
			else if(1 == i || 2 == i)
			{
				nrec.calc();
				nrec.b = p[d+1]-'0';
				nrec.e = ins[i]; 
			}
			else
			{
				if (nrec.m)
					nrec.b *= nrec.c;
				else
					nrec.m = true;
				nrec.c = p[d+1]-'0';
			}
			dfs(d+1, (i != 3 && p[d+1] == '0') ? false : true, nrec);
		}
	}
}

int main()
{
	int ka=0;
	while(cin>>p && '=' != p[0])
	{
		cout<<"Problem "<<++ka<<endl;
		p[strlen(p)-1] = 0;
		n = strlen(p)-1;

		if (strcmp(p, "2000") == 0)
		{
			cout<<"  "<<"IMPOSSIBLE"<<endl;
			continue;
		}
		memset(a, 0, sizeof(a));
		solve = false;
		dfs(0, '0' == p[0] ? false : true, Rec(0, '+', p[0]-'0', false, 0));
		if (!solve)
			cout<<"  "<<"IMPOSSIBLE"<<endl;
	}
}
