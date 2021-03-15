#include "Simulation.h"
#include "DotParticle.h"
#include "physics.h"
#include <string>
#include <QImage>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

using namespace std;

int main(){
	Simulation hydrogene(200, 200, 1, 100000000000);
	
	DotParticle nucleus(80,80,0,M_PROTON,E_CHARGE);
	
	hydrogene.add(nucleus);
	hydrogene.init();
	
	
	for(int i=0;i<10;i++){
		string title = "hydrogene";
		title = title+to_string(i)+".png";
		hydrogene.run(1, 200);
	
		hydrogene.savePicture(0,title);
	}
	
	//hydrogene.run(1, 100);
	
	//hydrogene.savePicture(0,"test2.png");
	
	//hydrogene.run(1, 10000);
	
	//hydrogene.savePicture(0,"test4.png");
	//hydrogene.run(1, 10000);
	
	//hydrogene.savePicture(0,"test5.png");
}
