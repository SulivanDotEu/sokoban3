#include "Box.h"
#include "Model.h"
#include <iostream>

MyBox::MyBox(void)
{
	x = 0;
	y = 0;
}


MyBox::~MyBox(void)
{
}

bool MyBox::move(int dir)
{
	int nX = x;
	int nY = y;

	std::cout<<"x "<< x <<" y"<<y<<endl;

	//Determination des coordonnees de la case de deplacement
	switch (dir) {
		case LEFT: {nY--; break;}
		case RIGHT: {nY++; break;}
		case UP: {nX--; break;}
		case DOWN:{nX++; break;}
	}
	//Est-ce que la case de deplacement est vide ?
	if ((Model::getInstance()->getCase(nX, nY)->isEmpty())== true){
		//Alors on fait le deplacement
		Model::getInstance()->addDeplacementB();
		//La case de deplacement contient la Box
		Model::getInstance()->getCase(nX, nY)->setContents(this);
		std::cout<<"NEW POSITION BOX x : "<< x << " - y : " <<y << endl;
		Model::getInstance()->getMove()->add(this);
		return true;
		
	}
	return false;
}
