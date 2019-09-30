#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

char s[101];
char d[101];
int sf[26], sf2[26];
int df[26], df2[26];
int l;

int main()
{
	while(cin>>s>>d)
	{
		l = strlen(s);
		for(int i = 0; i < 26; i++)
			sf[i] = df[i] = 0;
		for(int i = 0; i < l; i++)
		{
			sf[s[i]-'A']++;
			df[d[i]-'A']++;
		}
		memcpy(df2, df, sizeof(df));
		memcpy(sf2, sf, sizeof(sf));
		sort(sf2, sf2+26, greater<int>());
		sort(df2, df2+26, greater<int>());
		int i = 0;
		for(; i < 26 && (sf2[i] == df2[i]); i++);
		if (i < 26)
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
}
