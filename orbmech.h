#ifndef ORBMECH_H
#define ORBMECH_H

#include <math.h>           /*sqrt()*/


// hyperbolicExcessSpeed relative to the body being orbited //==============================================================================
double hyperbolicExcessSpeed(double u_relative, double r_orb_1, double r_orb_2) {
    // example leaving earth.
    //      u_relative   = u_sun, 
    //      r_orb_1  = r_orb_earth
    //      r_orb_higher = r_orb_desiredHelioCentricAltitude 
    double v_inf;
    if( r_orb_1 < r_orb_2){
        v_inf = sqrt(u_relative/r_orb_1) * (sqrt(2*r_orb_2/(r_orb_1+r_orb_2)) - 1); 
    }
    else {
        v_inf = sqrt(u_relative/r_orb_2) * (1 - sqrt(2*r_orb_1/(r_orb_1+r_orb_2))); 
    }
    
    
    return v_inf;
}

// Circular orbit speed of anything  //==============================================================================
    // Example of earth orbit speed around sun
    //      u_relative = u_sun
    //      r_orbit    = r_orb_earth
double circularOrbitSpeed(double u_relative, double r_orbit) {
    double v_circ;
    v_circ = sqrt(u_relative/r_orbit);
    return v_circ;
}

// Escape speed needed to reach hyperbolic excess speed //==============================================================================
    // Example of spacecraft departing earth
    //      u_relative   = u_earth
    //      v_inf        = hyperbolic excess speed
    //      r_orb_inital = spacecraft orbital radius 
double escapeSpeed(double u_relative, double v_inf, double r_orb_initial){
    double v_esc;
    v_esc = sqrt(pow(v_inf,2)+2*u_relative/r_orb_initial);
    return v_esc;
}


// DeltaV to park in a circular orbit from a hyperbolic
    // Example of spacecraft arriving at earth
    //      v_circ  = parking orbit velocity around earth
    //      v_inf   = hyperbolic excess speed from arrival parabola to earth orbital speed
double d_v_circle(double v_circ, double v_inf) {
    double d_v_circ;
    d_v_circ = v_circ * ( sqrt( 2 + pow((v_inf/v_circ),2)) - 1); 
    return d_v_circ;
}
















// Transfer elipse departure speed 
    // example of departing from the orbital radius of earth
    //      u_relative   = u_sun
    //      r_orb_higher = r_orb_jupiter
    //      r_orb_lower  = r_orb_earth
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
















double r_ellipse(double trueAnomaly, double semimajorAxis, double eccentricity) {
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






double time_ellipse(double u_rel, double semimajorAxis) {
    double timee;
    timee = 2*M_PI/sqrt(u_rel)*pow(semimajorAxis, 1.5);
    timee = timee/86400/30.4;
    return timee;
}











#endif