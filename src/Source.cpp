#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846

#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Ensemble.cpp"
#include "Neuron.cpp"

using namespace std;

auto compute_ensemble(double d, double sigma)
{
	Neuron n1(2, 1.01);
	Neuron n2(0, 1.09);
	Ensemble ens1(d, sigma);

	ens1.addConnection(n1);
	ens1.addConnection(n2);


	const double dt = 0.01;


	// std::ofstream outf("Ensemble.txt");

	//outf.setf(std::ofstream::fixed);
	//outf.precision(4);

	vector<double> time_points, n1_phase_points, n2_phase_points;

	for (double time = 0; time < 1000; time += dt)
	{
		ens1.doTic(dt);
		time_points.push_back(time);
		n1_phase_points.push_back(ens1.connection[0].getNewPhase());
		n2_phase_points.push_back(ens1.connection[1].getNewPhase());
		// outf << time << " " << ens1.connection[0].getNewPhase() << " " << ens1.der(0) << " " << ens1.connection[1].getNewPhase() << " " << ens1.der(1) << std::endl;
	}

	return make_tuple(time_points, n1_phase_points, n2_phase_points);
}

PYBIND11_MODULE(ensemble, m)
{
    m.def("compute_ensemble", &compute_ensemble);
}