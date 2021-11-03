#include "Ensemble.h"

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
					phase += (gateFunc() * connectionFunc(connection[j].getPhase())) * dt;
				else
					phase += (gateFunc() * connectionFunc(connection[j].getNewPhase())) * dt;
			while (phase > 2 * M_PI)
				phase -= 2 * M_PI;
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
					 res += (gateFunc() * connectionFunc(connection[j].getPhase()));
				 else
					 res += (gateFunc() * connectionFunc(connection[j].getNewPhase()));
		 }
	return res;
}

double gateFunc()
{
	return 0.4;
}

double connectionFunc(double phase)
{
	return phase;
}
