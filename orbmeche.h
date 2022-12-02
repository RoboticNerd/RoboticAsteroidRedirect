#ifndef ORBMECHE_H
#define ORBMECHE_H

#include <math.h>           /*sqrt()*/

class SCRecover {
    public: 
        double sc_mass;
        double sc_r;
        double sc_prop;

};


double v_circ_e(double u_relative, double a){
    return sqrt(u_relative/a);
}

double thrust_e(double dmdt){
    return g_0 * isp_NEXTC * dmdt;  // thrust
}

double deltaV_e(double force, double time, double mass){
    return force * time / mass;     // dV
}




vector<double> electric(vector<double> scVec_i, vector<double> scVec_f)
{	
	//cout << "Successful script run." << endl;

	double vel_i = v_circ_e(u_earth, scVec_i[1]);
	//cout << "Initial velocity = " << vel_i << endl;

	scVec_f[0] = scVec_i[0] - scVec_i[3] * scVec_i[2];

	//cout << "velocity change = " << ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]) << endl;

	double vel_f = vel_i - ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]);
	//cout << "Final velocity = " << vel_f << endl;

	scVec_f[1] = u_earth/pow(vel_f,2);
	//cout << "final a = " << scVec_f[1] << endl;

    scVec_f[4] = scVec_i[4] + scVec_i[3];

	return scVec_f;
}


vector<double> electricD(vector<double> scVec_i, vector<double> scVec_f)
{	
	//cout << "Successful script run." << endl;

	double vel_i = v_circ_e(u_earth, scVec_i[1]);
	//cout << "Initial velocity = " << vel_i << endl;

	scVec_f[0] = scVec_i[0] - scVec_i[3] * scVec_i[2];

	//cout << "velocity change = " << ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]) << endl;

	double vel_f = vel_i + ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]);
	//cout << "Final velocity = " << vel_f << endl;

	scVec_f[1] = u_earth/pow(vel_f,2);
	//cout << "final a = " << scVec_f[1] << endl;

    scVec_f[4] = scVec_i[4] + scVec_i[3];

	return scVec_f;
}





vector<double> electricSun(vector<double> scVec_i, vector<double> scVec_f)
{	
	//cout << "Successful script run." << endl;

	double vel_i = v_circ_e(u_sun, scVec_i[1]);
	//cout << "Initial velocity = " << vel_i << endl;

	scVec_f[0] = scVec_i[0] - scVec_i[3] * scVec_i[2];

	//cout << "velocity change = " << ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]) << endl;

	double vel_f = vel_i - ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]);
	//cout << "Final velocity = " << vel_f << endl;

	scVec_f[1] = u_sun/pow(vel_f,2);
	//cout << "final a = " << scVec_f[1] << endl;

    scVec_f[4] = scVec_i[4] + scVec_i[3];

	return scVec_f;
}


vector<double> electricSunD(vector<double> scVec_i, vector<double> scVec_f)
{	
	//cout << "Successful script run." << endl;

	double vel_i = v_circ_e(u_sun, scVec_i[1]);
	//cout << "Initial velocity = " << vel_i << endl;

	scVec_f[0] = scVec_i[0] - scVec_i[3] * scVec_i[2];

	//cout << "velocity change = " << ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]) << endl;

	double vel_f = vel_i + ((g_0/1000 * isp_NEXTC * scVec_i[2]) * scVec_i[3] / scVec_i[0]);
	//cout << "Final velocity = " << vel_f << endl;

	scVec_f[1] = u_sun/pow(vel_f,2);
	//cout << "final a = " << scVec_f[1] << endl;

    scVec_f[4] = scVec_i[4] + scVec_i[3];

	return scVec_f;
}






#endif