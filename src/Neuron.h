#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

double func(double w, double phase);


class Neuron
{
private:
	double phaseNew;
	double phase;
	double w;
public:
	Neuron(double phase_start = 0.0, double param = 1);
	Neuron(const Neuron& copy);
	double getPhase();
	void setPhase(double setedPhase);
	double getParam();
	void setParam(double newParam);
	double getNewPhase();
	void setNewPhase(double settedPhase);

	double doTic(double dt);
};