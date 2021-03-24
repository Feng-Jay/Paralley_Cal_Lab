#include <iostream>
#include <time.h>
#include <iomanip>
#include <pthread.h>

using namespace std;

long long N,T;
double PI=0;
pthread_mutex_t mut;

void* thread_function(void* arg)
{
    int order=*(int *)arg;
    int slice=N/T;
    int start=slice*order;
    int end=slice*(order+1);
    double temp=0;
    for(int i=start;i<end;i++){
        temp+=(4.0/N)*(1.0/(1+((i+0.5)/N)*((i+0.5)/N)));
    }
    pthread_mutex_lock(&mut);
    PI+=temp;
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main()
{
    cout<<"Input the number of N And thread"<<endl;
    cin>>N>>T;
    clock_t start,end;
    start=clock();
    pthread_t *thread=new pthread_t[T];
    int *X=new int[T];
    for(int i=0;i<T;i++){
        X[i]=i;
        pthread_create(&thread[i],NULL,thread_function,&X[i]);
    } 
    for(int i=0;i<T;i++){
        pthread_join(thread[i],NULL);
    }
    end=clock();
    double tim=1.0*(end-start)/CLOCKS_PER_SEC;
    cout<<"time spend is: "<<tim<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}