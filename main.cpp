// CMakeAst.cpp : Defines the entry point for the application.
//
#include "./lib/pbPlots.cpp"
#include "./lib/supportLib.cpp"

#include <iostream>
#include <fstream>
#include "constants.h"
#include "orbmech.h"		/*orbital mechanics methods*/
#include "orbmeche.h"		/*electric orbital mechanica methods*/
#include "masscalc.h"		/*mass methods*/
#include <math.h> 			/*cos()*/

#include <vector>
#include "functions.h"
#include "electricscript.cpp"

using namespace std;
//
int graphtest();
int graphingescapes();
vector<double> asteroidReturnHohman(double m_asteroid, double r_orb_asteroid, double inert_fraction, int verbosity);
int printVec(vector<double> vec);

int chemicalReturnScript();
int electricalReturnScript();
int hybridScript();
int graphHohman(vector<double> radii, vector<double> asteroid_masses);
int graphHohman3(vector<double> radii, vector<double> asteroid_masses8,vector<double> asteroid_masses9,vector<double> asteroid_masses95);
int graphElectric(vector<double> radii, vector<double> asteroid_masses_4, vector<double> asteroid_masses_5, vector<double> asteroid_masses_6);
int graphElectric1(vector<double> radii, vector<double> asteroid_masses_4);
int graphTimeH(vector<double> radii, vector<double> h_time);
int graphTimeE(vector<double> radii, vector<double> h_time);

int debugi = 0;

const double final_sc_drymass = 10;						// kg 		sc remaining mass on asteroid post burn 					<---- Set
extern int flop_iter = 0;

int main() 
{
	cout << "Successful open." << endl;

	//chemicalReturnScript();
	//electricalReturnScript();
	hybridScript();



	



	return 0;
}



int hybridScript(){
	cout << "----------------" << endl;
	// initializations

	//cout << "Earth departing velocity = " << earth_dep_v << endl;

	//const double r_arr_v = v_circ(u_sun, r_orb_mars);
	//cout << "Mars arriving velocity = " << r_arr_v << endl;

	//const double scan_step = 0.001e8;                          	// km step size for heliocentric orbital radii
	//const double step_count = (r_orb_ast_outer - r_orb_mercury) / scan_step;
	
	const double step_count = 16;
	const double scan_step = (r_orb_ast_outer - r_orb_mercury)/step_count;

	// Initializing mask for Earth's hill sphere (won't search in that range)
	const double soi_lower = r_orb_earth - soi_earth*1.5;
	const double soi_higher = r_orb_earth + soi_earth*1.5;

	// Building the scanning range (asteroid orbital radii)
	vector<double> x_scanning_radii;
	vector<double> h_time;
	x_scanning_radii.push_back(r_orb_mercury);
	h_time.push_back(0);
	for (int i = 0; i < step_count; i++){
		x_scanning_radii.push_back(x_scanning_radii[i] + scan_step);
		h_time.push_back(0);
	}

	// Scanning each radii for maximum asteroid size

	vector<double> y_asteroids4;
	vector<double> y_asteroids5;
	vector<double> y_asteroids6;
	vector <double> asteroidMass;
	int iterrr = 1;

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids4.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScanH(x_scanning_radii[i], .4);
				y_asteroids4.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanHD(x_scanning_radii[i], .4);
				y_asteroids4.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids5.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScan(x_scanning_radii[i], .5);
				y_asteroids5.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanD(x_scanning_radii[i], .5);
				y_asteroids5.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids6.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScan(x_scanning_radii[i], .6);
				y_asteroids6.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanD(x_scanning_radii[i], .6);
				y_asteroids6.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}



	// Converting radii to AU before graphing
	for (int i = 0; i < x_scanning_radii.size(); i++){
		x_scanning_radii[i] = x_scanning_radii[i] / r_orb_earth; 
	}

	// Converting time to months before graphing
	for (int i = 0; i < x_scanning_radii.size(); i++){
		h_time[i] = h_time[i] / 60 / 60 / 24 / 30.4; 
	}


	// Optional clipping of asteroid mass for graphing
	// double clip = 5000;
	// for (int i = 0; i < x_scanning_radii.size(); i++){
	// 	if(y_asteroids4[i] > clip){
	// 		y_asteroids4[i] = clip;
	// 	}
	// 	if(y_asteroids5[i] > clip){
	// 		y_asteroids5[i] = clip;
	// 	}
	// 	if(y_asteroids6[i] > clip){
	// 		y_asteroids6[i] = clip;
	// 	}
	// }



	cout << x_scanning_radii.size() << " " << y_asteroids4.size() << " " << h_time.size() << endl;
	graphElectric(x_scanning_radii, y_asteroids4, y_asteroids5, y_asteroids6);
	graphElectric1(x_scanning_radii, y_asteroids4);
	graphTimeE(x_scanning_radii, h_time);

	std::ofstream ff("electric_radii.txt");
	for(vector<double>::const_iterator i = x_scanning_radii.begin(); i != x_scanning_radii.end(); ++i) {
    	ff << *i << '\n';
	}

	std::ofstream gg("electric_ast4.txt");
	for(vector<double>::const_iterator i = y_asteroids4.begin(); i != y_asteroids4.end(); ++i) {
    	gg << *i << '\n';
	}
	
	std::ofstream hh("electric_ast5.txt");
	for(vector<double>::const_iterator i = y_asteroids5.begin(); i != y_asteroids5.end(); ++i) {
    	hh << *i << '\n';
	}	
	
	std::ofstream kk("electric_ast6.txt");
	for(vector<double>::const_iterator i = y_asteroids6.begin(); i != y_asteroids6.end(); ++i) {
    	kk << *i << '\n';
	}
	



	return 0;
}



