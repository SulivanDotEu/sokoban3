// EventController.h
#pragma once
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

using namespace osg;
using namespace osgGA;

// Classe qui va servir � d�finir une animation li�e au click gauche de la souris
class EventHandler :
	public GUIEventHandler
{
public:
	virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);
};

