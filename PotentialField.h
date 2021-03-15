#ifndef POTENTIALFIELD_H
#define POTENTIALFIELD_H

#include "Field.h"
#include "DotParticle.h"

class PotentialField : public Field<double>{
	public:
	
	PotentialField(int const& width, int const& length, int const& height, double const& boxPerMeter);
	
	void compute(DotParticle particle);
};

#endif //POTENTIALFIELD_H_INCLUDED
