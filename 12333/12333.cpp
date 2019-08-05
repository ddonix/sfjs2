#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

const int JZ = 1000000000;
const int MAXB = 999999999;
const int MAXZ = 10;
const int ZS = 9;

struct LLL
{
	int w;
	unsigned long data[10000];

	LLL()
	{
		w = 1;
		data[0] = 0;
	}

	LLL(unsigned long d)
	{
		if (d < JZ)
		{
			w = 1;
			data[0] = d;
		}
		else
		{
			w = 2;
			data[0] = d%JZ;
			data[1] = d/JZ;
		}
	}
	
	LLL operator +(const LLL & right)
	{
		LLL temp;
		unsigned long c = 0, t;
		int w1 = (w < right.w) ? w : right.w;
		int w2 = (w > right.w) ? w : right.w;
		temp.w = w2;
		
		for(int i = 0; i < w1; i++)
		{
			t = data[i]+right.data[i]+c;
			if (t > JZ)
			{
				c = 1;
				temp.data[i] = t-JZ;
			}
			else
			{
				c = 0;
				temp.data[i] = t;
			}
		}
		const unsigned long *x=0;
		if (w < right.w)
			x = right.data;
		else if(w > right.w)
			x = data;
		if(x)
		{
			for(int i = w1; i < w2; i++)
			{
				t = x[i]+c;
				if (t > JZ)
				{
					c = 1;
					temp.data[i] = t-JZ;
				}
				else
				{
					c = 0;
					temp.data[i] = t;
				}
			}
		}
		if(c)
		{
			temp.data[temp.w] = c;
			temp.w++;
		}
		return temp;
	}

	void print(void)
	{
		string r;
		for(int i = w-1; i >= 0; i--)
		{
			stringstream ss;
			ss<<data[i];
			string s = ss.str()+" ";
			r += s;
		}
		cout<<r<<endl;	
	}

	void getstr(char *r)
	{
		char temp[20];
		sprintf(r, "%u", data[w-1]);
		for(int i = w-2; i >= 0; i--)
		{
			sprintf(temp, "%09u", data[i]);
			strcat(r, temp);
			if(strlen(r) >= 40)
			{
				r[40] = 0;
				break;
			}
		}
	}
};

struct Node
{
	struct Node * child[10];
	int f;
	Node()
	{
		for(int i = 0; i < 10; i++)
			child[i] = 0;
		f = -1;
	}
	
	Node(int ff) : f(ff)
	{
		for(int i = 0; i < 10; i++)
			child[i] = 0;
	}
};

struct Node root;

int find(const char *s)
{
	struct Node *r = &root;
	struct Node *t;
	for(int i = 0; i < strlen(s); i++)
	{
		if (r->child[s[i]-'0'] == 0)
			return -1;
		r = r->child[s[i]-'0'];
	}
	return r->f;
}

void insert(const char *s, int f)
{
	struct Node *r = &root;
	struct Node *t;
	int i,j;
	for(i = 0; i < strlen(s); i++)
	{
		j = s[i]-'0';
		if (r->child[j] == 0)
			r->child[j] = new Node(f);
		r = r->child[j];
	}
}

int main()
{

	LLL a(1), b(1), c;
	insert("1", 0);
	char buff[55];
	for(int i = 2; i <= 100000; i++)
	{
		c = a+b;
		a = b;
		b = c;
		buff[0] = 0;
		c.getstr(buff);
		insert(buff, i);
	}
	int t;
	cin>>t;
	for(int i = 1; i <= t; i++)
	{
		buff[0] = 0;
		cin>>buff;
		int j = find(buff);
		cout<<"Case #"<<i<<": "<<j<<endl;
	}
}
