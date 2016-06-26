#include "Move.h"
#include <iostream>

Move::Move(void){
	
}

Move::~Move(void){

}

void Move::setUpInitialPosition(int a, int b){
	this->initialX = a;
	this->initialY = b;
	std::cout << "initial x = " << a << "\n";
	std::cout << "initial x = " << b << "\n";
}

void Move::setUpEndPosition(int a, int b){
	this->endX = a;
	this->endY = b;
	std::cout << "end x = " << a << "\n";
	std::cout << "end x = " << b << "\n";
}

void Move::add(osg::ref_ptr<CaseContents> o){
	tableau.push_back(o);
}