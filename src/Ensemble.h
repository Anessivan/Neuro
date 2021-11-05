#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Neuron.h"
#include <vector>

class Ensemble
{
public:
	std::vector<Neuron> connection;
	double d;
	double sigma;

	Ensemble(std::vector<Neuron> vector, double, double);
	Ensemble(double, double);
	void addConnection(Neuron& newNeuron);
	void doTic(double dt);

	double der(int number);

	double connectionFuncDown(int number);

	double connectionFuncUp(int number);
};

double gateFunc();