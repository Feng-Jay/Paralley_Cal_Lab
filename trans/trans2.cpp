#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

using namespace std;

int len,T;
int **martix;

struct subblock{
    int id;
    int child_len;
};

void init_martix()
{
    martix=new int*[len];
    for(int i=0;i<len;i++){
        martix[i]=new int [len];
    }
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            martix[i][j]=i;
        }
    }
}

void print_martix()
{
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++)
        cout<<martix[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void* trans(void* arg)
{
    subblock * temp=(subblock*)arg;
    int id=temp->id;
    int child_len=temp->child_len;
    int blocknum=len/child_len;
    int row_begin=(id/blocknum)*child_len;
    int clob_egin=(id%blocknum)*child_len;
    for(int i=0;i<child_len;i++){
        for(int j=0;j<child_len;j++){
            martix[row_begin+i][clob_egin+j]=martix[row_begin+i][clob_egin+j]^martix[clob_egin+i][row_begin+j];
            martix[clob_egin+i][row_begin+j]=martix[row_begin+i][clob_egin+j]^martix[clob_egin+i][row_begin+j];
            martix[row_begin+i][clob_egin+j]=martix[clob_egin+i][row_begin+j]^martix[row_begin+i][clob_egin+j];
        }
    }
    
    return NULL;
}


void* inner_trans(void* arg)
{
    int order= *(int *)arg;
    int child_len=len/sqrt(T);
    int rowblock_num=len/child_len;

    int row_begin=(order/rowblock_num)*child_len;
    int clo_begin=(order%rowblock_num)*child_len;

    for(int i=0;i<child_len;i++){
        for(int j=i+1;j<child_len;j++){
            martix[row_begin+i][clo_begin+j]=martix[row_begin+i][clo_begin+j]^martix[row_begin+j][clo_begin+i];
            martix[row_begin+j][clo_begin+i]=martix[row_begin+i][clo_begin+j]^martix[row_begin+j][clo_begin+i];
            martix[row_begin+i][clo_begin+j]=martix[row_begin+j][clo_begin+i]^martix[row_begin+i][clo_begin+j];
        }
    }
    return NULL;
}

int main(int agrc, char* agrv[])
{
    int m=atoi(agrv[1]);//m=100
    T=m*m;//T=10000
    len=m*m;//len=10000
    int child_len=(int)sqrt((len*len)/T);//100
    int num=len/child_len;//100
    int num_thread=num*(num-1)/2;//99*50
    pthread_t *thread=new pthread_t[num_thread];
    int *X=new int [num_thread];
    init_martix();
    // print_martix();
    int temp=0;
    for(int i=0;i<num;i++){
        for(int j=i+1;j<num;j++){
            subblock locate;
            locate.id=i*child_len+j;
            locate.child_len=child_len;
            pthread_create(&thread[temp],NULL,trans,&locate);
            temp++;
        }
    }
    for(int i=0;i<num_thread;i++){
        pthread_join(thread[i],NULL);
    }
    // delete(thread);
    // delete(X);
    // cout<<"first trans"<<endl;
    // print_martix();
    
    pthread_t *thread_2=new pthread_t[T];
    int *Y=new int [T];
    for(int i=0;i<T;i++){
        Y[i]=i;
        pthread_create(&thread_2[i],NULL,inner_trans,&Y[i]);
    }
    for(int i=0;i<T;i++){
        pthread_join(thread_2[i],NULL);
    }
    // delete(thread_2);
    // delete(Y);
    // cout<<"second trans"<<endl;
    // print_martix();

}