#pragma once
#include "CaseContents.h"
#include <osg\Array>

using namespace osg;

class CaseContents : public Referenced
{
protected:
	int x;
	int y;
	virtual ~CaseContents(void);

public:
	CaseContents(void);
	///Renvoie la coordonnee X
	int getX();
	///Renvoie la coordonnee Y 
	int getY();
	///Met a jour les coordonees X et Y
	void setCoord(int,int);
	
	///Deplacement de l'element. Renvoie true si le mouvement a ete possible, false sinon
	virtual bool move(int);
};
