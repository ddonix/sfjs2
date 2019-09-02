#include<bits/stdc++.h>
using namespace std;
 
int isten(int x)
{
    return x==10 || x==20 || x==30;
}
 
int check1(deque<int>piple) //头2+尾1
{
    int sum=0;
    sum+=piple.front(); piple.pop_front();
    sum+=piple.front(); piple.pop_front();
    sum+=piple.back(); piple.pop_back();
    return isten(sum);
}
 
int check2(deque<int>piple) //头1+尾2
{
    int sum=0;
    sum+=piple.front(); piple.pop_front();
    sum+=piple.back(); piple.pop_back();
    sum+=piple.back(); piple.pop_back();
    return isten(sum);
}
 
int check3(deque<int>piple) //尾3
{
    int sum=0;
    sum+=piple.back(); piple.pop_back();
    sum+=piple.back(); piple.pop_back();
    sum+=piple.back(); piple.pop_back();
    return isten(sum);
}
 
int putit(deque<int>&piple, deque<int>&all) //试图拿piple这堆,按从头到尾顺序，拿到总堆
{
    if(piple.size()<3)return 0;
    if(check1(piple))
    {
        int s1=piple.front(); piple.pop_front();
        int s2=piple.front(); piple.pop_front();
        int s3=piple.back(); piple.pop_back();
        all.push_back(s1);
        all.push_back(s2);
        all.push_back(s3);
        return 1;
    }
    else if(check2(piple))
    {
        int s1=piple.front(); piple.pop_front();
        int s2=piple.back(); piple.pop_back();
        int s3=piple.back(); piple.pop_back();
        all.push_back(s1);
        all.push_back(s3);
        all.push_back(s2);
        return 1;
    }
    else if(check3(piple))
    {
        int s1=piple.back(); piple.pop_back();
        int s2=piple.back(); piple.pop_back();
        int s3=piple.back(); piple.pop_back();
        all.push_back(s3);
        all.push_back(s2);
        all.push_back(s1);
        return 1;
    }
    return 0;
}
void output(vector<deque<int> > dui,deque<int> all)
{
    while(!all.empty()) {cout<<all.front()<<" ";all.pop_front();}cout<<endl;
    for(int i=0;i<7;i++)
    {
        cout<<i<<" : ";
        while(!dui[i].empty()){cout<<dui[i].front()<<" ";dui[i].pop_front();}cout<<endl;
    }
}
int main()
{
    vector<deque<int> > dui;
    int a[52];
    set< vector<deque<int> > > status; //8个堆的状态
    for(int i=0;i<8;i++) dui.push_back(deque<int>()); //初始8堆
    deque<int> &all=dui[7];
    while(scanf("%d",&a[0])!=EOF&&a[0])
    {
        all.clear();
        status.clear();
        for(int i=1;i<52;i++) scanf("%d",&a[i]);
        for(int i=0;i<52;i++) all.push_back(a[i]); //放入总堆
        for(int i=0;i<7;i++)
        {
            int num=all.front();
            all.pop_front();
            dui[i].clear();
            dui[i].push_back(num);
        }
        int ans=7;
        int point=0; //指向牌堆
        while(1)
        {
            ans++;
            int num=all.front(); all.pop_front();
            dui[point].push_back(num); //point堆的尾部放上一张num
            while(putit(dui[point],all));
            //cout<<"step: "<<ans<<endl;
            //output(dui,all);
            if(status.count(dui))
            {
                printf("Draw: %d\n",ans);
                break;
            }
            status.insert(dui);
            if(all.size()==0)
            {
                printf("Loss: %d\n",ans);
                break;
            }
            if(all.size()==52)
            {
                printf("Win : %d\n",ans);
                break;
            }
 
            do{
                point=(point+1)%7;
            }while(dui[point].size()==0);
        }
    }
    return 0;
}
