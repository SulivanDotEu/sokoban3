// EventController.h
#pragma once
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>
#include "Model.h"
#include <stdio.h>
#include "Command.h"
#include "ConcreteCommands.h"
#include <stdlib.h>
#include <map>

using namespace osg;
using namespace osgGA;
using namespace std;

// Classe qui va servir à definir un "event callback" lie aux actions de l'utilisateur
class EventController :
	public NodeCallback
{
public:
	EventController();
	/// C'est l'operateur ci-dessous, herite de NodeCallback, qui doit être redefini
	/// afin de gerer des evenements lies à un Node dans le cadre du parcours d'un NodeVisitor
	virtual void operator()(Node* node, NodeVisitor* nv);
	///~EventController();

private:
	///Map des touches
	map<int, Command*> controllers;
};

