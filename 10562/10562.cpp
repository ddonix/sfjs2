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

string dfs(char root, int l, string::size_type rp)
{
	if (l == (line-1))
		return root+string("()");
	if (map[l+1][rp] != '|')
		return root+string("()");

	string t, res;
	string s, s1, s2;
	int left, right;
	for(left = rp-1; map[l+2][left] == '-'; left--);
	for(right = rp+1; map[l+2][right] == '-'; right++);
	left++;
	
	res = root+string("(");
	for(int p = left; p < right && p < map[l+3].length(); p++)
	{
		char c = map[l+3][p];
		string rr;
		if (c != '-' && c != '|' && c != ' ' && c != '#')
		{
			rr = dfs(c, l+3, p);
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
			char r;
		        for(string::size_type p = 0; p < map[0].length(); p++)
			{
				r = map[0][p];
				if (r != '-' && r != '|' && r != ' ' && r != '#')
				{
					s = dfs(r, 0, p);
					cout<<"("<<s<<")"<<endl;
					break;
				}
			}
		}
	}
}
