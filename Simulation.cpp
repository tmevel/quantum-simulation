#include "Simulation.h"

#include "physics.h"

#include <cmath>
#include <complex>
#include <iostream>
#include <QImage>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

using namespace std;

Simulation::Simulation(int const& width, int const& length, int const& height, double const& boxPerMeter):
m_vField(width,length,height,boxPerMeter),
m_phi(width,length,height,complex<double>(0,0),boxPerMeter)
{
	
}

void Simulation::add(DotParticle particle){
	m_vField.compute(particle);
}

void Simulation::init(){
	m_phi.set(100,100,0,complex<double>(1,0));
	//double iniProb = 1.0/(m_phi.width()*m_phi.length()*m_phi.height());
	//for(int i(0);i<m_phi.width();i++){
		//for(int j(0);j<m_phi.length();j++){
			//for(int k(0);k<m_phi.height();k++){
				//m_phi.set(i,j,k,complex<double>(iniProb,0));
			//}
		//}
	//}
	//for(int i(0);i<m_phi.width();i++){
		//for(int j(0);j<m_phi.length();j++){
			//for(int k(0);k<m_phi.height();k++){
				//m_vField.set(i,j,k, j);
				//if(j==110){
					//m_vField.set(i,j,k, 10000);
				//}
			//}
		//}
	//}
}

void Simulation::run(double const& secPerFrame, double const& simTime){
	complex<double> i_over_h(0,1/H_);
	complex<double> ih_over_2m(0 ,H_/(2*M_ELECTRON));
	//QApplication a(1," ");
    //QGraphicsScene scene;
    //QGraphicsView view(&scene);
    //QGraphicsPixmapItem item(QPixmap("t1.png"));
    //scene.addItem(&item);
    //view.show();
    //a.exec();
	
	for(double t=0;t<=simTime;t+=secPerFrame){
		cout<<t<<endl;
		
		Field<complex<double>> vphi(m_phi);
		for(int i(0);i<m_phi.width();i++){
			for(int j(0);j<m_phi.length();j++){
				for(int k(0);k<m_phi.height();k++){
					vphi.set(i,j,k, m_phi.get(i,j,k)*m_vField.get(i,j,k)*(-E_CHARGE)); //-
				}
			}
		}
		
		Field<complex<double>> dphi =  ((m_phi.laplacian()*ih_over_2m) - (vphi*i_over_h)) * complex<double>(secPerFrame,0);
		//if(t==simTime)cout<<((m_phi.laplacian()*ih_over_2m) - (vphi*i_over_h))).get(90,90,0) * (complex<double>(secPerFrame,0)<<" "<<((m_phi.laplacian()*ih_over_2m) - (vphi*i_over_h))).get(90,90,0) * (complex<double>(secPerFrame*10,0)<<endl;
		m_phi += dphi;
		
		double sump(0);
		
		for(int i(0);i<m_phi.width();i++){
			for(int j(0);j<m_phi.length();j++){
				for(int k(0);k<m_phi.height();k++){
					double n = norm(m_phi.get(i,j,k));
					sump += n;
				}
			}
		}
		
		m_phi/=sump;
	}
}

void Simulation::savePicture(int const& layer, string filename) const{
	Field<double> proba(m_phi.width(), m_phi.length(), m_phi.height(), 0, m_phi.boxPerMeter());
	
	for(int i(0);i<m_phi.width();i++){
		for(int j(0);j<m_phi.length();j++){
			for(int k(0);k<m_phi.height();k++){
				double n = norm(m_phi.get(i,j,k));
				proba.set(i,j,k, n*n);
				//double n = real(m_phi.get(i,j,k));
				//proba.set(i,j,k, n);
			}
		}
	}
	
	QImage im(m_phi.width(),m_phi.length(),QImage::Format_RGB32);
	im.fill(qRgb(255, 255, 255));
	
	double max(0);
	
	for(int i(0);i<200;i++){
		for(int j(0);j<200;j++){
			if(proba.get(i,j,layer)>max){
				max = proba.get(i,j,layer);
			}
		}
	}
	
	//max = 0.00001;
	
	for(int i(0);i<200;i++){
		for(int j(0);j<200;j++){
			ColorScale color(proba.get(i,j,layer), 0, max);
			
			im.setPixel(i,j,qRgb(color.red,color.green,color.blue));
		}
	}
	
	for(int i(0);i<1;i++){
		for(int j(0);j<200;j++){
			ColorScale color(j, 0, 200);
			
			im.setPixel(i,j,qRgb(color.red,color.green,color.blue));
		}
	}
	
	im.save(filename.c_str());
}

ColorScale::ColorScale(double const& value, double const& min, double const& max){
	double quarter = (max - min)/4;
	if(value <= quarter){
		blue = 255;
		red = 0;
		green = 255 - ((quarter - value)/quarter)*255;
	}else if(value <= 2*quarter){
		green = 255;
		red = 0;
		blue = ((quarter*2 - value)/quarter)*255;
	}else if(value <= 3*quarter){
		green = 255;
		blue = 0;
		red = 255 - ((quarter*3 - value)/quarter)*255;
	}else{
		red = 255;
		blue = 0;
		green = ((quarter*4 - value)/quarter)*255;
	}
}
