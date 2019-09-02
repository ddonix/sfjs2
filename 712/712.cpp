#include <iostream>
#include <cmath>

using namespace std;

int bit[7] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40};

int main()
{
	int ka=1;
	int n;
	int ord1[7];
	int ord2[7];
	string f;
	while(cin>>n && n)
	{
		string s,v;
		string res;
		char t;
		for(int i = 0; i < n; i++)
		{
			cin>>s;
			ord1[n-1-i] = s[1]-'0'-1;
		}
		for(int i = 0; i < n; i++)
		{
			int j;
			for(j = 0; ord1[j] != i; j++);
			ord2[i] = j;
		}
		cin>>f;
		
		int m;
		cin>>m;
		res = "";
		for(int i = 0; i < m; i++)
		{
			cin>>s;
			t = 0;
			for(int j = 0;j < n; j++)
			{
				if(s[ord2[j]] == '1')
				{
					t |= bit[j];
				}
			}
			res += f[t];
		}
		cout<<"S-Tree #"<<ka++<<":"<<endl;
		cout<<res<<endl<<endl;
	}
}
