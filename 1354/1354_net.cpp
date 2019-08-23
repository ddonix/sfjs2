#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;
double val[10],l[105],r[105],w[10],ans,room;
int n,t[105],visit[105];
int judge(int x)
{
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    memset(val,0,sizeof(val));
    for(int i=x;i;i--)
    {
        if(t[i]==-1){ //是天平棍，对它的子节点进行处理。
            int x=i*2,y=i*2+1;
            val[i]=val[y]+val[x];
            double L=val[y]/val[i];
            double R=val[x]/val[i];
            l[i]=min(-L+l[x],R+l[y]);
            r[i]=max(-L+r[x],R+r[y]);
        }
        else if (t[i])//或者是挂件。只计量挂件的重量就行了。
        {
            val[i]=w[t[i]];
        }
    }
    double a=r[1]-l[1];
    if(a-room<1e-5)ans=max(ans,a);
}
int DFS(int num,int sit,int use)
{
    if(use==0){//所有的挂件都放完了，开始计算长度。
        judge(num-1);
        return 0;
    }
    if(t[num/2]!=-1){//父亲节点不是棍子，就不能往下放东西。
        DFS(num+1,sit,use);
    }
    else
    {
        if(use>sit){//挂件要比位置多，创位置。
            t[num]=-1;
            DFS(num+1,sit+1,use);
            t[num]=0;
        }
        if(sit==1&&use>1) return 0;
        for(int i=1;i<=n;i++)
        {
            if(!visit[i]){
                visit[i]=1;
                t[num]=i;
                DFS(num+1,sit-1,use-1);//放挂件
                visit[i]=0;
                t[num]=0;
            }
        }
    }
}
int main()
{
    int tot;
    scanf("%d",&tot);
    while(tot--)
    {
        scanf("%lf%d",&room,&n);
        memset(w,0,sizeof(w));
        memset(t,0,sizeof(t));
        memset(visit,0,sizeof(visit));
        for(int i=1;i<=n;i++)
        scanf("%lf",&w[i]);
        ans=-1;
        t[1]=-1;  //第一个根就是个棍。
        if(n==1){
            printf("%.10lf\n",0.0);
        }
        else {
            DFS(2,2,n);//从节点2开始枚举。刚好就只有2个位置。
            if(ans==-1)printf("-1\n");
            else printf("%.10lf\n",ans);
        }
    }
    return 0;
}
