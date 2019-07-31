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
	cn = 0;
	while(getline(cin, s))
	{
		istringstream ss(s);
		j = 0;
		while(ss>>t)
		{
			data[i].push_back(t);
			if(j < cn)
			{
				if (t.length() > cnm[j])
					cnm[j] = t.length();
			}	
			else
			{
				cnm[j] = t.length();
				cn++;
			}
			j++;
		}
		i++;
	}
	rn = i;
	for(int i = 0; i < rn; i++)
	{
		for(int j = 0; j < data[i].size()-1; j++)
		{
			cout<<data[i][j];
			for(int k = 0; k < cnm[j]-data[i][j].length()+1; k++) 
				cout<<' ';
		}
		cout<<data[i][data[i].size()-1];
		cout<<endl;
	}
	return 0;
}
