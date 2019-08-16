#include <iostream>
#include <cstring>

using namespace std;

char b[129];

bool isValid(int s, int e)
{
	if(e<=s)
		return false;
	if(e-s == 1)
	{
		return ('('==b[s] && ')'==b[e])||('['==b[s] && ']'==b[e]);
	}
	else if (('('==b[s] && ')'==b[e])||('['==b[s] && ']'==b[e]))
	{
		return isValid(s+1, e-1);
	}
	else 
	{
		return false;
	}

}

int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		scanf("%s", b);
		if(isValid(0, strlen(b)-1))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
}

int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		scanf("%s", b);
		if(isValid(0, strlen(b)-1))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
}
