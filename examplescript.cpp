#include <iostream>
#include "constants.h"
#include "orbmech.h"
#include "orbmeche.h"

using namespace std;

int electric(vector<double> radii)
{	
	cout << "Successful script run." << endl;

	const double time_step = 3600;				// seconds
	const double dmdt = 5.7415e-6;				// kg/s
	const double sc_mass_i = sls_payload_LEO;   // kg

	const double prop_frac = .396; 				// Mimicking DAWN
	const double inert_frac = prop_frac-1;


	double time_e = 0;

	double a_i = (10000+r_earth)/2;

	double vel_i = v_circ_e(u_earth, a_i);
	cout << "Initial velocity = " << vel_i << endl;

	double sc_mass = sc_mass_i + time_e * dmdt;

	double vel_f = vel_i - ((g_0 * isp_NEXTC * dmdt) * time_step / sc_mass);
	cout << "Final velocity = " << vel_f << endl;



	return 0;
}