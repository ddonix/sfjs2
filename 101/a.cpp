#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	string s1 = "wget https://uva.onlinejudge.org/external/";
	string s2;
	string s;
	while(cin>>s && s != "" && s!= "0")
	{
		s2 = s1+s.substr(0, s.length()-2)+"/"+s+".pdf";
		cout<<s2<<endl;
		system(s2.c_str());
	}
	return 0;
}
