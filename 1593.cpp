#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXLINE = 1000+5;
const int MAXCOL = 180;

vector<string> data[MAXLINE];

int main()
{
	int i,j;
	string s,t;

	int cn;
	int rn;
	
	int cnm[MAXCOL];

	i = 0;
	while(cin>>s)
	{
		istringstream ss(s);
		j = 0;
		while(ss>>t)
		{
			data[i].push_back(t);
		}
	}
	return 0;
}
