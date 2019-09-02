#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 100002;

int out[26];
int in[26];


int n;
int cn = 0;

pair<int, int> *nodes;
int *idx;

void dfs(int v)
{
	if (idx[v])
		return;
	idx[v] = 1;
	cn++;
	
	for(int i = 0; i < n; i++)
		if (!idx[i] && ((nodes[i].first == nodes[v].second) || (nodes[i].second == nodes[v].first)))
			dfs(i);
}

int main()
{
	int T;
	char buff[1001];
	
	nodes = new pair<int, int>[maxn];
	idx = new int[maxn];
	cin>>T;
	
	while(T--)
	{
		cin>>n;
		memset(out, 0, sizeof(out));
		memset(in, 0, sizeof(in));
		memset(nodes, 0, maxn*sizeof(pair<int,int>));
		memset(idx, 0, maxn*sizeof(int));
		cn = 0;
		
		for(int i = 0; i < n; i++)
		{
			cin>>buff;
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
			cout<<"The door cannot be opened."<<endl;
			continue;
		}
		dfs(0);
		if(cn < n)
		{
			cout<<"The door cannot be opened."<<endl;
			continue;
		}
		if(0 == diff)
		{
			cout<<"Ordering is possible."<<endl;
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
			cout<<"Ordering is possible."<<endl;
		else
			cout<<"The door cannot be opened."<<endl;

	}
}
