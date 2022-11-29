#include <iostream>
#include "constants.h"
#include "orbmech.h"
#include "orbmeche.h"

using namespace std;

	//scVec_i.push_back(sc_mass_i);
	//scVec_i.push_back(r_i);
	//scVec_i.push_back(dmdt);
	//scVec_i.push_back(time_step);

vector<double> electric(vector<double> scVec_i, vector<double> scVec_f)
{	
	cout << "Successful script run." << endl;

	double vel_i = v_circ_e(u_earth, scVec_i[1]);
	cout << "Initial velocity = " << vel_i << endl;

	scVec_f[0] = scVec_i[0] - scVec_i[3] * scVec_i[2];

	cout << "velocity change = " << ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]) << endl;

	double vel_f = vel_i - ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]);
	cout << "Final velocity = " << vel_f << endl;

	scVec_f[1] = u_earth/pow(vel_f,2);
	cout << "final a = " << scVec_f[1] << endl;



	return scVec_f;
}