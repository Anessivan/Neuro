#define _USE_MATH_DEFINES
#include <cmath>
#include "Ensemble.h"
#include <iostream>
#include <algorithm>


Ensemble::Ensemble(double _sigma = 0.0, double _d = 0.0, std::vector<Neuron> v = std::vector<Neuron>(), std::vector<std::pair< size_t, size_t >> connect = std::vector<std::pair< size_t, size_t >>(), double _k = -500.0)
{
	neurons = v;
	connection = connect;
	sort(connection.begin(), connection.end());
	sigma = _sigma;
	d = _d;
	k = _k;
}

std::vector<double> Ensemble::doTic(double dt)
{
	std::vector<double> res;

	for(int i = 0; i < neurons.size(); i++)
	{
		neurons[i].doTic(dt);
		for (int j = 0; j < connection.size(); j++)
			if(connection[j].first == i)
			{
				double phase = neurons[i].getNewPhase();
				phase -= d * connectionFunction(j) * dt;
				neurons[i].setNewPhase(phase);
			}
		res.push_back(neurons[i].getNewPhase());
	}
	return res;
}

void Ensemble::addConnection(std::pair<size_t, size_t> add)
{
	connection.push_back(add);
	sort(connection.begin(), connection.end());
}

void  Ensemble::addConnection(size_t number_in, size_t number_out)
{
	std::pair<size_t, size_t> added(number_in, number_out);
	addConnection(added);
}



double Ensemble::connectionFunction(size_t connection_number)
{
	double phase = neurons[connection[connection_number].second].getNewPhase();

	double res = 1.0 / (1.0 + k * exp(cos(sigma) - sin(phase)));

	return res;
}
