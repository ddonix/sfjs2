#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	int n,m;
	vector<vector<int>> db;
	string s;
	map<string, int> mp;
	map<long long, int> mp2;
	char buff[100000];
	char ch;
	
	int sn;
	bool flag;
	while(cin>>n)
	{
		cin>>m;
		db.resize(n);
		for(int i = 0;i < n; i++)
			db[i].resize(m);
		mp.clear();
		sn=0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				s = "";
				while(1)
				{
					cin.get(ch);
//					cout<<(int)ch<<'*';
					if(ch == 0 || ch == ',')
					{
						break;
					}
					else if(ch == '\n' || ch == '\r')
					{
						if(s == "")
							continue;
						else
							break;
					}
					else
						s += ch;

				}
//				cout<<endl;
//				cout<<s<<s.length()<<endl;
				if(mp.count(s) < 1)
					db[i][j] = mp[s] = sn++;
				else
					db[i][j] = mp[s];
			
			}
		}
		
		flag = true;
		for(int j0 = 0; j0 < (m-1) && flag; j0++)
			for(int j1=j0+1; j1 < m && flag; j1++)
			{
				mp2.clear();
				for(int i = 0; i < n && flag; i++)
				{
					long long temp = (long long)db[i][j0] | (long long)db[i][j1] << 32;
					if(mp2.count(temp) == 1)
					{
						int i0 = mp2[temp];
						cout<<"NO"<<endl;
						cout<<i0+1<<' '<<i+1<<endl;
						cout<<j0+1<<' '<<j1+1<<endl;
						flag = false;
						break;
					}
					else
					{
						mp2[temp] = i;
					}
				}
			}
		if(flag)
			cout<<"YES"<<endl;
	}
}
