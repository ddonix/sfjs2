#include <iostream> 
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50;
const int EDGE = 102;
const int maxd = 102;

int 
vector<int> adis[3];
int adisn[3];

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
};

struct Box
{
	int a0[3];
	int a1[3];
	int t;		//0:铜 1:空气
	int touch;	//接触面积
	int volume;	//体积
	int edge[6];

	Box(){}
	Box(const int a0_[3], const int a1_[3]) : t(0)	//铜
	{
		for(int i = 0; i < 3; i++)
		{
			a0[i] = a0_[i];
			a1[i] = a1_[i];
		}
	}

	int relation(const Box & b) const
	{
		int u0, v0, u1, v1;
		int o0, p0, o1, p1;
		for(int i = 0; i < 3;i++)
		{
			u0 = ((i==0) ? a0[1] : a0[0]);
			u1 = ((i==0) ? a1[1] : a1[0]);
			v0 = ((i==2) ? a0[1] : a0[2]);
			v1 = ((i==2) ? a1[1] : a1[2]);
			
			o0 = ((i==0) ? b.a0[1] : b.a0[0]);
			o1 = ((i==0) ? b.a1[1] : b.a1[0]);
			p0 = ((i==2) ? b.a0[1] : b.a0[2]);
			p1 = ((i==2) ? b.a1[1] : b.a1[2]);
			if((u0 <= o0) && (u1 >= o1) && (v0 <= p0) &&(v1 >= p1))
			{
				if (a0[i] > b.a1[i] || a1[i] < b.a0[i])
					return -1;		//分离
				if (a0[i] <= b.a0[i] && a1[i] > b.a0[i])
					return -2;		//重合
				if (a1[i] >= b.a1[i] && a0[i] < b.a1[i])
					return -2;		//重合
				if (a0[i] == b.a1[i])
					return 2*i;
			 	if (a1[i] == b.a0[i])
					return 2*i+1;
				cout<<"*******************************"<<endl;
			}
		}
		return -1;
	}
};

Box box[maxn];		//0 --- n-1铜盒子
int n;

bool isAir(Box & b)
{
	for(int i = 0; i < 6; i++)
		b.edge[i] = 1;
	for(int i = 0; i < n; i++)
	{
		int r = box[i].relation(b);
		if (r == -2)
			return false;
		if(r >= 0)
			b.edge[r] = 0;
	}
	b.t = 1;			//空气
	b.volume =  (b.a1[0]-b.a0[0])*(b.a1[1]-b.a0[1])*(b.a1[2]-b.a0[2]);
	b.touch = 0;
	for(int i = 0; i < 6; i++)
	{
		int ar;
		if ((0 == i) || (1 == i))
			ar = (b.a1[1] - b.a0[1])*(b.a1[2] - b.a0[2]);
		else if ((2 == i) || (3 == i))
			ar = (b.a1[0] - b.a0[0])*(b.a1[2] - b.a0[2]);
		else
			ar = (b.a1[0] - b.a0[0])*(b.a1[1] - b.a0[1]);
		
		if (b.edge[i] == 0)
			b.touch += ar;
	}
	return true;
}

int vis[maxd][maxd][maxd];
int area;
int volume;
void bfs()
{
	queue<Index> q;
	q.push(Index(0,0,0));
	
	area = volume = 0;
	memset(vis, 0, sizeof(vis));
	while(!q.empty())
	{
		Index ind = q.front();
		q.pop();

		if (vis[ind.id[0]][ind.id[1]][ind.id[2]])
			continue;
		vis[ind.id[0]][ind.id[1]][ind.id[2]] = 1;

		bool mb = true;
		for(int i = 0; i < 3; i++)
		{
			if(ind.id[i] > 0)
				q.push(ind.next(i*2+1));
			
			if(ind.id[i] < adisn[i]-2)
				q.push(ind.next(i*2));
			else if(ind.id[i] > adisn[i]-2)
				mb = false;
		}
		if (!mb)
			continue;
		
		int a0[3], a1[3];
		for(int i = 0; i < 3; i++)
		{
			a0[i] = adis[i][ind.id[i]];
			a1[i] = adis[i][ind.id[i]+1];
		}
		Box b(a0, a1);
		if (isAir(b))
		{
			volume += b.volume;
			area += b.touch;
		}
		//cout<<b.t<<" "<<b.touch<<" "<<"("<<a0[0]<<" "<<a0[1]<<" "<<a0[2]<<") ("<<a1[0]<<" "<<a1[1]<<" "<<a1[2]<<")"<<endl; 
	}
	volume = EDGE*EDGE*EDGE - volume;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		set<int> aset[3];
		cin>>n;
		for(int i = 0; i < 3; i++)
			adis[i].clear();
		
		for(int i = 0; i < n; i++)
		{
			int a0[3], a1[3];
			cin>>a0[0]>>a0[1]>>a0[2]>>a1[0]>>a1[1]>>a1[2];
			for(int j = 0; j < 3; j++)
			{
				a1[j] += a0[j];
				aset[j].insert(a0[j]);
				aset[j].insert(a1[j]);
			}
			box[i] = Box(a0, a1);
		}
		for(int i = 0; i < 3; i++)
		{
			int j = 1;
			adisn[i] = aset[i].size()+2;
			adis[i].resize(adisn[i]);
			
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
