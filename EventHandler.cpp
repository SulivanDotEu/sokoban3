// EventHandler.cpp

//#pragma once

#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include "MyView.h"
#include "EventHandler.h"

#define START_TIME 0
#define STOP_TIME 1

bool EventHandler::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	ref_ptr<AnimationPath> myPath; // Permet de définir le "cheminement" de l'animation
	ref_ptr<AnimationPathCallback> myAnimationCallback; // Permet de gérer l'animation via un mécanisme de callback
	switch(ea.getEventType())
	{
	case GUIEventAdapter::PUSH:
		switch(ea.getButton()){
		case GUIEventAdapter::LEFT_MOUSE_BUTTON:
			// Définition du cheminement de l'animation
			myPath = new AnimationPath();
			myPath->insert(START_TIME, AnimationPath::ControlPoint(Vec3(-1,-1,-1))); // Positionnement de départ
			myPath->insert(STOP_TIME, AnimationPath::ControlPoint(Vec3(3,1,0.5),Quat(3.14,Z_AXIS))); // Positionnement d'arrivée
			myPath->setLoopMode(AnimationPath::NO_LOOPING); // L'animation a lieu une seule fois
			// Le CallBack de gestion de l'animation est créé et associé au noeud de transformation ad hoc
			myAnimationCallback = new AnimationPathCallback(myPath.get());
			//MyView::getInstance()->getMyPat()->setUpdateCallback(myAnimationCallback);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return true; // false si l'évènement doit être pris en compte par d'autres handlers ou callbacks
}