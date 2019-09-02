#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Adis
{
	int a[3];
	Adis & operator=(const Adis & b)
	{
		for(int i = 0; i < 3; i++) a[i] = b.a[i];
		return *this;
	}
	
	bool operator==(const Adis & b) const
	{
		return (a[0] == b.a[0] && a[1] == b.a[1] && a[2] == b.a[2]);
	}
	
	bool operator<(const Adis & b) const
	{
		for(int i = 0; i < 3; i++)
			if (a[i] != b.a[i])
				return a[i] < b.a[i];
		return false;
	}
	
	Adis() {};
	Adis(int x, int y, int z)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
	}
	Adis(int aa[3])
	{
		for(int i = 0; i < 3; i++) a[i] = aa[i];
	}
};

struct Plane
{
	int a0[2];
	int a1[2];
	Plane(){};
	Plane & operator=(const Plane & p)
	{
		for(int i = 0; i < 2; i++) 
		{
			a0[i] = p.a0[i];
			a1[i] = p.a1[i];
		}
		return *this;
	}
	Plane(int u0, int v0, int u1, int v1)
	{
		a0[0] = u0;
		a0[1] = v0;
		a1[0] = u1;
		a1[1] = v1;
	}
	
	bool istouch(int u, int v)
	{
		return !(u < a0[0] || u > a1[0] || v < a0[1] || v > a1[1]);
	}
	
	bool istouch(int u0, int v0, int u1, int v1)
	{
		if ((u0 == u1) || (v0 == v1))
			return !(u0 < a0[0] || u1 > a1[0] || v0 < a0[1] || v1 > a1[1]);
		else
			return !(u1 < a0[0] || u0 > a1[0] || v1 < a0[1] || v0 > a1[1]);

	}
};

//Box box[maxn];		//0 --- n-1铜盒子, n -- n+nc-1 空气盒子
struct Box
{
	Adis a0;
	Adis a1;
	int t;		//0:铜 1:空气
	int touch;	//面积
	int v;
	int edge[6];

	Box(){}
	Box(Adis l, Adis r)	//铜
	{
		a0 = l;
		a1 = r;
		t = 0;
		v =  (a1.a[0]-a0.a[0])*(a1.a[1]-a0.a[1])*(a1.a[2]-a0.a[2]);
	}

	Box(int e[6])	//空气
	{
		for(int i = 0; i < 6; i++) edge[i] = e[i];
		t = 1;
		touch = 0;
	}

	Plane getplane(string type)
	{
		Plane plane;
		if ("YZ" == type)
			plane = Plane(a0.a[1], a0.a[2], a1.a[1], a1.a[2]);
		else if ("XZ" == type)
			plane = Plane(a0.a[0], a0.a[2], a1.a[0], a1.a[2]);
		else //	"XY" == type
			plane = Plane(a0.a[0], a0.a[1], a1.a[0], a1.a[1]);
		return plane;
	}
	bool istouch(string type, int u, int v)
	{
		Plane plane = getplane(type);
		return plane.istouch(u, v);
	}
	bool istouch(string type, int u0, int v0, int u1, int v1)
	{
		Plane plane = getplane(type);
		return plane.istouch(u0, v0, u1, v1);
	}
};

const int maxn = 1000;
const int EDGE = 510;
Box box[maxn];		//0 --- n-1铜盒子, n -- n+nc-1 空气盒子

int nk;
int nc;

int area;
int volume;

vector<int> adis[3];
set<int> aset[3];
set<Adis> cu;

void makeBox(int i)
{
	bool af[6];
	Box b = box[i];
	for(int i = 0; i < 3; i++)
	{
		b.a0.a[i] = (b.edge[i*2] < 0) ? 0 : (box[b.edge[i*2]].a1.a[i]);
		b.a1.a[i] = (b.edge[i*2+1] < 0) ? EDGE : (box[b.edge[i*2+1]].a0.a[i]);
	}
	
	b.v = (b.a1.a[0] - b.a0.a[0])*(b.a1.a[1] - b.a0.a[1])*(b.a1.a[2] - b.a0.a[2]);
	b.t = 0;
	for(int i = 0; i < 6; i++)
	{
		int area;
		if ((0 == i) || (1 == i))
			area = (b.a1.a[1] - b.a0.a[1])*(b.a1.a[2] - b.a0.a[2]);
		else if ((2 == i) || (3 == i))
			area = (b.a1.a[0] - b.a0.a[0])*(b.a1.a[2] - b.a0.a[2]);
		else
			area = (b.a1.a[0] - b.a0.a[0])*(b.a1.a[1] - b.a0.a[1]);
		
		if (b.edge[i] >= 0 && b.edge[i] < nc) 
			b.t += area;
	}
	box[i] = b;
}

