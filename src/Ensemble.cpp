#include "Ensemble.h"

#include <cmath>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES

Ensemble::Ensemble(std::vector<Neuron> v = std::vector<Neuron>(), std::vector<std::pair< size_t, size_t >> connect = std::vector<std::pair< size_t, size_t >>())
{
	neurons = v;
	connection = connect;
	sort(connection.begin(), connection.end());
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
	// while(phase > 2 * M_PI)
	// 	phase -= 2 * M_PI;
	// // double out_neuron_w = neurons[connection[connection_number].second].getParam();
	// // if((asin(out_neuron_w - sigma) < phase) && (asin(out_neuron_w + sigma) > phase))
	// if (((M_PI / 2 - sigma) <= phase) && ((M_PI / 2 + sigma) >= phase))
	// {
	// 	// std::cout << "Ab" << std::endl;
	// 	return 0.0;
	// }
	// else
	// {
	// 	// std::cout << "Ba" << std::endl;
	// 	return 1.0;
	// }

	return res;
}

auto Ensemble::compute_ensemble(double _d, double _sigma, double _k, double max_time = 100, double dt = 0.01)
{
	sigma = _sigma;
	d = _d;
	k = _k;

	std::vector<double> time;
	std::vector<std::vector<double>> neurons_phases(neurons.size());

	for (size_t i = 0; i < neurons.size(); i++)
		neurons[i].reset();

	for (double t = 0; t < max_time; t += dt)
	{
		doTic(dt);
		time.push_back(t);
		for (size_t i = 0; i < neurons.size(); i++)
		{
			neurons_phases[i].push_back(neurons[i].getNewPhase());
		}
	}

	return make_tuple(time, neurons_phases);
}
