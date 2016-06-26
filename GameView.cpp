#include "GameView.h"
#include "MyView.h"
#include "BoxView.h"
#include "WallView.h"
#include "PlayerView.h"
#include "Platform.h"
#include "Player.h"
#include "Case.h"
#include "Wall.h"
#include "Model.h"
#include "EventController.h"
#include "ReceiverView.h"
#include <osgViewer/Viewer>
#include <iostream>
#define START_TIME 0
#define STOP_TIME 1

using namespace osg;


//Model* View::model = Model::getInstance();

GameView::GameView(void){
	groupe = new osg::Group();
	camera = new osg::Camera();
}

void GameView::zoom(){
	if(cam_z < 4) return;
	cam_z--;

	if(setUpCameraOnPlayerIfNecessary()) return;

	osg::Vec3 eye = osg::Vec3(cam_x,cam_y, cam_z);
	camera->setViewMatrixAsLookAt(eye,center,up);
}

void GameView::dezoom(){
	if(cam_z > 30) return;
	cam_z++;
	if(setUpCameraOnPlayerIfNecessary()) return;

	osg::Vec3 eye = osg::Vec3(cam_x,cam_y, cam_z);

	camera->setViewMatrixAsLookAt(eye,center,up);
}

bool GameView::setUpCameraOnPlayerIfNecessary(){
	if(cam_z<10){

		Model* model = Model::getInstance();
		Player* p = model->getPlayer();
		osg::Vec3 center2 = osg::Vec3(p->getX(), p->getY(), 0);
		osg::Vec3 eye = osg::Vec3(p->getX(),p->getY(), cam_z);
		camera->setViewMatrixAsLookAt(eye,center2,up);
		return true;
	}
	return false;
}



void GameView::init()
{
	camera->removeChild(groupe);
	groupe = new osg::Group();
	//camera = new osg::Camera();


	vector<ObjectView*> objetsMap2(0);
	int x(Model::getInstance()->getSizeX()),
		y(Model::getInstance()->getSizeY());

	for (int i = 0; i< Model::getInstance()->getSizeX() ; i++)
	{
		for (int j = 0; j < Model::getInstance()->getSizeY() ; j++)
		{
			cout << "getCase("<<j<<", "<<i<<")";
			ObjectView* o = 0;
			ref_ptr<Case> c = Model::getInstance()->getCase(i, j);
			ref_ptr<CaseContents> content = c->getContents();

			if(c->isReceiver()){
				
				ReceiverView* p1 = new ReceiverView();
				p1->setPosition(i, j);
				groupe->addChild(p1->getPat());
				
			} else {
				Platform* p1 = new Platform();
				p1->setPosition(i, j);
				groupe->addChild(p1->getPat());
			}

			if (dynamic_cast<MyBox*>(content.get())){
				o = new BoxView(content);
				o->setPosition(i, j);
				groupe->addChild(o->getPat());
				
				objetsMap2.push_back(o);
			}

			else if (dynamic_cast<Player*>(content.get())){
				//std::cout << "---- X player : " << content->getX() << std::endl;
				//std::cout << "---- Y player : " << content->getY() << std::endl;
				o = new PlayerView(content);
				o->setPosition(i, j);
				groupe->addChild(o->getPat());

				objetsMap2.push_back(o);
			}

			else if (dynamic_cast<Wall*>(content.get())){
				WallView* w = new WallView();
				w->setPosition(i, j);
				groupe->addChild(w->getPat());
			}
		}
	}
	objetsMap = objetsMap2;

	for (int i =0; i< this->objetsMap.size(); i++)
	{
		//this->objetsMap[i]->updateByModel();
	}
	this->updateView();
	//viewer->setSceneData(camera.get());

	//osg::Vec3 eye = osg::Vec3(1,5, 12);
	cam_x = x*1.25;
	cam_y = y/2.0;
	cam_z = 12;
	osg::Vec3 eye = osg::Vec3(cam_x,cam_y, cam_z);
	center = osg::Vec3(x/2.0,y/2.0,0);
	up = osg::Vec3(-1,0,0);

	camera->setViewMatrixAsLookAt(eye,center,up);
	// Definit un volume de projection 
	//camera->setProjectionMatrixAsOrtho(-1, 1, -1, 1, 1.5, 5);
	float near = 0.1; 
	float far = 2; 
	float fovy = 55.0; 
	float ratio = 2; 
	camera->setProjectionMatrixAsPerspective( 
		fovy, 
		ratio, 
		near, 
		far 
		);
	

	// Definit une viewport où projeter le modele 
	camera->setViewport(new osg::Viewport(0,0,1000,500));
	// Annule la camera par defaut 
	camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
	// Definit la couleur de fond de la viewport de la camera 
	camera->setClearColor(osg::Vec4(0.5,0.5,0.5,1));
	// A METRE DANS MY VIEW viewer->getCamera()->setClearColor(osg::Vec4(0,0.7,0.7,1));

	// Event controller avec les touches
	camera->setEventCallback(new EventController());


	// DEFINITION DE LA LUMIERE
	osg::Light* light = new osg::Light();
	osg::LightSource * lightsource = new osg::LightSource();
	lightsource->setLight(light);

	double i1 = 0.3;
	double i2 = 0.5;
	light->setAmbient(osg::Vec4d(i1, i1, i1, 1));
	//light->setDiffuse(osg::Vec4d(i2, i2, i2, 1.0));
	light->setPosition(Vec4(3, 3,5,1));
	//light->setDirection(osg::Vec3d(0.0, 0.0, 0));
	light->setSpotCutoff(30.0);
	groupe->addChild(lightsource);

	osg::Light* light2 = new osg::Light();
	osg::LightSource * lightsource2 = new osg::LightSource();
	lightsource2->setLight(light2);

	double i3 = 0.4;
	double i4 = 0.5;
	light2->setAmbient(osg::Vec4d(i3, i3, i3, 1));
	light2->setDiffuse(osg::Vec4d(i4, i4, i4, 1.0));
	light2->setPosition(Vec4(0, 0, 5,1));
	//light2->setDirection(osg::Vec3d(0.0, 0.0, 0));
	//light2->setSpotCutoff(30.0);
	//groupe->addChild(lightsource2);

	camera->addChild(groupe);
}

