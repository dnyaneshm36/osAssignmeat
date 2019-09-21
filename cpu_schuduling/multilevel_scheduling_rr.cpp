#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct process
{
    int name;	
    int total_cpu_burst_time;
    int completed_time;
    int ioburst_time;
    int arrival_time;
    int iointerval;
    int priority;
    int response_time;
    int turnaround_time;
    int waiting_time;
    int numofio;
    int iostart_time;
    int ready_time;
	int timeslice;
	int flag;
	int timeslicecounter;
	
};

int previous;

class comparator1 
{ 
public: 
    int operator() ( process& p1,  process& p2) 
    { 

    	if(p1.flag==0 || p2.flag==0)
    	{
    		p1.flag=1;
    		p2.flag=1;
    		if(p1.ready_time!=p2.ready_time)
			{
				return p1.ready_time>p2.ready_time;
			}
		else
		{
			return p1.priority<p2.priority;
		}
    	}
    	else
    	{
		if(p1.priority!=p2.priority)
		{
			return p1.priority>p2.priority;
		}
		else
		{
			return p1.ready_time<p2.ready_time;
		}
	}
    }
};

class comparator2 
{ 
public: 
    int operator() (process& p1, process& p2) 
    { 
        if(p1.iostart_time+p1.ioburst_time!=p2.iostart_time+p2.ioburst_time)
		{
			return p1.iostart_time+p1.ioburst_time>p2.iostart_time+p2.ioburst_time;
		}        
	        else if(p1.priority!=p2.priority)
		{
			return p1.priority<p2.priority;
		}
		else
		{
			return p1.iostart_time>p2.iostart_time;
		}
    } 
};

void multischudling(priority_queue <process, vector<process>, comparator1 > &ready,int n)
{ 	
	priority_queue <process, vector<process>, comparator2 > blocked;
	vector<process> pq;
	int context=0;
	process running;
	running=ready.top();
	ready.pop();
	running.response_time=0;
	running.completed_time=0;
	running.timeslicecounter=0;
	int current=running.arrival_time+1;
	while(1)
	{
		if(ready.size()==0 && blocked.size()==0 && running.total_cpu_burst_time<=0)
		{
			break;
		}
		
		/*if(ready.size()==0)
		{
			break;
		}*/
		//cout<<running.totalbursttime<<endl;
		if(blocked.size()!=0 && (current==blocked.top().iostart_time+blocked.top().ioburst_time))
		{
			process p;
			p=blocked.top();
			p.ready_time=current;
			
			ready.push(p);
			blocked.pop();
		}
		if(ready.size()!=0 && running.total_cpu_burst_time==0)
		{
			running.waiting_time=current-running.arrival_time-running.numofio*running.ioburst_time;
			running.turnaround_time=current-running.arrival_time;
			//cout<<"\nAT : "<<current;
			//cout<<"\n\nentered "<<running.num<<endl<<endl;
			pq.push_back(running);
			running=ready.top();
			if(previous!=running.name)
			{
				context++;
			}
			previous=running.name;
			
			ready.pop();
		}
		else if(ready.size()!=0 && running.completed_time==running.iointerval)
		{
			
			//running.totalbursttime--;
			current--;
			running.numofio++;
			running.iostart_time=current;
			//cout<<"SENT TO BLOCKED : "<<current<<endl;
			//cout<<"RUNNING MOVED TO BLOCKED PROCESS "<<running.name<<endl;
			blocked.push(running);
			running=ready.top();
			if(previous!=running.name)
			{
				context++;
			}
			previous=running.name;
			
			if(running.response_time==-1)
			{
				running.response_time=current-running.arrival_time;
				//cout<<"\n\nRESPONSE TIME : "<<running.name<<" : "<<running.responsetime<<endl;
			}
			running.completed_time=0;
			ready.pop();
		}
		else if(ready.size()!=0 && running.timeslicecounter==running.timeslice)
		{
			current--;
			running.ready_time=current;
			ready.push(running);
			
			running=ready.top();
			if(running.response_time==-1)
			{
				running.response_time=current-running.arrival_time;
				//cout<<"\n\nRESPONSE TIME : "<<running.name<<" : "<<running.responsetime<<endl;
			}
			if(previous!=running.name)
			{
				context++;
			}
			previous=running.name;
			running.timeslicecounter=0;
			ready.pop();
		}
		else 
		{
			running.completed_time++;
			running.total_cpu_burst_time--;
			running.timeslicecounter++;
			
			//cout<<endl<<running.completedtime<<" "<<running.totalbursttime;
		}
		current++;
	}
	running.waiting_time=current-running.arrival_time-running.numofio*running.ioburst_time;
	running.turnaround_time=current-running.arrival_time;
	pq.push_back(running);
	float avgres=0,avgturn=0,avgwait=0;
	//cout<<"\n\nTHE RESPONSE TIMES ARE : "<<endl;
	cout<<endl<<endl<<endl<<"THE SUMMARY IS : "<<endl<<endl;
	for(int i=0;i<pq.size();i++)
	{
		cout<<"PROCESS "<<pq[i].name<<" : "<<endl;
		cout<<"TURNAROUND TIME : "<<pq[i].turnaround_time<<"\nRESPONSE TIME : "<<pq[i].response_time<<"\nWAITING TIME : "<<pq[i].waiting_time<<endl;
		avgres=avgres+pq[i].response_time;
		//cout<<pq[i].name<<" : "<<pq[i].responsetime<<endl;
		avgturn=avgturn+pq[i].turnaround_time;
		avgwait=avgwait+pq[i].waiting_time;
		cout<<endl;
	}
	cout<<"AVERAGE TURNAROUND TIME : "<<avgturn/pq.size()<<endl;
	cout<<"AVERAGE WAITING TIME : "<<avgwait/pq.size()<<endl;
	cout<<"AVERAGE RESPONSE TIME : "<<avgres/pq.size()<<endl;
	cout<<"CURRENT TIME : "<<current<<endl;
	cout<<"CONTEXT SWITCHES : "<<context<<endl;
}


	void givetheinput(priority_queue <process, vector<process>, comparator1 > &ready,int n)
	{
			int i=0;
			process a;
		while(i<n)
		{
		cout<<"PROCESS : "<<i<<endl;;
		a.name=i;
		cout<<"PRIORITY : ";
		cin>>a.priority;
		cout<<"\nARRIVAL TIME : ";
		cin>>a.arrival_time;
		a.ready_time=a.arrival_time;
		cout<<"CPU BURST TIME : ";
		cin>>a.total_cpu_burst_time;
		cout<<"I/O BURST TIME : ";
		cin>>a.ioburst_time;
		cout<<"I/O CPU TIME : ";
		cin>>a.iointerval;
		cout<<"TIME SLICE : ";
		cin>>a.timeslice;
		a.priority=0;
		a.response_time=-1;
		a.flag=0;
		a.numofio=0;
		a.timeslicecounter=0;
		ready.push(a);
		i++;
		cout<<endl<<endl;
		}
	}

	




