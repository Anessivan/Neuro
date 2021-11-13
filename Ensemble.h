#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Neuron.h"
#include <vector>

class Ensemble
{
public:
	std::vector<Neuron> connection;

	Ensemble(std::vector<Neuron> vector);
	Ensemble();
	void addConnection(Neuron& newNeuron);
	void doTic(double dt);

	double der(int number);

	double connectionFuncDown(int number);

	double connectionFuncUp(int number);
};

double gateFunc();


class Ensemble_cycle
{
private:
	std::vector<Neuron> Neurons;

public:
	Ensemble_cycle(std::vector<Neuron> vector);
	Ensemble_cycle();

	void addNeuron(Neuron add, size_t size = Neurons.size());

	double NeuronPhase(int number);

	void doTic(double dt);

	double connectionFuncDown(int number);

	double connectionFuncUp(int number);

	//double der(int number);

}