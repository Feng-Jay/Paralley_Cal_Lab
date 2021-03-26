#include <iostream>
#include <time.h>
#include <iomanip>
#include <pthread.h>

using namespace std;

const long long N=1000000000;
const long long T=10;
double PI=0;
pthread_mutex_t mut;

void* thread_function(void* arg)
{
    int order=*(int *)arg;
    int neg_pos;
    if(order%2==0)
        neg_pos=1;
    else
        neg_pos=-1;
    int slice=N/T;
    int start=slice*order;
    int end=slice*(order+1);
    double temp=0;
    for(int i=start;i<end;i++,neg_pos=-neg_pos){
        temp+=(1.0*neg_pos)/(2*i+1);
    }
    pthread_mutex_lock(&mut);
    PI+=4.0*temp;
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main()
{
    // clock_t start,end;
    // start=clock();
    pthread_t thread[T];
    int X[T];
    for(int i=0;i<T;i++){
        X[i]=i;
        pthread_create(&thread[i],NULL,thread_function,&X[i]);
    } 
    for(int i=0;i<T;i++){
        pthread_join(thread[i],NULL);
    }
    // end=clock();
    // double tim=1.0*(end-start)/CLOCKS_PER_SEC;
    // cout<<"time spend is: "<<tim<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}