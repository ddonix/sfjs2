#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 5;
const int maxsq = 55;
const int maxss[4] = {5, 14, 30, 55};
const int maxm = 2*(maxn+1)*maxn;

bool mtv[maxm];
bool mts1[maxm][maxsq];
int mtss[maxm];

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
	memset(mts1, 0, sizeof(mts1));
	memset(mtss, 0, sizeof(mtss));
	
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
					mts1[axistoi0(x, y+k)][ns] = true;
					mtss[axistoi0(x, y+k)]++;
					
					mts1[axistoi0(x+l, y+k)][ns] = true;
					mtss[axistoi0(x+l, y+k)]++;
					
					mts1[axistoi1(x+k, y)][ns] = true;
					mtss[axistoi1(x+k, y)]++;
					
					mts1[axistoi1(x+k, y+l)][ns] = true;
					mtss[axistoi1(x+k, y+l)]++;
				}
				ns++;
			}
		}
	for(int i = 0; i < nm; i++)
		if (mtv[i] && mtss[i])
			mtt.push_back(i);
}

void removemt(int mi, map<int, vector<int> > & mp)
{
	int m = mtt[mi];
	for(int s = 0; mtss[m]; s++)
	{
		if (mts1[m][s] == true)
		{
			square[s] = false;
			as--;
			for(int j = 0; j < smt[n-2][s].size(); j++)
			{
				int m1 = smt[n-2][s][j];
				if (mp.count(m1) < 1)
					mp[m1] = vector<int>();
				mp[m1].push_back(s);
				mts1[m1][s] = false;
				mtss[m1]--;
			}
		}
	}
	for(int i = mtt.size()-1; i >= 0; i--)
		if (!mtss[mtt[i]])
			mtt.erase(mtt.begin()+i);
}

void recovermt(map<int, vector<int> > & mp)
{
	for(auto it = mp.begin(); it != mp.end(); it++)
	{
		int m = (*it).first;
		mtss[m] += (*it).second.size();
		for(int i = 0; i < (*it).second.size(); i++)
		{
			int s = (*it).second[i];
			mts1[m][s] = true;
			if (!square[s])
			{
				square[s] = true;
				as++;
			}
		}
	}
}

bool cmp(int a, int b)
{
	return mtss[a] > mtss[b];
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
		if (mtss[mtt[0]] == 1)
		{
			set<int> st;
			int s=0;
			for(int i = mtt.size()-1; i >= 0 && d+s <= dd; i--)
			{
				int sq;
				for(sq = 0; !mts1[mtt[i]][sq]; sq++);
				if (!st.count(sq))
				{
					st.insert(sq);
					s++;
				}
			}
			return  (d+s == dd) ? dd : 0;
		}
		int a = 0, k;
		for(k = 0; a < as; k++)
			a += mtss[mtt[k]];
		if (k+d > dd)
			return 0;
		
		vector<int> mttback = mtt;
		int r, s = mtt.size();
		cout<<s<<endl;
		for(int i = 0; i < s; i++)
		{
			map<int, vector<int> > mp;
			removemt(i, mp);	//火柴拿走, 正方形破坏
			mtv[mtt[i]] = false;
			r = ida(d+1);
			if (r > 0)
				return r;
			mtt = mttback;
			recovermt(mp);
			mtv[mtt[i]] = true;
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
