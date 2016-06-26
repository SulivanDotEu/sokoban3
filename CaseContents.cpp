#include "CaseContents.h"
#include "Model.h"
#include <iostream>


CaseContents::CaseContents(void)
{
	x = 0;
	y = 0;
}


CaseContents::~CaseContents(void)
{
}

void CaseContents::setCoord(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool CaseContents::move(int dir)
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
		
		//La case de deplacement contient la Box
		Model::getInstance()->getCase(nX, nY)->setContents(this);
		std::cout<<"NEW POSITION BOX x : "<< x << " - y : " <<y << endl;

		Model::getInstance()->getMove()->add(this);
		return true;
		
	}
	return false;
}

int CaseContents::getX(){
	return x;
}

int CaseContents::getY()
	{return y;}

