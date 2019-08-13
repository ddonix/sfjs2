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

vector<int> adis[3];
set<int> aset[3];

struct Index
{
	int id[3];
	Index(int i0, int i1, int i2)
	{
		id[0] = i0;
		id[1] = i1;
		id[2] = i2;
	}

	Index next(int fx)
	{
		Index temp = Index(id[0], id[1], id[2]);
		if (fx == 0) temp.id[0]++;
		if (fx == 1) temp.id[0]--;
		if (fx == 2) temp.id[1]++;
		if (fx == 3) temp.id[1]--;
		if (fx == 4) temp.id[2]++;
		if (fx == 5) temp.id[2]--;
		return temp;
	}
	
	bool operator< (const Index & right) const 
	{ 
		for(int i = 0; i < 3; i++)
			if (id[i] != right.id[i])
				return id[i] < right.id[i];
		return false;
	}
};

//Box box[maxn];		//0 --- n-1铜盒子, n -- n+nc-1 空气盒子
struct Box
{
	Adis a0;
	Adis a1;
	int t;		//0:铜 1:空气
	int touch;	//面积
	int volume;
	int edge[6];

	Box(){}
	Box(Adis l, Adis r)	//铜
	{
		a0 = l;
		a1 = r;
		t = 0;
		volume =  (a1.a[0]-a0.a[0])*(a1.a[1]-a0.a[1])*(a1.a[2]-a0.a[2]);
	}

	int relation(const Box & b)
	{
		int u0, v0, u1, v1;
		int o0, p0, o1, p1;
		for(int i = 0; i < 3;i++)
		{
			u0 = ((i==0) ? a0.a[1] : a0.a[0]);
			u1 = ((i==0) ? a1.a[1] : a1.a[0]);
			v0 = ((i==2) ? a0.a[2] : a0.a[1]);
			v1 = ((i==2) ? a1.a[2] : a1.a[1]);
			
			o0 = ((i==0) ? b.a0.a[1] : b.a0.a[0]);
			o1 = ((i==0) ? b.a1.a[1] : b.a1.a[0]);
			p0 = ((i==2) ? b.a0.a[2] : b.a0.a[1]);
			p1 = ((i==2) ? b.a1.a[2] : b.a1.a[1]);
			if((u0 <= o0) && (u1 >= o1) && (v0 <= p0) &&(v1 >= p1))
			{
				if (a0.a[i] > b.a1.a[i] || a1.a[i] < b.a0.a[i])
					return -1;		//分离
				if (a0.a[i] == b.a0.a[i] || a1.a[i] == b.a1.a[i])
					return -2;		//重合
				if (a0.a[i] == b.a1.a[i])
					return 2*i;
			 	else if	(a1.a[i] == b.a0.a[i])
					return 2*i+1;

			}
		}
		return -1;
	}
};

const int maxn = 1000;
const int EDGE = 510;
Box box[maxn];		//0 --- n-1铜盒子, n -- n+nc-1 空气盒子

int nk;
int nc;

int area;
int volume;

Box makeBox(Adis a0, Adis a1)
{
	bool af[6];
	Box b = Box(a0, a1);
	for(int i = 0; i < 6; i++)
		b.edge[i] = 1;
	b.t = 0;
	for(int i = 0; i < nc; i++)
	{
		int r = box[i].relation(b);
		if (r == -2)
			return b;
		if(r >= 0)
			b.edge[r] = 0;
	}
	b.t = 1;			//空气
	b.touch = 0;
	for(int i = 0; i < 6; i++)
	{
		int area;
		if ((0 == i) || (1 == i))
			area = (b.a1.a[1] - b.a0.a[1])*(b.a1.a[2] - b.a0.a[2]);
		else if ((2 == i) || (3 == i))
			area = (b.a1.a[0] - b.a0.a[0])*(b.a1.a[2] - b.a0.a[2]);
		else
			area = (b.a1.a[0] - b.a0.a[0])*(b.a1.a[1] - b.a0.a[1]);
		
		if (b.edge[i] == 0)
			b.touch += area;
	}
	return b;
}

set<Index> cu;
void bfs()
{
	queue<pair<Index, int> > q;
	q.push(make_pair(Index(0,0,0), 0));		//小点
	
	nk = 0;
	area = volume = 0;
	while(!q.empty())
	{
		int edge[6];				//0:铜 1:空气
		Index ind = (q.front()).first;
		edge[(q.front()).second] = 1;
		
		q.pop();
		if (cu.count(ind))
			continue;
		cu.insert(ind);

		bool mb = true;
		for(int i = 0; i < 3; i++)
		{
			if(ind.id[i] > 0)
				q.push(make_pair(ind.next(i*2+1),i*2+1));
			
			if(ind.id[i] < adis[i].size()-2)
				q.push(make_pair(ind.next(i*2), i*2));
			else if(ind.id[i] > adis[i].size()-2)
				mb = false;
		}
		if (!mb)
			continue;
		
		Adis a0, a1;
		for(int i = 0; i < 3; i++)
		{
			a0.a[i] = adis[i][ind.id[i]];
			a1.a[i] = adis[i][ind.id[i]+1];
		}
		Box b = makeBox(a0, a1);
		cout<<b.t<<" "<<b.touch<<" "<<"("<<a0.a[0]<<" "<<a0.a[1]<<" "<<a0.a[2]<<") ("<<a1.a[0]<<" "<<a1.a[1]<<" "<<a1.a[2]<<")"<<endl; 
		if (b.t == 1)
		{
			volume += b.volume;
			area += b.touch;
			box[nc+nk] = b;
			nk++;
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
