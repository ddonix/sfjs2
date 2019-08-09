#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
const int maxn = 10000+2;

int in_order[maxn];
int post_order[maxn];

int Left[maxn];
int Right[maxn];

int value[maxn];

int nn;
int root;

int getroot(pair<int, int> ind, pair<int, int> posto)
{
	int rt = post_order[posto.second];
	int l, r, i;
	for(i = ind.first; in_order[i] != rt; i++);
	if (i > ind.first)
		l = getroot(make_pair(ind.first,i-1), make_pair(posto.first, posto.first+(i-1-ind.first)));
	else
		l = 0;
	
	if (i < ind.second)
		r = getroot(make_pair(i+1, ind.second), make_pair( posto.second+i-ind.second , posto.second-1));
	else
		r = 0;
	Left[rt] = l;
	Right[rt] = r;
	return rt;
}

void printtree()
{
	queue<int> q;
	q.push(root);
	while(!q.empty())
	{
		int r = q.front();
		q.pop();
		cout<<r<<" ";
		if (Left[r])
			q.push(Left[r]);
		if (Right[r])
			q.push(Right[r]);
	}
	cout<<endl;
}

int minvalue;
int leaf;

int setvalue(int rt, int exp)
{
	int l, r;
	value[rt] = rt+exp;

	l = Left[rt];
	r = Right[rt];

	if (l)
		setvalue(l, value[rt]);
	if (r)
		setvalue(r, value[rt]);

	if (!l && !r)
	{
		if (value[rt] < minvalue || ((value[rt] == minvalue) && (rt < leaf)))
		{
			minvalue = value[rt];
			leaf = rt;
		}

	}
	return rt;
}

void maketree()
{
	root = getroot(make_pair(1,nn), make_pair(1, nn));
//	printtree();
}

int main()
{
	string s;
	while(getline(cin, s))
	{
		stringstream ss1(s);
		int t;
		int i = 0;
		nn = 0;
		while(ss1>>t)  in_order[++nn] = t;
		
		getline(cin, s);
		stringstream ss2(s);
		for(int i = 1; i <= nn; i++)
		{
			ss2>>t;
			post_order[i]= t;
		}

		root = getroot(make_pair(1,nn), make_pair(1, nn));
		
		minvalue = maxn*maxn;
		leaf = 0;
		setvalue(root, 0);
		cout<<leaf<<endl;
	}
}
