#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char qiPan[10][15],moNi[10][15];
int qingKuang[10];
int main()
{
    bool slove(int);
    int count=0;
    while(1){
        memset(qiPan,0,sizeof(qiPan));
        fgets(qiPan[0],10,stdin);
        if(qiPan[0][0]=='0')
            break;
        for(int i=1;i<5;i++)
            fgets(qiPan[i], 10,stdin);
        for(int i=0;i<5;i++)
            for(int j=0;j<9;j++)
                moNi[i][j]=' ';
        memset(qingKuang,0,sizeof(qingKuang));
        printf("Case %d: ",++count);
        if(slove(0))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
bool slove(int x)
{
    int flag=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++)
            if(qiPan[i][j]!=moNi[i][j]){
                flag=1;
                break;
            }
        if(flag)
            break;
    }
    if(!flag)
        return true;
    if(x>=6)
        return false;
    char chongZhi[10][15];
    for(int i=0;i<5;i++)
        for(int j=0;j<9;j++)
          chongZhi[i][j]=moNi[i][j];//每次枚举完都对模拟棋盘进行重置
    for(int i=0;i<9;i++){//对棋盘9种情况的递归
        if(!qingKuang[i]){
            qingKuang[i]=1;
            int r=i/3,c=2*(i%3)+1;
            moNi[r][c]=moNi[r][c+2]=moNi[r+2][c]=moNi[r+2][c+2]='_';
            moNi[r+1][c-1]=moNi[r+2][c-1]=moNi[r+1][c+3]=moNi[r+2][c+3]='|';
            moNi[r+1][c]=moNi[r+1][c+1]=moNi[r+1][c+2]=moNi[r+2][c+1]=' ';
            if(slove(x+1))
              return true;
            qingKuang[i]=0;
            for(int j=0;j<5;j++)
                for(int k=0;k<9;k++)
                  moNi[j][k]=chongZhi[j][k];//重置模拟棋盘
        }
    }
    return false;
}



