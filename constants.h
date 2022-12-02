#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants needed globally will be saved here.

// http://astro.vaporia.com/start/standardgravitationalparameter.html#:~:text=Example%20standard%20gravitational%20parameters%3A,1011%20km3s&text=Earth%20(aka%20geocentric%20gravitational%20constant,105%20km3s&text=Moon%3A%204.9028695%20%C3%97%20103%20km3s

//https://hanspeterschaub.info/Papers/UnderGradStudents/ConicReport.pdf

// Gravitational Coefficients
extern const double u_sun		    = 1.32712440018e11;		// km^3/s^2
extern const double u_earth		    = 3.986004418e5;		// km^3/s^2
extern const double u_moon		    = 4.9028695e3;			// km^3/s^2
extern const double u_jupiter       = 1.26686e8;            // km^3/s^2

// Orbital Radii
extern const double r_orb_mercury   = 5.7909050e7;          // km wrt sun
extern const double r_orb_earth		= 1.496e8;			    // km wrt sun
extern const double r_orb_moon		= 3.85e6;			    // km wrt earth
extern const double r_orb_mars      = 2.2613e8;             // km wrt sun
extern const double r_orb_ast_inner = 3.29e8;               // km wrt sun
extern const double r_orb_ast_outer = 4.787e8;              // km wrt sun
extern const double r_orb_jupiter   = 7.786e8;              // km wrt sun
extern const double r_orb_saturn    = 1.4711e9;             // km wrt sun
extern const double r_orb_uranus    = 2.9427e9;             // km wrt sun
extern const double r_orb_kuiper_inner = 4.4e9;             // km wrt sun
extern const double r_orb_neptune   = 4.4737e9;             // km wrt sun
extern const double r_orb_pluto     = 5.906356272e9;        // km wrt sun
extern const double r_orb_kuiper_outer = 14.9e9;            // km wrt sun

// ASE Spacecraft Dynamics
// https://solarsystem.nasa.gov/moons/earths-moon/in-depth/#:~:text=With%20a%20radius%20of%20about,miles%20(384%2C400%20kilometers)%20away.
// Radii
extern const double r_earth         = 6378;                 // km
extern const double r_moon          = 1740;                 // km

// Sphere of Influences
extern const double soi_earth	    = 9.29e5;				// km
extern const double soi_moon	    = 6.61e4;				// km
extern const double earth_soi       = 924659;               // km

// Typical GTO characteristics  https://conference.sdo.esoc.esa.int/proceedings/isdrw02/paper/10/ISDRW02-paper10.pdf
extern const double a_GTO           = 24371;                // km - semimajor axis
extern const double e_GTO           = 0.73;                 // - eccentricity
extern const double r_a_GTO         = a_GTO*(e_GTO + 1);    // km - apoapsis
extern const double r_p_GTO         = -a_GTO*(e_GTO - 1);   // km - periapsis
// argument of perigee 180          // deg
// orbital period 10.52             // hrs

// Propulsion constants
extern const double g_0             = 9.80665;              // m/s^2
extern const double isp_RL10        = 465;                  // sec
extern const double isp_NEXTC       = 4190;                 // sec                  https://www1.grc.nasa.gov/space/sep/gridded-ion-thrusters-next-c/#:~:text=NEXT%20can%20produce%206.9%20kW,compared%20to%203%2C120%20for%20NSTAR).

// SLS Vehicle Constants   https://www.lpi.usra.edu/lunar/constellation/SLS_FactSheet_long.pdf
extern const double sls_payload_LEO = 130000;               // kg Block 2 config
extern const double sls_payload_helio = 44905.6;            // kg Block 2 config
extern const double DAWN_wet        = 1217.7;               // kg




#endif