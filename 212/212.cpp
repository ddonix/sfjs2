#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int no, nr, first, transt, opt, rpt, np;

struct Patient
{
	string name;
	int surgeryt;
	int recovert;

	int state; 	//0:wo;1:oing; 2:ting; 3:ring;4:ok

	int orid;
	int sbt;
	int set;
	int rrid;
	int rbt;
	int ret;
	
	Patient() :state(0) {}
	Patient(string n, int st, int rt) : name(n), surgeryt(st), recovert(rt){}
};

struct Room
{
	int state;	//0: avaliable, 1:using, 2:prepare
	int bt;		//begin time, -1: avaliable
	int et;		//end tiem
	int p;		//patient
	Room() : state(0), usingt(0) {}
	int usingt;
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
		string name;
		int st, rt;
		cin>>name>>st>>rt;
		patient[i] = Patient(name, st, rt);
	}
	printf(" Patient          Operating Room          Recovery Room\n");
	printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
	printf(" ------------------------------------------------------\n");
	
	c_time = 0;
	while(1)
	{
		int oa = -1, ra = -1;
		int newt = INF;

		for(int i = 0; i < nr; i++)
		{
			if (rroom[i].state == 0)
			{
				if (ra < 0)
					ra = i;
				continue;
			}
			if(rroom[i].et != c_time)
				continue;
			if(rroom[i].state == 1)
			{
				rroom[i].state = 2;
				rroom[i].bt = c_time;
				rroom[i].et = c_time+rpt;
				newt = (newt < rroom[i].et) ? newt : rroom[i].et;
			}
		}
		for(int i = 0; i < no; i++)
		{
			if (oroom[i].state == 0)
			{
				if (oa < 0)
					oa = i;
				continue;
			}
			if(oroom[i].et != c_time)
				continue;
			if(oroom[i].state = 1)
			{
				oroom[i].state = 2;
				oroom[i].bt = c_time;
				oroom[i].et = c_time+opt;
				newt = (newt < oroom[i].et) ? newt : oroom[i].et;
			}
			else
			{
				oroom[i].state = 0;
			}
		}
		break;
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
