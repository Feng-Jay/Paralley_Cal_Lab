#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

long long N;
double PI=0;


int main()
{
    cout<<"Input the number of N"<<endl;
    cin>>N;
    clock_t start,end;
    start=clock();
    for(int i=0;i<N;i++){
         PI+=(4.0/N)*(1.0/(1+((i+0.5)/N)*((i+0.5)/N)));
    }
    end=clock();
    double tim=1.0*(end-start)/CLOCKS_PER_SEC;
    cout<<"time spend is: "<<tim<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}