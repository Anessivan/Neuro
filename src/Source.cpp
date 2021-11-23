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

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(ensemble, m)
{
	py::class_<Neuron>(m, "Neuron")
		.def(py::init<double, double>());
	py::class_<Ensemble>(m, "Ensemble")
		.def(py::init<vector<Neuron>, vector<pair<size_t, size_t>>>())
		.def("compute", &Ensemble::compute_ensemble);
}
