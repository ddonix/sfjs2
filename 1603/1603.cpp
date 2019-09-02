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

void itoaxis(int i, int &x, int & y)
{
	int t = i%(2*n+1);
	x = i/(2*n+1);
	y = (t < n) ? t : t-n;
}

int axistoi(int rc, int x, int y)
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


void updatemtt(int p)
{

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
		vector<MatchStick> mttback = mtt;
		
		if (mtt[0].sq.size() == 1)
		{
			set<int> se;
			for(int i = 0; i < mtt.size(); i++)
				se.insert(mtt[i].sq[0]);
			return d+se.size();
		}

		int r;
		for(int i = 0; i < mtt.size(); i++)
		{
			int p = mtt[i].p;
			mtv[p] = false;
			updatemtt(p);
			r = ida(d+1);
			if (r > 0)
				return r;
			mtt = mttback;
			mtv[p] = true;
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
			int r = ida(dd);
			if (!r)
				continue;
			cout<<r<<endl;
			break;
		}
	}
}
