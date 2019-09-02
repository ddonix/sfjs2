#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main()
{
	string s, s0;
	set<string> dict; 
	while(cin>>s)
	{
		for(int i = 0; i < s.length(); i++)
		{
			if (isalpha(s[i]))
				s[i] = tolower(s[i]);
			else
				s[i] = ' ';
		}
		stringstream ss(s);
		while(ss>>s0)
		{
			dict.insert(s0);
		}
	}
	for(set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		cout<<*it<<endl;
	return 0;
}
