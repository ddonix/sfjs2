#include <iostream>
#include <set>

using namespace std;

const int maxn = 20;
unsigned long rt[5];
unsigned long task;
int n;

unsigned long bits[20] = {	0x1,	0x2,	0x4,	0x8,
				0x10,	0x20,	0x40,	0x80,
				0x100,	0x200,	0x400,	0x800,
				0x1000,	0x2000,	0x4000,	0x8000,
				0x10000,0x20000,0x40000,0x80000};

int btime[maxn];

bool conflict(const set<int> & a, const set<int> & b)
{
	for(auto it = a.begin(); it != a.end(); it++)
		if (b.count(*it))
			return true;
	return false;
}

void add(set<int> & a, const set<int> &b)
{
	for(auto it = b.begin(); it != b.end(); it++)
		a.insert(*it);
}

int simulation()
{
	int ctime = 0;
	set<int> ub[5];
	for(int tk = 0; tk < n; tk++)
		btime[tk] = -1;
	for(int tk = 0; tk < n;tk++)
	{
		set<int> ut[5];
		while(1)
		{
			bool ok = true;
			int u;
			for(u = 0; u < 5 && ok; u++)
			{
				ut[u].clear();
				for(int i = 0; i < n && ok; i++)
				{
					if(rt[u] & bits[i])
					{
						if (ub[u].count(ctime+i))
							ok = false;
						else
							ut[u].insert(ctime+i);
					}
				}
			}
			if (5 == u)
				break;
			ctime++;
		}
		btime[tk] = ctime++;
		for(int u = 0; u < 5; u++)
			add(ub[u], ut[u]);
	}
	return ctime;
}

int main()
{
	while(cin>>n && n)
	{
		char c;
		for(int i = 0; i < 5; i++)
		{
			rt[i] = 0;
			for(int j = 0; j < n; j++)
			{
				cin>>c;
				rt[i] |= (c == 'X') ? bits[j] : 0;
			}
		}
		cout<<simulation()<<endl;
	}
}
