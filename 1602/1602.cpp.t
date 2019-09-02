/* 思路：1.判重！！！切片思想
 * 	 2.减少枚举次数！！！对称的，只枚举一边。
 * 
*/
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

const int maxn = 10;
int w,h, n;

bool cmpvec(const int * v1, const int * v2, int n)
{
	bool h=true, t=true;
	for(int i = 0; i < n && (h || t); i++)
	{
		if (h && v1[i] != v2[i])
			h = false;
		if (t && v1[i] != v2[n-1-i])
			t = false;
	}
	return h || t;
}

struct Polyom
{
	set<pair<int, int> > c;
	int l, r, u, d;
	int xr, yr;

	unsigned long codex, codey;	//每个连通块编一个代码
	bool xbalance, ybalance;
	int xa[maxn], ya[maxn];

	Polyom(){}
	Polyom(const Polyom & b)
	{
		c = b.c;
		l = b.l;
		r = b.r;
		u = b.u;
		d = b.d;
		xr = b.xr;
		yr = b.yr;
		xbalance = b.xbalance;
		ybalance = b.ybalance;
		for(int i = 0; i < xr; i++)
			xa[i] = b.xa[i];
		for(int i = 0; i < yr; i++)
			ya[i] = b.ya[i];
	}
	
	bool operator!=(const Polyom & r) const
	{
		return !(*this == r);
	}

	void update()
	{
		xbalance = ybalance = true;
		memset(xa, 0, sizeof(int)*xr);
		memset(ya, 0, sizeof(int)*yr);
		int maxx = 0, maxy = 0;
		for(auto it = c.begin(); it != c.end(); it++)
		{
			if (xbalance && c.count(make_pair(l+r-(*it).first, (*it).second)) < 1)
				xbalance = false;
			if (ybalance && c.count(make_pair((*it).first, u+d-(*it).second)) < 1)
				ybalance = false;
			xa[(*it).first-l]++;
			ya[(*it).second-d]++;
		}
		for(int i = 0; i < xr; i++)
			maxx = xa[i] > maxx ? xa[i] : maxx;
		for(int i = 0; i < yr; i++)
			maxy = ya[i] > maxy ? ya[i] : maxy;
		codex = (maxx > 7) ? 0x8000 : 0;
		codey = (maxy > 7) ? 0x8000 : 0;

		bool dir;
		if (xbalance)
			dir = true;
		else
		{
			int i,j;
			for(i = 0, j = n-1; xa[i] == xa[j]; i++, j--);
			dir = xa[i] < xa[j];
		}
		for(int i = 0; i < xr; i++)
			codex |= (xa[dir ? i : n-1-i] << (maxx > 7 ? 4: 3)*i);
		
		
		if (ybalance)
			dir = true;
		else
		{
			int i,j;
			for(i = 0, j = n-1; ya[i] == ya[j]; i++, j--);
			dir = ya[i] < ya[j];
		}
		for(int i = 0; i < yr; i++)
			codey |= (ya[dir ? i : n-1-i] << (maxy > 7 ? 4: 3)*i);
	}
	
	bool operator==(const Polyom  & r) const
	{
		if(!((xr == r.xr && yr == r.yr) || (xr == r.yr && yr == r.xr)))
			return false;

		if (xr == yr)
		{
			if (cmpvec(xa, r.xa, xr) && cmpvec(ya, r.ya, xr))
				return true;
			return cmpvec(xa, r.ya, xr) && cmpvec(ya, r.xa, xr);
		}
		if (xr == r.xr)
			return cmpvec(xa, r.xa, xr) && cmpvec(ya, r.ya, yr);
		else
			return cmpvec(xa, r.ya, xr) && cmpvec(ya, r.xa, yr);
	}
};

vector<Polyom> se[maxn];

int ans;
int dx[] = { 0, 0, -1, 1};
int dy[] = {-1, 1,  0, 0};

void buildtable()
{
	se[0].resize(1);
	Polyom & p1 = se[0][0];
	
	p1.c.insert(make_pair(0,0));
	p1.l = p1.r = p1.u = p1.d = 0;
	p1.xr = p1.yr = 1;
	p1.update();
	
	for(int i = 1; i < maxn; i++)
	{
		for(auto it = se[i-1].begin(); it != se[i-1].end(); it++)
		{
			Polyom & p = *it;
			for(auto it2 = p.c.begin(); it2 != p.c.end(); it2++)
			{
				/*
				if (p.xbalance)
				{       
					if(p.r + p.l <= 0 && (*it2).first < 0) 
						continue;
					else if(p.r + p.l > 0 && (*it2).first > 0) 
						continue;
				}
				if (p.ybalance)
				{
					if(p.u + p.d <= 0 && (*it2).second < 0)
						continue;
					else if(p.u + p.d > 0 && (*it2).second > 0)
						continue;
				}*/
				for(int d = 0; d < 4; d++)
				{
					int x = (*it2).first+dx[d], y = (*it2).second+dy[d];
					bool iflag = false;
					Polyom np = p;
					if (x > np.r)
					{
						np.r = x;
						iflag = true;
					}
					else if (x < np.l)
					{
						np.l = x;
						iflag = true;
					}
				        else if (y > np.u)
					{
						np.u = y;
						iflag = true;
					}
					else if (y < np.d)
					{
						np.d = y;
						iflag = true;
					}
					pair<int, int> pa = make_pair(x,y);
					if (iflag)
						np.c.insert(pa);
					else if (np.c.count(pa) < 1)
						np.c.insert(pa);
					else
						continue;
					np.xr = np.r - np.l + 1;
					np.yr = np.u - np.d + 1;
					np.update();
					int j;
					for(j = 0; j < se[i].size() && se[i][j] != np; j++);
					if (j == se[i].size())
						se[i].push_back(np);
				}
			}
		}
	}
}

int main()
{
	buildtable();
	while(cin>>n>>w>>h)
	{
		int t;
		if (w > h)
		{
			t = w;
			w = h;
			h = t;
		}
		ans = 0;
		for(int i = 0; i < se[n-1].size(); i++)
		{
			if (se[n-1][i].xr <= w && se[n-1][i].yr <= h)
				ans++;
			else if (se[n-1][i].yr <= w && se[n-1][i].xr <= h)
				ans++;
		}
		cout<<ans<<endl;
	}
}
