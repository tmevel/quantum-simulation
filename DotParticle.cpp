#include "DotParticle.h"

using namespace std;

DotParticle::DotParticle(int const& x, int const& y, int const& z, double const& mass, double const& charge) : m_x(x),m_y(y),m_z(z),m_mass(mass),m_charge(charge){
}

int DotParticle::x() const{
	return m_x;
}

int DotParticle::y() const{
	return m_y;
}

int DotParticle::z() const{
	return m_z;
}

double DotParticle::mass() const{
	return m_mass;
}

double DotParticle::charge() const{
	return m_charge;
}
