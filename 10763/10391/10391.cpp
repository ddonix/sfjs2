#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


int main()
{
	int n;
	const int MAXW = 120000+5;
	string *data = new string[MAXW];
	set<string> s;
	n = 0;
	while(cin>>data[n])
	{
		s.insert(data[n]);
		n++;
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 1; j <= data[i].length()-1; j++)
		{
			string t = data[i].substr(0, j);
			string t1 = data[i].substr(j);
			if (s.count(t) && s.count(t1))
			{
				cout<<data[i]<<endl;
				break;
			}
		}
	}
}
