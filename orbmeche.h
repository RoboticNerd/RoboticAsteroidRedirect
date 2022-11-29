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








#endif