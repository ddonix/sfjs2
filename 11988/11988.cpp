#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

int main()
{
	char e[100002];
	char s[100002];
	int len;
	while(cin>>e)
	{
		vector<int> v;
		
		int i = 0;
		auto it = v.end();
		len = strlen(e);
		while(i < len && (e[i] == '[' || e[i] == ']')) i++;
		while(i < len)
		{
			int j,k;
			for(j = i+1; j < len && e[j] != '[' && e[j] != ']'; j++);
			it = v.insert(it, i);
			for(k = j+1; k < len && (e[k] == '[' || e[k] == ']'); k++);
			i = k;

			if(e[k-1] == '[')
				it = v.begin();
			else if(e[k-1] == ']')
				it = v.end();
			e[j] = 0;
		}
		for(int i = 0; i < v.size(); i++)
			cout<<e+v[i];
		cout<<endl;
	}
}
