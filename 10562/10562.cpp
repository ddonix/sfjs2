#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 202;
string map[maxn];
int len[maxn];

int line;

string dfs(char root, int l)
{
	string t, res;
	string s, s1, s2;
	if (l == (line-1))
		return root+string("()");
	
	string::size_type p = map[l+1].find('|');
	if (p == string::npos)
		return root+string("()");
	
	int left, right;
	for(left = p-1; map[l+2][left] == '-'; left--);
	for(right = p+1; map[l+2][right] == '-'; right++);
	left++;

	
	for(int p = left; p < right; p++)
	{
		char c = map[l+3][p];
		string rr;
		if (c != '-' && c != '|' && c != ' ' && c != '#')
		{
			rr = dfs(c, l+3);
			res += rr;
		}
	}
	res += ")";
	return res;
}

int main()
{
	int T;
	cin>>T;
	cin.ignore(1024, '\n');
	while(T--)
	{
		string s;
		line = 0;
		while(1)
		{
			getline(cin, s);
			if ('#' == s[0])
				break;
			map[line] = s;
			len[line++] = s.length();
		}
		if (0 == line)
		{
			cout<<"()"<<endl;
		}
		else
		{
			stringstream ss(map[0]);
			char r;
			ss>>r;
		        s = dfs(r, 0);
			cout<<"("<<s<<")"<<endl;
		}
	}
}
