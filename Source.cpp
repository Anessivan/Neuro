#include <vector>
#include "Ensemble.h"
#include "Neuron.h"
#include <fstream>
#include <iomanip>

void main()
{
	Neuron n1;
	Neuron n2;
	Ensemble ens1;

	ens1.addConnection(n1);
	ens1.addConnection(n2);


	const double dt = 0.01;


	std::ofstream outf("Ensemble.dt=0.01.txt");

	//outf.setf(std::ofstream::fixed);
	//outf.precision(4);

	for (double time = 0; time < 10; time += dt)
	{
		ens1.doTic(dt);
		outf << time << " " << ens1.connection[0].getNewPhase() << " " << ens1.der(0)<< " " << ens1.connection[1].getNewPhase() << " " << ens1.der(1) << std::endl;
	}
}