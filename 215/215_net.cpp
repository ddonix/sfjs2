#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int Row = 22,Cloumn = 12;
const int maxl = 80;
int vis[Row][Cloumn];
bool is_circle[Row][Cloumn];
int n,m;

struct Point{
    bool is_num;
    int num;
    char ss[80];
    Point(bool is_num = false,int num = 0) :
        is_num(is_num),num(num) {}
};
Point gra[Row][Cloumn];

bool dfs(int x,int y){
    if(is_circle[x][y]) return false;
    if(vis[x][y] == -1){
        gra[x][y].is_num = false;
        is_circle[x][y] = true;
        return false;
    }
    if(vis[x][y] == 1) return true;
    vis[x][y] = -1;
    int ans = 0;
    char *p = &gra[x][y].ss[0];
    int flag = 1;
    //bool IsNum = true;
    for(int i = 0;i < strlen(p);){
        if(p[i] == '+'){
            i++;
            flag = 1;
            continue;
        }
        else if(p[i] == '-'){
            i++;
            flag = -1;
            continue;
        }
        if(isdigit(p[i])){
            int temp;
            sscanf(p+i,"%d",&temp);
            ans += temp*flag;
            while(isdigit(p[i])) i++;
        }
        else{
            //IsNum = false;
            int r = p[i]-'A',c = p[i+1]-'0';
            i += 2;
            if(gra[r][c].is_num) ans += flag*gra[r][c].num;
            else{
                if(dfs(r,c)){
                    ans += flag*gra[r][c].num;
                }
                else{
                    gra[x][y].is_num = false;
                    is_circle[x][y] = true;
                    vis[x][y] = 1;
                    return false;
                }
            }
        }
    }
    gra[x][y].is_num = true;
    gra[x][y].num = ans;
    vis[x][y] = 1;
    return true;
}

void output(){
    printf(" ");
    for(int i = 0;i < m;i++){
        printf("%6d",i);
    }
    printf("\n");
    for(int i = 0;i < n;i++){
        printf("%c",i+'A');
        for(int j = 0;j < m;j++){
            printf("%6d",gra[i][j].num);
        }
        printf("\n");
    }
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    while(~scanf("%d%d",&n,&m) && (n||m)){
        char str[100];
        memset(vis,0,sizeof(vis));
        memset(is_circle,false,sizeof(is_circle));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                scanf("%s",str);
                gra[i][j].is_num = false;
                strncpy(gra[i][j].ss,str,sizeof(str));
            }
        }
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(gra[i][j].is_num) continue;
                dfs(i,j);
            }
        }
        bool ok = true;
        for(int i = 0;i < n;i++){
            int j;
            for(j = 0;j < m;j++){
                if(is_circle[i][j]){
                    ok = false;
                    break;
                }
            }
            if(j != m) break;
        }
        if(ok){
            output();
        }
        else{
            for(int i = 0;i < n;i++){
                for(int j = 0;j < m;j++){
                    if(is_circle[i][j]){
                        printf("%c%d: %s\n",i+'A',j,gra[i][j].ss);
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}
