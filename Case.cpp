#include "Case.h"
#include "Box.h"
#include "Wall.h"
#include "Player.h"
#include <iostream>

Case::Case(void)
{
}

Case::Case(int x, int y, CaseContents *contents, bool receiver)
{
	this->x = x;
	this->y = y;
	this->receiver = receiver;
	this->completed = false;
	setContents(contents);
}

Case::~Case(void)
{
	contents = 0;
}

ref_ptr<CaseContents> Case::getContents()
{
	return contents;
}

void Case::setContents(CaseContents *contents)
{
	this->contents = contents;
	//Si la case n'est pas vide
	if (contents !=0)
	{	//On donne les nouvelles coordonnees à son contenu
		this->contents->setCoord(this->x, this->y);
	}

	//Si le contenu est une boite et que la case est un socle
	if (dynamic_cast<MyBox*>(contents) && receiver == true)
		{   //Alors la case est complete
			this->completed = true;
			std::cout << "COMPLETED\n";
		}
		//Sinon
		else
		{
			this->completed = false;
		}
}

int Case::getX()
{
	return x;
}

int Case::getY()
{
	return y;
}

bool Case::move(int dir)
{	//Si la case est vide
	if (contents == 0) {
		std::cout<<"EMPTY SPOT\n";
		//Deplacement possible
		return true;
	}//Si la case n'est pas vide
	else {
		std::cout<<type()<<"\n";
		//On demande au contenu son deplacement et on renvoie s'il a ete effectue
		//ou s'il est impossible
		return contents->move(dir);
	}
}

bool Case::isCompleted()
{
	return completed;
}

std::string Case::type(){

	if (dynamic_cast<MyBox*>(contents.get())){
		return "Box";
	}
	else if (dynamic_cast<Wall*>(contents.get())){
		return "Wall";
	}

	else return "??";
}

bool Case::isEmpty()
{
	if (contents == 0) return true;
	else return false;
}

bool Case::isReceiver()
{
	return receiver;
}