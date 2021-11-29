#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Neuron.h"
#include <vector>


class Ensemble
{
private:

	std::vector<Neuron> neurons;

	std::vector<std::pair< size_t, size_t> > connection;

	double sigma;

	double d;

	double k;

public:

	Ensemble(double sigma = 0, double d = 0, std::vector<Neuron> v = std::vector<Neuron>(), std::vector<std::pair< size_t, size_t >> connect = std::vector<std::pair< size_t, size_t >>(), double _k = -500.0);

	std::vector<double> doTic(double dt);

	void addConnection(std::pair<size_t, size_t>);
	void addConnection(size_t number_in, size_t number_out);


	double connectionFunction(size_t connection_number);


};