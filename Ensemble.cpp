#define _USE_MATH_DEFINES
#include <cmath>
#include "Ensemble.h"
#include <iostream>

Ensemble::Ensemble(std::vector<Neuron> vector)
{
	connection = vector;
}

Ensemble::Ensemble()
{

}

void Ensemble::addConnection(Neuron& newNeuron)
{
	connection.push_back(newNeuron);
}

void Ensemble::doTic(double dt)
{
	double phase;
	for (int i = 0; i < connection.size(); i++)
	{
		connection[i].doTic(dt);
		for (int j = 0; j < connection.size(); j++)
		{
			phase = connection[i].getNewPhase();
			if (i != j)
				if (i < j)
					phase += (gateFunc() * connectionFunc(j) * dt);
				else
					phase += (gateFunc() * connectionFunc(j) * dt);
			//while (phase > 2 * M_PI)
				//phase -= 2 * M_PI;
			connection[i].setNewPhase(phase);
		}
	}
}

double Ensemble::der(int number)
{
	double res = 0;
	//if (number < connection.size())
		 res += func(connection[number].getParam(), connection[number].getNewPhase());
		 for (int j = 0; j < connection.size(); j++)
		 {
			 if (number != j)
				 if (number < j)
					 res += (gateFunc() * connectionFunc(j));
				 else
					 res += (gateFunc() * connectionFunc(j));
		 }
	return res;
}

double gateFunc()
{
	return 1.0;
}

double Ensemble::connectionFunc(int number)
{
	double sigma = 0.5;
	//std::cout << asin(connection[number].getParam()) << " " << connection[number].getNewPhase() << std::endl;
	double phase = connection[number].getNewPhase();
	while (phase > 2 * M_PI)
		phase -= 2 * M_PI;
	if (((asin(connection[number].getParam()) - sigma) < phase) && ((asin(connection[number].getParam()) + sigma) > (phase)))
		return 0.0;
	else 
		return 1.0;
}
