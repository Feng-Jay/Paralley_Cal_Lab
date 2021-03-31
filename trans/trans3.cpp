#include <iostream>
#include <pthread.h>

using namespace std;

int **martix;
int N,T;

void* trans(void* arg)
{
    int order=*(int *)arg;
    int child_len=N/T;
    int begin=order*child_len;
    int end=(order==N-1)?N : begin+child_len;
    for(int i=begin;i<end;i++){
        for(int j=0;j<i;j++){
            martix[i][j]=martix[i][j]^martix[j][i];
            martix[j][i]=martix[i][j]^martix[j][i];
            martix[i][j]=martix[j][i]^martix[i][j];
        }
    }
    return NULL;
}

void print_martix()
{
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
        cout<<martix[i][j]<<" ";
        cout<<endl;
    }
}

void init_martix()
{
    martix=new int*[N];
    for(int i=0;i<N;i++){
        martix[i]=new int[N];
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            martix[i][j]=i;
        }
    }
}

int main(int agrc, char* agrv[])
{
    N=atoi(agrv[1]);
    T=atoi(agrv[2]);
    init_martix();
    print_martix();
    pthread_t *thread=new pthread_t[T];
    int *X=new int [T];
    for(int i=0;i<T;i++){
        X[i]=i;
        pthread_create(&thread[i],NULL,trans,&X[i]);
    }

    for(int i=0;i<T;i++){
        pthread_join(thread[i],NULL);
    }
    cout<<"outcome:\n";
    print_martix();
    return 0;
}