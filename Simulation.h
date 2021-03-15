#ifndef SIMULATION_H
#define SIMULATION_H

#include "Field.h"
#include "DotParticle.h"
#include "PotentialField.h"
#include <complex>

class ColorScale{
	public:
	
	ColorScale(double const& value, double const& min, double const& max);
	
	int red;
	int green;
	int blue;
};

class Simulation{
	public:
	
	Simulation(int const& width, int const& length, int const& height, double const& boxPerMeter);
	
	void add(DotParticle particle);
	void init();
	void run(double const& secPerFrame, double const& simTime);
	void savePicture(int const& layer, std::string filename) const;
	
	
	private:
	
	PotentialField m_vField;
	Field<std::complex<double>> m_phi;
};

#endif //SIMULATION_H_INCLUDED
