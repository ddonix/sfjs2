#include <bits/stdc++.h>

using namespace std;

const int maxn = 10;
const int n = 7,m = 8;

int table[maxn][maxn];
int gra[maxn][maxn],ans[maxn][maxn];
int _count;
bool vis[maxn][maxn];
bool used[maxn<<2];
int dx[] = {0,1};
int dy[] = {1,0};

void init(){
    memset(table,0,sizeof(table));
    memset(vis,false,sizeof(vis));
    memset(used,false,sizeof(used));
    int i = 0,j = 0,cnt = 1;
    for(int len = 7;len >= 0;len--){
        for(int p = j;p < 7;p++){
            table[i][p] = table[p][i] = cnt++;
        }
        i++,j++;
    }
}

void dfs(int x,int y,int cnt){
    if(cnt == 28){
        _count++;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                printf("%4d",ans[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    if(y == m) x++,y = 0;
    if(vis[x][y]) dfs(x,y+1,cnt);
    else{
        for(int i = 0;i < 2;i++){
            int xx = x+dx[i],yy = y+dy[i];
            if(xx>=n || yy>=m) continue;
            if(vis[xx][yy] || used[table[gra[x][y]][gra[xx][yy]]]) continue;

            ans[x][y] = ans[xx][yy] = table[gra[x][y]][gra[xx][yy]];
            vis[x][y] = vis[xx][yy] = used[table[gra[x][y]][gra[xx][yy]]] = true;
            dfs(x,y+1,cnt+1);
            vis[x][y] = vis[xx][yy] = used[table[gra[x][y]][gra[xx][yy]]] = false;
        }
    }
}

int main()
{
#ifdef GEH
    freopen("input.txt","r",stdin);
#endif
    init();
    int iCase = 0;
    while(~scanf("%d",&gra[0][0])){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(i==0 && j==0) continue;
                scanf("%d",&gra[i][j]);
            }
        }

        if(iCase) printf("\n\n\n");
        printf("Layout #%d:\n\n",++iCase);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                printf("%4d",gra[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Maps resulting from layout #%d are:\n\n",iCase);
        _count = 0;
        dfs(0,0,0);
        printf("There are %d solution(s) for layout #%d.\n",_count,iCase);
    }
    return 0;
}
