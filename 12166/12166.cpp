#include<iostream>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int n;
string line;
map<long long, int> mp;

void dfs(int s, int length, int d)
{
    if (line[s] == '[')
    {
        int p = 0;
        for (int i = s + 1; i<length-1; i++)
        {
            if (line[i] == '[')  p++;
            if (line[i] == ']')  p--;
            if (p == 0 && line[i] == ',')
            {
                dfs(s + 1, i, d+1);
                dfs(i + 1, length-1, d+1);
				break;
            }
        }
    }
    else {
        long long w = 0;
        for (int i = s; i < length; i++)
            w = w * 10 + line[i] - '0';
        n++;
        mp[w << d]++;
    }
}

int main()
{
    int t,r;
    int maxn;
    cin >> t;
    while (t--)
    {
        cin >> line;
        mp.clear();
        n = 0;
        dfs(0, line.size(), 0);
        r = 0;
        for (auto it = mp.begin(); it != mp.end(); it++)
        {
			if (it->second > r)
            	r = it->second;
        }
        cout << n - r<< endl;
    }
    return 0;
}
