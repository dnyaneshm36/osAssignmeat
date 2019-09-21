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
    
};

int alpha;
int beta;
class comparator1 
{ 
public: 
    int operator() (const process& p1, const process& p2) 
    { 
        if(p1.ready_time!=p2.ready_time)
        {
            
            return p1.ready_time>p2.ready_time;
        }
        else
        {
            return p1.priority<p2.priority;
        }
    } 
}; 


class comparator2 
{ 
public: 
    int operator() (const process& p1, const process& p2) 
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


void alphamodify(priority_queue <process, vector<process> ,comparator1 > &abc)
{
    vector<process> temp;
    process p;
    while(abc.size()!=0)
    {
        p=abc.top();
        abc.pop();
        p.priority=p.priority+alpha;
        temp.push_back(p);
        
    }
    for(int i=0;i<temp.size();i++)
    {
        abc.push(temp[i]);
    }
}



void preemptive_scheduling(vector<process> p,int n)
{

    priority_queue <process, vector<process>, comparator1 > ready;  
    priority_queue <process, vector<process>, comparator2 > blocked;
    vector<process> pq;
    for(int i=0;i<p.size();i++)
    {
        ready.push(p[i]);
    }
    int context=0;
    process running;
    running=ready.top();
    ready.pop();
    running.response_time=0;
    running.completed_time=0;
    int current=running.arrival_time+1;
    while(1)
    {
        //end
        //iocomplete block>ready
        //end of running prosss
        //runing > bock fro io
        //io geting completed
        if(ready.size()==0 && blocked.size()==0 && running.total_cpu_burst_time==0)
        {
            break;
        }
        
        if(blocked.size()!=0 && (current==blocked.top().iostart_time+blocked.top().ioburst_time))
        {
            process p;
            p=blocked.top();
            p.ready_time=current;
            p.priority=0;
            ready.push(p);
            blocked.pop();
        }
        if(ready.size()!=0 && running.total_cpu_burst_time==0)
        {
            running.waiting_time=current-running.arrival_time-running.numofio*running.ioburst_time;
            running.turnaround_time=current-running.arrival_time;
            
            
            pq.push_back(running);
            
            running=ready.top();      
            context++;
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
            if(running.response_time==0 && running.arrival_time!=0)
            {
                running.response_time=current-running.arrival_time;
                //cout<<"\n\nRESPONSE TIME : "<<running.name<<" : "<<running.responsetime<<endl;
            }
            context++;
            
            running.completed_time=0;
            ready.pop();
        }
        else 
        {
            running.completed_time++;
            running.total_cpu_burst_time--;
            //cout<<endl<<running.completedtime<<" "<<running.totalbursttime;
        }
            
        current++;  
        alphamodify(ready);
        running.priority=running.priority+beta;
    }
    running.waiting_time=current-running.arrival_time-running.numofio*running.ioburst_time;
            running.turnaround_time=current-running.arrival_time;
    pq.push_back(running);
    float avgres=0,avgturn=0,avgwait=0;
    cout<<"\nINFROMATION OF PROCESS AFTER EXECUTIONS \n";
    for(int i=0;i<pq.size();i++)
    {
        cout<<"PROCESS "<<pq[i].name<<" : \n";
        cout<<"TURNAROUND TIME : "<<pq[i].turnaround_time<<"\nRESPONSE TIME : "<<pq[i].response_time<<"\nWAITING TIME : "<<pq[i].waiting_time<<endl;
        avgres=avgres+pq[i].response_time;
        //cout<<pq[i].name<<" : "<<pq[i].responsetime<<endl;
        avgturn=avgturn+pq[i].turnaround_time;
        avgwait=avgwait+pq[i].waiting_time;
        cout<<endl;
    }

    cout<<"\n INFROMATION all process\n";

    cout<<"\nAVERAGE TURNAROUND TIME : "<<avgturn/pq.size()<<endl;
    cout<<"AVERAGE WAITING TIME : "<<avgwait/pq.size()<<endl;
    cout<<"AVERAGE RESPONSE TIME : "<<avgres/pq.size()<<endl;
    cout<<"CURRENT TIME : "<<current<<endl;
    cout<<"CONTEXT SWITCHES : "<<context<<endl;
}
void givetheinput(vector <process> &input,int n)
{
    int i=0;
    process a;
     while(i<n)
    {
        cout<<"PROCESS : "<<i;
        a.name=i;
        cout<<"\nARRIVAL TIME : ";
        cin>>a.arrival_time;
        a.ready_time=a.arrival_time;
        cout<<"CPU BURST TIME : ";
        cin>>a.total_cpu_burst_time;
        cout<<"I/O BURST TIME : ";
        cin>>a.ioburst_time;
        cout<<"I/O CPU TIME : ";
        cin>>a.iointerval;
        a.priority=0;
        a.response_time=0;
        a.numofio=0;
        a.turnaround_time=0;
        a.waiting_time=0;
        input.push_back(a);
        i++;
    }
}
void hardcodeinput(vector <process> & input)
{

process temp;
    temp.name=0;
    temp.arrival_time=0;
    temp.ready_time=0;
    temp.total_cpu_burst_time=18;
    temp.ioburst_time=5;
    temp.iointerval=5;
    temp.priority=0;
    temp.response_time=0;
    temp.numofio=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push_back(temp);
    
     temp.name=1;
    temp.arrival_time=3;
    temp.ready_time=3;
    temp.total_cpu_burst_time=27;
    temp.ioburst_time=6;
    temp.iointerval=6;
    temp.priority=0;
    temp.response_time=0;
    temp.numofio=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push_back(temp);
    
     temp.name=2;
    temp.arrival_time=8;
    temp.ready_time=8;
    temp.total_cpu_burst_time=44;
    temp.ioburst_time=4;
    temp.iointerval=6;
    temp.priority=0;
    temp.response_time=0;
    temp.numofio=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push_back(temp);
    
     temp.name=3;
    temp.arrival_time=12;
    temp.ready_time=12;
    temp.total_cpu_burst_time=50;
    temp.ioburst_time=3;
    temp.iointerval=9;
    temp.priority=0;
    temp.response_time=0;
    temp.numofio=0;
    temp.turnaround_time=0;
    temp.waiting_time=0;
    input.push_back(temp);
    


}

int main()
{
    
    int n,i=0,hard;
    vector<process> input;

    cout<<"ENTER VALUE OF alpha : ";
    cin>>alpha;
    cout<<"ENTER VALUE OF beta : ";
    cin>>beta;

    if(alpha<=0||beta<0)
    {
        cout<<"both should be +ve ";
        cout<<"and alpha is not =0 exiting program";
        exit(0);
    }
    
    cout<<" hard coded input press 1 :";
    cin>>hard;
    if(hard==1)
    {
        hardcodeinput(input);
        preemptive_scheduling(input,4);
    }
    else
    {
        cout<<"ENTER NUMBER OF PROCESSES : ";
            cin>>n;
        givetheinput( input,n);
        preemptive_scheduling(input,n);
    }

    
    return 0;
}
