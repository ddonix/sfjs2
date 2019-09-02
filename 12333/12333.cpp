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

	LLL & operator=(const LLL &right)
	{
		w = right.w;
		for(int i = 0; i < w; i++)
			data[i] = right.data[i];
		return *this;
	}
	
	void add(const LLL & a1, const LLL & a2)
	{
		LLL temp;
		unsigned long c = 0, t;
		int wmin, wmax;
		
		wmin = (a1.w < a2.w) ? a1.w : a2.w;
		wmax = (a1.w > a2.w) ? a1.w : a2.w;
		this->w = wmax;
	
		for(int i = 0; i < wmin; i++)
		{
			t = a1.data[i]+a2.data[i]+c;
			if (t > JZ)
			{
				c = 1;
				this->data[i] = t-JZ;
			}
			else
			{
				c = 0;
				this->data[i] = t;
			}
		}
		const unsigned long *x=0;
		if (a1.w < a2.w)
			x = a2.data;
		else if(a1.w > a2.w)
			x = data;
		if(x)
		{
			for(int i = wmin; i < wmax; i++)
			{
				t = x[i]+c;
				if (t > JZ)
				{
					c = 1;
					this->data[i] = t-JZ;
				}
				else
				{
					c = 0;
					this->data[i] = t;
				}
			}
		}
		if(c)
		{
			this->data[this->w] = c;
			this->w++;
		}
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
	for(int i = 2; i < 100000; i++)
	{
		c.add(a,b);
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
