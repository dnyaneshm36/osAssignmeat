#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
#define magicno 30000


struct allocated_data
{
    char name;
    int start;
    int size;

};
struct allocated_data a[10];

    int heap[100];
	int headptr;
    
  

void init()
{
	for(int i=0;i<10;i++){
		a[i].name='*';
		a[i].size=0;
		a[i].start=0;
	}	
	headptr=0;
	heap[0]=98;
	heap[1]=-1;
	
}  
    
void mallocinheap(string str)
{
	int flag1=1;
int  first = str.find("(");
int last = str.find(")");
	string strNew = str.substr(first+1,last-first-1);
	int size;
	 size=stoi(strNew);
	first=str.find("=");
	char name=str[first-1];

	int temp=headptr;
	
CHEAKINGSIZE:	
	
	if(heap[temp]>=size+2)
	{	int flag=0;
		for(int i=0;i<10&&flag==0;i++){ 
			if(a[i].name=='*'&&a[i].size==0){
				a[i].name=name;
				a[i].start=temp+2;
				a[i].size=size;
				flag=1;
			}
		}
		if(flag==0)
		{
			cout<<"the allocated memory  for storring names should be more\n";
		}
		else{
					heap[temp+size+3]=heap[temp+1];
					heap[temp+size+2]=heap[temp]-(size+2);
					heap[temp]=size;  //size of allocated memory
					heap[temp+1]=magicno;  //TO show that it allocaated
					headptr=temp+size+2;
		}

	}
	else
	{
		if(heap[temp+1]==-1)
		{
			flag1=0;
			cout<<"HEAP OVERFLOW: there no more space to allocated";
		}
		else{
			temp=heap[temp+1];
			goto CHEAKINGSIZE;
		}

	}
	
	if(flag1==1)
	{
		cout<<size<<"units of memory is allocated pointed by "<<name<< ". Changed pointers: "<<name<<"="<<temp+2<<",head="<<headptr;
		cout<<endl;

	}

	
}
void freeinheap(string str)
{
int  first = str.find("(");
int last = str.find(")");
char newchar = str[first+1];

	int i;
	for( i=0;i<10;i++)
	{
		if(a[i].name==newchar)
		{
			a[i].name='*';
			heap[a[i].start-1]=headptr;
			headptr=a[i].start-2;
		}
	}
	cout<<"Memory pointed by" <<newchar<<"(" <<a[i].size<<" units) is freed. Changed pointers: head="<<headptr<<endl;
	
	
/*	
		//collasing if possible
	for(int j=0;j<10;j++)
	{
		if(a[j].name=='*'&&a[j].size!=0)
		{
			if((a[j].start+a[j].size+2)==a[i].start)
			{
				int jprev,inext,jnext,iprev;
				inext=heap[a[i].start-1];
				jnext=heap[a[j].start-1];
				int trav=headptr;
				jprev=trav;
				while(heap[trav+1]!=-1)
				{
					if(a[j].start-2==trav)
					{
						break;
					}
					else
					{
						jprev=trav;
					}
					
				}
				
				heap[jprev]=jnext;
				headptr=a[j].start-2;
				heap[a[j].start-2]=inext;
				heap[a[j].start-1]=a[i].size+a[j].size+2;
				a[i].start=a[j].start;
				a[j].start=-1;
				a[i].size=a[i].size+a[j].size+2;  //big space stored at i 
				a[j].size=0; //intitial value  for j
				//now we hava to maintaint the the links in heap
				// so the it problem similar to joining to two node in the list
				
			
				j=0;	
				
			}	
		}
	}
	for(int j=0;j<10;j++)
	{
		if(a[j].name=='*'&&a[j].size!=0)
		{
			if((a[i].size+a[j].size+2)==a[j].start)
			{
				int jprev,inext,jnext,iprev;
				inext=heap[a[i].start-1];
				jnext=heap[a[j].start-1];
				int trav=headptr;
				jprev=trav;
				while(heap[trav+1]!=-1)
				{
					if(a[j].start-2==trav)
					{
						break;
					}
					else
					{
						jprev=trav;
					}
					
				}
				
				heap[jprev]=jnext;
				
				heap[a[i].start-2]=a[i].size+a[j].size+2;
				
				a[i].start=a[j].start;
				a[j].start=-1;
				a[i].size=a[i].size+a[j].size+2;  //big space stored at i 
				a[j].size=0; //intitial value  for j
				//now we hava to maintaint the the links in heap
				// so the it problem similar to joining to two node in the list
				
			
				j=0;	
				
			}	
		}
	}
	*/

}
void display_status()
{
	cout<<"Free memory track: head="<<headptr<<", ";
	int temp=headptr;
	int total=0;
FREENOTEND:	
	if(heap[temp+1]==-1)
	{
		cout<<temp<<"("<<heap[temp]<<"units ) ->null.\n";
		total+=heap[temp];
		cout<<"Total free memeory ="<<total<< " units. \n";
	}
	else
	{
		cout<<temp<<"("<<heap[temp]<<"units)->"; 
		total+=heap[temp];
		temp=heap[temp+1];
		goto FREENOTEND;
	}
	cout<<"User pointers:";
	for(int i=0;i<10;i++)
	{
		if(a[i].name!='*')
		{
			cout<<a[i].name<<"="<<a[i].start<<"("<<a[i].size<<"units)";
		}
	}
	cout<<endl;
	
}
void coalesce_memory()
{
	int flag=1;
	int j;
	for(int i=0;i<100;i=i+heap[i]+2)
	{

		if(heap[i+1]!=magicno)
		{
			if(flag==1)
			{
				flag=0;
				headptr=i;
				j=i;
				if(heap[i+heap[i]+2+1]!=magicno)
				{
					int temp=heap[i];
					heap[i]=temp+2+heap[i+2+temp];
					continue;
				}
			}
			if(heap[i+heap[i]+2+1]!=magicno)
			{	
					heap[j+1]=i;
					j=i;
					int temp=heap[i];
					heap[i]=temp+2+heap[i+temp+2];
					continue;
			}
		}

	}
	heap[j+1]=-1;
}
int main() {
    //code
	init();
    string str="";
        string ext="exit";
        while(str!=ext)
        {
            cout<<"Shell$";
            getline(cin,str);
            if(str!="")
            {
                if(str==ext)
                {
                    return 0;
                }
                else if (str.find("malloc") != std::string::npos) 
				{
   	 					mallocinheap(str);
				}
				else if (str.find("free") != std::string::npos) 
				{
					freeinheap(str);
				}
				else if (str.find("display_status") != std::string::npos) 
				{
					display_status();
				}
				else if(str.find("coalesce_memory") != std::string::npos)
				{
					coalesce_memory();
				}
				else
				{
					cout<<"ENTER THE CORRECT STATEMENT \n";
				}
                

            }
        }
    return 0;
}
