#include <iostream>
#include <ctime>
#include <pthread.h>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;
const long long N=1000000000;
const long long T=10;
double PI=0;
double tim;
pthread_mutex_t mut;

void* thread_function(void* arg)
{
    unsigned int seed=110;
    int slice = N/T;
    long long temp=0;
    for (int i=0;i<slice;i++){
        double x=1.0*rand_r(&seed)/RAND_MAX;
        double y=1.0*rand_r(&seed)/RAND_MAX;
        if (x*x+y*y<1)
        {
            temp++;
        }
    }
    pthread_mutex_lock(&mut);
    PI+=temp;
    pthread_mutex_unlock(&mut);
    return NULL;
}
int main()
{
    pthread_t thread[T];
    int X[T];
    // clock_t start,end;
    // start=clock();
    for (long long i=0;i<T;i++){
        X[i]=i;
        pthread_create(&thread[i],NULL,thread_function,&X[i]);
    }
    for(long long i=0;i<T;i++){
        pthread_join(thread[i],NULL);
    }
    // end=clock();
    // tim=(double)(end-start)/CLOCKS_PER_SEC;
    // cout<<"time: "<<tim<<"s"<<endl;
    cout<<fixed<<setprecision(10)<<PI*4/N<<endl;
}