#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

double func(double w, double phase);


class Neuron
{
private:
	double phase_start;
	double phaseNew;
	double w;
public:
	Neuron(double phase_start = 0.0, double param = 1);
	double getParam();
	void setParam(double newParam);
	double getNewPhase();
	void setNewPhase(double settedPhase);
	void reset();

	double doTic(double dt);
};