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
	int state;	//0: avaliable, 1:using, 2:prepare
	int p;		//patient
	int et;		//end tiem
	
	Room() : state(0), usingt(0) {}
	int usingt;
};

int main()
{
	int no, nr, first, transt, opt, rpt, np;
	while(cin>>no)
	{
		vector<Patient> patient;
		vector<Room> oroom;
		vector<Room> rroom;
		priority_queue<int, vector<int>, greater<int> > newtime;
		int c_time = 0, newt;
	
		cin>>nr>>first>>transt>>opt>>rpt>>np;
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
		printf(" Patient          Operating Room          Recovery Room\n");
		printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
		printf(" ------------------------------------------------------\n");
	
		c_time = 0;
		int okp = 0;
		int nextp = 0;
		while(okp < np)
		{
			for(int i = 0; i < no; i++)
			{
				if((1 == oroom[i].state) && (oroom[i].et == c_time))
				{
					oroom[i].state = 2;
					oroom[i].et = c_time+opt;
					newtime.push(oroom[i].et);
					
					int j;
					for(j = 0; rroom[j].state != 0; j++);
					Room & r = rroom[j];
					
					Patient & p = patient[oroom[i].p];
					p.rrid = j;
				
					r.state = 1;
					r.p = i;
					r.et = p.ret;
					r.usingt += p.recovert;
					newtime.push(r.et);
				}
				else if((2 == oroom[i].state) && (oroom[i].et == c_time))
					oroom[i].state = 0;
			
				if(0 == oroom[i].state)
				{
					if(nextp == np)
						continue;
					Patient & p = patient[nextp];
					Room & r = oroom[i];
					
					p.orid = i;
					p.obt = c_time;
					p.oet = c_time+p.surgeryt;
					p.rbt = p.oet+transt;
					p.ret = p.rbt+p.recovert;

					r.state = 1;
					r.p = nextp;
					r.et = c_time+p.surgeryt;
					r.usingt += p.surgeryt;
					nextp++;
					newtime.push(r.et);
				}
			}

			for(int i = 0; i < nr; i++)
			{
				if((1 == rroom[i].state) && (rroom[i].et == c_time))
				{
					rroom[i].state = 2;
					rroom[i].et = c_time+rpt;
					newtime.push(rroom[i].et);

					okp++;
				}
				if((2 == rroom[i].state) && (rroom[i].et == c_time))
					rroom[i].state = 0;
			}
			do
			{
				newt = newtime.top();
				newtime.pop();
			}while(newt <= c_time);
			c_time = newt;
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
