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
	void doTic(double dt);// если сила связи одинакова для всех, то добавить умножение в форик. Если нет - думать.

	double der(int number);

	double connectionFunc(int number);
};

double gateFunc();