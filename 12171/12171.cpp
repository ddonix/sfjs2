#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Adis
{
	int x;
	int y;
	int z;
	Adis & operator=(const Adis & b)
	{
		x = b.x;
		y = b.y;
		z = b.z;
		return *this;
	}
	
	bool operator==(const Adis & b) const
	{
		return (x == b.x && y == b.y && z == b.z);
	}
	
	bool operator<(const Adis & b) const
	{
		if (x != b.x) return x < b.x;
		if (y != b.y) return y < b.y;
		if (z != b.z) return z < b.z;
		return false;
	}
	
	Adis() : x(-1), y(-1), z(-1) {}
	Adis(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}
};

struct Box
{
	Adis a0;
	Adis a1;
	int t;	//0:铜 1:空气

	Box(){}
	Box(Adis l, Adis r, int type)
	{
		a0 = l;
		a1 = r;
		t = type;
	}

	int v()
	{
		return (a1.x-a0.x)*(a1.y-a0.y)*(a1.z-a0.z);
	}
	
	bool relation(Adis a, string type)
	{
		if ("YZ" == type)	//在yz平面上
			return (a.y >= a0.y) && (a.y <= a1.y) && (a.z >= a0.z) && (a.z <= a1.z);
		else if ("XZ" == type)	//在xz平面上
			return (a.x >= a0.x) && (a.x <= a1.x) && (a.z >= a0.z) && (a.z <= a1.z);
		else if ("XY" == type)	//在xy平面上
			return (a.x >= a0.x) && (a.x <= a1.x) && (a.y >= a0.y) && (a.y <= a1.y);
		return true;
	}
};

const int maxn = 500;
Box box[maxn];		//铜盒子

int nk;
int nc;

int area;
int volume;

vector<int> adis_all[3];
vector<int> adis_c[3];
vector<int> adis_m[3];
set<int> aset[3];
set<Adis> cu;

bool Findcube(Adis a, Adis &a0, Adis &a1)
{
	vector<Box> v;
	int x0,y0,z0, x1,y1,z1;
	for(int i = 0; i < nc+nk; i++)
		if (box[i].relation(a, "YZ"))
			v.push_back(box[i]);
	x0 = 0;
	x1 = adis_c[0].back()+2;
	for(int i = 0; i < v.size(); i++)
	{
		if (v[i].a1.x < a.x && v[i].a1.x > x0) x0 = v[i].a1.x;
		if (v[i].a0.x > a.x && v[i].a0.x < x1) x1 = v[i].a0.x;
	}
	
	Adis t0(a), t1(a);
	t0.x = x0;
	t1.x = x1;
	v.clear();
	for(int i = 0; i < nc+nk; i++)
		if (box[i].relation(t0, "XZ") || box[i].relation(t1, "XZ"))
			v.push_back(box[i]);
	y0 = 0;
	y1 = adis_c[1].back()+2;
	for(int i = 0; i < v.size(); i++)
	{
		if (v[i].a1.y < a.y && v[i].a1.y > y0) y0 = v[i].a1.y;
		if (v[i].a0.y > a.y && v[i].a0.y < y1) y1 = v[i].a0.y;
	}
	
	t0.y = y0;
	t1.y = y0;
	Adis t2(t0), t3(t1);
	t2.y = y1;
	t3.y = y1;
	for(int i = 0; i < nc+nk; i++)
		if (box[i].relation(t0, "XY") || box[i].relation(t1, "XY") ||
							box[i].relation(t2, "XY") || box[i].relation(t3, "XY"))
			v.push_back(box[i]);
	z0 = 0;
	z1 = adis_c[2].back()+2;
	for(int i = 0; i < v.size(); i++)
	{
		if (v[i].a1.z < a.z && v[i].a1.z > z0) z0 = v[i].a1.z;
		if (v[i].a0.z > a.z && v[i].a0.z < z1) z1 = v[i].a0.z;
	}
	
	a0 = Adis(x0, y0, z0);
	a1 = Adis(x1, y1, z1);
	//cout<<x0<<" "<<x1<<endl;
	//cout<<y0<<" "<<y1<<endl;
	//cout<<z0<<" "<<z1<<endl;
}

void bfs()
{
	queue<Adis> q;
	Adis a(1,1,1);
	q.push(a);
	
	nk = 0;
	area = volume = 0;
	while(!q.empty())
	{
		a = q.front();
		q.pop();
		if (cu.count(a))
			continue;
		cu.insert(a);

		Adis a1, a2;
		Findcube(a, a1, a2);
		Box b = Box(a1, a2, 1);
		box[nc+nk++] = b;
		volume += b.v();
	}
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
			adis_c[i].clear();
		}
		cu.clear();
		
		for(int i = 0; i < nc; i++)
		{
			int x0, y0, z0, x, y, z;
			cin>>x0>>y0>>z0>>x>>y>>z;
			x0 *= 2;
			y0 *= 2;
			z0 *= 2;
			x = 2*x+x0;
			y = 2*y+y0;
			z = 2*z+z0;
			box[i] = Box(Adis(x0, y0, z0), Adis(x, y, z), 0);
			aset[0].insert(x0);
			aset[0].insert(x);
			aset[1].insert(y0);
			aset[1].insert(y);
			aset[2].insert(z0);
			aset[2].insert(z);
		}
		for(int i = 0; i < 3; i++)
		{
			int j = 0;
			adis_c[i].resize(aset[i].size());
			for(auto it = aset[i].begin(); it != aset[i].end(); it++)
				adis_c[i][j] = *it;
			
			sort(adis_c[i].begin(), adis_c[i].end());
			
			adis_m[i].resize(adis_c[i].size()+1);
			adis_all[i].resize(adis_c[i].size()*2+2);
			adis_all[i][0] = 0;
			adis_all[i][1] = 1;
			adis_m[i][0] = 1;
			for(int j = 0; j < adis_c[i].size(); j++)
			{
				adis_all[i][j*2+2] = adis_c[i][j];
				adis_all[i][j*2+3] = adis_c[i][j]+1;
				adis_m[i][j+1] = adis_c[i][j]+1;
			}
		}
		bfs();
		cout<<area<<" "<<volume<<endl;
	}
}
