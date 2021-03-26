#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;

const long long N=1000000000;
double PI,tim;

int main()
{
    // clock_t start,end;
    // start=clock();
    unsigned int seed=123;
    for(int i=0;i<N;i++){
        double x=1.0*rand_r(&seed)/RAND_MAX;
        double y=1.0*rand_r(&seed)/RAND_MAX;
        if(x*x+y*y<1.0)
        PI++;
    }
    PI=4*PI/N;
    // end=clock();
    // tim=(double)(end-start)/CLOCKS_PER_SEC;
    // cout<<"time: "<<tim<<"s"<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}