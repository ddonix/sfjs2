#include <iostream>
#include <cstring>

using namespace std;

int table[26][26];

int out[26];
int in[26];

int main()
{
	int T;
	int n;
	char buff[1001];
	cin>>T;
	while(T--)
	{
		cin>>n;
		memset(table, 0, sizeof(table));
		memset(out, 0, sizeof(out));
		memset(in, 0, sizeof(in));
		for(int i = 0; i < n; i++)
		{
			cin>>buff;
			int a = buff[0]-'a';
			int b = buff[strlen(buff)-1]-'a';
			table[a][b]++;
			out[a]++;
			in[b]++;
		}
		int diff = 0;
		int n[3];
		for(int i = 0; i < 26 && diff <= 2; i++)
		{
			if (out[i] != in[i])
			{
				n[diff]=i;
				diff++;
			}
		}
		if (diff > 2)
			cout<<"The door cannot be opened."<<endl;
		else if (0 == diff)
		{
			cout<<"Ordering is possible."<<endl;
		}
		else
		{
			int a, b;
			bool ok = false;
			for(int i = 0; i < 2 && !ok; i++)
			{
				a = n[i];
				b = n[(i+1)%2];
				if ((out[a]-in[a] == 1) && (in[b]-out[b] == 1))
				{
					if (!(table[a][b]%2))
						ok = true;
				}
			}
			if (ok)
				cout<<"Ordering is possible."<<endl;
			else
				cout<<"The door cannot be opened."<<endl;
		}
	}
}
