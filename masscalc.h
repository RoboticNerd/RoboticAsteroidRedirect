#include <math.h>           /*sqrt()*/
#include "constants.h"


// Preburn mass
    // Example 
double fuelMass(double d_V, double m_dry, double isp){
    double m_fuel;
    double m_initial;
        
    m_initial = m_dry/exp(d_V/(-isp*g_0));
    m_fuel = m_initial - m_dry;
    
    return m_fuel;
}

