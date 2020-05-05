#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
int double_precision();
int long_double_precision();
int float_precision();

int main()
{
    while (1){
     double_precision();
     long_double_precision();
    float_precision();  
    cout << "----------------" << endl; 
    }
    return 0;
}

int double_precision()
{
double x = 0;
double inc = 1;
double x0 = -inc;
double diff;
 int ctr=0;

 while(x-x0==inc){
    inc = inc*10;
    x0 = x;
    x = x+inc;
    ctr++;
    diff = x-x0;
}

    cout << "the precision double is: " << ctr << endl;
 return 0;       
}

int float_precision()
{
float x = 0;
float inc = 1; //random large number
float x0 = -inc;
float diff;
 int ctr=0;

 while(x-x0==inc){
    inc = inc*10;
    x0 = x;
    x = x+inc;
    ctr++;
    diff = x-x0;
}

    cout << "the precision float is: " << ctr << endl;
 return 0;       
}

int long_double_precision()
{
long double x = 0;
long double inc = 1; //random large number
long double x0 = -inc;
long double diff;
 int ctr=0;

 while(x-x0==inc){
    inc = inc*10;
    x0 = x;
    x = x+inc;
    ctr++;
    diff = x-x0;
}

    cout << "the precision for long double is: " << ctr << endl;
 return 0;       
}
