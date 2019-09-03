#include<cstdio>

using namespace std;

typedef long long LL;

int n,cnt,maxd,tot;

LL bit[61];

LL base[6][6],squ[56];

int get_ud(int i,int j)
{
    return (2*n+1)*(i-1)+j-1;
}

int get_lr(int i,int j)
{
    return (2*n+1)*(i-1)+j+n-1;
}

void build()
{
    cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            base[i][j]=0;
            base[i][j]|=bit[get_ud(i,j)]|bit[get_ud(i+1,j)];
            base[i][j]|=bit[get_lr(i,j)]|bit[get_lr(i,j+1)];
            squ[++cnt]=base[i][j];
        }
    for(int siz=2;siz<=n;siz++)
        for(int i=1;i+siz-1<=n;i++)
            for(int j=1;j+siz-1<=n;j++)
            {
                squ[++cnt]=0;
                for(int w=0;w<siz;w++)
                    for(int h=0;h<siz;h++)
                        squ[cnt]^=base[i+w][j+h];
            }
}

bool dfs(int d,LL state)
{
    if(d==maxd) 
    {
        for(int i=1;i<=cnt;i++)
            if((squ[i]&state)==squ[i]) return false;
        return true;
    }
    LL s=state;
    int need=0,del=0;
    for(int i=1;i<=cnt;i++)
        if((squ[i]&s)==squ[i])
        {
            need++;
            s^=squ[i];
            if(!del) del=squ[i];
        }
    if(d+need>maxd) return false;
    for(int i=1;i<=tot;i++)
        if((del&bit[i-1])==bit[i-1])
            if(dfs(d+1,state^bit[i-1])) return true;
    return false;
}

int main()
{
    int T;
    scanf("%d",&T);
    bit[0]=1;
    for(int i=1;i<=60;i++) bit[i]=bit[i-1]<<1;
    int m,x; LL state;
    while(T--)
    {
        scanf("%d",&n);
        tot=2*n*(n+1); state=bit[tot]-1;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d",&x);
            state^=bit[x-1];
        }
        build();
        for(maxd=0;;maxd++) 
         if(dfs(0,state)) break;
        printf("%d\n",maxd);
    }
}
