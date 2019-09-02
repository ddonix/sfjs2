#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct Topic
{
    int t;//处理一个请求的时间
    queue<int> table;//该主题的所有请求的开始时间表
};
map<int, Topic> topic;//主题的tid对应请求
struct Person
{
    int pid, k, time, st, tid[25];
    bool operator < (const Person& that) const
    {
        if (st != that.st) return st < that.st;
        return pid < that.pid;
    }
};
int N, M;//N个请求,M个人
int main()
{
    int Scenario = 1;
    while (~scanf("%d", &N) && N)
    {
        int time(INF), ans(0);//当前时间,答案
        topic.clear();
        for (int i = 0; i < N; i++)
        {
            int tid, num, t0, t, dt;
            Topic temp;
            scanf("%d%d%d%d%d", &tid, &num, &t0, &temp.t, &dt);
            time = min(time, t0);//维护开始时间
            Topic& x = (topic[tid] = temp);
            while (num--) x.table.push(t0), t0 += dt;//该主题所有请求的开始时间放入队列
        }
        scanf("%d", &M);
        vector<Person> person(M);//定义一个长度为M的Person类型的一个数组
        for (int i = 0; i < M; i++)
        {
            scanf("%d%d", &person[i].pid, &person[i].k);
            for (int j = 0; j < person[i].k; j++)
                scanf("%d", &person[i].tid[j]);
        }
        //time表示当前时间，整个模拟过程主要以时间为线索
        while (N)//还有请求未完成
        {
            int jumpt(INF);//所有人的下次时间点
            sort(person.begin(), person.end());//按要求排序
            for (auto& p: person)//遍历每个人
            {
                int nexttime(INF);//维护当前这个人的下次时间点
                if (p.time > time)//当前时间为time的时候这个人在忙
                    nexttime = p.time;
                else//不忙
                {
                    for (int i = 0; i < p.k; i++)//按优先级遍历该人可以处理的主题
                    {
                        Topic& x = topic[p.tid[i]];
                        if (x.table.empty()) continue;//该主题请求已经全部完成
                        if (x.table.front() < nexttime)//该请求无法做
                            nexttime = x.table.front();
                        if (x.table.front() <= time)//该请求可以做
                        {
                            nexttime = time + x.t;//该人的下次时间点为做完这个任务的时间
                            ans = max(ans, nexttime);//维护答案
                            p.st = time;//在做当前任务,那么上次开始处理请求的时间为当前时间
                            x.table.pop();//删掉该主题请求的第一个
                            if (x.table.empty()) N--;//如果该主题请求已经全部完成
                            break;//该人接了一个任务就跳出,不看后面优先级的任务了
                        }
                    }
                    p.time = nexttime;//更改该人的当前时间点
                }
                jumpt = min(jumpt, nexttime);//维护所有人的下个时间点
            }
            time = jumpt;//时间变为所有人的下个时间点
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", Scenario++, ans);
    }
    return 0;
}
