#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <ctime>
#include <vector>
#include <utility>
using namespace std;

pthread_mutex_t m;
vector<pair<int,int>> waiting_list_l;
vector<pair<int,int>> waiting_list_r;
int m_buses=2,m_cars=4,b_l=0,c_l=0,b_r=0,c_r=0,t_b=0,t_c=0;
struct Argmt{

};
void Add_it_left(int t,int d)
{
    waiting_list_l.emplace_back(t,d);
}
void Add_it_right(int t,int d)
{
    waiting_list_r.emplace_back(t,d);
}
void drop_left()
{
    waiting_list_l.pop_back();
}
void drop_right()
{
    waiting_list_r.pop_back();  
}
void bridge_functionality(bool d)
{
    //here pick the first 1 or 2 or 3 or 4 buses from the vector 1 and allow to go
    pthread_mutex_lock(&m);
    if(d==0)//left
    {
        int count_c=0,count_b=0;
        for (const auto& p : waiting_list_l) 
        {
            if(p.first==1)
            {   
                ++count_c;
            }
            else
            {
                ++count_b;
            }
            if(count_c==4)
            {
                    --count_c;
                     --count_c; 
                     --count_c; 
                     --count_c;
                     c_l=c_l-4;
                     cout<<"\nCars on the bridge :"<<4;
                     cout<<"\nBuses on the bridge:"<<0;
                   break;
            }
            else if(count_b>=1 && count_c==2)
            {
                     cout<<"\nCars on the bridge :"<<4;
                     cout<<"\nBuses on the bridge:"<<1;
                     --count_c; 
                     --count_c;
                     --count_b;
                     c_l=c_l-2;
                     b_l-=1;
                   break;
            }
            else if(count_c==3)
            {
                    c_l-=3;
                     cout<<"\nCars on the bridge :"<<3;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                     --count_c;
                     --count_c;
                   break;
            }
            else if(count_c==2)
            {
                    c_l-=2;
                     cout<<"\nCars on the bridge :"<<2;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                     --count_c;
                break;
            }
            else if(count_c==1)
            {
                    c_l-=1;
                     cout<<"\nCars on the bridge :"<<1;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                break;
            }
            else{

                     cout<<"\nCars on the bridge :"<<0;
                     cout<<"\nBuses on the bridge:"<<0;
            }
        }
    }
    else{//right
                int count_c=0,count_b=0;
                        for (const auto& p : waiting_list_r) 
                        {
                            if(p.first==1)
            {   
                ++count_c;
            }
            else
            {
                ++count_b;
            }
            if(count_c==4)
            {
                    --count_c;
                     --count_c; 
                     --count_c; 
                     --count_c;
                     c_r=c_r-4;
                     cout<<"\nCars on the bridge :"<<4;
                     cout<<"\nBuses on the bridge:"<<0;
                   break;
            }
            else if(count_b>=1 && count_c==2)
            {
                     cout<<"\nCars on the bridge :"<<4;
                     cout<<"\nBuses on the bridge:"<<1;
                     --count_c; 
                     --count_c;
                     --count_b;
                     c_r=c_l-2;
                     b_r-=1;
                   break;
            }
            else if(count_c==3)
            {
                    c_r-=3;
                     cout<<"\nCars on the bridge :"<<3;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                     --count_c;
                     --count_c;
                   break;
            }
            else if(count_c==2)
            {
                    c_r-=2;
                     cout<<"\nCars on the bridge :"<<2;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                     --count_c;
                break;
            }
            else if(count_c==1)
            {
                    c_r-=1;
                     cout<<"\nCars on the bridge :"<<1;
                     cout<<"\nBuses on the bridge:"<<0;
                     --count_c; 
                break;
            }
            else{

                     cout<<"\nCars on the bridge :"<<0;
                     cout<<"\nBuses on the bridge:"<<0;
            }
                        }
    }
    pthread_mutex_unlock(&m);
}
void Arrived(int t,int d)
{
    //0 for left and 1 for right
    bool p=0;
    if(d==0)
    {
        Add_it_left(t,d);
    }
    else
    {
        Add_it_right(t,d);
        p=1;
    }
    //conditions
    if(t==0)// 0 for the car. 
    {
        cout<<"\nCar Arrived.";
           if(p)
           {
                ++c_r;
           }
           else{
                ++c_l;
           }
            ++t_c;
    }
    else if(t==1)// 1 for the bus.
    {
        cout<<"\nBus Arrived.";
           if(p)
           {
                ++b_r;
           }
           else{
                ++b_l;
           }
            ++t_b;
    }
    sleep(2);
    //here 1st funtionality for the left and then for the right
    bridge_functionality(0);//left
    bridge_functionality(1);//right

}
void* thread_function(void* Arguments)
{
    sleep(2);
    int*n = (int*)Arguments;
    srand(time(NULL));
    int t=rand()%2;
    int d=rand()%2;
    Arrived(t,d);
    pthread_exit(NULL);
}
int main()
{
    pthread_mutex_init(&m,NULL);
    pthread_t threads[20];
    int i=0;
    int* n=new int;
    while(i<20){
        *n=i;
        pthread_create(&threads[i],NULL,thread_function,n);
        ++i;
    }
    for(int i=0;i<20;i++)
    {
        pthread_join(threads[i],NULL);
    }
    delete n;
    pthread_mutex_destroy(&m);
    return 0;
}
