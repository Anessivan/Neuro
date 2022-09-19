#include "Ensemble.h"

#include <cmath>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES

Ensemble::Ensemble(std::vector<Neuron> _neurons = std::vector<Neuron>(), std::vector<Connection> _connections = std::vector<Connection>())
{
	neurons = _neurons;
	connections = _connections;

	sort(connections.begin(), connections.end(), compareConnectionsByIndexes);
}

void Ensemble::doTic(double dt)
{
	int inputs = 0;
	double coupling_result, neuronPhase, connectedNeuronPhase, neuron_input, phase;
	std::vector<double> coupling_values(neurons.size(), -1);

	auto it = connections.begin();
	size_t connected_index;
	int output_index = (*it).neurons_indexes.first;

	for (size_t neuron_index = 0; neuron_index < neurons.size(); neuron_index++)
	{
		while ((neuron_index == output_index) && (it != connections.end()))
		{
			connected_index = (*it).neurons_indexes.second;

			if (coupling_values[connected_index] == -1)
			{
				connectedNeuronPhase = neurons[connected_index].getNewPhase();
				coupling_result = couplingFunction(connectedNeuronPhase);
				coupling_values[connected_index] = coupling_result;
			}
			else
			{
				coupling_result = coupling_values[connected_index];
			}
			
			neuron_input += coupling_result * (*it).d * dt;
			++inputs;

			++it;
			output_index = (*it).neurons_indexes.first;
		}
		
		if (coupling_values[neuron_index] == -1)
		{
			neuronPhase = neurons[neuron_index].getNewPhase();
			coupling_result = couplingFunction(neuronPhase);
			coupling_values[neuron_index] = coupling_result;
		}

		neurons[neuron_index].doTic(dt);

		if (inputs > 0)
		{
			neuron_input = neuron_input / inputs;
			phase = neurons[neuron_index].getNewPhase() + neuron_input;
			neurons[neuron_index].setNewPhase(phase);
		}

		neuron_input = 0;
		inputs = 0;
	}
}


double Ensemble::couplingFunction(double phase)
{
	return 1.0 / (1.0 + exp(k * (cos(sigma) - sin(phase))));
}

auto Ensemble::computeEnsemble(double _sigma, double _k, double max_time = 100, double dt = 0.01)
{
	sigma = _sigma;
	k = _k;

	std::vector<double> time;
	std::vector<std::vector<double>> neurons_phases(neurons.size());

	for (size_t i = 0; i < neurons.size(); i++)
		neurons[i].reset();

	for (double t = 0; t < max_time; t += dt)
	{
		for (size_t i = 0; i < neurons.size(); i++)
			neurons_phases[i].push_back(neurons[i].getNewPhase());
		time.push_back(t);

		doTic(dt);
	}

	return make_tuple(time, neurons_phases);
}
