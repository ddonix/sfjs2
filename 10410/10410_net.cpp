#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
 
using namespace std;
const int maxn = 1005;
 
int N, pos[maxn];
vector<int> g[maxn];
 
int main () {
    while (scanf("%d", &N) == 1) {
        int x;
        for (int i = 1; i <= N; i++) {
            scanf("%d", &x);
            g[i].clear();
            pos[x] = i;
        }
 
        int root;
        stack<int> sta;
        scanf("%d", &root);
        sta.push(root);
 
        for (int i = 1; i < N; i++) {
            scanf("%d", &x);
 
            while (true) {
                int u = sta.top();
 
                if (u == root || pos[u] + 1 < pos[x]) {
                    g[u].push_back(x);
                    sta.push(x);
                    break;
                } else 
                    sta.pop();
            }
        }
 
        for (int i = 1; i <= N; i++) {
            printf("%d:", i);
            for (int j = 0; j < g[i].size(); j++)
                printf(" %d", g[i][j]);
            printf("\n");
        }
    }
    return 0;
}
