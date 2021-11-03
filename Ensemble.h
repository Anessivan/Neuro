#pragma once


#include "Neuron.h"
#include <vector>

class Ensemble
{
public:
	std::vector<Neuron> connection;

	Ensemble(std::vector<Neuron> vector);
	Ensemble();
	void addConnection(Neuron& newNeuron);
	void doTic(double dt);// ���� ���� ����� ��������� ��� ����, �� �������� ��������� � �����. ���� ��� - ������.
};

double gateFunc();
double connectionFunc(double phase);