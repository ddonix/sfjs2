#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 5;
const int maxsq = 55;
const int maxm = 2*(maxn+1)*maxn;

bool mtv[maxm];
vector<int> mts[maxm];
vector<int> mtt;

bool square[maxsq];		//每个正方形编个号
vector<int> smt[maxn-1][maxsq];

int as;				//avaliable square
int n, nm, k;			//
int dd;

int inline axistoi0(int x, int y)
{
	return x*(2*n+1)+y;
}

int inline axistoi1(int x, int y)
{
	return x*(2*n+1)+y+n;
}

void initializeg()
{
	for(n = 2; n <= maxn; n++)
	{
		int ns = 0;
		for(int x = 0; x < n; x++)
			for(int y = 0; y < n; y++)
			{
				for(int l = 1; l <= n; l++)
				{
					if (x + l > n || y + l > n)
						break;
					for(int k = 0; k < l; k++)
					{
						smt[n-2][ns].push_back(axistoi0(x,y+k));
						smt[n-2][ns].push_back(axistoi0(x+l, y+k));
						smt[n-2][ns].push_back(axistoi1(x+k, y));
						smt[n-2][ns].push_back(axistoi1(x+k, y+l));
					}
					ns++;
				}
			}
	}
}

void initialize()
{
	memset(square, 0, sizeof(square));
	for(int i = 0; i < nm; i++)
		mts[i].clear();
	mtt.clear();
	
	int ns = 0;
	as = 0;
	for(int x = 0; x < n; x++)
		for(int y = 0; y < n; y++)
		{
			for(int l = 1; l <= n; l++)
			{
				if (x + l > n || y + l > n)
					break;
				int k;
				for(k = 0; k < l; k++)
					if (!(mtv[axistoi0(x,y+k)] && mtv[axistoi0(x+l, y+k)] 
							&& mtv[axistoi1(x+k, y)] && mtv[axistoi1(x+k, y+l)]))
						break;
				if (k < l)
				{
					ns++;
					continue;
				}
				square[ns] = true;
				as++;
				for(k = 0; k < l; k++)
				{
					mts[axistoi0(x, y+k)].push_back(ns);
					mts[axistoi0(x+l, y+k)].push_back(ns);
					mts[axistoi1(x+k, y)].push_back(ns);
					mts[axistoi1(x+k, y+l)].push_back(ns);
				}
				ns++;
			}
		}
	for(int i = 0; i < nm; i++)
		if (mtv[i] && !mts[i].empty())
			mtt.push_back(i);
}

void removemt(int mi, vector<int> & sq, map<int, vector<int> > & mp)
{
	sq = mts[mtt[mi]];
	mtt.erase(mtt.begin()+mi);
	
	for(int i = 0; i < sq.size(); i++)
	{
		square[sq[i]] = false;
		for(int j = 0; j < smt[n-2][sq[i]].size(); j++)
		{
			int m = smt[n-2][sq[i]][j];
			if (mp.count(m) < 1)
				mp[m] = vector<int>();
			mp[m].push_back(sq[i]);
			auto it = find(mts[m].begin(), mts[m].end(), sq[i]);
			mts[m].erase(it);
		}
	}
	for(int i = mtt.size()-1; i >= 0; i--)
		if (mts[mtt[i]].empty())
			mtt.erase(mtt.begin()+i);
}

void recovermt(map<int, vector<int> > & mp)
{
	for(auto it = mp.begin(); it != mp.end(); it++)
	{
		int m = (*it).first;
		for(int i = 0; i < (*it).second.size(); i++)
			mts[m].push_back((*it).second[i]);
	}
}

bool cmp(int a, int b)
{
	return mts[a].size() > mts[b].size();
}

int ida(int d)
{
	if (d == dd)
	{
		if (0 == as)
			return dd;
		return 0;
	}
	else
	{
		sort(mtt.begin(), mtt.end(), cmp);
		if (mts[mtt[0]].size() == 1)
		{
			set<int> se;
			for(int i = 0; i < mtt.size(); i++)
				se.insert(mts[mtt[i]][0]);
			return (d+se.size() == dd) ? dd : 0;
		}
		int a = 0, k;
		for(k = 0; a < as; k++)
			a += mts[mtt[k]].size();
		if (k+d > dd)
			return 0;
		
		vector<int> mttback = mtt;
		int r, s = mtt.size();
		for(int i = 0; i < s; i++)
		{
			map<int, vector<int> > mp;
			vector<int> sq;
			
			removemt(i, sq, mp);	//火柴拿走, 正方形破坏
			mtv[mtt[i]] = false;
			as -= sq.size();
			r = ida(d+1);
			if (r > 0)
				return r;
			mtt = mttback;
			recovermt(mp);
			mtv[mtt[i]] = true;
			as += sq.size();
			for(int i = sq.size()-1; i >= 0; i--)
				square[sq[i]] = true;
		}
	}
	return 0;
}

int main()
{
	int T,t;
	initializeg();
	
	cin>>T;
	while(T--)
	{
		cin>>n>>k;

		if (n == 1)
			cout<< ((k==0) ? 1 : 0)<<endl;
		else
		{
			nm = 2*(n+1)*n;
			for(int i = 0; i < nm; i++)
				mtv[i] = true;
			for(int i = 0; i < k; i++)
			{
				cin>>t;
				mtv[t-1] = false;
			}
			initialize();
			for(dd = 0; dd <= n*(n+1); dd++)
			{
				int r = ida(0);
				if (!r)
					continue;
				cout<<r<<endl;
				break;
			}
		}
	}
}
