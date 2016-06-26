#include "Model.h"
#include "EventController.h"
#include "ClickController.h"
#include "LogView.h"
#include "TextBox.h"
#include <osgViewer/Viewer>
#include <iostream>
#include <osg/ShapeDrawable>


using namespace osg;

LogView::LogView(void){
	unTexte = new osgText::Text();
}

void LogView::init()
{
	StateSet* stateset; // pour gerer les caracteristiques d'etat des Drawables

	Vec3 eye = Vec3(0,0,1.5);
	Vec3 center = Vec3(0,0,0);
	Vec3 up = Vec3(0,1,0);
	
	camera = new Camera();
	camera->setViewMatrixAsLookAt(eye,center,up);
	camera->setProjectionMatrixAsOrtho(-5, 5, -2,2, 0.5, 7);
	//camera->setViewport(new osg::Viewport(0,500,500,200));
	camera->setViewport(new osg::Viewport(500,500,500,200)); // complementaire de la viewport de l'autre camera ...
	camera->setReferenceFrame(Camera::ABSOLUTE_RF);
	camera->setClearColor(Vec4(0,0,0,1));

	// Definition d'un bouton graphique et d'un Geode pour l'accueillir
	ref_ptr<Geode> message = new Geode;
	stateset = message->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
	unTexte->setCharacterSize(0.5); // PAS des pixels
	unTexte->setPosition(Vec3(-4.1,-0.5,0)); // PAS des pixels
	unTexte->setText("Sokoban");
	unTexte->setColor(VERT);
	message->addDrawable(unTexte);
	message->setStateSet(stateset);

	camera->addChild(message);


}

void LogView::newEvent(std::string s){
	this->unTexte->setText(s);
}

void LogView::updateView(void){
	
}

osg::ref_ptr<osg::Camera> LogView::getCamera(){
	return camera;
}

LogView::~LogView(void)
{
}