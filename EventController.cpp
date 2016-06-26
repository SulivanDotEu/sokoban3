// EventController.cpp
#include <osg/MatrixTransform>
#include "EventController.h"
//#include <iostream>
#include "Model.h"

EventController::EventController(){
	//Instanciation d'une map qui relie l'ID d'une touche et sa commande effective
	controllers[GUIEventAdapter::KEY_Right] = new Right(Model::getInstance());
	controllers[GUIEventAdapter::KEY_Left] = new Left(Model::getInstance());
	controllers[GUIEventAdapter::KEY_Up] = new Up(Model::getInstance());
	controllers[GUIEventAdapter::KEY_Down] = new Down(Model::getInstance());

	controllers[GUIEventAdapter::KEY_U] = new UndoCommand(Model::getInstance());

	controllers[GUIEventAdapter::KEY_Z] = new Zoom(MyView::getInstance());
	controllers[GUIEventAdapter::KEY_A] = new Dezoom(MyView::getInstance());
}

void EventController::operator()(Node* node, NodeVisitor* nv)
{
	//La classe osgGA::GUIEventAdapter gere tous les types d'evenemens  qui peuvent survenir
	std::list<ref_ptr<GUIEventAdapter>> events; // Structure de type liste (librairie standard)
	EventVisitor* ev = dynamic_cast<EventVisitor*>(nv); // Particularise le "visiteur" de noeuds
	if(ev) events = ev->getEvents(); // Recupere les "evenements" dans la liste
	ref_ptr<GUIEventAdapter> ea = events.back(); // Recupere le dernier element de la liste
	events.pop_back(); // Supprime l'element recupere de la liste
	
	
	switch(ea->getEventType())
	{
	case GUIEventAdapter::KEYDOWN: // Enfoncement d'une touche
		//Si la touche est reliee à une commande
		if (controllers[ea->getKey()]!= 0)
			//On l'execute
			controllers[ea->getKey()]->execute();
		break;
	default:
		break;
	}
	if (ea->getKey()!= GUIEventAdapter::KEY_U)
	traverse(node,nv);
}