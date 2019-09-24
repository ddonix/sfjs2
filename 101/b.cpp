#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	string s;
	while(cin>>s && s != "")
	{ 
		string s1;
		for(int i = 0; i < s.length(); i++)
		{
			if (isdigit(s[i]))
				s1 += s[i];
		}
		cout<<s1<<" ";
	}
	return 0;
}
