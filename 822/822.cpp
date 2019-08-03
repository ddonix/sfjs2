#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Req
{
	Req(){}
	Req(int t):t_t(t) {}

	int t_t;
	queue<int> task;
	set<int> p;
};

struct Per
{
	int start_t;	//
	int end_t;	//
	int prev_t;	//
	
	int pri;
	Per(){}
	
	Per(int i) : pri(i), prev_t(-1), start_t(-1), end_t(-1) {}

	bool operator < (const Per & right) const
	{
		if (prev_t != right.prev_t)
			return prev_t < right.prev_t;
		return pri < right.pri;
	}
};

map<int, Req> req;
map<int, Per> per;
const int INF = 0x7fffffff;
int c_time;

int get_reqt()
{
	int t=INF;
	for(auto it = req.begin(); it != req.end(); it++)
		if ((*it).second.task.front() < t)
			t = (*it).second.task.front();
	return t;
}

int main()
{
	int ka = 1;
	int t;
	int N;
	while(cin>>t && t)
	{
		cout<<"#"<<endl;
		req.clear();
		for(int i = 0; i < t; i++)
		{
			int r, num, f, t, b;
			cin>>r>>num>>f>>t>>b;
			req[r] = Req(t);
			for(int j = 0; j < num; j++)
				req[r].task.push(f+b*j);
		}
		
		per.clear();
		cin>>t;
		cout<<"*"<<endl;
		for(int i = 0; i < t; i++)
		{
			int id, nr, r;
			cin>>id>>nr;
			per[id] = Per(i);
			for(int j = 0; j < nr; j++)
			{
				cin>>r;
				req[r].p.insert(id);
			}
		}

		cout<<"Scenario "<<ka++<<": All requests are serviced within ";
		c_time = 0;
		N = req.size();
		int ct1, ct2;
		while(N)
		{
			cout<<__LINE__<<endl;
			for(auto it = per.begin(); it != per.end(); it++)
			{
				if((*it).second.end_t == c_time)
				{
					(*it).second.prev_t = (*it).second.start_t;
					(*it).second.start_t = (*it).second.end_t = -1;
				}
			}

			ct1 = INF;
			cout<<__LINE__<<endl;
			for(auto it = req.begin(); it != req.end(); it++)
			{
				if((*it).second.task.empty())
				{
					req.erase(it);
					N--;
					continue;
				}
				cout<<__LINE__<<endl;
				(*it);
				cout<<__LINE__<<endl;
				(*it).second;
				cout<<__LINE__<<endl;
				(*it).second.task;
				cout<<__LINE__<<endl;
				cout<<(*it).second.task.empty()<<endl;
				cout<<__LINE__<<endl;
				cout<<(*it).second.task.front();
				cout<<__LINE__<<endl;
				int tt = (*it).second.task.front();
				cout<<__LINE__<<endl;
				if(tt > c_time)
				{
					if (ct1 > tt)
						ct1 = tt;
				}
				else
				{
					vector<int> maybe;
					auto it1=(*it).second.p.begin();
					for(;it1 != (*it).second.p.end(); it1++)
						if(per[*it1].start_t < 0)
							maybe.push_back(*it1);
					if(maybe.empty())	
						continue;
					int p = maybe[0];
					for(int i = 1; i < maybe.size(); i++)
					{
						if(per[maybe[i]] < per[p])
							p = maybe[i];
					}
					per[p].start_t = c_time;
					per[p].end_t = c_time+(*it).second.t_t;
					per[p].prev_t = -1;
					(*it).second.task.pop();
				}
			}
			c_time++;
		}
		ct2 = c_time;
		cout<<__LINE__<<endl;
		for(auto it = per.begin(); it != per.end(); it++)
			if((*it).second.end_t > ct2)
			{
				ct2 = (*it).second.end_t;
				cout<<__LINE__<<endl;
			}
		cout<<__LINE__<<endl;
		cout<<ct2<<" minutes."<<endl;
	}
}
