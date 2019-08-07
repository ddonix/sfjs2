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
	int pid;

	int orid;
	int obt;
	int oet;
	
	int rrid;
	int rbt;
	int ret;
	
	Patient() {}
	Patient(const char *n, int id, int st, int rt) : pid(id), surgeryt(st), recovert(rt)
	{
		strcpy(name, n);
	}
};

bool cmp1(const Patient & ap, const Patient & bp)
{
	if (ap.oet != bp.oet)
		return ap.oet < bp.oet;
	return ap.orid < bp.orid;
}

bool cmp2(const Patient & ap, const Patient & bp)
{
	return ap.pid < bp.pid;
}

struct Room
{
	int p;		//patient
	Room() : usingt(0) {}
	int usingt;
};

struct ORoom
{
	int time;
	int id;
	ORoom(int t, int i) : time(t), id(i){}
	bool operator > (const ORoom & right) const
	{
		if (time != right.time)
			return time > right.time;
		return id > right.id;
	}
};

struct RRoom
{
	int atime;
	int usingt;
	RRoom() : atime(0), usingt(0) {}
};

int alltime;

int main()
{
	int no, nr, first, transt, opt, rpt, np;
	int alltime;
	while(cin>>no)
	{
		vector<Patient> patient;
		vector<Room> oroom;
		vector<RRoom> rroom;
		priority_queue<ORoom, vector<ORoom>, greater<ORoom> > avaliableoroom;
	
		cin>>nr>>first>>transt>>opt>>rpt>>np;
		patient.resize(np);
		oroom.resize(no);
		rroom.resize(nr);
		
		for(int i = 0; i < np; i++)
		{
			char name[9];
			int st, rt;
			cin>>name>>st>>rt;
			patient[i] = Patient(name, i, st, rt);
		}
	
		for(int i = 0; i < no; i++)
			avaliableoroom.push(ORoom(0, i));
		
		for(int i = 0; i < np; i++)
		{
			ORoom orm = avaliableoroom.top();
			avaliableoroom.pop();
			Patient & p = patient[i];
			
			p.orid = orm.id;
			p.obt = orm.time;
			p.oet = orm.time+p.surgeryt;

			p.rrid = -1;
			p.rbt = p.oet+transt;
			p.ret = p.rbt+p.recovert;
			
			oroom[orm.id].usingt += p.surgeryt;
			avaliableoroom.push(ORoom(p.oet+opt, orm.id));
		}
		sort(patient.begin(), patient.end(), cmp1);
	
		alltime = 1;
		for(int i = 0; i < np; i++)
		{
			int rid;
			int ret = patient[i].ret;
			for(rid = 0; rroom[rid].atime > patient[i].oet; rid++);
			rroom[rid].atime = ret+rpt;
			patient[i].rrid = rid;
			rroom[rid].usingt += patient[i].recovert;
			if(patient[i].ret > alltime)
				alltime = ret;
		}
		sort(patient.begin(), patient.end(), cmp2);
		
		printf(" Patient          Operating Room          Recovery Room\n");
		printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
		printf(" ------------------------------------------------------\n");
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
		
		for(int i = 0; i < no; i++)
			printf("Room %2d %7d %7.2lf\n",i+1, oroom[i].usingt, (double)(100*oroom[i].usingt)/(double)alltime);
		for(int i = 0; i < nr; i++)
			printf("Bed  %2d %7d %7.2lf\n",i+1, rroom[i].usingt, (double)(100*rroom[i].usingt)/(double)alltime); 
		printf("\n");
	}
}
