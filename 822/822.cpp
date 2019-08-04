#include <iostream> 
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Req
{
	Req() {}
	Req(int t):t_t(t) {}

	int t_t;
	queue<int> task;
};

struct Per
{
	int pri;        //优先级，小的高 
    int n;         //处理req个数
    vector<int> r;  //处理req的id
	
    int start_t;	//开始时间
	int end_t;	    //结束时间
	int prev_t;	    //前次开始时间

	Per(){}
	
	Per(int i, int nn) : pri(i), n(nn), prev_t(-1), start_t(-1), end_t(-1) 
    {
        r.resize(nn);
    }

	bool operator < (const Per & right) const
	{
		if (prev_t != right.prev_t)
			return prev_t < right.prev_t;
		return pri < right.pri;
	}
};

map<int, Req> req;
vector<Per> per;
int c_time;
const int INF = 1000000;

int main()
{
	int ka = 1;
	int N, M;
	while(cin>>N && N)
	{
        req.clear();
        for(int i = 0; i < N; i++)
		{
			int r, num, f, t, b;
			cin>>r>>num>>f>>t>>b;
			req[r] = Req(t);
			for(int j = 0; j < num; j++)
				req[r].task.push(f+b*j);
		}
		
        
		cin>>M;
        per.clear();
        per.resize(M);
		for(int i = 0; i < M; i++)
		{
			int id, n, r;
			cin>>id>>n;
			per[i] = Per(i, n);
			for(int j = 0; j < n; j++)
			{
				cin>>r;
                per[i].r[j] = r;
			}
		}

		cout<<"Scenario "<<ka++<<": All requests are serviced within ";
		c_time = 0;
		while(N)
		{
            int ct;
            ct = INF;
            sort(per.begin(), per.end());
            for(auto & p:per)
            {
                if(p.start_t >= 0)
                {
                    if (p.end_t == c_time)
                    {
                        p.start_t = p.end_t = -1;
                    }
                }
                if (p.start_t >= 0) 
                {
                    ct = (ct < p.end_t) ? ct : p.end_t;
                    continue;
                }
                for(int i = 0; i < p.n; i++)
                {
                    Req & r = req[p.r[i]];
                    if(r.task.empty())
                        continue;
                    int st = r.task.front();
                    if(st > c_time)
                    {
                        ct = (ct < st) ? ct : st;
                        continue;
                    }
                    p.prev_t = p.start_t = c_time;
                    p.end_t = c_time+r.t_t;
                    ct = (ct < p.end_t) ? ct : p.end_t;
                    
                    r.task.pop();
                    if (r.task.empty())
                        N--;
                    break;
                }
            }
            c_time = ct;
		}
        for(auto & p:per)
        {
            c_time = (p.end_t > c_time) ? p.end_t : c_time;
        }
		cout<<c_time<<" minutes."<<endl;
	}
}
