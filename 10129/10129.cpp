#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int maxn = 100002;

int out[26];
int in[26];



int n;
int cn = 0;

pair<int, int> *nodes;
int *idx;

int outf[26];
int inf[26];
void sfs()
{
	memset(outf, 0, sizeof(outf));
	memset(inf, 0, sizeof(inf));

	idx[0] = 1;
	cn++;
	outf[nodes[0].first] = inf[nodes[0].second] = 1;
	
	int next = 1;
	while(cn < n)
	{
		bool nfirst = true;
		int cnt = cn;
		for(int i = next; i < n; i++)
		{
			if (!idx[i])
			{
				if (inf[nodes[i].first] || outf[nodes[i].second])
				{
					outf[nodes[i].first] = 1;
					inf[nodes[i].second] = 1;
					idx[i] = 1;
					cn++;
				}
				else 
				{
					if (nfirst)
					{
						nfirst = false;
						next = i;
					}
				}
			}
		}
		if (cnt == cn)
			break;
	}
}

int main()
{
	int T;
	char buff[1001];
	
	nodes = new pair<int, int>[maxn];
	idx = new int[maxn];
	scanf("%d", &T);
	
	while(T--)
	{
		scanf("%d", &n);
		memset(out, 0, sizeof(out));
		memset(in, 0, sizeof(in));
		memset(nodes, 0, maxn*sizeof(pair<int, int>));
		memset(idx, 0, maxn*sizeof(int));
		cn = 0;
		
		for(int i = 0; i < n; i++)
		{
			scanf("%s", buff);
			int a = buff[0]-'a';
			int b = buff[strlen(buff)-1]-'a';
			nodes[i].first = a;
			nodes[i].second = b;
			in[a]++;
			out[b]++;
		}
		
		int diff = 0;
		int d[3];
		for(int i = 0; i < 26 && diff <= 2; i++)
		{
			if (out[i] != in[i])
			{
				d[diff]=i;
				diff++;
			}
		}
		if (diff > 2)
		{
			printf("The door cannot be opened.\n");
			continue;
		}
		sfs();
		if(cn < n)
		{
			printf("The door cannot be opened.\n");
			continue;
		}
		if(0 == diff)
		{
			printf("Ordering is possible.\n");
			continue;
		}
		bool flag = false;
		for(int i = 0; i < 2 && !flag; i++)
		{
			int a = d[i];
			int b = d[(i+1)%2];
			if ((out[a]-in[a] == 1) && (in[b]-out[b] == 1))
				flag = true;
		}
		if(flag)
			printf("Ordering is possible.\n");
		else
			printf("The door cannot be opened.\n");
	}
}
