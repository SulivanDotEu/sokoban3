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
#include "ClickController.h"
#include "ReceiverView.h"
#include <iostream>



MyView* MyView::instance = 0;

//Singleton
MyView *MyView::getInstance(){
	if (instance == 0)
		instance = new MyView();

	return instance;
}

MyView::MyView(void){
}

void MyView::newEvent(std::string s){
	this->logView->newEvent(s);
}

void MyView::start()
{

	// construction des vues : du jeu, des commandes et des logs
	gameView = new GameView();
	controlView = new ControlView();
	logView = new LogView();

	gameView->init();
	controlView->init();
	logView->init();	

	// Definir un viewer 
	viewer = new osgViewer::Viewer();
	// Positionne et dimensionne la fenêtre
	viewer->setUpViewInWindow(32, 32, 1000, 700); // en pixels

	viewer->getCamera()->setAllowEventFocus(false);
	//viewer->addEventHandler(new EventHandler);

	// on recupere les camera pour le mettre dans le viewer
	osg::ref_ptr<osg::Camera> cameraGame = gameView->getCamera();
	osg::ref_ptr<osg::Camera> cameraControl = controlView->getCamera();
	osg::ref_ptr<osg::Camera> cameraLog = logView->getCamera();

	// INTRODUCTION DES CAMERAs
	
	root = new osg::Group();
	root->addChild(cameraLog);
	root->addChild(cameraGame);
	root->addChild(cameraControl);
	
	viewer->setSceneData(root);

	

	viewer->run();
	/*
	while (!viewer->done()) {
		//rotate->setMatrix(osg::Matrix::rotate(angle, axis));
		//viewer->frame(); angle += 0.05;
		viewer->frame();
		//Model::getInstance()->move(RIGHT);
		//Model::getInstance()->move(LEFT);

	}
	*/
	//viewer->run();

}

void MyView::updateView(void){
	gameView->updateView();	
}

void MyView::newGame(){
	osg::ref_ptr<osg::Camera> camera = gameView->getCamera();
	//root->removeChild(camera);

	//gameView = 0;
	//gameView = new GameView();
	gameView->init();
	camera = gameView->getCamera();
	//root->addChild(camera);
	//viewer->setSceneData(root);
	//viewer->run();
}

void MyView::zoom(){
	gameView->zoom();
}

void MyView::dezoom(){
	gameView->dezoom();
}

void MyView::performMove(ref_ptr<Move> move){
	gameView->performMove(move);
}