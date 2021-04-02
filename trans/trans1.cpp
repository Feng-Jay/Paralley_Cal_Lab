#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int **martix;

void init_martix(int length)
{
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            martix[i][j]=i;
        }
    }
}

// void print_martix(int length)
// {
//     for(int i=0;i<length;i++){
//         for(int j=0;j<length;j++)
//         cout<<martix[i][j]<<" ";
//         cout<<endl;
//     }
// }

void trans_martix(int length)
{
    for(int i=0;i<length;i++){
        for(int j=i+1;j<length;j++){
            int temp=martix[i][j];
            martix[i][j]=martix[j][i];
            martix[j][i]=temp;
        }
    }
}

int main(int argc, char* argv[])
{
    int length= atoi(argv[1]);
    cout<<length<<endl;
    martix=new int*[length];
    for(int i=0;i<length;i++){
        martix[i]=new int[length];
    }
    init_martix(length);
    clock_t start,end;
    start=clock();
    trans_martix(length);
    end=clock();
    cout<<"time spend="<<(1.0*(end-start)/CLOCKS_PER_SEC)<<endl;
    return 0;
}