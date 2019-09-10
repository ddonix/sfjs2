/* uva 817: According to Bartjens
 * 题意：n个数字（0～9) 排成一个序列，在序列种插入+，-，×运算符，使得表达式值为2000。要求数不能有前导0，运算符按四则
 *       运算优先级计算。
 *       要求输出所有的解，多个解按照字典序从大到小排列。
 * 分析：9个数字，最多8个位置可以插入，每个位置可以插入+，-，×三种符号，最多有pow(4,8) = 65536种排列。
 * 思路：按字典序dfs
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

//c: _, +, -, × 

int strtoint(const string & s)
{
	int r;
	stringstream ss(s);
	ss>>r;
	return r;
}

void printans()
{
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
	string s = t;

	stringstream ss(s);
	queue<int> q;
	for(int i = 0; i < s.length(); )
	{
		int j, r;
		for(j = i+1; j < s.length() && s[j] >= '0' && s[j] <= '9';j++);
		if ('0' == s[i] && (j-i) > 1)	//前导0
			return;
		stringstream ss(s.substr(i, j-i));
		ss>>r;
		q.push(r);
		if (j < s.length())
		{
			if('*' == s[j])
				q.push(-1);
			else if('+' == s[j])
				q.push(-2);
			else
				q.push(-3);
			i = j+1;
		}
		else
			break;
	}
	stack<int> st;
	int e, a, b;
	while(!q.empty())
	{
		e = q.front();
		q.pop();

		if (e == -1)
		{
			int a = st.top();
			int b = q.front();
			st.pop();
			q.pop();
			st.push(a*b);
		}
		else
			st.push(e);
	}
	while(st.size() > 1)
	{
		b= st.top();
		st.pop();
		e = st.top();
		st.pop();
		a = st.top();
		st.pop();
		if (e == -2)
			st.push(a+b); 	
		else
			st.push(a-b);
	}
	if (st.top() == 2000)
	{
		solve = true;
		cout<<"  "<<s<<"="<<endl;	
	}
}

const char *ins = "_+-*";
void dfs(int d)
{
	if (d == n)
	{
		printans();
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			a[d] = ins[i];
			dfs(d+1);
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
		memset(a, 0, sizeof(a));
		solve = false;
		dfs(0);//第0个位置，不插入
		if (!solve)
			cout<<"  "<<"IMPOSSIBLE"<<endl;
	}
}
