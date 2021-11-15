#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Ensemble.cpp"
#include "Neuron.cpp"

using namespace std;

auto compute_ensemble(double d, double sigma, double p1, double p2, double p3)
{
	Neuron n1(p1, 1.01);
	Neuron n2(p2, 1.05);
	Neuron n3(p3, 1.09);

	vector<Neuron> neurons = {n1, n2, n3};

	// std::vector<std::pair< size_t, size_t >> connections = {{0, 1}, {1, 0}};

	std::vector<std::pair< size_t, size_t >> connections = {{0, 1}, {1, 2}, {2, 0}};

	Ensemble ens1(sigma, d, neurons, connections);

	const double dt = 0.01;

	vector<double> time_points, n1_phase_points, n2_phase_points, n3_phase_points;

	for (double time = 0; time < 200; time += dt)
	{
		ens1.doTic(dt);
		time_points.push_back(time);
		n1_phase_points.push_back(ens1.neurons[0].getNewPhase());
		n2_phase_points.push_back(ens1.neurons[1].getNewPhase());
		n3_phase_points.push_back(ens1.neurons[2].getNewPhase());
	}

	return make_tuple(time_points, n1_phase_points, n2_phase_points, n3_phase_points);
}

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(ensemble, m)
{
    m.def("compute_ensemble", &compute_ensemble);
}