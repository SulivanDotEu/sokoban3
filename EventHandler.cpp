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
	ref_ptr<AnimationPath> myPath; // Permet de d�finir le "cheminement" de l'animation
	ref_ptr<AnimationPathCallback> myAnimationCallback; // Permet de g�rer l'animation via un m�canisme de callback
	switch(ea.getEventType())
	{
	case GUIEventAdapter::PUSH:
		switch(ea.getButton()){
		case GUIEventAdapter::LEFT_MOUSE_BUTTON:
			// D�finition du cheminement de l'animation
			myPath = new AnimationPath();
			myPath->insert(START_TIME, AnimationPath::ControlPoint(Vec3(-1,-1,-1))); // Positionnement de d�part
			myPath->insert(STOP_TIME, AnimationPath::ControlPoint(Vec3(3,1,0.5),Quat(3.14,Z_AXIS))); // Positionnement d'arriv�e
			myPath->setLoopMode(AnimationPath::NO_LOOPING); // L'animation a lieu une seule fois
			// Le CallBack de gestion de l'animation est cr�� et associ� au noeud de transformation ad hoc
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

	return true; // false si l'�v�nement doit �tre pris en compte par d'autres handlers ou callbacks
}