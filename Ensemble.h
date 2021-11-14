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

public:

	Ensemble(double sigma = 0, double d = 0, std::vector<Neuron> v = std::vector<Neuron>(), std::vector<std::pair< size_t, size_t >> connect = std::vector<std::pair< size_t, size_t >>());

	void doTic(double dt);

	void addConnection(std::pair<size_t, size_t>);
	void addConnection(size_t number_in, size_t number_out);


	double connectionFunction(siae_t pos_in, size_t pos_out);


};