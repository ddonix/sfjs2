#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;
int main()
{
	int ka,t;
	int i,j,k;
	int t0,t1,t2;
	int a,b;
	string s;
	queue<int> que, qa[1000];
	map<int, int> team;
	ka = 1;
	
	cin>>t;
	while(0 != t)
	{
		cout<<"Scenario #"<<ka<<endl;
		ka++;

		team.clear();
		while(!que.empty()) que.pop();
		for(i = 0; i < 1000; i++) while(!qa[i].empty()) qa[i].pop();
			
		for(i = 0; i < t; i++)
		{
			cin>>j;
			while(j--)
			{
				cin>>t0;
				team[t0]=i;
			}
		}
		while(1)
		{
			cin>>s;
			if ("STOP" == s)
				break;
			if ("ENQUEUE" == s)
			{
				cin>>a;
				b = team[a];
				if(qa[b].empty())
					que.push(b);
				qa[b].push(a);
			}
			else
			{
				b = que.front();
				cout<<qa[b].front()<<endl;
				qa[b].pop();
				if(qa[b].empty())
					que.pop();
			}
		}
		cout<<endl;
		cin>>t;
	}
}
