#include "Player.h"
#include "Model.h"
#include <iostream>

Player::Player(void)
{
	x= 0;
	y = 0;
}


Player::~Player(void)
{
}

bool Player::move(int dir)
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
	//On teste si le player peut se deplacer
	if (Model::getInstance()->getCase(nX, nY)->move(dir)){
		//Si oui

		//La case courante devient vide
		Model::getInstance()->getCase(x, y)->setContents(0);

		//La case de deplacement contient le player
		Model::getInstance()->getCase(nX, nY)->setContents(this);
		Model::getInstance()->getMove()->add(this);
		return true;
	}//Sinon
	return false;
}
