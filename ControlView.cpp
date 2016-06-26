#include "Model.h"
#include "EventController.h"
#include "ClickController.h"
#include "ReceiverView.h"
#include "Bouton.h"
#include <osgViewer/Viewer>
#include <iostream>
#include <osgText/Text>
#include <osg/ShapeDrawable>

using namespace osg;
//Model* View::model = Model::getInstance();

ControlView::ControlView(void){
	unTexte = new osgText::Text();
	haut  = new Bouton("haut.png", "haut2.png");
	bas  = new Bouton("bas.png", "bas2.png");
	droite  = new Bouton("droite.png", "droite2.png");
	gauche  = new Bouton("gauche.png", "gauche2.png");
	 
	save  = new Bouton("save.png", "save2.png");
	restore  = new Bouton("open.png", "open2.png");

	recommencer  = new Bouton("gauche.png", "gauche2.png");
	 suivant  = new Bouton("droite.png", "droite2.png");
}

void ControlView::init()
{

	StateSet* stateset; // pour gerer les caracteristiques d'etat des Drawables

	Vec3 eye = Vec3(0,0,1.5);
	Vec3 center = Vec3(0,0,0);
	Vec3 up = Vec3(0,1,0);
	
	camera = new Camera;
	camera->setViewMatrixAsLookAt(eye,center,up);
	camera->setProjectionMatrixAsOrtho(-5,5,-2, 2, 0.4,7);
	camera->setViewport(new osg::Viewport(0,500,500,200)); // complementaire de la viewport de l'autre camera ...
	camera->setReferenceFrame(Camera::ABSOLUTE_RF);
	camera->setClearColor(Vec4(0,0,0,1));

	ref_ptr<Geode> unBouton = new Geode;
	stateset = unBouton->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,StateAttribute::OFF);

	//ref_ptr<PositionAttitudeTransform> pat  = new osg::PositionAttitudeTransform();
	//pat->addChild(unBouton);
	//pat->setPosition(Vec3(-2,1,0));

	 


	 haut->getPat()->setPosition(Vec3(0+3,0.6,0));
	bas->getPat()->setPosition(Vec3(0+3,-0.5,0));
	droite->getPat()->setPosition(Vec3(1.1+3,-0.5,0));
	gauche->getPat()->setPosition(Vec3(-1.1+3,-0.5,0));

	restore->getPat()->setPosition(Vec3(0-3,-0.5,0));
	save->getPat()->setPosition(Vec3(-1.1-3,-0.5,0));

	
	suivant->getPat()->setPosition(Vec3(0-0,-0.5,0));
	recommencer->getPat()->setPosition(Vec3(-1.1-0,-0.5,0));

	camera->addChild(haut->getPat());
	camera->addChild(bas->getPat());
	camera->addChild(droite->getPat());
	camera->addChild(gauche->getPat());

	camera->addChild(save->getPat());
	camera->addChild(restore->getPat());

	camera->addChild(recommencer->getPat());
	camera->addChild(suivant->getPat());



	ref_ptr<Geode> message = new Geode;
	stateset = message->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
	unTexte->setCharacterSize(0.5); // PAS des pixels
	unTexte->setPosition(Vec3(1.1+5,-0.5,0)); // PAS des pixels
	unTexte->setText("Log");
	unTexte->setColor(VERT);
	message->addDrawable(unTexte);

	camera->addChild(message);


	// Associe les noeuds contenant le message et le bouton graphique à la camera2 
	//camera->addChild(pat.get());
	// Associe un "event callback" à la camera : gestion de l'utilisation du bouton graphique
	camera->setEventCallback(new ClickController());


}

void ControlView::newEvent(std::string s){
	this->unTexte->setText(s);
}

/*
void ControlView::init()
{
	StateSet* stateset; // pour gerer les caracteristiques d'etat des Drawables


	camera = new osg::Camera;
	osg::Vec3 eye = osg::Vec3(1,1,6);
	osg::Vec3 center = osg::Vec3(1,1,0);
	osg::Vec3 up = osg::Vec3(-1,0,0);
	camera->setViewMatrixAsLookAt(eye,center,up);

	float near = 0.1; 
	float far = 2; 
	float fovy = 45.0; 
	float ratio = 1.0; 

	//camera->setProjectionMatrixAsOrtho(fovy, ratio, near,far ); 
	camera->setProjectionMatrixAsOrtho(-4,4,-4,4,0.5,5);

	ReceiverView* haut  = new ReceiverView();
	ReceiverView* gauche  = new ReceiverView();
	ReceiverView* droite  = new ReceiverView();
	ReceiverView* bas  = new ReceiverView();


	//haut->setPosition(2, 1);
	//bas->setPosition(0, 1);
	//gauche->setPosition(2, -1);
	//droite->setPosition(2, 3);

	//haut->getPat()->addEventCallback(new ClickController(UP));
	//bas->getPat()->addEventCallback(new ClickController(DOWN));
	//gauche->getPat()->addEventCallback(new ClickController(LEFT));
	//droite->getPat()->addEventCallback(new ClickController(RIGHT));

	//camera->addChild(haut->getPat());
	//camera->addChild(gauche->getPat());
	//camera->addChild(droite->getPat());
	//camera->addChild(bas->getPat());

	camera->setViewport(new osg::Viewport(0,500,200,200));
	// Annule la camera par defaut 
	camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	// Definit la couleur de fond de la viewport de la camera 
	camera->setClearColor(osg::Vec4(1,1,1,1));


	ref_ptr<ShapeDrawable> bouton = new ShapeDrawable;
	bouton->setShape(new Box(Vec3(3,0,0),.5,.5,0.1));
	bouton->setColor(Vec4(.5,.3,0,1));
	ref_ptr<Geode> unBouton = new Geode;
	stateset = unBouton->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
	unBouton->addDrawable(bouton.get());



	camera->setEventCallback(new ClickController());



}
*/

void ControlView::updateView(void){
	
}

osg::ref_ptr<osg::Camera> ControlView::getCamera(){
	return camera;
}

ControlView::~ControlView(void)
{
}