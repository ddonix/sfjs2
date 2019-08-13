#include<bits/stdc++.h>
using namespace std;
const int maxc=1005;
const int maxn=105;
int dx[]={-1,1,0,0,0,0};
int dy[]={0,0,-1,1,0,0};
int dz[]={0,0,0,0,-1,1};
int color[maxn][maxn][maxn];
int xs[maxn],ys[maxn],zs[maxn];
int X[maxn],Y[maxn],Z[maxn],X0[maxn],Y0[maxn],Z0[maxn];
int t,n,nx,ny,nz;
struct Cell
{
    int x,y,z;
    Cell(int x,int y,int z):x(x),y(y),z(z) {}
    void Setvis()//外围方块
    {
        color[x][y][z]=2;
     } 
     bool getvis()
     {
     	return color[x][y][z]==2;
     }
     bool solid()//想象成固体方块
     {
     	return color[x][y][z]==1;
     }
     int volume()//离散化后每个单位长方体的体积
     {
     	return (xs[x+1]-xs[x])*(ys[y+1]-ys[y])*(zs[z+1]-zs[z]);
     }
     int area(int i)//根据移动的方向计算面积
     {
     	if(dx[i]!=0) return (ys[y+1]-ys[y])*(zs[z+1]-zs[z]);
     	if(dy[i]!=0) return (xs[x+1]-xs[x])*(zs[z+1]-zs[z]);
     	if(dz[i]!=0) return (xs[x+1]-xs[x])*(ys[y+1]-ys[y]);
     }
     bool valid()//不越界
     {
     	return x>=0&&x<nx-1&&y>=0&&y<ny-1&&z>=0&&z<nz-1;
     }
     Cell neighbour(int i)//行走函数
     {
        return Cell(x+dx[i],y+dy[i],z+dz[i]);
     }
};
int ID(int *x,int n,int k)//离散化后点的编号
{
    return lower_bound(x,x+n,k)-x;
}
void floodfill(int &s,int &v)//bfs
{
    Cell c(0,0,0);
    queue<Cell> Q;
    Q.push(c);
    c.Setvis();
    while(!Q.empty())
    {
      c=Q.front();
      Q.pop();
      v+=c.volume();
      //cout<<v<<endl;
      //cout<<c.x<<" "<<c.y<<" "<<c.z<<endl;
      for(int i=0;i<6;i++)
      {
        Cell c2=c.neighbour(i); 
        if(!c2.valid()) continue;
        if(c2.solid()) s+=c.area(i);
        else if(!c2.getvis())
        {
        	c2.Setvis();
        	Q.push(c2);
        }
      }	
    } 
    v=maxc*maxc*maxc-v;//v计算的是外围水的体积
}
void discretization(int *x,int &n)//计算离散化后点的个数
{
        sort(x,x+n);
        n=unique(x,x+n)-x;
}
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&t);
        nx=ny=nz=2;
        xs[0]=ys[0]=zs[0]=0;
        xs[1]=ys[1]=zs[1]=maxc;
        for(int i=1;i<=t;i++)
        {
            scanf("%d%d%d%d%d%d",&X[i],&Y[i],&Z[i],&X0[i],&Y0[i],&Z0[i]);
            X0[i]+=X[i];Y0[i]+=Y[i];Z0[i]+=Z[i];
            xs[nx++]=X[i];xs[nx++]=X0[i];
            ys[ny++]=Y[i];ys[ny++]=Y0[i];
            zs[nz++]=Z[i];zs[nz++]=Z0[i];
        }
        discretization(xs,nx);
        discretization(ys,ny);
        discretization(zs,nz);
        memset(color,0,sizeof(color));
        
        for(int i=1;i<=t;i++)
        {
            int sx=ID(xs,nx,X[i]);int ex=ID(xs,nx,X0[i]);
            int sy=ID(ys,ny,Y[i]);int ey=ID(ys,ny,Y0[i]);
            int sz=ID(zs,nz,Z[i]);int ez=ID(zs,nz,Z0[i]);
            for(int X=sx;X<ex;X++)
            for(int Y=sy;Y<ey;Y++)
            for(int Z=sz;Z<ez;Z++)
                color[X][Y][Z]=1;
        }
        int s=0,v=0;
        floodfill(s,v);
        printf("%d %d\n",s,v);
        }
    return 0;
}

