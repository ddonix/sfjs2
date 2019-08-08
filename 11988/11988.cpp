#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

int main()
{
	char e[100001];
	char s[100001];
	int len;
	while(cin>>e)
	{
		queue<pair<int,int> > q;
		vector<pair<int,int> > v;
		
		int i = 0;
		len = strlen(e);
		while(i < len)
		{
			int j;
			if ('[' == e[i])
			{
				for(j = i+1; j < len && e[j] == '['; j++);
				q.push(make_pair(-1, j-1));
			}
			else if (']' == e[i])
			{
				for(j = i+1; j < len && e[j] == ']'; j++);
				q.push(make_pair(-2, j-1));
			}
			else
			{
				for(j = i+1; j < len && e[j] != '[' && e[j] != ']'; j++);
				q.push(make_pair(i, j-1));
			}
			i = j;
		}
		auto it = v.end();
		while(!q.empty())
		{
			pair<int, int> p = q.front();
			q.pop();
			if (p.first == -1)
				it = v.begin();
			else if(p.first == -2)
				it = v.end();
			else
			{
				it = v.insert(it, p);
				it--;
			}
		}
		int ii = 0;
		for(int i = 0; i < v.size(); i++)
		{
			strncpy(s+ii, e+v[i].first, v[i].second-v[i].first+1);
			ii += v[i].second-v[i].first+1;
		}
		cout<<s<<endl;
	}
}
