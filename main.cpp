// CMakeAst.cpp : Defines the entry point for the application.
//
//#include "../lib/matplotlib-cpp-master/matplotlibcpp.h"
//namespace plt = matplotlibcpp;

#include <iostream>
#include "constants.h"
#include "orbmech.h"
#include <math.h> 			/*cos()*/

#include <vector>
#include "functions.h"
#include "examplescript.cpp"

using namespace std;


int main()
{
	run1();

	cout << "Successful open." << endl;
	
	cout << r_moon << endl;
	
    double v_inf = hyperbolicExcessSpeed(u_sun, r_orb_earth, 778600000);
    cout << v_inf << endl;
    double v_esc = sqrt(pow(v_inf,2)+2*u_earth/6678);
    cout << v_esc << endl;
    double d_v = v_esc - circularOrbitSpeed(u_earth,6678);
    cout << d_v << endl;
    

	return 0;
}
