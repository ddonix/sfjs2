#include <iostream>
#include <string>

using namespace std;

string sw(string p, string d)
{
	string res;
	int len = p.size();
	if(len <= 1)
		res = p;
	else
	{
		string pl, pr, dl, dr;
		string rl, rr;
		int i;
		char r = p[0];
		for(i = 0; d[i] != r; i++);
		if(i == 0)
		{
			dl = "";
			dr = d.substr(1, len-1);
			pl = "";
			pr = p.substr(1, len-1);
		}
		else if(i == len-1)
		{
			dl = d.substr(0, len-1);
			dr = "";
			pl = p.substr(1, len-1);
			pr = "";
		}
		else
		{
			dl = d.substr(0, i);
			dr = d.substr(i+1, len-i-1);
			int k;
			for(k = 1; p[k] != d[i-1]; k++);
			pl = p.substr(1, k);
			pr = p.substr(k+1,len-k-1);
		}
		res += r;
		res += sw(pr, dr);
		res += sw(pl, dl);
	}
	return res;
}

int main()
{
	string p, d;
	string res;
	while(cin>>p)
	{
		cin>>d;
		res = sw(p, d);
		for(int i = res.size()-1; i>= 0; i--)
			cout<<res[i];
		cout<<endl;
	}
}
