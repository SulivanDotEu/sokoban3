#pragma once

#include "CaseContents.h";
#include <osg/PositionAttitudeTransform>

class ObjectView
{
public:
	/// Constructeur par defaut, il ne fait rien
	ObjectView();

	/// Constructeur avec le model
	/// post : cree l'objet en enregistrant le model associe,
	///		ici un objet correspondant à un objet de case comme une boite ou un mur
	ObjectView(CaseContents* model);

	virtual ~ObjectView(void);

	/// Reactualise la vue selon le model
	/// pre: le model est initialise
	/// post: represente le modele graphiquement sur le graphe de scene
	void virtual updateByModel(void);

	/// renvoie le Pat
	/// post : si l'attribut pat n'est pas initialisee, la methode l'initialise
	///		de  telle que l'objet reprensantant le modele y soit associe.
	virtual osg::ref_ptr<osg::PositionAttitudeTransform> getPat()=0;

	/// positionne l'objet representant le modele sur le graphe de scene
	/// post: l'objet est positionne selon les coordonnees donnes en parametre
	virtual void setPosition(double x, double y);

	virtual CaseContents* getModel(){return model;};

	virtual int getX(){return x;};
	virtual int getY(){return y;};

protected:
	/// modele associe à l'objet
	CaseContents* model;
	/// objet contenant la forme graphique reprensant le model
	/// permet le changement de position de la forme graphique
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;

	double x;
	double y;
};