int electricalReturnScript(){

	
	cout << "----------------" << endl;
	// initializations

	//cout << "Earth departing velocity = " << earth_dep_v << endl;

	//const double r_arr_v = v_circ(u_sun, r_orb_mars);
	//cout << "Mars arriving velocity = " << r_arr_v << endl;

	//const double scan_step = 0.001e8;                          	// km step size for heliocentric orbital radii
	//const double step_count = (r_orb_ast_outer - r_orb_mercury) / scan_step;
	
	const double step_count = 1000;
	const double scan_step = (r_orb_ast_outer - r_orb_mercury)/step_count;

	// Initializing mask for Earth's hill sphere (won't search in that range)
	const double soi_lower = r_orb_earth - soi_earth*1.5;
	const double soi_higher = r_orb_earth + soi_earth*1.5;

	// Building the scanning range (asteroid orbital radii)
	vector<double> x_scanning_radii;
	vector<double> h_time;
	x_scanning_radii.push_back(r_orb_mercury);
	h_time.push_back(0);
	for (int i = 0; i < step_count; i++){
		x_scanning_radii.push_back(x_scanning_radii[i] + scan_step);
		h_time.push_back(0);
	}

	// Scanning each radii for maximum asteroid size

	vector<double> y_asteroids4;
	vector<double> y_asteroids5;
	vector<double> y_asteroids6;
	vector <double> asteroidMass;
	int iterrr = 1;

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids4.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScan(x_scanning_radii[i], .4);
				y_asteroids4.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanD(x_scanning_radii[i], .4);
				y_asteroids4.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids5.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScan(x_scanning_radii[i], .5);
				y_asteroids5.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanD(x_scanning_radii[i], .5);
				y_asteroids5.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}

	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids6.push_back(0);
			h_time[i] = 0;
		}
		else{ 
			if (x_scanning_radii[i] > r_orb_earth){
				asteroidMass = electricRadiusScan(x_scanning_radii[i], .6);
				y_asteroids6.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}
			if (x_scanning_radii[i] < r_orb_earth){
				asteroidMass = electricRadiusScanD(x_scanning_radii[i], .6);
				y_asteroids6.push_back(asteroidMass[0]);
				h_time[i] = asteroidMass[1];
			}

		}
		cout << "Percent Complete: " << iterrr/(step_count+1)*100 << " %" << endl;
		iterrr++;
	}



	// Converting radii to AU before graphing
	for (int i = 0; i < x_scanning_radii.size(); i++){
		x_scanning_radii[i] = x_scanning_radii[i] / r_orb_earth; 
	}

	// Converting time to months before graphing
	for (int i = 0; i < x_scanning_radii.size(); i++){
		h_time[i] = h_time[i] / 60 / 60 / 24 / 30.4; 
	}


	// Optional clipping of asteroid mass for graphing
	double clip = 5000;
	for (int i = 0; i < x_scanning_radii.size(); i++){
		if(y_asteroids4[i] > clip){
			y_asteroids4[i] = clip;
		}
		if(y_asteroids5[i] > clip){
			y_asteroids5[i] = clip;
		}
		if(y_asteroids6[i] > clip){
			y_asteroids6[i] = clip;
		}
	}



	cout << x_scanning_radii.size() << " " << y_asteroids4.size() << " " << h_time.size() << endl;
	graphElectric(x_scanning_radii, y_asteroids4, y_asteroids5, y_asteroids6);
	graphElectric1(x_scanning_radii, y_asteroids4);
	graphTimeE(x_scanning_radii, h_time);

	std::ofstream ff("electric_radii.txt");
	for(vector<double>::const_iterator i = x_scanning_radii.begin(); i != x_scanning_radii.end(); ++i) {
    	ff << *i << '\n';
	}

	std::ofstream gg("electric_ast4.txt");
	for(vector<double>::const_iterator i = y_asteroids4.begin(); i != y_asteroids4.end(); ++i) {
    	gg << *i << '\n';
	}
	
	std::ofstream hh("electric_ast5.txt");
	for(vector<double>::const_iterator i = y_asteroids5.begin(); i != y_asteroids5.end(); ++i) {
    	hh << *i << '\n';
	}	
	
	std::ofstream kk("electric_ast6.txt");
	for(vector<double>::const_iterator i = y_asteroids6.begin(); i != y_asteroids6.end(); ++i) {
    	kk << *i << '\n';
	}
	



	return 0;
}