void GameView::updateView(void){
	
	for (int i =0; i< this->objetsMap.size(); i++)
	{
		this->objetsMap[i]->updateByModel();
	}
	if(setUpCameraOnPlayerIfNecessary()) return;
}

osg::ref_ptr<osg::Camera> GameView::getCamera(){
	return camera;
}


void GameView::performMove(ref_ptr<Move> move){
	/*
	ref_ptr<PositionAttitudeTransform> pat = new PositionAttitudeTransform();
	ref_ptr<AnimationPath> myPath;
	ref_ptr<AnimationPathCallback> myAnimationCallback;
	ref_ptr<osg::Group> g = new osg::Group();
	*/
	vector<ref_ptr<PositionAttitudeTransform>> tabPat;
	vector<ObjectView*> tabContents;

	std::vector<osg::ref_ptr<CaseContents>> tab = move->getCasesContents();
	for(int a = 0; a < objetsMap.size(); a++){
		for(int i = 0; i < tab.size() ; i++){
			ref_ptr<CaseContents> model = objetsMap[a]->getModel();
			if(model.get() == tab[i].get()){

				ref_ptr<PositionAttitudeTransform> pat = new PositionAttitudeTransform();
				ref_ptr<AnimationPath> myPath;
				ref_ptr<AnimationPathCallback> myAnimationCallback;
				ref_ptr<osg::Group> g = new osg::Group();
				pat = this->objetsMap[a]->getPat();

				myPath = new AnimationPath();
				myPath->insert(START_TIME, 
					AnimationPath::ControlPoint(Vec3(objetsMap[a]->getX(),objetsMap[a]->getY(),0))); // Positionnement de départ
				myPath->insert(STOP_TIME, 
					AnimationPath::ControlPoint(Vec3(model->getX(),model->getY(),0),Quat(0,Z_AXIS))); // Positionnement d'arrivée
				myPath->setLoopMode(AnimationPath::NO_LOOPING);
				myAnimationCallback = new AnimationPathCallback(myPath.get());
				myAnimationCallback->setTimeMultiplier(8);
				pat->setUpdateCallback(myAnimationCallback);
				myAnimationCallback->reset();

				cout << "x graph " << this->objetsMap[a]->getX() << " x model " <<model->getX();

				//g->addChild(this->objetsMap[a]->getPat());
				//pat->addChild(this->objetsMap[a]->getPat());
				//pat = this->objetsMap[a]->getPat();
				//g->addChild = this->objetsMap[a]->getPat().get()->getChild(0);
				//pat->addChild(n);
				//cout << "AnimationPath : g->addChild";
				//tabPat.push_back(this->objetsMap[a]->getPat());
				//tabContents.push_back(objetsMap[a]);
			}
		}
	}

	this->updateView();
	/*
	pat->addChild(g);
	
	myPath = new AnimationPath();
	myPath->insert(START_TIME, 
		AnimationPath::ControlPoint(Vec3(move->getInitialX(),move->getInitialY(),0))); // Positionnement de départ
	myPath->insert(STOP_TIME, 
		AnimationPath::ControlPoint(Vec3(move->getEndX(),move->getEndY(),0),Quat(0,Z_AXIS))); // Positionnement d'arrivée
	myPath->setLoopMode(AnimationPath::NO_LOOPING);
	//myAnimationCallback->setTimeMultiplier(8);
	myAnimationCallback = new AnimationPathCallback(myPath.get());
	pat->setUpdateCallback(myAnimationCallback);
	myAnimationCallback->reset();
	*/

	//pat->setPosition(Vec3(move->getEndX(),move->getEndY(),0));


	/*
	double shift = 0;
	while(shift < 1){
		shift += 0.05;

		for(int i=0; i<tabContents.size(); i++){
			ObjectView* o = tabContents[i];
			o->setPosition(o->getX(), o->getY());
			//tabPat[i]->setPosition(Vec3(tabContents[i]->getX()+0.05,tabContents[i]->getY(),0));
		}
	}
	*/
}

GameView::~GameView(void)
{
}
