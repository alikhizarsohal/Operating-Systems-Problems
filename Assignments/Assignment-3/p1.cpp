// 5 7 9 11 12 14 72 92 110 114 135 192
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include <pthread.h>
#include<unistd.h>
using namespace std;
class lock_unlock{
public:
	lock_unlock(int n)
	{
		this->total_number_of_processes=n;
        for(int i=0;i<n;i++)
        {
            v.emplace_back(0, 0);
        }
	}
    void set_to_fAlse(int i)
    {
        this->v[i].second=0;
    }
    void set_to_true(int i)
    {
        this->v[i].second=1;
        auto n = max_element(v.begin(), v.end(),
        [](const auto& n1, const auto& n2) {
            return n1.first < n2.first;
        });
        int An = n->first;
        this->v[i].first=An+1;
    }
    void ActuAl_lock(int t)
    {
        int i=0;
        while(i<this->total_number_of_processes)
        {
            if(i!=t);
            while(this->v[i].second==true);
            while(this->v[i].first!=0 && this->v[t].first > this->v[i].first);
            ++i;
        }
    }
    void set_ticket_to_zero(int i)
    {
        this->v[i].first=0;
        cout<<"Thread "<<i<<" left the critical section.\n";
    }
    void is_ko_lock_kr_do(int t)
    {
        set_to_true(t);
        set_to_fAlse(t);
        ActuAl_lock(t);
    }
    void is_ko_unlock_kr_do(int t)
    {
        set_ticket_to_zero(t);
    }
    void display()
    {
          for (const auto& p : v) {
            cout << p.first << " " << p.second<< endl;
    }
    }
	~lock_unlock()
	{

	}
public:
	int total_number_of_processes;
    vector<pair<int, bool>> v;
};
lock_unlock p(5);
void * run_All(void* Arguments)
{
    int* n=(int*)Arguments;
//    while(1)
//    {
        p.is_ko_lock_kr_do(*n);
        cout<<"Thread "<<*n<<" is in the critical section.\n";
        sleep(2);
        p.is_ko_unlock_kr_do(*n);
  //      cout<<"Thread "<<*n<<" left the critical section.\n";
  //      sleep(1);
  //  }
    pthread_exit(NULL);
}
int main()
{
    int n=5;
    pthread_t All_threads[n];
    int i=0;
    while(i<n)
    {
        int* numberr=new int;
        *numberr=i;
        pthread_create(&All_threads[i],NULL,run_All,numberr); 
        ++i;
    }
    for(int i=0;i<n;i++)
    {
        pthread_join(All_threads[i],NULL);
    }
//    p.display();
	return 0;
}
