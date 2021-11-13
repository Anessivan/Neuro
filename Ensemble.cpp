#define _USE_MATH_DEFINES
#include <cmath>
#include "Ensemble.h"
#include <iostream>

#define SIGMA 1.0

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
					phase += (gateFunc() * connectionFuncDown(j) * dt);
				else
					phase += (gateFunc() * connectionFuncUp(j) * dt);
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
					 res += (gateFunc() * connectionFuncDown(j));
				 else
					 res += (gateFunc() * connectionFuncUp(j));
		 }
	return res;
}

double gateFunc()
{
	return 1.0;
}

double Ensemble::connectionFuncDown(int number)
{

	//std::cout << asin(connection[number].getParam()) << " " << connection[number].getNewPhase() << std::endl;
	double phase = connection[number].getNewPhase();
	while (phase > 2 * M_PI)
		phase -= 2 * M_PI;
	if (((asin(connection[number].getParam()) - SIGMA) < phase) && ((asin(connection[number].getParam()) + SIGMA) > (phase)))
		return 0.0;
	else 
		return 1.0;
}


double Ensemble::connectionFuncUp(int number)
{
	//std::cout << asin(connection[number].getParam()) << " " << connection[number].getNewPhase() << std::endl;
	double phase = connection[number].getPhase();
	while (phase > 2 * M_PI)
		phase -= 2 * M_PI;
	if (((asin(connection[number].getParam()) - SIGMA) < phase) && ((asin(connection[number].getParam()) + SIGMA) > (phase)))
		return 0.0;
	else 
		return 1.0;
}



Ensemble_cycle::Ensemble_cycle(std::vector<Neuron> vector)
{
	Neurons = vector;
}

void Ensemble_cycle::addNeuron(Neuron add, size_t position = Neurons.size())
{
	Neurons.insert(position, add);

}

double Ensemble_cycle::NeuronPhase(int number)
{
	return Neurons[number].getPhase();
}


void Ensemble_cycle::doTic(double dt)
{
	for (int i = 0; i < Neurons.size(); i++)
	{
		Neurons[number].doTic();

		double phase = Neurons[number].getNewPhase();

		if(i = 0)
		{
			phase += gateFunc() * connectionFuncDown(Neurons.size() - 1);
			phase += gateFunc() * connectionFuncDown(i + 1);
		}
		else if (i = Neurons[Neurons.size() - 1)
		{
			phase += gateFunc() * connectionFuncDown(0);
			phase += gateFunc() * connectionFuncUp(i - 1);
		}
		else
		{
			phase += gateFunc() * connectionFuncDown(i + 1);
			phase += gateFunc() * connectionFuncUp(i - 1);
		}
	}
}


double Ensemble_cycle::connectionFuncDown(int number)
{

	//std::cout << asin(connection[number].getParam()) << " " << connection[number].getNewPhase() << std::endl;
	double phase = connection[number].getNewPhase();
	while (phase > 2 * M_PI)
		phase -= 2 * M_PI;
	if (((asin(connection[number].getParam()) - SIGMA) < phase) && ((asin(connection[number].getParam()) + SIGMA) > (phase)))
		return 0.0;
	else 
		return 1.0;
}


double Ensemble_cycle::connectionFuncUp(int number)
{
	//std::cout << asin(connection[number].getParam()) << " " << connection[number].getNewPhase() << std::endl;
	double phase = connection[number].getPhase();
	while (phase > 2 * M_PI)
		phase -= 2 * M_PI;
	if (((asin(connection[number].getParam()) - SIGMA) < phase) && ((asin(connection[number].getParam()) + SIGMA) > (phase)))
		return 0.0;
	else 
		return 1.0;
}