int chemicalReturnScript() {
		// scanning asteroid distances


		// calculating arrival dv's ==============================================================
	// initializations
	double m_asteroid 		= 1000;						// kg		asteroid mass												<---- Set
	double inert_fraction   = 0.10;						// 			inert fraction per stage of fuel mass						<---- Set

	vector<double> astVec;
//	astVec = asteroidReturnHohman(m_asteroid, r_orb_asteroid, inert_fraction, 1);
	astVec = asteroidReturnHohman(100, r_orb_earth*.9, inert_fraction, 1);



	const double scan_step = 0.001e8;                          	// km step size for heliocentric orbital radii
	const double step_count = (r_orb_ast_outer - r_orb_mercury) / scan_step;
	
	const double m_asteroid_step = 1;						// kg 	asteroid mass step size
	const double m_asteroid_start = 10;						// kg 	asteroid mass size minimum
	double inert_fraction8 = 0.20;								// how much inert mass to support spacecraft fuel at that stage
	double inert_fraction9 = 0.1;
	double inert_fraction95 = 0.05;

	// Initializing mask for Earth's hill sphere (won't search in that range)
	const double soi_lower = r_orb_earth - soi_earth*1.5;
	const double soi_higher = r_orb_earth + soi_earth*1.5;

	// Building the scanning range (asteroid orbital radii)
	vector<double> x_scanning_radii;
	vector<double> h_time;
	x_scanning_radii.push_back(r_orb_mercury);
	h_time.push_back(time_ellipse(u_sun, (x_scanning_radii[0] + r_orb_earth)/2));
	for (int i = 0; i < step_count; i++){
		x_scanning_radii.push_back(x_scanning_radii[i] + scan_step);
		h_time.push_back(time_ellipse(u_sun, (x_scanning_radii[i] + scan_step + r_orb_earth)/2));
	}

	// Scanning each radii for maximum asteroid size
	double sc_seek = 100;
	double m_asteroid_iter = m_asteroid_start;

	vector<double> y_asteroids8;
	vector<double> y_asteroids9;
	vector<double> y_asteroids95;
	
	
	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids8.push_back(0);
			h_time[i] = 0;
		}
		else {
			// Use minimum asteroid mass.
			astVec = asteroidReturnHohman(m_asteroid_start, x_scanning_radii[i], inert_fraction8, 0);
			
			if (astVec[0] < sls_payload_LEO) {
				while ( sc_seek < sls_payload_LEO) {
					astVec = asteroidReturnHohman( m_asteroid_iter, x_scanning_radii[i], inert_fraction8, 0);
					sc_seek = astVec[0];

					m_asteroid_iter = m_asteroid_iter + m_asteroid_step;
					
				}
				
				y_asteroids8.push_back(m_asteroid_iter);
				sc_seek = 100;
				m_asteroid_iter = m_asteroid_start;

			}
			else {
				y_asteroids8.push_back(0);
			}
		}
	}



	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids9.push_back(0);
			h_time[i] = 0;
		}
		else {
			// Use minimum asteroid mass.
			astVec = asteroidReturnHohman(m_asteroid_start, x_scanning_radii[i], inert_fraction9, 0);
			
			if (astVec[0] < sls_payload_LEO) {
				while ( sc_seek < sls_payload_LEO) {
					astVec = asteroidReturnHohman( m_asteroid_iter, x_scanning_radii[i], inert_fraction9, 0);
					sc_seek = astVec[0];

					m_asteroid_iter = m_asteroid_iter + m_asteroid_step;
					
				}
				
				y_asteroids9.push_back(m_asteroid_iter);
				sc_seek = 100;
				m_asteroid_iter = m_asteroid_start;

			}
			else {
				y_asteroids9.push_back(0);
			}
		}
	}




	for (int i = 0; i < x_scanning_radii.size(); i++){
		// Ignoring SOI masked region
		if (x_scanning_radii[i] > soi_lower && x_scanning_radii[i] < soi_higher) {
			y_asteroids95.push_back(0);
			h_time[i] = 0;
		}
		else {
			// Use minimum asteroid mass.
			astVec = asteroidReturnHohman(m_asteroid_start, x_scanning_radii[i], inert_fraction95, 0);
			
			if (astVec[0] < sls_payload_LEO) {
				while ( sc_seek < sls_payload_LEO) {
					astVec = asteroidReturnHohman( m_asteroid_iter, x_scanning_radii[i], inert_fraction95, 0);
					sc_seek = astVec[0];

					m_asteroid_iter = m_asteroid_iter + m_asteroid_step;
					
				}
				
				y_asteroids95.push_back(m_asteroid_iter);
				sc_seek = 100;
				m_asteroid_iter = m_asteroid_start;

			}
			else {
				y_asteroids95.push_back(0);
			}
		}
	}



	
	// Converting radii to AU before graphing
	for (int i = 0; i < x_scanning_radii.size(); i++){
		x_scanning_radii[i] = x_scanning_radii[i] / r_orb_earth; 
	}

	// Optional clipping of asteroid mass for graphing
	double clip = 5000;
	for (int i = 0; i < x_scanning_radii.size(); i++){
		if(y_asteroids8[i] > clip){
			y_asteroids8[i] = clip;
		}
		if(y_asteroids9[i] > clip){
			y_asteroids9[i] = clip;
		}
		if(y_asteroids95[i] > clip){
			y_asteroids95[i] = clip;
		}
	}

	
