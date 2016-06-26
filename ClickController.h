// Objet permettant le controle des evenements � la souris

#pragma once
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>
#include "Model.h"

using namespace osg;
using namespace osgGA;


class ClickController : public NodeCallback
{
public:
	ClickController();
	/// C'est l'operateur ci-dessous, herite de NodeCallback, qui doit �tre redefini
	/// afin de gerer des evenements lies � un Node dans le cadre du parcours d'un NodeVisitor
	virtual void operator()(Node* node, NodeVisitor* nv);
	//~EventController();
private:

};

