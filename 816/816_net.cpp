#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

struct Node {
  int r, c, dir; // 位于(r,c)朝向dir(0~3表示四个方向N, E, S, W)
  Node(int r=0, int c=0, int dir=0):r(r),c(c),dir(dir) {}
};

const int maxn = 10;
const char* dirs = "NESW"; // 顺时针旋转。 
const char* turns = "FLR";//“三种转弯方式”。 

int has_edge[maxn][maxn][4][3];// 表示当前状态（r，c，dir），是否可以沿着转弯方向[trun]行走。 
int d[maxn][maxn][4];          //表示初始状态到（r，c，dir）的最短路长度。 
Node p[maxn][maxn][4];          //同时用p[r][c][dir]保存了状态(r, c, dir)在BFS树中的父结点。 
int r0, c0, dir, r1, c1, r2, c2;

//把四个方向和3种“转弯方式”编号0~3和0~2. 
int dir_id(char c) { return strchr(dirs, c) - dirs; }
int turn_id(char c) { return strchr(turns, c) - turns; }
//用于转弯。 
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

Node walk(const Node& u, int turn) { 
  int dir = u.dir;                    //直行， 方向不变 
  if(turn == 1) dir = (dir + 3) % 4; // 逆时针 ，转向 
  if(turn == 2) dir = (dir + 1) % 4; // 顺时针 ，转向 
  return Node(u.r + dr[dir], u.c + dc[dir], dir);//下一步可能的状态 
}

//判断是否出界 
bool inside(int r, int c) {
  return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

//读取r0，c0，dir，并计算出r1，c1， 然后读入has_edge数组。 
bool read_case() {
  char s[99], s2[99];
  if(scanf("%s%d%d%s%d%d", s, &r0, &c0, s2, &r2, &c2) != 6) return false;
  printf("%s\n", s);

  dir = dir_id(s2[0]);
  r1 = r0 + dr[dir];
  c1 = c0 + dc[dir];

  memset(has_edge, 0, sizeof(has_edge));
  for(;;) {
    int r, c;
    scanf("%d", &r);
    if(r == 0) break;
    scanf("%d", &c);
    while(scanf("%s", s) == 1 && s[0] != '*') {
      for(int i = 1; i < strlen(s); i++)
        has_edge[r][c][dir_id(s[0])][turn_id(s[i])] = 1;
    }
  }
  return true;
}

void print_ans(Node u) {
  // 从目标结点逆序追溯到初始结点。 
  vector<Node> nodes;
  for(;;) {
    nodes.push_back(u);
    if(d[u.r][u.c][u.dir] == 0) break;
    u = p[u.r][u.c][u.dir];
  }
  nodes.push_back(Node(r0, c0, dir));

  //打印解， 每行 10 个。 
  int cnt = 0;
  for(int i = nodes.size()-1; i >= 0; i--) {
    if(cnt % 10 == 0) printf(" ");
    printf(" (%d,%d)", nodes[i].r, nodes[i].c);
    if(++cnt % 10 == 0) printf("\n");
  }
  if(nodes.size() % 10 != 0) printf("\n");
}

//BFS主过程。 
void solve() {
  queue<Node> q;
  memset(d, -1, sizeof(d));
  Node u(r1, c1, dir);
  d[u.r][u.c][u.dir] = 0;
  q.push(u);
  while(!q.empty()) {
    Node u = q.front(); q.pop();
    if(u.r == r2 && u.c == c2) { print_ans(u); return; }//到达目的地 
    for(int i = 0; i < 3; i++) {//所有可能的转向，（直行，逆时针转， 顺时针转） 
      Node v = walk(u, i);      //下一步的状态 
      if(has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) {//分别判断
                //从这一步是否可以达到下一步，下一步是否出界， 下一步是否被走过（同方向）。 
        d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;//最短长度加 1. 
        p[v.r][v.c][v.dir] = u;//记录父结点。 
        q.push(v);  
      }
    }
  }
  printf("  No Solution Possible\n");//走了所有可以走的可能， 无法到达终点。 
}

int main() {
  while(read_case()) {
    solve();
  }
  return 0;
}