//	// normalizing x values
//	for (int i = 0; i <= x_scanning_radii.size(); i++){
//		x_scanning_radii[i] = x_scanning_radii[i]/r_orb_earth;
//	}
	cout << "hohman calls : " << flop_iter << endl;
	cout << x_scanning_radii.size() << " " << y_asteroids8.size() << " " << h_time.size() << endl;
	graphHohman(x_scanning_radii, y_asteroids8);
	graphHohman3(x_scanning_radii, y_asteroids8, y_asteroids9, y_asteroids95);
	graphTimeH(x_scanning_radii, h_time);
//	printVec(x_scanning_radii);

}







vector<double> asteroidReturnHohman(double m_asteroid, double r_orb_asteroid, double inert_fraction, int verbosity){

	vector<double> returning;
	flop_iter = flop_iter + 1;

	if (r_orb_asteroid > r_orb_earth){
		if (verbosity == 1) {cout << "===========================================================" << endl;} 
		double v_final = v_circ(u_earth, 10000);			// km/s		sc parking orbit velocity

		double v_earth = v_circ(u_sun, r_orb_earth);		// km/s 	earth orbital velocity

		double aaa = (r_orb_asteroid + r_orb_earth)/2;
		double v_p_f = v_ellipse(u_sun, aaa, r_orb_earth);						// km/s  perigee arrival velocity
		if (verbosity == 1) {cout << "velocity of arrival ellipse perigee        : " << v_p_f << " km/s" << endl;}

		double v_inf_f = abs(v_p_f - v_earth);
		if (verbosity == 1) {cout << "Arriving excess speed                      : " << v_inf_f << " km/s" << endl;}

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
		if (verbosity == 1) {cout << "Apogee velocity of arriving ellipse        : " << v_a_2 << " km/s" << endl;}

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


		returning.push_back(fuel_1 + mass_1 + inert_1);										// preburn spacecraft mass
		returning.push_back(fuel_1 + fuel_2 + fuel_3 + fuel_final);							// fuel mass
		returning.push_back(inert_1 + inert_2 + inert_3 + inert_final + final_sc_drymass);	// inert mass
		returning.push_back(m_asteroid);													// asteroid mass
	}
	else {
		if (verbosity == 1) {cout << "===========================================================" << endl;} 
		double v_final = v_circ(u_earth, 10000);			// km/s		sc parking orbit velocity

		double v_earth = v_circ(u_sun, r_orb_earth);		// km/s 	earth orbital velocity

		double aaa = (r_orb_asteroid + r_orb_earth)/2;
		double v_a_f = v_ellipse(u_sun, aaa, r_orb_earth);						// km/s  perigee arrival velocity
		if (verbosity == 1) {cout << "velocity of arrival ellipse apogee         : " << v_a_f << " km/s" << endl;}

		double v_inf_f = abs(v_a_f - v_earth);
		if (verbosity == 1) {cout << "arriving excess speed                      : " << v_inf_f << " km/s" << endl;}

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

		double v_p_3 = v_ellipse(u_sun, aaa, r_orb_asteroid);			// km/s  apogee departure velocity
		if (verbosity == 1) {cout << "velocity of departure ellipse at perigee   : " << v_p_3 << " km/s" << endl;}

		double d_v_3 = abs(v_asteroid - v_p_3);							// km/s  dV 3rd burn
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
		double v_p_2 = v_p_3;													// km/s  apogee departure velocity
		if (verbosity == 1) {cout << "Perigee velocity of arriving ellipse       : " << v_p_2 << " km/s" << endl;}

		double d_v_2 = abs(v_asteroid - v_p_2);									// km/s  dV 3rd burn
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


		returning.push_back(fuel_1 + mass_1 + inert_1);										// preburn spacecraft mass
		returning.push_back(fuel_1 + fuel_2 + fuel_3 + fuel_final);							// fuel mass
		returning.push_back(inert_1 + inert_2 + inert_3 + inert_final + final_sc_drymass);	// inert mass
		returning.push_back(m_asteroid);	
	}


	return returning;
}





