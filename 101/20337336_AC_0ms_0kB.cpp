#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;
vector<int> a[maxn];
int n;

void find_block(int x, int &p, int &h)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < a[i].size(); j++)
			if (a[i][j] == x)
			{
				p = i;
				h = j;
				return;
			}
	}
}

void clear_above(int p, int h)
{
	int x;
	for(int i = h+1; i < a[p].size(); i++)
	{
		x = a[p][i];
		a[x].push_back(x);
	}
	a[p].resize(h+1);
}

void pile_onto(int p, int h, int p2)
{
	int x;
	for(int i = h; i < a[p].size(); i++)
	{
		x = a[p][i];
		a[p2].push_back(x);
	}
	a[p].resize(h);
}

int main()
{
	char c0[10],c1[10];
	int l,r;
	int lp, lh, rp, rh;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		a[i].push_back(i);
	}
	while(1)
	{
		scanf("%s", c0);
		if(0 == strcmp(c0, "quit"))
			break;
		scanf("%d %s %d", &l, c1, &r);
		find_block(l, lp, lh);
		find_block(r, rp, rh);
		if (lp == rp)
			continue;
		if (0 == strcmp(c0, "move"))
				clear_above(lp, lh);
		if (0 == strcmp(c1, "onto"))
				clear_above(rp, rh);
		pile_onto(lp, lh, rp);

	}
	for(int i = 0; i < n; i++)
	{
		printf("%d:", i);
		for(int j = 0; j < a[i].size(); j++)
			printf(" %d", a[i][j]);
		printf("\n");
	}
}
