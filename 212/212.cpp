#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Patient
{
	char name[9];
	int surgeryt;
	int recovert;

	int orid;
	int obt;
	int oet;
	
	int rrid;
	int rbt;
	int ret;
	
	Patient() {}
	Patient(const char *n, int st, int rt) : surgeryt(st), recovert(rt)
	{
		strcpy(name, n);
	}
};

struct Room
{
	int p;		//patient
	
	Room() : usingt(0) {}
	int usingt;
};

struct Event
{
	int time;
	int action;		//0:surgery end; 1:oroom avaliable; 2:rroom avaliable
	int rid;
	Event(int t, int a, int id) : time(t), action(a), rid(id) {}
	bool operator > (const Event & right) const
	{
		if (time != right.time)
			return time > right.time;
		if (action != right.action)
			return action > right.action;
		return rid > right.rid;
	}
};

int main()
{
	int no, nr, first, transt, opt, rpt, np;
	while(cin>>no)
	{
		vector<Patient> patient;
		vector<Room> oroom;
		vector<Room> rroom;
		priority_queue<Event, vector<Event>, greater<Event> > event;
		priority_queue<int, vector<int>, greater<int> > avaliablerroom;
		priority_queue<int, vector<int>, greater<int> > avaliableoroom;
		int c_time = 0, newt;
	
		cin>>nr>>first>>transt>>opt>>rpt>>np;
		patient.resize(np);
		oroom.resize(no);
		rroom.resize(nr);
	
		
		for(int i = 0; i < no; i++)
		{
			event.push(Event(0, 1, i));
			avaliableoroom.push(i);
		}
		for(int i = 0; i < nr; i++)
			avaliablerroom.push(i);
		
		for(int i = 0; i < np; i++)
		{
			char name[9];
			int st, rt;
			cin>>name>>st>>rt;
			patient[i] = Patient(name, st, rt);
		}
		printf(" Patient          Operating Room          Recovery Room\n");
		printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
		printf(" ------------------------------------------------------\n");
	
		c_time = 0;
		int okp = 0;
		int nextp = 0;
		while(!event.empty())
		{
			Event e = event.top();
			int i = e.rid;
			c_time = e.time;
			
			event.pop();
			if(0 == e.action)
			{
				Patient & p = patient[oroom[i].p];
				p.rrid = avaliablerroom.top();
				avaliablerroom.pop();
				
				Room & r = rroom[p.rrid];
				r.usingt += p.recovert;
				
				event.push(Event(p.ret+rpt,2, p.rrid));
			}
			else if (1 == e.action)
			{
				if(nextp == np)
					continue;
				Patient & p = patient[nextp];
					
				p.orid = i;
				p.obt = c_time;
				p.oet = c_time+p.surgeryt;
				p.rbt = p.oet+transt;
				p.ret = p.rbt+p.recovert;

				oroom[i].p = nextp;
				oroom[i].usingt += p.surgeryt;
				event.push(Event(p.oet, 0, i));
				event.push(Event(p.oet+opt, 1, i));
				
				nextp++;
			}
			else
				avaliablerroom.push(i);
		}
		for(int i = 0; i < np; i++)
		{
			Patient & p = patient[i];
			printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n",  i+1, p.name, 
								p.orid+1, first+p.obt/60, p.obt%60, first+p.oet/60, p.oet%60,
								p.rrid+1, first+p.rbt/60, p.rbt%60, first+p.ret/60, p.ret%60);
		}

		printf("\nFacility Utilization\n");
		printf("Type  # Minutes  \% Used\n");
		printf("-------------------------\n");
	
		c_time = (0 == np) ? 1:(c_time-rpt);
		for(int i = 0; i < no; i++)
			printf("Room %2d %7d %7.2lf\n",i+1, oroom[i].usingt, (double)(100*oroom[i].usingt)/(double)c_time);
		for(int i = 0; i < nr; i++)
			printf("Bed  %2d %7d %7.2lf\n",i+1, rroom[i].usingt, (double)(100*rroom[i].usingt)/(double)c_time); 
		printf("\n");
	}
}
