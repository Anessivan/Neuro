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
					phase += gateFunc() * connectionFunc(connection[i].getPhase());
				else
					phase += gateFunc() * connectionFunc(connection[i].getNewPhase());
			while (phase > 2 * M_PI)
				phase -= 2 * M_PI;
			connection[i].setNewPhase(phase);
		}
	}
}

double gateFunc()
{
	return 1;
}

double connectionFunc(double phase)
{
	return phase;
}
