#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct MAP
{
	string name;
	double w, e;
	double n, s;
	double area;
	double ratio;

	MAP(){}
	
	MAP(const string & na, double x1, double y1, double x2, double y2)
	{
		name = na;
		w = (x1 < x2) ? x1 : x2;
		e = (x1 < x2) ? x2 : x1;
		n = (y1 < y2) ? y2 : y1;
		s = (y1 < y2) ? y1 : y2;
		
		area  = (n-s)*(e-w);
		ratio = (n-s)/(e-w) - 0.75;
		ratio = (ratio > 0) ? ratio  : -ratio;
	}
	
	MAP(const MAP & m)
	{
		name = m.name;
		w = m.w;
		e = m.e;
		n = m.n;
		s = m.s;
		area  = m.area;
		ratio = m.ratio;
	}
};

struct LOCATION
{
	double x, y;
	
	bool mflag;
	vector<int> mindex;

	LOCATION(){}
	LOCATION(double xx, double yy):x(xx), y(yy) 
	{
		mflag = false;
	}
	
	LOCATION(const LOCATION & loca)
	{
		x = loca.x;
		y = loca.y;
		mflag = false;
	}
};

vector<MAP> maps;
map<string, LOCATION> locations;

class cmp
{
public:	
	cmp(double xx, double yy) : x(xx), y(yy) {}
	bool operator()(int a, int b) const 
	{
		if (maps[a].area != maps[b].area)
			return maps[a].area > maps[b].area;
	
		double length1, length2;
		length1 = (2*x-maps[a].w-maps[a].e)*(2*y-maps[a].n-maps[a].s);
		length2 = (2*x-maps[b].w-maps[b].e)*(2*y-maps[b].n-maps[b].s);
		if (length1 != length2)
			return length1 > length2;
	
		if (maps[a].ratio != maps[b].ratio)
			return maps[a].ratio > maps[b].ratio;
	
		double lowr1, lowr2;
		lowr1 = (maps[a].e-x)*(maps[a].e-x)+(y-maps[a].s)*(y-maps[a].s);
		lowr2 = (maps[b].e-x)*(maps[b].e-x)+(y-maps[b].s)*(y-maps[b].s);
		if (lowr1 != lowr2)
			return lowr1 > lowr2;

		return maps[a].w > maps[b].w;
	}

private:	
	double x, y;
};

int main()
{
	int nm;
	string s;
	cin>>s;
	
	nm = 0;
	maps.resize(100);
	while(cin>>s && s != "LOCATIONS")
	{
		double x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		maps[nm++] = MAP(s, x1, y1, x2, y2);
		if(!(nm%100))
			maps.resize(nm+100);
	}
	maps.resize(nm);
	
	while(cin>>s && s != "REQUESTS")
	{
		double x,y;
		cin>>x>>y;
		locations[s] = LOCATION(x, y);
	}
	
	while(cin>>s && s != "END")
	{
		int level;
		cin>>level;
		cout<<s<<" at detail level "<<level;
		if(locations.count(s) < 1)
		{
			cout<<" unknown location"<<endl;
			continue;
		}
		if(!locations[s].mflag)
		{
			double x,y;
			int j = 0;
			x = locations[s].x;
			y = locations[s].y;
			for(int i = 0; i < nm; i++)
			{
				if(x > maps[i].w && x < maps[i].e && y > maps[i].s && y < maps[i].n)
					locations[s].mindex.push_back(i);
			}
			sort(locations[s].mindex.begin(), locations[s].mindex.end(), cmp(x,y));
			for(int i = 0; i < locations[s].mindex.size(); i++)
			{
				int j = locations[s].mindex[i];
			//	cout<<maps[j].name<<" "<<maps[j].area<<endl;
			}
			locations[s].mflag = true;
		}
		if (locations[s].mindex.empty())
			cout<<" no map contains that location"<<endl;
		else if(level > locations[s].mindex.size())
		{
			int i = locations[s].mindex.back();
			cout<<" no map at that detail level; using "<<maps[i].name<<endl;
		}
		else
		{
			int i = locations[s].mindex[level-1];
			cout<<" using "<<maps[i].name<<endl;
		}
	}
}
