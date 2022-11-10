#include <math.h>           /*sqrt()*/


// hyperbolicExcessSpeed() for departure (same as ellipticDepartureSpeed())
double hyperbolicExcessSpeed(double u_relative, double r_orb_lower, double r_orb_higher) {
    // example leaving earth.
    //      u_relative = u_sun, 
    //      r_orb_lower = r_orb_earth
    //      r_orb_higher = r_orb_helioCentricAltitude 
    double v_inf;
    v_inf = sqrt(u_relative/r_orb_lower) * (sqrt(2*r_orb_higher/(r_orb_lower+r_orb_higher))-1); 
    return v_inf;
}

double circularOrbitSpeed(double u_relative, double r_orbit) {
    double v_circ;
    v_circ = sqrt(u_relative/r_orbit);
    return v_circ;
}

double ellipticDepartureSpeed(double u_relative, double r_orb_lower, double r_orb_higher) {
    double v_elipDep;
    v_elipDep = sqrt(2*u_relative) * sqrt(r_orb_higher/(r_orb_lower*(r_orb_lower+r_orb_higher)));
    return v_elipDep;
}

double deltaV_Departure(double u_relative_lower, double u_relative_higher, double r_orbit, double r_orb_lower, double r_orb_higher){
    double deltaV;
    double v_circ = circularOrbitSpeed(u_relative_lower, r_orbit);
    double v_hyperExcess = hyperbolicExcessSpeed(u_relative_higher, r_orb_lower, r_orb_higher);
    deltaV = v_circ * (sqrt(2 + pow((v_hyperExcess/v_circ),2)) - 1);
    return deltaV;
}







double r_eclipse(double trueAnomaly, double semimajorAxis, double eccentricity) {
    double radius;
    radius = semimajorAxis * ((1 - pow(eccentricity,2)) / (1 + eccentricity * cos(trueAnomaly)));
    return radius;
}

double v_ellipse(double u_relative, double semimajorAxis, double radius) {
    double v_ellip;
    v_ellip = sqrt((2*u_relative)/(radius) - u_relative/semimajorAxis);
    return v_ellip; 
}

double v_circ(double u_relative, double r_orbit){
    double v_circ;
    v_circ = sqrt(u_relative/r_orbit);
    return v_circ;
}

double v_escape(double u_relative, double r_orbit){
    double v_esc;
    v_esc = sqrt((2*u_relative) / r_orbit);
    return v_esc;
}
