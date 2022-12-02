#include <iostream>
#include "constants.h"
#include "orbmech.h"
#include "orbmeche.h"

using namespace std;

	//scVec_i.push_back(sc_mass_i);
	//scVec_i.push_back(r_i);
	//scVec_i.push_back(dmdt);
	//scVec_i.push_back(time_step);

vector <double> electricMission(double asteroidMass, double helioRadius, vector <double> scVec_i, vector <double> &scVec_f){
	
	
	//cout << "---------------- Leaving Earth ----------------" << endl;

	while (scVec_i[1] < earth_soi) {
		scVec_f = electric(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	double a_i = earth_soi + r_orb_earth;


	//cout << "---------------- Earth SOI (flipping) ----------------" << endl;

	scVec_i[1] = a_i;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Earth Orbit (flipped) ----------------" << endl;

	while (scVec_i[1] < helioRadius) {
		scVec_f = electricSun(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Mars Orbit (Grabbing asteroid)----------------" << endl;

	scVec_i[0] = scVec_i[0]+asteroidMass;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Mars Orbit (Grabbed asteroid)----------------" << endl;

	while (scVec_i[1] > a_i) {
		scVec_f = electricSunD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Earth Orbit (flipping) ----------------" << endl;


	scVec_i[1] = earth_soi;
	//printVec(scVec_i);

	scVec_f = scVec_i;


	//cout << "---------------- Earth SOI (flipped) ----------------" << endl;

	while (scVec_i[1] > 10000) {
		scVec_f = electricD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Earth Parked ----------------" << endl;

	scVec_f[0] = scVec_f[0] - asteroidMass;

	return scVec_f;
}


vector <double> electricMissionD(double asteroidMass, double helioRadius, vector <double> scVec_i, vector <double> scVec_f){
	
	
	//cout << "---------------- Leaving Earth ----------------" << endl;

	while (scVec_i[1] < earth_soi) {
		scVec_f = electric(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	double a_i = r_orb_earth - earth_soi;


	//cout << "---------------- Earth SOI (flipping) ----------------" << endl;

	scVec_i[1] = a_i;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Earth Orbit (flipped) ----------------" << endl;

	while (scVec_i[1] > helioRadius) {
		scVec_f = electricSunD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Mars Orbit (Grabbing asteroid)----------------" << endl;

	scVec_i[0] = scVec_i[0]+asteroidMass;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Mars Orbit (Grabbed asteroid)----------------" << endl;

	while (scVec_i[1] < a_i) {
		scVec_f = electricSun(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Earth Orbit (flipping) ----------------" << endl;


	scVec_i[1] = earth_soi;
	//printVec(scVec_i);

	scVec_f = scVec_i;


	//cout << "---------------- Earth SOI (flipped) ----------------" << endl;

	while (scVec_i[1] > 10000) {
		scVec_f = electricD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Earth Parked ----------------" << endl;

	scVec_f[0] = scVec_f[0] - asteroidMass;

	return scVec_f;

}


vector <double> electricMissionH(double asteroidMass, double helioRadius, vector <double> scVec_i, vector <double> &scVec_f){
	
	
	double a_i = earth_soi + r_orb_earth;


	while (scVec_i[1] < helioRadius) {
		scVec_f = electricSun(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Mars Orbit (Grabbing asteroid)----------------" << endl;

	scVec_i[0] = scVec_i[0]+asteroidMass;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Mars Orbit (Grabbed asteroid)----------------" << endl;

	while (scVec_i[1] > a_i) {
		scVec_f = electricSunD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Earth Orbit (flipping) ----------------" << endl;


	scVec_i[1] = earth_soi;
	//printVec(scVec_i);

	scVec_f = scVec_i;


	//cout << "---------------- Earth SOI (flipped) ----------------" << endl;

	while (scVec_i[1] > 10000) {
		scVec_f = electricD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Earth Parked ----------------" << endl;

	scVec_f[0] = scVec_f[0] - asteroidMass;

	return scVec_f;
}




vector <double> electricMissionHD(double asteroidMass, double helioRadius, vector <double> scVec_i, vector <double> scVec_f){
	
	double a_i = r_orb_earth - earth_soi;

	while (scVec_i[1] > helioRadius) {
		scVec_f = electricSunD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Mars Orbit (Grabbing asteroid)----------------" << endl;

	scVec_i[0] = scVec_i[0]+asteroidMass;
	//printVec(scVec_i);

	scVec_f = scVec_i;

	//cout << "---------------- Helio Mars Orbit (Grabbed asteroid)----------------" << endl;

	while (scVec_i[1] < a_i) {
		scVec_f = electricSun(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Helio Earth Orbit (flipping) ----------------" << endl;


	scVec_i[1] = earth_soi;
	//printVec(scVec_i);

	scVec_f = scVec_i;


	//cout << "---------------- Earth SOI (flipped) ----------------" << endl;

	while (scVec_i[1] > 10000) {
		scVec_f = electricD(scVec_i, scVec_f);
		scVec_i = scVec_f; 
	}
	//printVec(scVec_f);

	//cout << "---------------- Earth Parked ----------------" << endl;

	scVec_f[0] = scVec_f[0] - asteroidMass;

	return scVec_f;

}




vector <double> electricRadiusScan(double radiusss, double prop_frac) {
	double asteroidMax;

	
	
	
	const double time_step = 300;							// seconds

	const double sc_mass_i = sls_payload_LEO;   			// kg
	const double sc_ratio = sls_payload_LEO / DAWN_wet;
	//const double dmdt = 5.7415e-6 * sc_ratio;				// kg/s
	const double dmdt_NEXT = 2*.71*6900/pow(g_0*isp_NEXTC,2);	// kg/s  efficiencty is ~71% for NEXT-C
	const double thrust_NEXT = g_0*isp_NEXTC*dmdt_NEXT;     // N
	//cout << "dmdt of NEXT = " << dmdt_NEXT << endl;
	//cout << "Thrust of NEXT = " << thrust_NEXT << endl;
	const double dmdt = dmdt_NEXT*sc_ratio;		// kg/s


	const double inert_frac = prop_frac-1;

	const double max_mission_time = (sc_mass_i * prop_frac)/dmdt;
	const double max_fuel_mass = sc_mass_i*prop_frac;

	


	
	double ttime = 0;

	vector<double> scVec_i;
	scVec_i.push_back(sc_mass_i);
	scVec_i.push_back(10000);
	scVec_i.push_back(dmdt);
	scVec_i.push_back(time_step);
	scVec_i.push_back(ttime);
	//printVec(scVec_i);
	vector<double> scVec_f = scVec_i;

	const double asteroidMassBB = 10000;
	const double asteroidMassB = 1000;
	const double asteroidMassM = 100;
	const double asteroidMassS = 10; 
	const double helioRadius = radiusss;

	double asteroidMassSeek = 0;

	scVec_f = electricMission(asteroidMassSeek, helioRadius, scVec_i, scVec_f);
	vector <double> outVec;

	if (scVec_f[0] > (1-prop_frac)*sc_mass_i){
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassBB;	
			scVec_f = electricMission(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassBB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassB;	
			scVec_f = electricMission(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassM;
			scVec_f = electricMission(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassM;
		scVec_f = scVec_i;
		

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassS;
			scVec_f = electricMission(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassS;
		double missionTime = scVec_f[4];

		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(missionTime);
		cout << "Mission Time :" << missionTime / 60 / 60 / 24 / 30.4 << endl;

	}
	else {
		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(0);
		cout << "Mission Time : " << 0 << endl;
	}


	return outVec;

}


vector <double> electricRadiusScanH(double radiusss, double prop_frac) {
	double asteroidMax;

	
	
	
	const double time_step = 300;							// seconds

	const double sc_mass_i = sls_payload_helio;   			// kg
	const double sc_ratio = sls_payload_helio / DAWN_wet;
	//const double dmdt = 5.7415e-6 * sc_ratio;				// kg/s
	const double dmdt_NEXT = 2*.71*6900/pow(g_0*isp_NEXTC,2);	// kg/s  efficiencty is ~71% for NEXT-C
	const double thrust_NEXT = g_0*isp_NEXTC*dmdt_NEXT;     // N
	//cout << "dmdt of NEXT = " << dmdt_NEXT << endl;
	//cout << "Thrust of NEXT = " << thrust_NEXT << endl;
	const double dmdt = dmdt_NEXT*sc_ratio;		// kg/s


	const double inert_frac = prop_frac-1;

	const double max_mission_time = (sc_mass_i * prop_frac)/dmdt;
	const double max_fuel_mass = sc_mass_i*prop_frac;

	
	double a_i = r_orb_earth + earth_soi;

	
	double ttime = 0;

	vector<double> scVec_i;
	scVec_i.push_back(sc_mass_i);
	scVec_i.push_back(a_i);
	scVec_i.push_back(dmdt);
	scVec_i.push_back(time_step);
	scVec_i.push_back(ttime);
	//printVec(scVec_i);
	vector<double> scVec_f = scVec_i;

	const double asteroidMassBB = 10000;
	const double asteroidMassB = 1000;
	const double asteroidMassM = 100;
	const double asteroidMassS = 10; 
	const double helioRadius = radiusss;

	double asteroidMassSeek = 0;

	scVec_f = electricMissionH(asteroidMassSeek, helioRadius, scVec_i, scVec_f);
	vector <double> outVec;

	if (scVec_f[0] > (1-prop_frac)*sc_mass_i){
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassBB;	
			scVec_f = electricMissionH(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassBB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassB;	
			scVec_f = electricMissionH(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassM;
			scVec_f = electricMissionH(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassM;
		scVec_f = scVec_i;
		

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassS;
			scVec_f = electricMissionH(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassS;
		double missionTime = scVec_f[4];

		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(missionTime);
		cout << "Mission Time :" << missionTime / 60 / 60 / 24 / 30.4 << endl;

	}
	else {
		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(0);
		cout << "Mission Time : " << 0 << endl;
	}


	return outVec;

}






vector <double> electricRadiusScanD(double radiusss, double prop_frac) {
	double asteroidMax;

	
	
	
	const double time_step = 300;							// seconds

	const double sc_mass_i = sls_payload_LEO;   			// kg
	const double sc_ratio = sls_payload_LEO / DAWN_wet;
	//const double dmdt = 5.7415e-6 * sc_ratio;				// kg/s
	const double dmdt_NEXT = 2*.71*6900/pow(g_0*isp_NEXTC,2);	// kg/s  efficiencty is ~71% for NEXT-C
	const double thrust_NEXT = g_0*isp_NEXTC*dmdt_NEXT;     // N
	//cout << "dmdt of NEXT = " << dmdt_NEXT << endl;
	//cout << "Thrust of NEXT = " << thrust_NEXT << endl;
	const double dmdt = dmdt_NEXT*sc_ratio;		// kg/s


	const double inert_frac = prop_frac-1;

	const double max_mission_time = (sc_mass_i * prop_frac)/dmdt;
	const double max_fuel_mass = sc_mass_i*prop_frac;

	


	
	double ttime = 0;

	vector<double> scVec_i;
	scVec_i.push_back(sc_mass_i);
	scVec_i.push_back(10000);
	scVec_i.push_back(dmdt);
	scVec_i.push_back(time_step);
	scVec_i.push_back(ttime);
	//printVec(scVec_i);
	vector<double> scVec_f = scVec_i;


	const double asteroidMassBB = 10000;
	const double asteroidMassB = 1000;
	const double asteroidMassM = 100;
	const double asteroidMassS = 10; 
	const double helioRadius = radiusss;

	double asteroidMassSeek = 0;

	scVec_f = electricMissionD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);
	vector <double> outVec;


	if (scVec_f[0] > (1-prop_frac)*sc_mass_i){
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassBB;	
			scVec_f = electricMissionD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassBB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassB;	
			scVec_f = electricMissionD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassM;
			scVec_f = electricMissionD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassM;
		scVec_f = scVec_i;
		

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassS;
			scVec_f = electricMissionD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassS;
		double missionTime = scVec_f[4];

		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(missionTime);
		cout << "Mission Time :" << missionTime / 60 / 60 / 24 / 30.4 << endl;

	}
	else {
		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(0);
		cout << "Mission Time : " << 0 << endl;
	}


	return outVec;

}


vector <double> electricRadiusScanHD(double radiusss, double prop_frac) {
	double asteroidMax;

	
	
	
	const double time_step = 300;							// seconds

	const double sc_mass_i = sls_payload_helio;   			// kg
	const double sc_ratio = sls_payload_helio / DAWN_wet;
	//const double dmdt = 5.7415e-6 * sc_ratio;				// kg/s
	const double dmdt_NEXT = 2*.71*6900/pow(g_0*isp_NEXTC,2);	// kg/s  efficiencty is ~71% for NEXT-C
	const double thrust_NEXT = g_0*isp_NEXTC*dmdt_NEXT;     // N
	//cout << "dmdt of NEXT = " << dmdt_NEXT << endl;
	//cout << "Thrust of NEXT = " << thrust_NEXT << endl;
	const double dmdt = dmdt_NEXT*sc_ratio;		// kg/s


	const double inert_frac = prop_frac-1;

	const double max_mission_time = (sc_mass_i * prop_frac)/dmdt;
	const double max_fuel_mass = sc_mass_i*prop_frac;

	
	double a_i = r_orb_earth - earth_soi;

	
	double ttime = 0;

	vector<double> scVec_i;
	scVec_i.push_back(sc_mass_i);
	scVec_i.push_back(a_i);
	scVec_i.push_back(dmdt);
	scVec_i.push_back(time_step);
	scVec_i.push_back(ttime);
	//printVec(scVec_i);
	vector<double> scVec_f = scVec_i;


	const double asteroidMassBB = 10000;
	const double asteroidMassB = 1000;
	const double asteroidMassM = 100;
	const double asteroidMassS = 10; 
	const double helioRadius = radiusss;

	double asteroidMassSeek = 0;

	scVec_f = electricMissionHD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);
	vector <double> outVec;


	if (scVec_f[0] > (1-prop_frac)*sc_mass_i){
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassBB;	
			scVec_f = electricMissionHD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassBB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassB;	
			scVec_f = electricMissionHD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);
		}
		
		asteroidMassSeek = asteroidMassSeek - asteroidMassB;
		scVec_f = scVec_i;

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassM;
			scVec_f = electricMissionHD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassM;
		scVec_f = scVec_i;
		

		while (scVec_f[0] > (1-prop_frac)*sc_mass_i){
			asteroidMassSeek = asteroidMassSeek + asteroidMassS;
			scVec_f = electricMissionHD(asteroidMassSeek, helioRadius, scVec_i, scVec_f);

			//printVec(scVec_f);

		}

		asteroidMassSeek = asteroidMassSeek - asteroidMassS;
		double missionTime = scVec_f[4];

		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(missionTime);
		cout << "Mission Time :" << missionTime / 60 / 60 / 24 / 30.4 << endl;

	}
	else {
		outVec.push_back(asteroidMassSeek);
		cout << "Asteroid Mass :" << asteroidMassSeek << endl;
		outVec.push_back(0);
		cout << "Mission Time : " << 0 << endl;
	}


	return outVec;

}