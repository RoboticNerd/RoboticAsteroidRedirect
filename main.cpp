// CMakeAst.cpp : Defines the entry point for the application.
//
#include "./lib/pbPlots.cpp"
#include "./lib/supportLib.cpp"

#include <iostream>
#include "constants.h"
#include "orbmech.h"		/*my orbital mechanics methods*/
#include "masscalc.h"		/*my mass methods*/
#include <math.h> 			/*cos()*/

#include <vector>
#include "functions.h"
#include "examplescript.cpp"

using namespace std;

int graphtest();
int graphingescapes();
vector<double> asteroidReturnHohman(double m_asteroid, double r_orb_asteroid, double inert_fraction, int verbosity);
int printVec(vector<double> vec);

int graphHohman(vector<double> radii, vector<double> asteroid_masses);

int debugi = 0;

const double final_sc_drymass = 10;						// kg 		sc remaining mass on asteroid post burn 					<---- Set


int main() 
{
	cout << "Successful open." << endl;
	run1();
	
	// calculating arrival dv's ==============================================================
	// initializations
	double r_orb_asteroid 	= r_orb_jupiter;			// km 		asteroid radius												<---- Set
	double m_asteroid 		= 1000;						// kg		asteroid mass												<---- Set
	double inert_fraction   = 0.20;						// 			inert fraction per stage of fuel mass						<---- Set

	vector<double> astVec;
	astVec = asteroidReturnHohman(m_asteroid, r_orb_asteroid, inert_fraction, 1);

	

	// scanning asteroid distances

	const double scan_step = 0.1e8;                          	// km step size for heliocentric orbital radii
	const double scan_start = 1.5e6 + r_orb_earth; 			// Edge of Earth's hill sphere (SOI) + orbital radius of earth (helio)
	const double m_asteroid_step = 10;						// kg 	asteroid mass step size
	const double m_asteroid_start = 100;						// kg 	asteroid mass size minimum
	inert_fraction = 0.20;								// how much inert mass to support spacecraft fuel at that stage
	const double total_steps = 1000;					// total steps to take



	vector<double> x_scanning_steps;
	x_scanning_steps.push_back(scan_start);
	vector<double> y_asteroids;
	

	int i = 0;
	double sc_seek;
	double m_asteroid_iter = m_asteroid_start;

	

	for (i=0; i < total_steps; i++){
		astVec = asteroidReturnHohman(m_asteroid_start, x_scanning_steps[i], inert_fraction, 0);
		
		if (astVec[0] < sls_payload_LEO){
			while ( sc_seek < sls_payload_LEO) {
				astVec = asteroidReturnHohman( m_asteroid_iter, x_scanning_steps[i], inert_fraction, 0);
				sc_seek = astVec[0];

				m_asteroid_iter = m_asteroid_iter + m_asteroid_step;

			}


			y_asteroids.push_back(m_asteroid_iter);
			sc_seek = 100;
			m_asteroid_iter = m_asteroid_start;
		}
		else {
			y_asteroids.push_back(0);
		}
			
		if (i < total_steps-1){
			x_scanning_steps.push_back(x_scanning_steps[i] + scan_step);

		}
		
	}


//	// normalizing x values
//	for (int i = 0; i <= x_scanning_steps.size(); i++){
//		x_scanning_steps[i] = x_scanning_steps[i]/r_orb_earth;
//	}
	cout << x_scanning_steps.size() << " " << y_asteroids.size() << endl;
	graphHohman(x_scanning_steps, y_asteroids);
//	printVec(x_scanning_steps);

	return 0;
}









