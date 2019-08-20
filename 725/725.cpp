#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
	int N, t;
	char c[6];
	char m[11];
	char s[11];
	c[5] = 0;
	s[10] = 0;
	bool first = true;
	while(cin>>N && N)
	{
		vector<string> r;
		for(c[0] = '0'; c[0] <= '9'; c[0]++)
		{
			for(c[1] = '0'; c[1] <= '9'; c[1]++)
			{
				if (c[1] == c[0])
					continue;
				for(c[2] = '0'; c[2] <= '9'; c[2]++)
				{
					if (c[2] == c[0] || c[2] == c[1])
						continue;
					for(c[3] = '0'; c[3] <= '9'; c[3]++)
					{
						if(c[3] == c[2] || c[3] == c[1] || c[3] == c[0])
							continue;
						for(c[4] = '0'; c[4] <= '9'; c[4]++)
						{
							if (c[4] == c[3] || c[4] == c[2] || c[4] == c[1] || c[4] == c[0])
								continue;
							
							stringstream ss(c);
							ss>>t;
							sprintf(m, "%d", t*N);
							if (strlen(m) < 4 || strlen(m) > 5)
								continue;
							if (strlen(m) == 4)
							{
								s[0] = '0';
								strncpy(s+1, m, 4);
							}
							else 
								strncpy(s, m, 5);
							strncpy(s+5, c, 5);

							int i;
							bool flag[10];
							for(i = 0; i < 10; i++)
								flag[i] = false;
							for(i = 0; i < 10 && !flag[s[i]-'0']; i++)
							{
								flag[s[i]-'0'] = true;
							}
							if (10 == i)
								r.push_back(s);
						}
					}
				}
			}
		}
		if (first)
			first = false;
		else
		{
			cout<<endl;
		}
		if (r.empty())
			cout<<"There are no solutions for "<<N<<"."<<endl;
		else
		{
			sort(r.begin(), r.end());
			for(int i = 0; i < r.size(); i++)
				cout<<r[i].substr(0,5)<<" / "<<r[i].substr(5)<<" = "<<N<<endl;
		}
	}
}
