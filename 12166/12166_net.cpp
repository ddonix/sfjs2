#include<iostream>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

int number;
string line;
map<long long, int> ans;

void dfs(int depth, int s, int length)
{
    if (line[s] == '[')
    {
        int p = 0;
        for (int i = s + 1; i<length; i++)
        {
            if (line[i] == '[')  p++;
            if (line[i] == ']')  p--;
            if (p == 0 && line[i] == ',')
            {
                dfs(depth + 1, s + 1, i-1);
                dfs(depth + 1, i + 1, length - 1);
            }
        }
    }
    else {
        long long w = 0;
        for (int i = s; i <= length; i++)
            w = w * 10 + line[i] - '0';
        ++number;
        ++ans[w << depth];
    }
}

int main()
{
    int t;
    int maxn;
    cin >> t;
    while (t--)
    {
        cin >> line;
        ans.clear();
        number = 0;
        dfs(0, 0, line.size()-1);
        maxn = 0;
        map<long long, int>::iterator it = ans.begin();
        for (; it != ans.end(); it++)
        {
            maxn = max(maxn, it->second);
        }
        cout << number - maxn << endl;
    }
    return 0;
}