vector<double> asteroidReturnHohman(double m_asteroid, double r_orb_asteroid, double inert_fraction, int verbosity){

	if (verbosity == 1) {cout << "===========================================================" << endl;} 
	double v_final = v_circ(u_earth, 10000);			// km/s		sc parking orbit velocity

	double v_earth = v_circ(u_sun, r_orb_earth);		// km/s 	earth orbital velocity

	double aaa = r_orb_asteroid + r_orb_earth;
	double v_p_f = v_ellipse(u_sun, aaa, r_orb_earth);						// km/s  perigee arrival velocity
	if (verbosity == 1) {cout << "velocity of arrival ellipse perigee        : " << v_p_f << " km/s" << endl;}

	double v_inf_f = abs(v_p_f - v_earth);
	if (verbosity == 1) {cout << "parking circular velocity                  : " << v_inf_f << " km/s" << endl;}

	double d_v_final = d_v_circle(v_final, v_inf_f);						// km/s 	dV needed to park in earth orbit
	if (verbosity == 1) {cout << "Arrival burn into parking orbit dV         : " << d_v_final << " km/s" << endl;}

	// Mass calculations now for last burn

	double fuel_final = fuelMass(d_v_final*1000, final_sc_drymass+m_asteroid, isp_RL10);
	double inert_final = fuel_final * inert_fraction;
	fuel_final = fuelMass(d_v_final*1000, final_sc_drymass+m_asteroid+inert_final, isp_RL10);
	if (verbosity == 1) {cout << "final burn fuel mass " << fuel_final << " kg" << endl;}
	if (verbosity == 1) {cout << "===========================================================" << endl;}




	
	
	// dv calculations for asteroid departure burn
	double v_asteroid = v_circ(u_sun, r_orb_asteroid);	// km/s circular orbit as far as jupiter
	if (verbosity == 1) {cout << "Velocity of asteroid circular orbit        : " << v_asteroid << " km/s" << endl;}

	double v_a_3 = v_ellipse(u_sun, aaa, r_orb_asteroid);			// km/s  apogee departure velocity
	if (verbosity == 1) {cout << "velocity of departure ellipse at apogee    : " << v_a_3 << " km/s" << endl;}

	double d_v_3 = abs(v_asteroid - v_a_3);							// km/s  dV 3rd burn
	if (verbosity == 1) {cout << "dV of burn to move asteroid into ellipse   : " << d_v_3 << " km/s" << endl;}

	// Mass calculations for 3rd burn
	double mass_3 = fuel_final + inert_final + final_sc_drymass + m_asteroid;
	if (verbosity == 1) {cout << "mass after departing with asteroid         : " << mass_3 << " kg" << endl;}
	double fuel_3 = fuelMass(d_v_3*1000, mass_3, isp_RL10);
	double inert_3 = fuel_3 * inert_fraction;
	fuel_3 = fuelMass(d_v_3*1000, mass_3+inert_3, isp_RL10);
	if (verbosity == 1) {cout << "third burn fuel mass " << fuel_3 << " kg" << endl;}
	if (verbosity == 1) {cout << "===========================================================" << endl;}




	// dv calculations for asteroid arrival burn
	double v_a_2 = v_a_3;													// km/s  apogee departure velocity
	if (verbosity == 1) {cout << "Apogee velocity of arriving elipse         : " << v_a_2 << " km/s" << endl;}

	double d_v_2 = abs(v_asteroid - v_a_2);									// km/s  dV 3rd burn
	if (verbosity == 1) {cout << "d_V of burn to join asteroid orbit         : " << d_v_2 << " km/s" << endl;}

	// Mass calculations for 2nd burn
	double mass_2 = mass_3 + fuel_3 + inert_3 - m_asteroid;
	if (verbosity == 1) {cout << "mass after burning to join with asteroid   : " << mass_2 << " kg" << endl;}
	double fuel_2 = fuelMass(d_v_2*1000, mass_2, isp_RL10);
	double inert_2 = fuel_2*inert_fraction;
	fuel_2 = fuelMass(d_v_2*1000, mass_2+inert_2, isp_RL10);
	if (verbosity == 1) {cout << "second burn fuel mass :" << fuel_2 << " kg" << endl;}
	if (verbosity == 1) {cout << "===========================================================" << endl;}






	// dv calculations for parabolic departure burn from earth
	
	double v_inf_1 = hyperbolicExcessSpeed(u_sun, r_orb_earth, r_orb_asteroid);
	if (verbosity == 1) {cout << "hyperbolic excess speed                    : " << v_inf_1 << " km/s" << endl;}
	double v_esc_1 = escapeSpeed(u_earth, v_inf_1, r_earth+200); 																// using leo
//	double v_esc_1 = escapeSpeed(u_earth, v_inf_1, r_p_GTO);          // 															FIX r orb departure
	if (verbosity == 1) {cout << "velocity needed to escape earth            : " << v_esc_1 << " km/s" << endl;}										// using leo
	double v_p_1 = v_circ(u_earth, r_earth+200);
//	double v_p_1 = v_ellipse(u_earth, a_GTO, r_p_GTO);
	if (verbosity == 1) {cout << "perigee velocity of departure ellipse      : " << v_p_1 << " km/s" << endl;}
	double d_v_1 = abs(v_esc_1 - v_p_1);
	if (verbosity == 1) {cout << "d_v of 1st burn                            : " << d_v_1 << " km/s" << endl;}


	// Mass calculations for 1st burn
	double mass_1 = fuel_2 + inert_2 + mass_2;
	if (verbosity == 1) {cout << "mass after burning to depart for asteroid  : " << mass_1 << " kg" << endl;}
	double fuel_1 = fuelMass(d_v_1*1000, mass_1, isp_RL10);
	double inert_1 = fuel_1*inert_fraction;
	fuel_1 = fuelMass(d_v_1*1000, mass_1+inert_1, isp_RL10);
	if (verbosity == 1) {cout << "1st burn fuel mass " << fuel_1 << " kg" << endl;}




	// Final things summary
	if (verbosity == 1) {
	cout << "===========================================================" << endl;
	cout << "===========================================================" << endl;
	cout << "Total spacecraft mass in LEO pre-burn      : " << fuel_1 + mass_1 + inert_1 << " kg" << endl;
	cout << "Total spacecraft fuel pre-burn             : " << fuel_1 + fuel_2 + fuel_3 + fuel_final << " kg" << endl;
	cout << "Total spacecraft inert mass                : " << inert_1 + inert_2 + inert_3 + inert_final + final_sc_drymass << " kg" << endl;
	cout << "Asteroid recovered mass to 10,000km orbit  : " << m_asteroid << " kg" << endl;
 	cout << "===========================================================" << endl;
	cout << "===========================================================" << endl;
	}


	// Returning final things
	vector<double> returning;

	returning.push_back(fuel_1 + mass_1 + inert_1);										// preburn spacecraft mass
	returning.push_back(fuel_1 + fuel_2 + fuel_3 + fuel_final);							// fuel mass
	returning.push_back(inert_1 + inert_2 + inert_3 + inert_final + final_sc_drymass);	// inert mass
	returning.push_back(m_asteroid);													// asteroid mass

	return returning;
}


