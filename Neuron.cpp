#include "Neuron.h"

Neuron::Neuron(double phase_start, double param)
{
	phase = phase_start;
	phaseNew = phase_start;
	w = param;
}

Neuron::Neuron(const Neuron& copy)
{
	phase = copy.phase;
	phaseNew = copy.phaseNew;
	w = copy.w;
}

double Neuron::getPhase()
{
	return phase;
}

void Neuron::setPhase(double setedPhase)
{
	phase = setedPhase;
}

double Neuron::getParam()
{
	return w;
}

void Neuron::setParam(double newParam)
{
	w = newParam;
}

double Neuron::getNewPhase()
{
	return phaseNew;
}

void Neuron::setNewPhase(double settedPhase)
{
	phaseNew = settedPhase;
}

double Neuron::doTic(double dt)
{
	phase = phaseNew;
	phaseNew += func(w, phaseNew) * dt;
	//while (phaseNew > 2 * M_PI)
	//	phaseNew -= 2 * M_PI;
	return phaseNew;
}


double func(double w, double phase)
{
	return w + sin(phase);
}
