#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
	string s, s0;
	map<string, int> m;
	map<string, string> m0;
	vector<string> ans;
	while(cin >> s)
	{
		if ('#' == s[0])
			break;
		s0 = s;
		
		for(int i = 0; i < s.length(); i++)
			s[i] = tolower(s[i]);
		sort(s.begin(), s.end());
		m0[s] = s0;
		if (m.count(s) == 0) 
			m[s] = 0;
		m[s]++;
	}
	for(map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		if (it->second == 1)
			ans.push_back(m0[it->first]);
	}
	sort(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		cout<<ans[i]<<endl;
}
