#define _USE_MATH_DEFINES
#include <cmath>
#include "Neuron.h"
#include <vector>
#include <tuple>

struct Connection
{
	std::pair<unsigned int, unsigned int> neurons_indexes;
	double d;
};

bool compareConnectionsByIndexes(const Connection &a, const Connection &b)
{
	return a.neurons_indexes.first < b.neurons_indexes.first;
}

class Ensemble
{
public:

	std::vector<Neuron> neurons;

	std::vector<Connection> connections;

	double sigma;
	double d;
	double k;

	Ensemble(
		std::vector<Neuron> = std::vector<Neuron>(), 
		std::vector<Connection> = std::vector<Connection>()
	);

	void doTic(double dt);

	double couplingFunction(double);

	auto computeEnsemble(double _sigma, double _k, double max_time, double dt);
};