void hardcodeinput(priority_queue <process, vector<process>, comparator1 > &input)
{

process temp;
    temp.name=0;
    temp.arrival_time=0;
    temp.ready_time=0;
    temp.total_cpu_burst_time=18;
    temp.ioburst_time=5;
    temp.iointerval=5;
    temp.priority=4;
    temp.timeslice=3;
    temp.response_time=-1;
    temp.numofio=0;
    temp.flag=0;
    temp.timeslicecounter=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push(temp);
    
     temp.name=1;
    temp.arrival_time=0;
    temp.ready_time=0;
    temp.total_cpu_burst_time=27;
    temp.ioburst_time=6;
    temp.iointerval=6;
    temp.priority=4;
    temp.timeslice=3;
    temp.timeslicecounter=0;
    temp.response_time=-1;
    temp.numofio=0;
    temp.flag=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push(temp);
    
     temp.name=2;
    temp.arrival_time=0;
    temp.ready_time=0;
    temp.total_cpu_burst_time=44;
    temp.ioburst_time=4;
    temp.iointerval=6;
    temp.priority=3;
    temp.timeslice=6;
    temp.timeslicecounter=0;
    temp.response_time=-1;
    temp.numofio=0;
    temp.flag=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push(temp);
    
     temp.name=3;
    temp.arrival_time=0;
    temp.ready_time=0;
    temp.total_cpu_burst_time=50;
    temp.ioburst_time=3;
    temp.iointerval=9;
    temp.priority=2;
    temp.timeslice=9;
    temp.flag=0;
    temp.timeslicecounter=0;
    temp.response_time=-1;
    temp.numofio=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push(temp);
    


}

int main()
{
	previous=-1;
	int n,i=0,hard;

	priority_queue <process, vector<process>, comparator1 > ready;
	process a;
	cout<<" hard coded input press 1 :";
    cin>>hard;
    if(hard==1)
    {
    	hardcodeinput(ready);
    		multischudling(ready,n);
    }
    else
    {

	cout<<"ENTER NUMBER OF PROCESSES TO BE ENTERED : ";
		cin>>n;
		givetheinput(ready,n);
			multischudling(ready,n);
    }


	return 0;
}
