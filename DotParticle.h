#ifndef DOT_PARTICLE_H
#define DOT_PARTICLE_H

class DotParticle{
	public:
	
	DotParticle(int const& x, int const& y, int const& z, double const& mass, double const& charge);
	
	int x() const;
	int y() const;
	int z() const;
	double mass() const;
	double charge() const;
	
	private:
	
	int m_x;
	int m_y;
	int m_z;
	double m_mass;
	double m_charge;
};

#endif //DOT_PARTICLE_H_INCLUDED
