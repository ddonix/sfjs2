#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

int d[4] = {1,2,4,8};
int dx[4] = {0,-1,0,1};
int dy[4] = {-1,0,1,0};
int ans[35];
int g[5][7];
bool f[5][7];
char str[] = "WNES";

int solve(int x, int y)
{
    if(x == 1 && (g[x][y]&2) == 0)
        return 1;
    if(x == 4 && (g[x][y]&8) == 0)
        return 3;
    if(y == 1 && (g[x][y]&1) == 0)
        return 0;
    if(y == 6 && (g[x][y]&4) == 0)
        return 2;
    return -1;
}

bool ida_star(int x, int y, int now, int max)
{
    if(now > max)
        return false;
    int num = solve(x, y);
    if(num != -1)
    {
        ans[now] = num;
        return true;
    }
    for(int i=0;i<4;i++)
    {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if(tx>=1 && tx <=4
            && ty >= 1 && ty <= 6
            && f[tx][ty] == 0)
        {
            if((g[x][y] & d[i]) == 0)
            {
                f[tx][ty] = 1;
                ans[now] = i;
                if(ida_star(tx, ty, now+1, max))
                    return true;
                f[tx][ty] = 0;
            }
            else if((g[tx][ty]&d[i]) == 0)
            {
                if(tx+dx[i]>=1 && tx+dx[i] <=4
                   && ty+dy[i] >= 1 && ty+dy[i] <= 6)
                    g[tx+dx[i]][ty+dy[i]]+=d[(i+2)%4];
                f[tx][ty] = 1;
                g[tx][ty] += d[i];
                g[x][y] -= d[i];
                ans[now] = i;
                if(ida_star(tx, ty, now+1, max))
                    return true;
                if(tx+dx[i]>=1 && tx+dx[i] <=4
                   && ty+dy[i] >= 1 && ty+dy[i] <= 6)
                    g[tx+dx[i]][ty+dy[i]]-=d[(i+2)%4];
                g[tx][ty] -= d[i];
                g[x][y] += d[i];
                f[tx][ty] = 0;
            }
        }
    }
    return false;
}

int main()
{
    int x,y;
    while(cin>>y>>x && x && y)
    {
        for(int i=1;i<=4;i++)
            for(int j=1;j<=6;j++)
                cin>>g[i][j];
        for(int m=0;;m++)
        {
            memset(f, 0, sizeof(f));
            f[x][y] = 1;
            //cout<<m<<"======="<<endl;
            if(ida_star(x,y,0,m))
            {
                for(int i=0;i<=m;i++)
                    cout<<str[ans[i]];
                cout<<endl;

                break;
            }
        }
    }
    return 0;
}
