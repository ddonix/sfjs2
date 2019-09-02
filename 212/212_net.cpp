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
#include<functional>
using namespace std;
 
struct Time
{
	int hour, minute;
};
struct Node
{
	string name;
	int room, bed;
	int ts, tr;//ts表示手术时长，tr表示恢复时长
	int st1, st2;//手术开始时间，恢复开始时间
};
typedef pair<int, int> P;
typedef pair<P, int>Q;
#define For(i,n) for(int i=0;i<(n);i++)
#define INF 100000000
vector<P>rooms, beds;
priority_queue<Q, vector<Q>, greater<Q> >patient;
vector<Node>names;
map<string, int>IDcache;
int n, m, T, t1, t2, t3, cnt;
int tot_time;
int used[45];//每个手术室和恢复室被利用的时间
void clear()
{
	memset(used, 0, sizeof(used));
	names.clear();
	IDcache.clear();
	rooms.clear();
	beds.clear();
	while (!patient.empty())patient.pop();
}
Time std_time(int m)//转化为标准时间
{
	int hour = m / 60;
	int minute = m % 60;
	Time u = { hour + T, minute };
	return u;
}
 
void print_table()//打印表格
{
	puts(" Patient          Operating Room          Recovery Room");
	puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
	puts(" ------------------------------------------------------");
	For(i, cnt)
	{
		Node&p = names[i];
		Time u1 = std_time(p.st1), u2 = std_time(p.st1 + p.ts), u3 = std_time(p.st2), u4 = std_time(p.st2 + p.tr);
		printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n", i + 1, p.name.c_str(), p.room + 1, u1.hour, u1.minute, u2.hour, u2.minute, p.bed + 1, u3.hour, u3.minute, u4.hour, u4.minute);
	}
	cout << "\n";
	puts("Facility Utilization");
	puts("Type  # Minutes  % Used");
	puts("-------------------------");
	For(i, n)
	{
		double rate = 0.0;
		if (tot_time>0)
			rate = (double)used[i] * 100 / tot_time;
		printf("Room %2d %7d %7.2lf\n", i + 1, used[i], rate);
	}
	For(i, m)
	{
		double rate = 0.0;
		if (tot_time > 0)
			rate = (double)100 * used[i + n] / tot_time;
		printf("Bed  %2d %7d %7.2lf\n", i + 1, used[n + i], rate);
	}
}
int main()
{
	//freopen("t.txt", "r", stdin);
	while (~scanf("%d%d%d%d%d%d%d", &n, &m, &T, &t1, &t2, &t3, &cnt))
	{
		clear();
 
		tot_time = 0;
		For(i, cnt)
		{
			string  s;
			int ts, tr;
			cin >> s >> ts >> tr;
			Node u = { s, 0, 0, ts, tr, 0, 0 };
			names.push_back(u);
		}
		int count = -1;
		For(i, n)rooms.push_back(P(0, i));//初始化所有手术室
		priority_queue<int, vector<int>, greater<int> >tl1;
		vector<int>tmp;//暂时存放每位病人进入恢复室的时间
		For(i, n)tl1.push(0);
		while (!tl1.empty())//第一阶段：选择手术室
		{
			if (++count == cnt)break;
			int now = tl1.top(); tl1.pop();//取出最小的时刻
			vector<P>::iterator it = rooms.begin();
			for (it; it->first != now; it++);//找编号最小的可用手术室
			int id = it->second;//手术室编号
			Node&person = names[count];
			person.st1 = now;
			person.room = id;
			used[id] += person.ts;
			int Next = now + person.ts + t2;//该手术室下一次可以被使用的时刻
			it->first = Next;
			person.st2 = Next - t2 + t1;//转移到恢复室的时间
			patient.push(Q(P(person.st2, id),count));//获得进入恢复室的队列，主要依据st2来排队,次要依据手术室编号排序
			tl1.push(Next);
		}
		For(i, m)beds.push_back(P(0, i));//初始化恢复室
		while (!patient.empty())//第二阶段：选择恢复室
		{
			Q u = patient.top(); patient.pop();//当前需要安排的病人
			P v = u.first;
			int now = v.first - t1;
			vector<P>::iterator it = beds.begin();
			for (it; it->first > now; it++);//查找编号最小的可用恢复室
			int id = it->second;//恢复室编号
			Node&person = names[u.second];
			person.bed = id;
			used[id + n] += person.tr;
			int Next = person.st2 + person.tr + t3;//下一次可以被使用的时刻
			tot_time = max(tot_time, person.st2 + person.tr);
			it->first = Next;
		}
		print_table();
		cout << endl;
	}
	return 0;
}
