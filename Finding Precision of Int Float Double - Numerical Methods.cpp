#include <cstdlib>
#include <iostream>
using namespace std;
bool x_plus_y_is_x (long double x, long double y);
int main(int argc, char *argv[])
{
long double x;
long double y, upper = 10000000000000000, lower = 0, mid;
int count = 0;

while (1)
{
	// Asking for user input
    if (!( cin>> x))
	{
		cout << "Invalid input. Exiting... \n";
		return 0;
	}
	
	//Initializing values for bisection method
    upper = 10000000000000000;
	lower = 0;
	mid = (upper + lower)/2;
	while (count<1000000)
	{
		if (x_plus_y_is_x (x, mid))
		{
			lower = mid;
		}
		else
		{
			upper = mid;
		}
		mid = (upper + lower)/2;
		count++;
	}
	cout<<upper<<endl<<endl;
	count=0;
}
return 0;
}

bool x_plus_y_is_x (long double x, long double y)
{
	if (x + y == x)
	return true;
	return false;
}
