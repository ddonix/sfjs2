#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Box
{
	int al[3];
	int ag[3];
	
	Box(){}
	Box(int x0, int y0, int z0, int x1, int y1, int z1)
	{
		al[0] = x0;
		al[1] = y0;
		al[2] = z0;
		ag[0] = x1;
		ag[1] = y1;
		ag[2] = z1;
	}
	
	bool include(const Box & right)
	{
		for(int i = 0; i < 3; i++)
			if (!(al[i] <= right.al[i] && ag[i] >= right.ag[i]))
				return false;
		return true;
	}

	bool include(int x, int y, int z)
	{
		if (!(x >= al[0] && x <= ag[0])) return false;
		if (!(y >= al[1] && y <= ag[1])) return false;
		if (!(z >= al[2] && z <= ag[2])) return false;
		return true;
	}
};

const int maxn = 50;
Box box[maxn];
int n;

int area;
int volume;

vector<int> adis[3];
vector<int> adis_c[3];
set<int> aset[3];

void bfs()
{
	queue<int *> q;
	int a[3] = {1, 1, 1};
	q.push(a);
	while(!q.empty())
	{
	
	}
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i = 0; i < 3; i++)
		{
			aset[i].clear();
			adis_c[i].clear();
		}
		for(int i = 0; i < n; i++)
		{
			int x0, y0, z0, x, y, z;
			cin>>x0>>y0>>z0>>x>>y>>z;
			x0 *= 2;
			y0 *= 2;
			z0 *= 2;
			x = 2*x+x0;
			y = 2*y+y0;
			z = 2*z+z0;
			box[i] = Box(x0, y0, z0, x, y, z);
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
			{
				adis_c[i][j] = *it;
			}
			sort(adis_c[i].begin(), adis_c[i].end());
			
			adis[i].resize(adis_c[i].size()*2+2);
			adis[i][0] = 0;
			adis[i][1] = 1;
			for(int j = 0; j < adis_c[i].size(); j++)
			{
				adis[i][j*2+2] = adis_c[i][j];
				adis[i][j*2+3] = adis_c[i][j]+1;
			}
		}
		bfs();
		cout<<area<<" "<<volume<<endl;
	}
}
