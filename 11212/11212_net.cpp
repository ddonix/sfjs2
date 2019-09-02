//Rey
#include<bits/stdc++.h>

const int maxn = 9;

int n,a[maxn];

inline bool End()
{
    for(int i = 1; i < n; i++){
        if(a[i] <= a[i-1]) return false;
    }
    return true;
}

inline int h()
{
    int cnt = 0;
    for(int i = 1; i < n; i++)
        if(a[i] != a[i-1]+1) cnt++;
    return cnt;
}

int maxd;
const int intsz = sizeof(int);
const int asz = sizeof(a);
bool dfs(int d)
{
    if(3*d + h() > 3*maxd) return false;
    if(End()) return true;

    int old[maxn];//保存a
    memcpy(old,a,asz);
    int b[maxn];//剪切板

    for(int i = 0; i < n; i++) if( i == 0 || old[i] != old[i-1] + 1) //策略3 选择尽量长的连续片段 剪切的起点
    for(int j = i; j < n; j++) { //终点 和 策略2不同选取片段可以不连续
        while(j+1 < n && old[j+1] == old[j] + 1)j++;//策略3
        memcpy(b,old+i,intsz*(j-i+1));
        //剪切移动片段
        for(int k = j+1;k < n;k++){//由于对称性，只要往后贴就行了
            while(k+1 < n && old[k+1] == old[k] + 1)k++;//策略3 不破坏
            memcpy(a+i,old+j+1,intsz*(k-j));
            memcpy(a+i+k-j,b,intsz*(j-i+1));
            if(dfs(d+1))return true;
            //恢复
            memcpy(a,old,asz);
        }
    }
    return false;
}

inline int solve()
{
    if(End())return 0;
    for(maxd = 1; maxd < 5 ;maxd++)
        if(dfs(0)) return maxd;
    return 5;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int Cas = 0;
    while(~scanf("%d",&n)&&n) {
        for(int i = 0; i < n; i++)
            scanf("%d",a+i);
        int ans = solve();
        printf("Case %d: %d\n",++Cas,ans);
    }
    return 0;
}
