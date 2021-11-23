#define _USE_MATH_DEFINES
#include <cmath>
#include "Neuron.h"
#include <vector>


class Ensemble
{
public:

	std::vector<Neuron> neurons;

	std::vector<std::pair< size_t, size_t> > connection;

	double sigma;

	double d;

	Ensemble(std::vector<Neuron> v, std::vector<std::pair< size_t, size_t >> connect);

	std::vector<double> doTic(double dt);

	void addConnection(std::pair<size_t, size_t>);
	void addConnection(size_t number_in, size_t number_out);

	double connectionFunction(size_t connection_n);

	auto compute_ensemble(double _d, double _sigma, double max_time, double dt);
};
