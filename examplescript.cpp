#include <iostream>
#include "constants.h"
#include "orbmech.h"

using namespace std;

int run1()
{
	cout << "Successful script run." << endl;
	double vel = hyperbolicExcessSpeed(u_sun, r_orb_earth, r_orb_earth*.8);
	cout << vel << endl;
	return 0;
}