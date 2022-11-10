// Constants needed globally will be saved here.

// http://astro.vaporia.com/start/standardgravitationalparameter.html#:~:text=Example%20standard%20gravitational%20parameters%3A,1011%20km3s&text=Earth%20(aka%20geocentric%20gravitational%20constant,105%20km3s&text=Moon%3A%204.9028695%20%C3%97%20103%20km3s

//https://hanspeterschaub.info/Papers/UnderGradStudents/ConicReport.pdf

// Gravitational Coefficients
extern const double u_sun		= 1.32712440018e11;		// km^3/s^2
extern const double u_earth		= 3.986004418e5;		// km^3/s^2
extern const double u_moon		= 4.9028695e3;			// km^3/s^2

// Orbital Radii
extern const double r_orb_earth		    = 1.496e8;			// km wrt sun
extern const double r_orb_moon		    = 3.85e6;			// km wrt earth


// ASE Spacecraft Dynamics
// https://solarsystem.nasa.gov/moons/earths-moon/in-depth/#:~:text=With%20a%20radius%20of%20about,miles%20(384%2C400%20kilometers)%20away.
// Radii
extern const double r_earth         = 6378;             // km
extern const double r_moon          = 1740;             // km

// Sphere of Influences
extern const double soi_earth	= 9.29e5;				// km
extern const double soi_moon	= 6.61e4;				// km

// Typical GTO characteristics  https://conference.sdo.esoc.esa.int/proceedings/isdrw02/paper/10/ISDRW02-paper10.pdf
extern const double a_GTO           = 24371;            // km - semimajor axis
extern const double e_GTO           = 0.73;              // - ecentricity
// argument of perigee 180          // deg
// orbital period 10.52             // hrs