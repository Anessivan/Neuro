#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

double func(double w, double phase);


class Neuron
{
private:
	double phase_start;
	double phaseNew;
	double phase;
	double w;
public:
	Neuron(double = 0.0, double = 1);
	double getPhase();
	void setPhase(double setedPhase);
	double getParam();
	void setParam(double newParam);
	double getNewPhase();
	void setNewPhase(double settedPhase);
	void reset();

	double doTic(double dt);
};