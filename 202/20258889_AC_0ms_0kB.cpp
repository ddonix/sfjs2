#include <stdio.h>
#include <string.h>
const int maxn = 100000 + 5;

int a, b;
int vis[maxn], res[maxn];

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    while(scanf("%d%d", &a, &b) == 2) {
        memset(vis, -1, sizeof(vis));
        int c = a % b, cnt = 0;
        c *= 10;
        while(vis[c] == -1) {
            res[cnt] = c / b;
            vis[c] = cnt++;
            c %= b;
            c *= 10;
        }
        // repeating cycle start-position
        int sta_pos = vis[c];
        printf("%d/%d = %d.", a, b, a/b);
        for(int i = 0; i < sta_pos; i++) {
            printf("%d", res[i]);
        }
        printf("(");
        if(cnt - sta_pos <= 50) {
            for(int i = sta_pos; i < cnt; i++) {
                printf("%d", res[i]);
            }
        } else {
            for(int i = sta_pos; i < sta_pos+50; i++) {
                printf("%d", res[i]);
            }
            printf("...");
        }
        printf(")\n");
        printf("   %d = number of digits in repeating cycle\n\n", cnt - sta_pos);
    }
    return 0;
}