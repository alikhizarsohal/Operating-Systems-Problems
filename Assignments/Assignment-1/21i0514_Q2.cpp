#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <limits>
using namespace std;
void write()
{

	/* shared memory file descriptor */
	int shared_mem_obj;
	/* create the shared memory object */
	shared_mem_obj= shm_open("OS",  O_CREAT | O_RDWR, 0666);
	/* configure the size of the shared memory object */
	ftruncate(shared_mem_obj, 4096);
	/* memory map the shared memory object */
	/* pointer to shared memory obect */
	char *char_pointer;
	char_pointer = (char*) mmap(0,4096, PROT_WRITE, MAP_SHARED, 	shared_mem_obj, 0);
	/* write to the shared memory object */
	int user=0;
	cout<<"\nEnter the number of users : ";
	cin>>user;
for(int i=0;i<=user;i++)
{
	if(i!=0)
	{
	cout<<"\nUser"<<i<<" : ";	
	}
	char c1[50]{};
	char c2[50]{};
	cin.getline(c2,50);
	cout<<c2;
	for(int j=0;j<50;j++)
	{
		if(c2[j]==' ')
		   c1[j]='*';
		else
		   c1[j]=c2[j];
	}
		cout<<"\n"<<c1<<endl;
		sprintf(char_pointer,"%s",c1);
		char_pointer += strlen(c1);
	if(i!=user)
	{
		char temp[2]{"^"};
		sprintf(char_pointer,"%s",temp);
		char_pointer += strlen(temp);
	}
}

}
void displAy(string s)
{
	s+='\n';
	int c=0;
	for(int i=0;s[i]!='\n';i++)
	{
		bool b=0;
		if(s[i]=='^')
		{
			c+=1;
			cout<<"\nUser"<<c<<" : ";	
		}
		else if(s[i]=='*')
		{
			cout<<' ';
		}
		else
		{
			cout<<s[i];
		}
	}
}
void read()
{
	char msg[500]{};

	/* shared memory file descriptor */
	int shared_mem_obj;
	/* create the shared memory object */
	shared_mem_obj= shm_open("OS",  O_CREAT | O_RDWR, 0666);
	/* configure the size of the shared memory object */
	ftruncate(shared_mem_obj, 4096);
	/* memory map the shared memory object */
	/* pointer to shared memory obect */
	char *char_pointer;
	/* memory map the shared memory object */
	char_pointer = (char*) mmap(0, 4096, PROT_WRITE, MAP_SHARED, shared_mem_obj, 0);
	sscanf(char_pointer, "%s", msg);
	//char c[500]{};
	//c=msg;
	//for(int i=0;c[i]!='\n';i++){
	cout << msg << '\n';
	string st(msg);
	displAy(st);
	//}
}
int main()
{
write();
cout<<"\n-----\n";
read();
return 0;
}