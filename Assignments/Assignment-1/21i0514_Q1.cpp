#include<iostream>
#include<fstream>
#include<string>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iomanip>
#include<ctime>
using namespace std;
int file_num=0;
void display_the_matrix()
{
}
void read_from_file(int n)
{
	fstream f;
      for(int i=2;i<=n+1;i++)
	{
	 cout<<endl;
	 string str_p=to_string(i);
	 str_p+='.';str_p+='t';str_p+='x';str_p+='t';
  	 f.open(str_p,ios::in); 
   		if (f.is_open()){ 
     		 string str;
      		while(getline(f, str)){ 
      		   cout << str << " "; 
      }
	 }
       f.close();
	} 
}
void multiply_row_with_cols(int i,int**arr,int n,pid_t p)
{
	int mul[n][n];
	for(int j=0;j<n;j++)
	{
	int sum=0;
		for(int k=0;k<n;k++)
		{
			sum+=arr[i][k]*arr[k][j];

		}
		string str=to_string(file_num);
		str+='.';str+='t';str+='x';str+='t'; 
	fstream f;
	f.open(str, ios::app);
	if (!f) {
	}
	else {
		if(j==0)
		{
			f<<'.'<<p<<'.'<<endl;
		}
		f << sum<<endl;
		f.close();
	}
//	cout<<"\nsum "<<sum<<"   "<<file_num<<endl;
	}
}
void process_creation(int** arr,int n)
{
	for(int i=0;i<n;i++)
	{
		fflush(stdout);
	//	cout<<"\nfork() up:"<<i<<endl;
		int process_id=fork();
		file_num+=1;
	//	cout<<"\nfork() :"<<i<<endl;
		if(process_id>=0)
		{
			if(process_id==0)
			{
				pid_t p=getpid();
				file_num+=1;
				multiply_row_with_cols(i,arr,n,p);
			      exit(0);
			//	cout<<endl;
			}
			else
			{
				wait(0);
			}		
		}
	}
}
int** population_of_matrix(int n)
{
	int** arr=new int*[n];
	for(int i=0;i<n;i++)
	{
		arr[i]=new int[n];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			arr[i][j]=(rand()%9);
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<arr[i][j]<<' ';
		}
			cout<<endl;
	}
	fstream f;
	f.open("mAtrix.txt", ios::app);
	if (!f) {
	}
	else {
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				f<<arr[i][j]<<' ';
			}
				f<<'\n';
		}
		f.close();
	}
	return arr;
}
int div_number(int num)
{
	return 514/num;
}
int mul_number(int num)
{
	return num*4;
}
int main()
{
	srand(time(0));
	int num=(rand()%90 + 10);
	int orig_num=div_number(mul_number(num)) % 25;
	cout<<orig_num<<endl;
	if(orig_num<10)
	{
		orig_num+=15;
	}
	cout<<orig_num<<endl;
	process_creation(population_of_matrix(orig_num),orig_num);
	cout<<"\nAfter Multiplication\n";
	read_from_file(orig_num);
	return 0;
}