int graphHohman(vector<double> radii, vector<double> asteroid_masses){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();

	series->xs = &radii;
	series->ys = &asteroid_masses;
	series->color = CreateRGBColor(0, .5, 0);


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->yMin = 0;
	settings->yMax = 2500;
	settings->title = toVector(L"Asteroid mass returned to Earth orbit vs asteroid orbital radii");
	settings->xLabel = toVector(L"Asteroid mass (kg)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "hohmann.png");
	DeleteImage(imageReference->image);
	
	return 0;
}

int graphHohman3(vector<double> radii, vector<double> asteroid_masses8,vector<double> asteroid_masses9,vector<double> asteroid_masses95){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series8 = GetDefaultScatterPlotSeriesSettings();
	series8->xs = &radii;
	series8->ys = &asteroid_masses8;
	series8->color = CreateRGBColor(0, .5, 0);

	ScatterPlotSeries *series9 = GetDefaultScatterPlotSeriesSettings();
	series9->xs = &radii;
	series9->ys = &asteroid_masses9;
	series9->color = CreateRGBColor(0, 0, 1);

	ScatterPlotSeries *series95 = GetDefaultScatterPlotSeriesSettings();
	series95->xs = &radii;
	series95->ys = &asteroid_masses95;
	series95->color = CreateRGBColor(1, 0, 0);


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->yMin = 0;
	settings->yMax = 2500;
	settings->title = toVector(L"Asteroid mass returned to Earth orbit vs asteroid orbital radii");
	settings->xLabel = toVector(L"Asteroid mass (kg)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series8);
	settings->scatterPlotSeries->push_back(series9);
	settings->scatterPlotSeries->push_back(series95);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "hohmann3.png");
	DeleteImage(imageReference->image);
	
	return 0;
}




int graphElectric(vector<double> radii, vector<double> asteroid_masses_4, vector<double> asteroid_masses_5, vector<double> asteroid_masses_6){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series4 = GetDefaultScatterPlotSeriesSettings();
	series4->xs = &radii;
	series4->ys = &asteroid_masses_4;
	series4->color = CreateRGBColor(0, .5, 0);

	ScatterPlotSeries *series5 = GetDefaultScatterPlotSeriesSettings();
	series5->xs = &radii;
	series5->ys = &asteroid_masses_5;
	series5->color = CreateRGBColor(0, 0 , 1);

	ScatterPlotSeries *series6 = GetDefaultScatterPlotSeriesSettings();
	series6->xs = &radii;
	series6->ys = &asteroid_masses_6;
	series6->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->yMin = 0;
	settings->yMax = 2500;
	settings->title = toVector(L"Asteroid mass returned to Earth orbit vs asteroid orbital radii");
	settings->xLabel = toVector(L"Asteroid mass (kg)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series4);
	settings->scatterPlotSeries->push_back(series5);
	settings->scatterPlotSeries->push_back(series6);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "Electric.png");
	DeleteImage(imageReference->image);
	
	return 0;
}

int graphElectric1(vector<double> radii, vector<double> asteroid_masses_4){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series4 = GetDefaultScatterPlotSeriesSettings();
	series4->xs = &radii;
	series4->ys = &asteroid_masses_4;
	series4->color = CreateRGBColor(0, .5, 0);


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->yMin = 0;
	settings->yMax = 2500;
	settings->title = toVector(L"Asteroid mass returned to Earth orbit vs asteroid orbital radii");
	settings->xLabel = toVector(L"Asteroid mass (kg)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series4);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "Electric1.png");
	DeleteImage(imageReference->image);
	
	return 0;
}







int graphTimeH(vector<double> radii, vector<double> h_time){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();

	series->xs = &radii;
	series->ys = &h_time;


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->title = toVector(L"Mission time for asteroid retrieval vs asteroid orbital radii");
	settings->xLabel = toVector(L"Total Mission Time (months)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "h_time.png");
	DeleteImage(imageReference->image);
	
	return 0;
}

int graphTimeE(vector<double> radii, vector<double> h_time){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();

	series->xs = &radii;
	series->ys = &h_time;


	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->title = toVector(L"Mission time for asteroid retrieval vs asteroid orbital radii");
	settings->xLabel = toVector(L"Total Mission Time (months)");
	settings->yLabel = toVector(L"Asteroid orbital radius (AU)");
	settings->scatterPlotSeries->push_back(series);

	DrawScatterPlotFromSettings(imageReference, settings);
	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "h_time.png");
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
	settings->width = 1800;
	settings->height = 1200;
	settings->title = toVector(L"Satellite dV required for departure vs orbital radii");
	settings->xLabel = toVector(L"dV required (km/s)");
	settings->yLabel = toVector(L"Orbital Radius (AU)");
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




