#pragma once

#include "ObjectView.h"
#include <osg/PositionAttitudeTransform>


class BoxView : public ObjectView
{
public:
	BoxView(CaseContents* model);
	virtual ~BoxView(void);
	///void setPosition(int x, int y);

	/// renvoie l'objet contenant la forme graphique
	/// post : si l'attribut pat n'est pas initialisee, la methode l'initialise
	///		de  telle que l'objet reprensantant la forme du modele y soit associe.
	static osg::ref_ptr<osg::Geode> getGeode();

	/// @see ObjectView.h::getPat();
	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();

private:
	/// objet contenant la forme graphique, a savoir une boite
	/// la forme graphique estdefinie une seule fois pour tout les instances
	static osg::ref_ptr<osg::Geode> geode;
	
};
