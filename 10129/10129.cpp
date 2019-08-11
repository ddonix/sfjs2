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
			table[buff[0]-'a'][buff[strlen(buff)-1]-'a']++;
		}
		for(int i = 0; i < 26; i++)
		{
			for(int j = 0; j < 26; j++)
			{
				out[i] += table[i][j];
				in[j] += table[i][j];
			}
		}
		
		int diff = 0;
		int n[3];
//		for(int i = 0; i < 26; i++)
//			if (out[i] > 0)
//				cout<<(char)('a'+i)<<" "<<out[i]<<endl;
//		cout<<endl;
//		for(int i = 0; i < 26; i++)
//			if (in[i] > 0)
//				cout<<(char)('a'+i)<<" "<<in[i]<<endl;
		
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
			cout<<"Ordering is possible."<<endl;
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
//					cout<<"&&&&&&&&&"<<table[a][b];
					if (!(table[a][b]%2))
						ok = true;
				}
			}
			if (ok)
				cout<<"Ordering is possible."<<endl;
			else
				cout<<"The door cannot be opened."<<endl;
		}
//		cout<<"******************"<<endl;
	}
}
