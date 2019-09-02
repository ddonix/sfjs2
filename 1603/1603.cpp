#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 5;
const int maxsq = maxn*maxn*maxn;
const int maxm = 2*(maxn+1)*maxn;

//左上顶点,高
struct SQuare
{
	int x;
	int y;
	int l;		//the length of square
	bool v;		//valid flag
};

struct MatchStick
{
	int p;		//position
	vector<int> sq;	//

	MatchStick(int p_, int sq_)
	{
		p = p_;
		sq.push_back(sq_);
	}

	bool operator<(const MatchStick & b) const
	{
		return sq.size() > b.sq.size();
	}
};

struct Find
{
	Find(int p_) : p(p_) {}
	bool operator()(const MatchStick & b)
	{
		return p == b.p;
	}
	int p;
};

bool mtv[maxm];
SQuare square[maxsq];
vector<MatchStick> mtt;

int ns;
int ne;
int cne;

int n, k;
int dd;

void inline itoaxis(int i, int &x, int & y)
{
	int t = i%(2*n+1);
	x = i/(2*n+1);
	y = (t < n) ? t : t-n;
}

int inline axistoi(int rc, int x, int y)
{
	return (0 == rc) ? x*(2*n+1)+y : x*(2*n+1)+y+n;
}

void initialize()
{
	ns = 0;
	for(int x = 0; x < n; x++)
		for(int y = 0; y < n; y++)
		{
			for(int l = 1; l <= n; l++)
			{
				if (x + l > n || y + l > n)
					continue;
				bool v = true;
				for(int k = 0; k < l && v; k++)
				{
					if (!((mtv[axistoi(0, x,y+k)] && mtv[axistoi(0, x+l, y+k)] 
							&& mtv[axistoi(1, x+k, y)] && mtv[axistoi(1, x+k, y+l)])))
						v = false;
				}
				if (!v)
					continue;
				square[ns].x = x;
				square[ns].y = y;
				square[ns].l = l;
				square[ns].v = true;
				for(int k = 0; k < l; k++)
				{
					auto it = find_if(mtt.begin(), mtt.end(), Find(axistoi(0, x, y+k)));
					if (it != mtt.end())
						(*it).sq.push_back(ns);
					else
						mtt.push_back(MatchStick(axistoi(0, x, y+k), ns));
					
					it = find_if(mtt.begin(), mtt.end(), Find(axistoi(0, x+l, y+k)));
					if (it != mtt.end())
						(*it).sq.push_back(ns);
					else
						mtt.push_back(MatchStick(axistoi(0, x+l, y+k), ns));
					
					it = find_if(mtt.begin(), mtt.end(), Find(axistoi(1, x+k, y)));
					if (it != mtt.end())
						(*it).sq.push_back(ns);
					else
						mtt.push_back(MatchStick(axistoi(1, x+k, y), ns));
					
					it = find_if(mtt.begin(), mtt.end(), Find(axistoi(1, x+k, y+l)));
					if (it != mtt.end())
						(*it).sq.push_back(ns);
					else
						mtt.push_back(MatchStick(axistoi(1, x+k, y+l), ns));
				}
				ns++;
			}
		}
	sort(mtt.begin(), mtt.end());
}


vector<int> updatemtt(int m)
{
	int p = mtt[m].p;
	vector<int> sq = mtt[m].sq;
	
	for(int i = 0; i < mtt[m].sq.size(); i++)
		square[mtt[m].sq[i]].v = false;
	mtt.erase(mtt.begin()+m);
	for(int i = mtt.size()-1; i >= 0; i--)
	{
		for(int j = mtt[i].sq.size()-1; j >= 0; j--)
		{
			auto it = find(sq.begin(), sq.end(), mtt[i].sq[j]);
			if (it != sq.end())
				mtt[i].sq.erase(mtt[i].sq.begin()+j);
		}
		if (mtt[i].sq.empty())
			mtt.erase(mtt.begin()+i);
	}
	return sq;
}

int ida(int d)
{
	if (d == dd)
	{
		if (mtt.empty())
			return dd;
		return 0;
	}
	else
	{
		if (mtt[0].sq.size() == 1)
		{
			set<int> se;
			for(int i = 0; i < mtt.size(); i++)
				se.insert(mtt[i].sq[0]);
			return d+se.size();
		}
		int a = 0, k;
		for(k = 0; k < mtt.size() && a < ns; k++)
			a += mtt[k].sq.size();
		if (k+d > dd)
			return 0;

		int r;
		vector<MatchStick> mttback = mtt;
		for(int i = 0; i < mtt.size(); i++)
		{
			int p = mtt[i].p;
			vector<int> sq = updatemtt(i);		//正方形破坏
			mtv[p] = false;				//火柴拿走
			ns -= sq.size();
			r = ida(d+1);
			if (r > 0)
				return r;
			mtt = mttback;
			mtv[p] = true;
			ns += sq.size();
			for(int i = 0; i < sq.size(); i++)
				square[sq[i]].v = true;
		}
	}
	return 0;
}

int main()
{
	int T,t;
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		ne = 2*(n+1)*n;
		for(int i = 0; i < ne; i++)
			mtv[i] = true;
		for(int i = 0; i < k; i++)
		{
			cin>>t;
			mtv[t-1] = false;
		}
		cne = ne - k;
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
