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

std::vector<double> Ensemble::doTic(double dt)
{
	std::vector<double> res;
 	
	for(size_t i = 0; i < neurons.size(); i++)
	{
		neurons[i].doTic(dt);
		double phase_changes = 0;
		int input_n = 0;
		for (size_t j = 0; j < connections.size(); j++)
			if(connections[j].neurons_indexes.first == i)
				if(connections[j].d != 0)
				{
					size_t connectedNeuronIndex = connections[j].neurons_indexes.second;
					double connectedNeuronPhase =  neurons[connectedNeuronIndex].getNewPhase();
				
					phase_changes += connections[j].d * couplingFunction(connectedNeuronPhase) * dt;
					input_n++;
				}
		if(input_n != 0)
		{
			phase_changes = phase_changes / input_n;
			double phase = neurons[i].getNewPhase() + phase_changes;
			neurons[i].setNewPhase(phase);
		}
		res.push_back(neurons[i].getNewPhase());
	}
	
	return res;
}

void Ensemble::addConnection(Connection connection)
{
	connections.push_back(connection);

	sort(connections.begin(), connections.end(), compareConnectionsByIndexes);
}


double Ensemble::couplingFunction(double phase)
{
	// double phase = neurons[connection[connection_number].second].getNewPhase();

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
		doTic(dt);
		time.push_back(t);
		for (size_t i = 0; i < neurons.size(); i++)
		{
			neurons_phases[i].push_back(neurons[i].getNewPhase());
		}
	}

	return make_tuple(time, neurons_phases);
}
