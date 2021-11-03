#define _USE_MATH_DEFINES

#include <vector>
#include "Ensemble.h"
#include "Neuron.h"
#include <fstream>
#include <iomanip>
#include <cmath>

void main()
{
	Neuron n1(0, 0.9);
	Neuron n2(0, 0.98);
	Ensemble ens1;

	ens1.addConnection(n1);
	ens1.addConnection(n2);


	const double dt = 0.01;


	std::ofstream outf("Ensemble.txt");

	//outf.setf(std::ofstream::fixed);
	//outf.precision(4);

	for (double time = 0; time < 100; time += dt)
	{
		ens1.doTic(dt);
		outf << time << " " << ens1.connection[0].getNewPhase() << " " << ens1.der(0) << " " << ens1.connection[1].getNewPhase() << " " << ens1.der(1) << std::endl;
	}
}