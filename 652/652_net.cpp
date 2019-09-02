#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;
#define MAXN 400000
 
struct State{
    int state[9];//状态数组
    int pos;//记录空格位置
    string path;//记录从目标状态到当前状态的路径
};
int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};//方向数组
int factor[9] = {1,1,2,6,24,120,720,5040,40320};//阶乘数组
string Path[MAXN];//存储每一个到达目标状态的路径
int vis[MAXN];//判重
char dirtion[4] = {'d' , 'l' , 'u' , 'r'};//对应方向的字符，注意由于是从目标到初始必须是相反输出才能是正确的方向
queue<State>q;
 
//哈希函数(利用康托展开)X=a[n]*(n-1)!+a[n-1]*(n-2)!+...+a[i]*(i-1)!+...+a[2]*1!+a[1]*0!
int Hash(int s[]){
    int i , j , temp , num;
    num = 0;
    for(i = 0 ; i < 9 ; i++){
        temp = 0;
        for(j = i+1 ; j < 9 ; j++){
            if(s[j] < s[i]) temp++;//这里是s[j] < s[i];
        }
        num += factor[8-i]*temp;
    }
    return num;
}
 
//从目标状态出发预处理
void Bfs(){
    while(!q.empty()) q.pop();
    State goal;//目标状态
    memset(vis , 0 , sizeof(vis));//初始化为每一个状态0
    for(int i = 0 ; i < 8 ; i++)
        goal.state[i] = i + 1;
    goal.state[8] = 9;
    goal.path = "" ; goal.pos = 8;
    q.push(goal) ; vis[0] = 1;//目标状态标记为1
     
    while(!q.empty()){
        State cur = q.front();
        q.pop();
        int x , y , r , c;//表示空格的坐标
        x = cur.pos/3 ; y = cur.pos%3;
        for(int i = 0 ; i < 4 ; i++){//四个方向枚举
            r = x + dir[i][0] ; c = y + dir[i][1];
            if(r < 0 || r >= 3 || c < 0 || c >= 3) continue;
            State tmp = cur;
            tmp.state[tmp.pos] = tmp.state[3*r+c];//之前的空格位置换成新的编号
            tmp.pos = 3*r+c;//空格的新位置
            tmp.state[tmp.pos] = 9;
            int hash = Hash(tmp.state);
             
            if(vis[hash]) continue;
            vis[hash] = 1;//标记为1
            tmp.path += dirtion[i];//路径接着加上此时的dirtion[i]
            Path[hash] = tmp.path;//这个状态的路径保存下来
            q.push(tmp);
        }
    }
}
 
 
 
int main(){
    //freopen("input.txt" , "r" , stdin);
    Bfs();
    State star ;
    char c;
    int t;
    scanf("%d" , &t);
    while(t--){
        for(int i = 0 ; i < 9 ; i++){
            scanf(" %c" , &c);
            if(c == 'x') { star.pos = i ; star.state[i] = 9;}
            else star.state[i] = c-'0';
        }
        getchar();
        int hash = Hash(star.state);
        if(vis[hash]){
            for(int i = Path[hash].size()-1 ; i >= 0 ; i--)
                cout<<Path[hash][i];
            printf("\n");
        }
        if(!vis[hash]) printf("unsolvable\n");
        if(t) printf("\n");
    }
    return 0;
}
