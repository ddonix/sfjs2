# include<iostream>
# include<cstdio>
# include<cmath>
# include<map>
# include<queue>
# include<cstring>
# include<algorithm>
using namespace std;
 
struct Node
{
    int t,n,s;
    Node(int _t,int _n,int _s):t(_t),n(_n),s(_s){}
    bool operator < (const Node &a) const {
        return t>a.t;
    }
};
 
map<char,int>mp;
int ss[8]={1,6,36,216,1296,7776,46656,279936};
int goal[9],path[9],vis[9][1679616],dist[9][1679616];
int d[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
int p[6][4]={
    {2,2,5,5},
    {4,4,3,3},
    {0,0,4,4},
    {5,5,1,1},
    {1,1,2,2},
    {3,3,0,0},
};
priority_queue<Node>q[2];
 
void dfs(int u,int gp)
{
    if(u==9){
        int sta=0,cnt=0;
        for(int i=0;i<9;++i)
            if(path[i]!=-1){
                sta=sta+ss[7-cnt]*path[i];
                ++cnt;
            }
        dist[gp][sta]=0;
        vis[gp][sta]=1;
        q[1].push(Node(0,gp,sta));
        return ;
    }
    if(goal[u]==1){
        path[u]=0;
        dfs(u+1,gp);
        path[u]=1;
        dfs(u+1,gp);
    }else if(goal[u]==2){
        path[u]=2;
        dfs(u+1,gp);
        path[u]=3;
        dfs(u+1,gp);
    }else if(goal[u]==3){
        path[u]=4;
        dfs(u+1,gp);
        path[u]=5;
        dfs(u+1,gp);
    }else{
        path[u]=-1;
        dfs(u+1,gp);
    }
}
 
void init(int x,int y)
{
    while(!q[0].empty())
        q[0].pop();
    while(!q[1].empty())
        q[1].pop();
    memset(dist,-1,sizeof(dist));
    memset(vis,-1,sizeof(vis));
    dist[x*3+y][0]=0;
    vis[x*3+y][0]=0;
    q[0].push(Node(0,x*3+y,0));
    for(int i=0;i<9;++i)
        if(goal[i]==0){
            dfs(0,i);
            break;
        }
}
 
int getv(int p,int s)
{
    for(int i=1;i<=8-p;++i)
        s/=6;
    return s%6;
}
 
int bfs(int id,int step)
{
    while(!q[id].empty())
    {
        Node u=q[id].top();
        if(u.t>step)
            return -1;
        q[id].pop();
 
        if(vis[u.n][u.s]==!id)
            return u.t;
 
        int gg[9];
        int x=u.n/3,y=u.n%3;
        for(int i=0;i<4;++i){
            int nx=x+d[i][0],ny=y+d[i][1];
            if(nx<0||nx>2||ny<0||ny>2)
                continue;
 
            int s=u.s;
            for(int j=8;j>=0;--j){
                if(j==u.n)
                    gg[j]=-1;
                else{
                    gg[j]=s%6;
                    s/=6;
                }
            }
            gg[u.n]=p[gg[nx*3+ny]][i];
            gg[nx*3+ny]=-1;
            int sta=0,cnt=0;
            for(int j=0;j<9;++j)
                if(gg[j]!=-1){
                    sta=sta+ss[7-cnt]*gg[j];
                    ++cnt;
                }
            if(vis[nx*3+ny][sta]!=id){
                if(vis[nx*3+ny][sta]==-1){
                    vis[nx*3+ny][sta]=id;
                    dist[nx*3+ny][sta]=u.t+1;
                    q[id].push(Node(u.t+1,nx*3+ny,sta));
                }
                else
                    return u.t+1+dist[nx*3+ny][sta];
            }
        }
    }
    return -1;
}
 
int solve()
{
    int step=0;
    while(!q[0].empty()||!q[1].empty()){
        if(step>30)
            return -1;
        if(!q[0].empty()&&step<=21){
            int k=bfs(0,step);
            if(k>30)
                return -1;
            if(k!=-1)
                return k;
        }
        if(!q[1].empty()&&step<=9){
            int k=bfs(1,step);
            if(k>30)
                return -1;
            if(k!=-1)
                return k;
        }
        ++step;
    }
    return -1;
}
 
int main()
{
    //freopen("UVA-1604 Cubic Eight-Puzzle.txt","r",stdin);
    mp['E']=0,mp['W']=1,mp['R']=2,mp['B']=3;
    int x,y,gx,gy;
    char s[2];
    while(scanf("%d%d",&y,&x)&&(x+y))
    {
        --x,--y;
        for(int i=0;i<9;++i){
            scanf("%s",s);
            goal[i]=mp[s[0]];
        }
        init(x,y);
        printf("%d\n",solve());
    }
    return 0;
}