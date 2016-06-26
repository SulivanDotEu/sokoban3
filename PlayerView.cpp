#include "PlayerView.h"
#include <iostream>

osg::ref_ptr<osg::Geode> PlayerView::geode = 0;

PlayerView::PlayerView(CaseContents* model) : ObjectView(model)
{
	std::cout << "BOXVIEW CONSTRUCTEUR" << "\n";
	pat = 0;
	// Instancie un noeud de geometrie pour accueillir le carre 
	pat = this->getPat();
	pat->addChild(PlayerView::geode);
	//pat->setPosition(osg::Vec3(0,0,0));
}


PlayerView::~PlayerView(void)
{
}


void PlayerView::setPosition(double x, double y){
	this->x=x;
	this->y=y;
	std::cout << "---- X model : " << this->model->getX() << " current x " << this->getX() <<std::endl;
	std::cout << "---- Y model : " << this->model->getY() << " current y " << this->getY() <<std::endl;
	pat = this->getPat();
	pat->setPosition(osg::Vec3(x,y,0));
}

osg::ref_ptr<osg::Geode> PlayerView::getGeode(){
	std::cout << "PlayerView::getGeode" << "\n";
	if(PlayerView::geode != 0){
		std::cout << "if(PlayerView::geode != 0) >>> YES" << "\n";
		return PlayerView::geode;
	}
	std::cout << "if(PlayerView::geode != 0) >>> NO" << "\n";

	// Instantiation d'une geometrie 
	osg::ref_ptr<osg::Geometry> pyramidGeometry  = new osg::Geometry;

	// Les 4 sommets du carre sont stockes dans un Vec3Array 
	osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;

	vertexArray->push_back( osg::Vec3( -.5, -.5, -.5) ); // devant à gauche 
	vertexArray->push_back( osg::Vec3(+.5, -.5, -.5) ); // devant à droite 
	vertexArray->push_back( osg::Vec3(+.5,+.5, -.5) ); // derriere à droite 
	vertexArray->push_back( osg::Vec3( -.5, +.5, -.5) ); // derriere à gauche 
	vertexArray->push_back( osg::Vec3(0, 0,+.5) ); // sommet 




	// Les couleurs à associer aux sommets sont stockes dans un Vec4Array 
	osg::ref_ptr<osg::Vec4Array> colorArray = new osg::Vec4Array;
	colorArray->push_back(osg::Vec4(1,0,0,1));
	colorArray->push_back(osg::Vec4(0,1,0,1));
	colorArray->push_back(osg::Vec4(0,0,1,1));
	colorArray->push_back(osg::Vec4(1,1,0,1));
	colorArray->push_back(osg::Vec4(1,0,0,1));



	// Le vecteur normal à associer au carre est stocke dans un Vec3Array 
	osg::ref_ptr<osg::Vec3Array> normalArray = new osg::Vec3Array;
	normalArray->push_back(osg::Vec3(0,0,1));

	// Une couleur par sommet 
	pyramidGeometry->setColorBinding(osg::Geometry::/*BIND_PER_VERTEX*/BIND_PER_PRIMITIVE);
	// Un vecteur normal pour l'ensemble 
	pyramidGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	// Definit le tableau des sommets à utiliser 
	pyramidGeometry->setVertexArray(vertexArray);
	// Definit le tableau des couleurs à utiliser 
	pyramidGeometry->setColorArray(colorArray);
	// Definit le tableau des vecteurs normaux à utiliser 
	pyramidGeometry->setNormalArray(normalArray);

	// Explicite comment il faut utiliser les sommets pour creer la surface requise 
	osg::ref_ptr<osg::DrawElementsUInt> drawElements =
		new osg::DrawElementsUInt(GL_TRIANGLES);

	// face 1
	drawElements->push_back(0);
	drawElements->push_back(1);
	drawElements->push_back(4);

	// face 2
	drawElements->push_back(1);
	drawElements->push_back(2);
	drawElements->push_back(4);

	// face 3
	drawElements->push_back(2);
	drawElements->push_back(3);
	drawElements->push_back(4);

	// face 4
	drawElements->push_back(3);
	drawElements->push_back(0);
	drawElements->push_back(4);

	pyramidGeometry->addPrimitiveSet(drawElements);


	osg::ref_ptr<osg::Geode> unePyramide = new osg::Geode;
	// Desactive le modele d'eclairage
	osg::StateSet* stateset = unePyramide->getOrCreateStateSet();
	// active la projection de lumiere
	stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON);
	// Ajoute le carre comme dessin associe au noeud de geometrie 
	unePyramide->addDrawable(pyramidGeometry.get());

	PlayerView::geode = unePyramide;

	return PlayerView::geode;
}

osg::ref_ptr<osg::PositionAttitudeTransform> PlayerView::getPat(){
	std::cout << "BoxView::getPat" << "\n";
	if(pat != 0){
		std::cout << "if(pat != 0) >>> YES" << "\n";
		return pat;
	}
	std::cout << "if(pat != 0) >>> NO" << "\n";

	pat =
		new osg::PositionAttitudeTransform();
	pat->addChild(PlayerView::getGeode());


	return pat;
}