int printVec(vector<double> vec) {
	for(vector<double>::iterator it = vec.begin(); it != vec.end(); it++) {
         cout << *it << endl;
     }

	return 0;
}


int graphHohman(vector<double> radii, vector<double> asteroid_masses){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();

	series->xs = &radii;
	series->ys = &asteroid_masses;


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 900;
	settings->height = 600;
	settings->title = toVector(L"Asteroid mass returned to Earth orbit vs asteroid orbit radius");
	settings->xLabel = toVector(L"Asteroid mass (kg)");
	settings->yLabel = toVector(L"Asteroid orbital radius (km)");
	settings->scatterPlotSeries->push_back(series);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "example.png");
	DeleteImage(imageReference->image);
	
	return 0;
}










int graphingescapes(){
		// initializing values for building radiuses and d_vs. ==========================
	double min_alt = r_p_GTO;
	double iter_alt = min_alt;

	vector<double> radiuses;
	vector<double> d_vs;

	cout << iter_alt << endl;
	cout << r_a_GTO << endl;

	while (iter_alt < r_a_GTO) {
		radiuses.push_back(iter_alt);
		d_vs.push_back(0);
		iter_alt = iter_alt + 1000;
		cout << iter_alt << endl;
	} 


	// Calculating dV's at varius orbital radiuses. ==========================================

	double v_inf;
	double v_esc;
	double d_v1;

	for (int i = 0; i <= radiuses.size(); i++) {
		cout << "Radius = " << radiuses[i] << " km" << endl;
		
		v_inf = hyperbolicExcessSpeed(u_sun, r_orb_earth, 778600000);
		v_esc = escapeSpeed(u_earth, v_inf, radiuses[i]);
//		d_vs[i] = v_esc - circularOrbitSpeed(u_earth, radiuses[i]);
		d_vs[i] = abs(v_esc - v_ellipse(u_earth, a_GTO, radiuses[i]));
		cout << "Delta V = " << d_vs[i] << " km/s" << endl;

	}


	size_t length;
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();


	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &radiuses;
	series->ys = &d_vs;

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 900;
	settings->height = 600;
	settings->title = toVector(L"Satellite dV required for departure at various radii");
	settings->xLabel = toVector(L"dV required (km/s)");
	settings->yLabel = toVector(L"Orbital Radius (km)");
	settings->scatterPlotSeries->push_back(series);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "example.png");
	DeleteImage(imageReference->image);

}

















int graphtest() {
	size_t length;

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	double xsa[] = {-2, -1, 0, 1, 2};
	vector<double> xs(xsa, xsa+sizeof(xsa)/sizeof(double));
	double ysa[] = {2, -1, -2, -1, 2};
	vector<double> ys(ysa, ysa+sizeof(ysa)/sizeof(double));

	DrawScatterPlot(imageReference, 900, 600, &xs, &ys);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "example.png");
	DeleteImage(imageReference->image);

	return 0;
}




