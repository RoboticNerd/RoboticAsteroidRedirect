// CMakeAst.cpp : Defines the entry point for the application.
//
#include "./lib/pbPlots.cpp"
#include "./lib/supportLib.cpp"

#include <iostream>
#include "constants.h"
#include "orbmech.h"
#include <math.h> 			/*cos()*/

#include <vector>
#include "functions.h"
#include "examplescript.cpp"

using namespace std;

int graphtest();

int debugi = 0;


int main()
{
	cout << "Successful open." << endl;
	run1();
	cout << "radius moon = " << r_moon << "km" << endl;
	

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


	double v_inf;
	double v_esc;
	double d_v1;



	for (int i = 0; i <= radiuses.size(); i++) {
		cout << "Radius = " << radiuses[i] << " km" << endl;
		v_inf = hyperbolicExcessSpeed(u_sun, r_orb_earth, 778600000);
		cout << v_inf << endl;
		v_esc = escapeSpeed(u_earth, v_inf, radiuses[i]);
		cout << v_esc << endl;
//		d_vs[i] = v_esc - circularOrbitSpeed(u_earth, radiuses[i]);
		d_vs[i] = v_esc - v_ellipse(u_earth, a_GTO, radiuses[i]);
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


	return 0;
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




