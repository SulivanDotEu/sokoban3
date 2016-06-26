#pragma once

#include <vector>
#include "ObjectView.h"
#include <osg/Vec4>

using namespace std;

class LogView : public Referenced
{
public:
	LogView();
	~LogView(void);
	void updateView();
	void init();

	osg::ref_ptr<osg::Camera> camera;
	osg::ref_ptr<osg::Camera> getCamera();

		// methode utilisee le modele pour informe la vue d'un message à afficher
	// à l'utilisateur
	// pre : l'objet est initialise
	// post : le message entre en parametre est affiche à l'utilisateur
	void newEvent(string);

private:
	// contient le texte a afficher
	ref_ptr<osgText::Text> unTexte;

};

