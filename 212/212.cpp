#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int no, nr, first, transt, opt, rpt, np;

struct Patient
{
	char name[9];
	int surgeryt;
	int recovert;

	int state; 	//0:wo;1:oing; 2:ting; 3:ring;4:ok

	int orid;
	int obt;
	int oet;
	
	int rrid;
	int rbt;
	int ret;
	
	Patient() : state(0) {}
	Patient(const char *n, int st, int rt) : state(0), surgeryt(st), recovert(rt)
	{
		strcpy(name, n);
	}
};

struct Room
{
	int id;		//
	
	int state;	//0: avaliable, 1:using, 2:prepare
	int p;		//patient
	int bt;		//begin time, -1: avaliable
	int et;		//end tiem
	
	Room() : state(0), usingt(0) {}
	int usingt;
};

struct Find_by_state
{
	Find_by_state(int s) : state(s) {}
	bool operator()(const Room &r) 
	{
		return state == r.state;
	}
	int state;
};
vector<Patient> patient;
vector<Room> oroom;
vector<Room> rroom;
int c_time = 0;
int endtime = 1;
const int INF = 0x7fffffff;
int main()
{
	cin>>no>>nr>>first>>transt>>opt>>rpt>>np;
	patient.resize(np);
	oroom.resize(no);
	rroom.resize(nr);
	for(int i = 0; i < np; i++)
	{
		char name[9];
		int st, rt;
		cin>>name>>st>>rt;
		patient[i] = Patient(name, st, rt);
	}
	for(int i = 0; i < no; i++)
		oroom[i].id = i;
	for(int i = 0; i < nr; i++)
		rroom[i].id = i;
	
	printf(" Patient          Operating Room          Recovery Room\n");
	printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
	printf(" ------------------------------------------------------\n");
	
	c_time = 0;
	int okp = 0;
	while(okp < np)
	{
		int newt = INF;

		for(int i = 0; i < nr; i++)
		{
			if((1 == rroom[i].state) && (rroom[i].et == c_time))
			{
				rroom[i].state = 2;
				rroom[i].bt = c_time;
				rroom[i].et = c_time+rpt;
				newt = (newt < rroom[i].et) ? newt : rroom[i].et;

				patient[rroom[i].p].state++;
				okp++;
			}
			else if((2 == rroom[i].state) && (rroom[i].et == c_time))
			{
				rroom[i].state = 0;
			}
		}
		for(int i = 0; i < no; i++)
		{
			if((1 == oroom[i].state) && (oroom[i].et == c_time))
			{
				oroom[i].state = 2;
				oroom[i].bt = c_time;
				oroom[i].et = c_time+opt;
				newt = (newt < oroom[i].et) ? newt : oroom[i].et;
				
				Patient & p = patient[oroom[i].p];
				p.state++;
				newt = (newt < p.oet+transt) ? newt : (p.oet+transt);
			}
			else if((2 == oroom[i].state) && (oroom[i].et == c_time))
			{
				oroom[i].state = 0;
			}
		}

		if(okp == np)
			break;
		
		for(int i = 0; i < np; i++)
		{
			if(patient[i].state == 0)
			{
				auto it = find_if(oroom.begin(), oroom.end(), Find_by_state(0));
				if (it != oroom.end())
				{
					Patient & p = patient[i];
					Room & r = *it;
					
					p.state = 1;
					p.orid = r.id;
					p.obt = c_time;
					p.oet = c_time+p.surgeryt;
					newt = (newt < p.oet) ? newt : p.oet;

					r.state = 1;
					r.p = i;
					r.bt = c_time;
					r.et = c_time+p.surgeryt;
					r.usingt += p.surgeryt;
				}
			}
			else if(patient[i].state == 2 && (c_time >= (patient[i].oet+transt)))//must c_time == ()
			{
				auto it = find_if(rroom.begin(), rroom.end(), Find_by_state(0));//it != rroom.end()
				Patient & p = patient[i];
				Room & r = *it;
					
				p.state = 3;
				p.rrid = r.id;
				p.rbt = c_time;
				p.ret = c_time+p.surgeryt;
				newt = (newt < p.ret) ? newt : p.ret;

				r.state = 1;
				r.p = i;
				r.bt = c_time;
				r.et = c_time+p.surgeryt;
				r.usingt += p.recovert;
			}
		}
		c_time = newt; 
	}
	for(int i = 0; i < np; i++)
	{
		Patient & p = patient[i];
		printf("%2d %-8s    %-4d%2d:%02d   %2d:%02d      %-2d   %2d:%02d  %2d:%02d\n", i+1, p.name, 
							p.orid, first+p.obt/60, p.obt%60, first+p.oet/60, p.oet%60,
							p.rrid, first+p.rbt/60, p.rbt%60, first+p.ret/60, p.oet%60);
	}
	
	cout<<"Facility Utilization"<<endl;
	cout<<"Type  # Minutes  \% Used"<<endl;
	cout<<"-------------------------"<<endl;
	for(int i = 0; i < no; i++)
	{
		printf("Room %2d%8d%8.2llf\n", i, oroom[i].usingt, (double)oroom[i].usingt/endtime);
	}
	for(int i = 0; i < nr; i++)
	{
		printf("Bed  %2d%8d%8.2llf\n", i, rroom[i].usingt, (double)rroom[i].usingt/endtime);
	}

}
