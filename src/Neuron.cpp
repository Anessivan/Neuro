#include "Neuron.h"

Neuron::Neuron(double phase_start_, double param)
{
	phase_start = phase_start_;;
	phaseNew = phase_start;
	w = param;
}

void Neuron::reset()
{
	phaseNew = phase_start;
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
	phaseNew += func(w, phaseNew) * dt;
	return phaseNew;
}


double func(double w, double phase)
{
	return w - sin(phase);
}
