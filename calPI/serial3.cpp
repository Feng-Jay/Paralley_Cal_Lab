#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

double PI=0;
const long long N=1000000000;
double tim=0;

int main()
{
    // clock_t start,end;
    // start=clock();
    int neg_pos=1;
    for(int i=0;i<N;i++,neg_pos=-neg_pos){
        PI+=1.0*neg_pos/(2*i+1);
    }
    PI*=4;
    // end=clock();
    // tim=1.0*(end-start)/CLOCKS_PER_SEC;
    // cout<<"time spend: "<<tim<<endl;
    cout<<fixed<<setprecision(10)<<PI<<endl;
}