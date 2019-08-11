#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int m,n;
vector<pair<int, int> > re;

map<int, set<int> > mp;
int main()
{
	while(cin>>n>>m && n != 0)
	{
		re.resize(m);
		for(int i = 0; i < m; i++)
		{
			cin>>re[i].first>>re[i].second;
			if (mp.count(re[i].second) < 1)
				mp[re[i].second] = set<int>();
			mp[re[i].second].insert(re[i].first);
		}
		
		for(int i = 1; i < n; i++)
			cout<<i<<" ";
		cout<<n<<endl;
	}
}
