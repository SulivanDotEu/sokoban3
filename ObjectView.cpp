#include "ObjectView.h"
#include <iostream>



ObjectView::ObjectView(CaseContents* m)
{
	this->model = m;
	x = 0;
	y = 0;
}


ObjectView::~ObjectView(void)
{
}


void ObjectView::updateByModel(void){
	std::cout << "---- X updateByModel : " << this->model->getX() << " current x " << this->getX() <<std::endl;
	std::cout << "---- Y updateByModel : " << this->model->getY() << " current y " << this->getY() <<std::endl;
	/*
	double oldX = this->getX();
	double newX = this->model->getX();

	double oldY = this->getY();
	double newY = this->model->getY();

	double shift = 0.005;

	
	
	if( this->getX() != newX){
		if(newX <  oldX){
			shift = -shift;
			while(newX < oldX){
				oldX  += shift;
				this->setPosition( oldX,oldY);
				std::cout << "---- X model : " << newX << " current x " << oldX <<std::endl;
				//this->setPosition(this->model->getX(), this->model->getY());
			}
		}
		else{
			while(newX > oldX){
				oldX  += shift;
				this->setPosition( oldX,oldY);
				std::cout << "---- X model : " << newX << " current x " << oldX <<std::endl;
				//this->setPosition(this->model->getX(), this->model->getY());
			}
		}
	}

	if( this->getY() != newY){
		if(newY <  oldY){
			shift = -shift;
		}
		while( this->getY() != newY){
			oldY += shift;
			this->setPosition(oldX,oldY);
			std::cout << "---- Y model : " << newY << " current y " << oldY <<std::endl;
			//this->setPosition(this->model->getX(), this->model->getY());
		}
	}
	*/
	
	
	this->setPosition(this->model->getX(), this->model->getY());
}

void ObjectView::setPosition(double i, double j){
	this->x=i;
	this->y=j;
	pat = this->getPat();
	pat->setPosition(osg::Vec3(i,j,0));
}