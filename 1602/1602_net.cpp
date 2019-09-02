#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<set>
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<deque>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cctype>
#include<functional>
using namespace std;
 
#define me(s) memset(s,0,sizeof(s))
#define pb push_back
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair <int, int> P;
 
 
struct Cell   //定义单元格
{
    int x,y;
    Cell(int x=0,int y=0):x(x),y(y){}
    bool operator<(const Cell&rhs)const
    {
        return x<rhs.x||(x==rhs.x&&y<rhs.y);//由于要使用set，必须对单元格定义大小关系
    }
};
 
typedef set<Cell>Polyomino;//定义连通块
 
#define FOR_CELL(c,p) for(Polyomino::const_iterator c=(p).begin();c!=(p).end();c++)
 
inline Polyomino normalize(const Polyomino &p)//标准化
{
    int minX=p.begin()->x,minY=p.begin()->y;//找到x,y的最小值，然后把每个单元格都分别减去minX,minY，得到标准化后的单元格
    FOR_CELL(c,p)
    {
        minX=min(minX,c->x);
        minY=min(minY,c->y);
    }
    Polyomino p2;
    FOR_CELL(c,p)
    p2.insert(Cell(c->x-minX,c->y-minY));
    return p2;
}
 
inline Polyomino rotate(const Polyomino&p)//旋转操作，对一个连通块顺时针旋转90度，并标准化
{
    Polyomino p2;
    FOR_CELL(c,p)
    p2.insert(Cell(c->y,-c->x));
    return normalize(p2);               //注意：此处一定要先旋转，再标准化！
}
 
inline Polyomino flip(const Polyomino&p)//翻转操作，对一个连通块沿x轴翻转，并标准化
{
    Polyomino p2;
    FOR_CELL(c,p)
        p2.insert(Cell(c->x,-c->y));
    return normalize(p2);
}
 
const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};
const int N=10;
 
set<Polyomino>poly[N+1];//连通块集合，poly[i]表示所有的i连通块构成的集合
int ans[N+1][N+1][N+1];//打表，ans[n][w][h]表示w*h网格中的n连通块的个数
 
void check_polyomino(const Polyomino&p0,const Cell&c)//判断重复性，如果p0+c构成的连通块不重复，则加入到集合中
{
    Polyomino p=p0;
    p.insert(c);
    p=normalize(p);//先进行标准化
 
    int n=p.size();
    for(int i=0;i<4;i++)//每次旋转90度，看能否在当前的n连通块集合里找到
    {
        if(poly[n].count(p))return;
        p=rotate(p);
    }
    p=flip(p);//翻转
    for(int i=0;i<4;i++)//再每次旋转90度，看能否找到
    {
        if(poly[n].count(p))return;
        p=rotate(p);
    }
    poly[n].insert(p);//说明是一个新的形态，加入集合
}
 
void Generate()//生成所有的n连通块，并打表
{
    Polyomino s;
    s.insert(Cell(0,0));
    poly[1].insert(s);
 
    for(int n=2;n<=N;n++)//枚举每个n连通块集合
        for(set<Polyomino>::iterator p=poly[n-1].begin();p!=poly[n-1].end();p++)//枚举每个n连通块
        FOR_CELL(c,*p)//枚举一个n连通块的每个单元格
        for(int dir=0;dir<4;dir++)//枚举4个方向，看能否扩展
    {
        Cell newc(c->x+dx[dir],c->y+dy[dir]);
        if(p->count(newc)==0)check_polyomino(*p,newc);
    }
 
    for(int n=1;n<=N;n++)
        for(int w=1;w<=N;w++)
        for(int h=1;h<=N;h++)//打表
    {
        int cnt=0;
        for(set<Polyomino>::iterator p=poly[n].begin();p!=poly[n].end();p++)
        {
            int maxX=0,maxY=0;
            FOR_CELL(c,*p)    //寻找当前的连通块的最大的x，y
            {
                maxX=max(maxX,c->x);
                maxY=max(maxY,c->y);
            }
            if(min(maxX,maxY)<min(h,w)&&max(maxX,maxY)<max(h,w))++cnt;//能够放入w*h网格内的条件
        }
        ans[n][w][h]=cnt;
    }
}
 
int main()
{
    Generate();
 
    int n,w,h;
    while(~scanf("%d%d%d",&n,&w,&h))
        printf("%d\n",ans[n][w][h]);
}
