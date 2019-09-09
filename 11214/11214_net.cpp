#include<cstdio>
#include<cstring>


const int maxn = 11;
char G[maxn][maxn];
int maxd;
int n,m;
bool visi[maxn],visj[maxn],vis1[maxn<<1],vis2[maxn<<1];


bool dfs(int d,int si,int sj)
{
    if(d == maxd){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++){
                if(G[i][j] == 'X'&&!visi[i]&&!visj[j]&&!vis1[i+j]&&!vis2[i-j+10])
                    return false;
            }
        return true;
    }
      for(int i = si; i < n; i++){
            for(int j = (i == si?sj:0); j < m; j++)
            if(!visi[i] || !visj[j] || !vis1[i+j]|| !vis2[i-j+10]){
                bool f1 = visi[i], f2 = visj[j], f3 = vis1[i+j], f4 = vis2[i-j+10];
                visi[i] = visj[j] = vis1[i+j] = vis2[i-j+10] = true;
                if(dfs(d+1,i,j))return true;
                visi[i] = f1; visj[j] = f2; vis1[i+j] = f3; vis2[i-j+10] = f4;
            }

    }
    return false;
}



int main()
{
    int cas = 0;
    while(scanf("%d%d",&n,&m),n){
        for(int i = 0;i < n; i++) scanf("%s",G[i]);
        for(maxd = 1; maxd < 5; maxd++){
            memset(visi,0,sizeof(visi));
            memset(visj,0,sizeof(visj));
            memset(vis1,0,sizeof(vis1));
            memset(vis2,0,sizeof(vis2));
            if(dfs(0,0,0))break;
        }
        printf("Case %d: %d\n",++cas,maxd);
    }
    return 0;
}
