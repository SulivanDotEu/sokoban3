#include <osg/MatrixTransform>
#include <osgUtil/LineSegmentIntersector>
#include "ClickController.h"
#include "Bouton.h"
#include <iostream>
#include <osg/Switch>

using namespace osgUtil;

ClickController::ClickController(){

}

void ClickController::operator()(Node* node, NodeVisitor* nv)
{

	// Définition d'objets utilisés dans le switch ci-dessous
	ref_ptr<LineSegmentIntersector> intersector;
	IntersectionVisitor iv;
	LineSegmentIntersector::Intersection result;

	//La classe osgGA::GUIEventAdapter gere tous les types d'evenemens qui peuvent survenir
	std::list<ref_ptr<GUIEventAdapter>> events; // Structure de type liste (librairie standard)
	EventVisitor* ev = dynamic_cast<EventVisitor*>(nv); // Particularise le "visiteur" de noeuds
	if(ev) events = ev->getEvents(); // Recupere les "evenements" dans la liste
	ref_ptr<GUIEventAdapter> ea = events.back(); // Recupere le dernier element de la liste
	events.pop_back(); // Supprime l'element recupere de la liste
	switch(ea->getEventType())
	{
	case GUIEventAdapter::PUSH: // Pression sur la souris
		if(ea->getButton()==GUIEventAdapter::LEFT_MOUSE_BUTTON){ // bouton du milieu (roulette)
			// Intersecteur à partir du point de l'ecran (en pixels) au moment du click
			ref_ptr<LineSegmentIntersector> intersector = 
				new LineSegmentIntersector(Intersector::WINDOW,ea->getX(),ea->getY());
			// Visite des noeuds specifies pour determiner si des Drawables entrent en intersection
			// avec la "ligne de mire" du click de la souris
			IntersectionVisitor iv(intersector.get());
			// chaque noeud visite sera traite pour la selection via un click de la souris
			node->accept(iv);
			// si au moins un Drawable est selectionne
			if(intersector->containsIntersections()){
				// on recupere le plus proche (?) et ses coordonnees dans l'univers de dessin
				LineSegmentIntersector::Intersection result = intersector->getFirstIntersection();
				float x = result.getWorldIntersectPoint().x();
				float y = result.getWorldIntersectPoint().y();
				std::cout << "x : " << x << " - y : " << y << std::endl;
				// si on est sur le bouton graphique, on change la couleur du texte du message
				//if(x>AAA && x<AAA && y>AAA && y<AAA)

				// SAVE THE GAME (THE TROLL)
				if(x>-4.56 && x<-3.64 && y>-1 && y<0)
					Model::getInstance()->saveTheGame();
				// RETORE THE GAME
				else if(x>-3.48 && x<-2.52 && y>-1 && y<0)
					Model::getInstance()->restoreGame("test");

				// RELOAD LEVEL
				else if(x>-1.6 && x<-0.6 && y>-1 && y<0)
					Model::getInstance()->reloadLevel();
				// NEXT LEVEL
				else if(x>-0.5 && x<0.5 && y>-1 && y<0)
					Model::getInstance()->nextLevel();

				// MOVE LEFT
				else if(x>1.4 && x<2.4 && y>-1 && y<0)
					Model::getInstance()->move(LEFT);
				// MOVE DOWN
				else if(x>2.5 && x<3.5 && y>-1 && y<0)
					Model::getInstance()->move(DOWN);
				// MOVE RIGHT
				else if(x>3.6 && x<4.6 && y>-1 && y<0)
					Model::getInstance()->move(RIGHT);
				//MOVE UP
				else if(x>2.5 && x<3.5 && y>0.1 && y<1.1)
					Model::getInstance()->move(UP);
			}
		}
		break;
		
		case GUIEventAdapter::MOVE: // Déplacement de la souris
			cout << "COUCOU";
		// Intersecteur à partir du point de l'écran (en pixels) au moment du déplacement
		intersector = new LineSegmentIntersector(Intersector::WINDOW,ea->getX(),ea->getY());
		// Visite des noeuds spécifiés pour déterminer si des Drawables entrent en intersection
		// avec la "ligne de mire" du pointeur de la souris
		iv.setIntersector(intersector.get());
		// chaque noeud visité sera traité pour le "survol" par le pointeur de la souris,
		node->accept(iv);

		if(intersector->containsIntersections()){

		result = intersector->getFirstIntersection();
				float x = result.getWorldIntersectPoint().x();
				float y = result.getWorldIntersectPoint().y();

				std::cout << "x : " << x << " - y : " << y << std::endl;
				// SAVE THE GAME (THE TROLL)
				if(x>-4.56 && x<-3.64 && y>-1 && y<0){
					std::cout << "SAVE" << std::endl;
					MyView::getInstance()->getControlView()->save->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->save->getSwitchBox()->setValue(1,true);
				}else {
					std::cout << "SAVE2" << std::endl;
					MyView::getInstance()->getControlView()->save->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->save->getSwitchBox()->setValue(1,false);
				}
				// RETORE THE GAME
				if(x>-3.48 && x<-2.52 && y>-1 && y<0){
					std::cout << "RESTORE" << std::endl;
					MyView::getInstance()->getControlView()->restore->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->restore->getSwitchBox()->setValue(1,true);
				}else {
					std::cout << "RESTORE" << std::endl;
					MyView::getInstance()->getControlView()->restore->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->restore->getSwitchBox()->setValue(1,false);
				}

				// RELOAD LEVEL
				if(x>-1.6 && x<-0.6 && y>-1 && y<0){
					MyView::getInstance()->getControlView()->recommencer->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->recommencer->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->recommencer->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->recommencer->getSwitchBox()->setValue(1,false);
				}

				// NEXT LEVEL
				if(x>-0.5 && x<0.5 && y>-1 && y<0){
					MyView::getInstance()->getControlView()->suivant->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->suivant->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->suivant->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->suivant->getSwitchBox()->setValue(1,false);
				}

				// MOVE LEFT
				if(x>1.4 && x<2.4 && y>-1 && y<0){
					MyView::getInstance()->getControlView()->gauche->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->gauche->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->gauche->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->gauche->getSwitchBox()->setValue(1,false);
				}
				// MOVE DOWN
				if(x>2.5 && x<3.5 && y>-1 && y<0){
					MyView::getInstance()->getControlView()->bas->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->bas->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->bas->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->bas->getSwitchBox()->setValue(1,false);
				}
				// MOVE RIGHT
				if(x>3.6 && x<4.6 && y>-1 && y<0){
					MyView::getInstance()->getControlView()->droite->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->droite->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->droite->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->droite->getSwitchBox()->setValue(1,false);
				}
				//MOVE UP
				if(x>2.5 && x<3.5 && y>0.1 && y<1.1){
					MyView::getInstance()->getControlView()->haut->getSwitchBox()->setValue(0,false);
					MyView::getInstance()->getControlView()->haut->getSwitchBox()->setValue(1,true);
				}else {
					MyView::getInstance()->getControlView()->haut->getSwitchBox()->setValue(0,true);
					MyView::getInstance()->getControlView()->haut->getSwitchBox()->setValue(1,false);
				}

		}
		break;
		
	default:
		break;
	}

	traverse(node,nv);
}