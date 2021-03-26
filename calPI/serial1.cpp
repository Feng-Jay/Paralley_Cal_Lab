#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

const long long N=1000000000;
double PI=0;


int main()
{
    // clock_t start,end;
    // start=clock();
    for(int i=0;i<N;i++){
         PI+=(4.0/N)*(1.0/(1+((i+0.5)/N)*((i+0.5)/N)));
    }
    // end=clock();
    // double tim=1.0*(end-start)/CLOCKS_PER_SEC;
    // cout<<"time spend is: "<<tim<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}