bool Findcube(Adis a, int edge[6])
{
	int t[6];
	for(int i = 0; i < 6; i++) 
		edge[i] = -1;
	for(int i = 0; i < 3; i++) 
	{
		t[i*2] = 0;
		t[i*2+1] = EDGE;
	}
	for(int i = 0; i < nk+nc; i++)
	{
		if (box[i].istouch("YZ", a.a[1], a.a[2]))
		{
			if ((box[i].a1.a[0] <= a.a[0]) && (box[i].a1.a[0] > t[0]))
			{
				t[0] = box[i].a1.a[0];
				edge[0] = i;
			}
			if ((box[i].a0.a[0] >= a.a[0]) && (box[i].a0.a[0] < t[1]))
			{
				t[1] = box[i].a0.a[0];
				edge[1] = i;
			}
		}
	}
	for(int i = 0; i < nk+nc; i++)
	{
		if (box[i].istouch("XZ", t[0], a.a[2], t[1], a.a[2]))
		{
			if ((box[i].a1.a[1] <= a.a[1]) && (box[i].a1.a[1] > t[2]))
			{
				t[2] = box[i].a1.a[1];
				edge[2] = i;
			}
			if ((box[i].a0.a[1] >= a.a[1]) && (box[i].a0.a[1] < t[3]))
			{
				t[3] = box[i].a0.a[1];
				edge[3] = i;
			}
		}
	}
	for(int i = 0; i < nk+nc; i++)
	{
		if (box[i].istouch("XY", t[0], t[2], t[1], t[3]))
		{
			if ((box[i].a1.a[2] <= a.a[2]) && (box[i].a1.a[2] > t[4]))
			{
				t[4] = box[i].a1.a[2];
				edge[4] = i;
			}
			if ((box[i].a0.a[2] >= a.a[2]) && (box[i].a0.a[2] < t[5]))
			{
				t[5] = box[i].a0.a[2];
				edge[5] = i;
			}
		}
	}
	for(int i = 0; i < 6; i++)
		if (edge[i] != -1)
			return true;
	return false;
}

void bfs()
{
	queue<Adis> q;
	Adis a(0,0,0);
	q.push(a);		//小点
	
	nk = 0;
	area = volume = 0;
	while(!q.empty())
	{
		a = q.front();
		q.pop();
		if (cu.count(a))
			continue;
		cu.insert(a);

		int e[6];
		Box b;		//新空气盒子
		Adis next;	//下一个结点
		Adis t;
		if (Findcube(a, e))
		{
			box[nc+nk] = Box(e);
			makeBox(nc+nk);
			
			volume += box[nc+nk].v;
			area += box[nc+nk].touch;
			t = box[nc+nk].a1;

			nk++;
		}
		else
			t = a;
			
		for(int i = 0; i < 3; i++)
		{
			if(t.a[i] < EDGE)
			{
				next = a;
				next.a[i] = *(++find(adis[i].begin(), adis[i].end(), t.a[i]));
				q.push(next);
			}
			if(a.a[i] > 0)
			{
				next = a;
				next.a[i] = *(--find(adis[i].begin(), adis[i].end(), a.a[i]));
				q.push(next);
			}
		}
	}
	volume = EDGE*EDGE*EDGE - volume;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>nc;
		for(int i = 0; i < 3; i++)
		{
			aset[i].clear();
			adis[i].clear();
		}
		cu.clear();
		
		for(int i = 0; i < nc; i++)
		{
			int x0, y0, z0, x1, y1, z1;
			cin>>x0>>y0>>z0>>x1>>y1>>z1;
			x1 += x0;
			y1 += y0;
			z1 += z0;
			box[i] = Box(Adis(x0, y0, z0), Adis(x1, y1, z1));
			aset[0].insert(x0);
			aset[0].insert(x1);
			aset[1].insert(y0);
			aset[1].insert(y1);
			aset[2].insert(z0);
			aset[2].insert(z1);
		}
		for(int i = 0; i < 3; i++)
		{
			int j = 1;
			adis[i].resize(aset[i].size()+2);
			adis[i][0] = 0;
			for(auto it = aset[i].begin(); it != aset[i].end(); it++)
				adis[i][j++] = *it;
			adis[i][j] = EDGE;
			for(auto it = aset[i].begin(); it != aset[i].end(); it++)
			sort(adis[i].begin(), adis[i].end());
		}
		bfs();
		cout<<area<<" "<<volume<<endl;
	}
}
