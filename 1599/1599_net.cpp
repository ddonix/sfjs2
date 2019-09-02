#include<cstdio>
#include<vector>
#include<queue>
#include<cstring> 
using namespace std; //min()函数 
#define max 100000
#define inf 0x7fffffff
typedef struct ver{
    int num, color;//边的另一端的节点编号 和 颜色 
    ver(int n,int c):num(n),color(c){}
}Ver;
int n,m,a,b,c;
int d[max],res[max];//d记录每个点到终点的最短距离 res记录最短路的颜色
bool vis[max],inqueue[max];//vis每个节点是否被访问过 inqueue标记节点是否加入了队列，防止重复加入 
vector<Ver> edge[max];//邻接表记录图 
void bfs(int start,int end){
    memset(inqueue,0,n);
    memset(vis,0,n);
    int u,v,c;
    queue<int> q;
    q.push(start);
    if(start==0)
    {//用于正向bfs 
        memset(res,0,sizeof(int)*n);
        while(!q.empty())
	{
            	u=q.front();
		q.pop();
		vis[u]=1;
            	if(u==n-1)
		{
			return;
		}
            	int minc=inf,len=edge[u].size();
            	for(int i=0;i<len;i++)
			if(!vis[v=edge[u][i].num] && d[u]-1==d[v])
				minc=min(edge[u][i].color,minc);//获取所有路径中最小的颜色
            	for(int i=0;i<len;i++)
			if(!vis[v=edge[u][i].num] && d[u]-1==d[v] && edge[u][i].color==minc && !inqueue[v])
				q.push(v),inqueue[v]=1; 	//若有多组颜色相同,且未入队，则将其入队 
            	int index=d[0]-d[u];//获得当前步数对应的下标
            	if(res[index]==0)
			res[index]=minc;
            	else 
			res[index]=min(res[index],minc);//获取最小颜色 
       	}
    }//用于反向bfs 构建层次图，找最短路 
    else while(!q.empty()){
        u=q.front();
	q.pop();
	vis[u]=1;
        for(int i=0,len=edge[u].size();i<len;i++)
		if(!vis[v=edge[u][i].num] && !inqueue[v])
		{ 
            		d[v]=d[u]+1; //一定是头一次入队，这通过inqueue保证 
            		if(v==0)return; //找到起点，退出 
            		q.push(v);//如果不是起点，就把这个点入队 
            		inqueue[v]=1;//入队标记
        	}
    }
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        for(int i=0;i<n;i++)edge[i].clear();
        memset(d,-1,sizeof(int)*n);d[n-1]=0;//注意初始化的细节
        while(m--)
	{
            scanf("%d%d%d",&a,&b,&c);
            if(a!=b)
	    { 
		//排除自环
                edge[a-1].push_back(ver(b-1,c));
                edge[b-1].push_back(ver(a-1,c));
            }
        }
        bfs(n-1,0);//反向bfs
        bfs(0,n-1);//正向bfs 
        printf("%d\n%d",d[0],res[0]);
        for(int i=1;i<d[0];i++)printf(" %d",res[i]);
        printf("\n");
    }
}
