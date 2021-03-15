#include "PotentialField.h"
#include "physics.h"
#include <cmath>

using namespace std;

PotentialField::PotentialField(int const& width, int const& length, int const& height, double const& boxPerMeter) : Field<double>(width,length,height,0.0,boxPerMeter){
}

void PotentialField::compute(DotParticle particle){
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				if(particle.x()==i && particle.y()==j && particle.z()==k){
					double nv = (m_boxPerMeter * INV_4PIE0 * particle.charge() / sqrt(pow((0.1),2))) + get(i,j,k);
					set(i,j,k,nv);
				}else{
					double nv = (m_boxPerMeter * INV_4PIE0 * particle.charge() / sqrt(pow((particle.x()-i),2)+pow((particle.y()-j),2)+pow((particle.z()-k),2))) + get(i,j,k);
					set(i,j,k,nv);
				}
			}
		}
	}
}
