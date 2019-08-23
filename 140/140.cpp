#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 26;
bool G[maxn][maxn];
bool o[maxn];

vector < int >g[maxn];
int n;
int mp[maxn];

int band;
int od[maxn];
int od2[maxn];
int odok[maxn];

bool updateband()
{
	int r = 0, t;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < g[i].size(); j++) {
			t = (od2[i] > od2[g[i][j]]) ? (od2[i] - od2[g[i][j]]) : (od2[g[i][j]] - od2[i]);
			if (t >= band)
				return false;
			r = (t > r) ? t : r;
		}
	band = r;
	return true;
}

bool vis[maxn];
void georder(int cur)
{
	int t;
	bool ok = true;
	if (cur == n) {
		if (updateband()) {
			for (int i = 0; i < n; i++)
				odok[i] = od[i];
		}
	} else {
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				ok = true;
				od[cur] = i;
				od2[i] = cur;
					
				int m = 0;
				for(int j = 0; j < g[i].size(); j++)
					if (!vis[g[i][j]])
						m++;
				if (m >= band)
					ok = false;
				
				if (ok && cur >= band) {
					for (int j = 0; j <= (cur - band); j++)
						if (G[mp[i]][mp[od[j]]]) {
							//待加入结点，距离如果大于等于当前最好结果，则剪枝
							ok = false;
							break;
						}
				}
				if (ok) {
					vis[i] = true;
					georder(cur + 1);
					vis[i] = false;
				}
			}
		}
	}
}

int main()
{
	string s;
	while (getline(cin, s) && s[0] != '#') {
		memset(G, 0, sizeof(G));
		memset(o, 0, sizeof(o));
		for (int i = 0; i < s.size();) {
			int x, j;
			x = s[i] - 'A';
			o[x] = true;
			for (j = i + 2; j < s.size() && s[j] != ';'; j++) {
				G[x][s[j] - 'A'] = true;
				G[s[j] - 'A'][x] = true;

				o[s[j] - 'A'] = true;
			}
			i = j + 1;
		}

		n = 0;
		for (int i = 0; i < 26; i++)
			if (o[i])
				mp[n++] = i;

		for (int i = 0; i < n; i++) {
			g[i].clear();
			for (int j = 0; j < n; j++)
				if (j != i && G[mp[i]][mp[j]])
					g[i].push_back(j);
		}
		band = maxn;
		memset(vis, 0, sizeof(vis));
		georder(0);
		for (int i = 0; i < n; i++)
			cout << (char)('A' + mp[odok[i]]) << " ";
		cout << "-> " << band << endl;
	}
}
