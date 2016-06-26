#pragma once

#include <vector>
#include "ObjectView.h"
#include "Bouton.h"
#include <osg/Vec4>
#include <osgText/Text>


using namespace std;

// Objet permettant le controle lie au model, les services à l'utilisateur
//	 à savoir bouger, sauver, afficher du texte, etc...

class ControlView : public Referenced
{
public:
	ControlView();
	~ControlView(void);

	/// met à jour la vue selon l'etat du model
	/// pre : le modele est defini et initialise, l'objet est initialise
	/// post : l'interface graphique presente l'etat du modele
	void updateView();

	/// methode utilisee le modele pour informe la vue d'un message à afficher l'utilisateur
	/// pre : l'objet est initialise
	/// post : le message entre en parametre est affiche à l'utilisateur
	void newEvent(string);

	/// initialise l'objet
	/// post : les commandes et les messages à l'ecran sont initialies et disposes
	void init();

	/// la camera contient les differents boutons et le message.
	osg::ref_ptr<osg::Camera> camera;

	/// renvoie la camera
	/// pre : la camera est initialisee
	osg::ref_ptr<osg::Camera> getCamera();

	/// declaration des boutons graphiques
	ref_ptr<Bouton> save ;
	ref_ptr<Bouton>  restore ;

	ref_ptr<Bouton>  recommencer ;
	ref_ptr<Bouton>  suivant ;

	
	ref_ptr<Bouton>  haut  ;
	ref_ptr<Bouton>  bas  ;
	ref_ptr<Bouton>  droite ;
	ref_ptr<Bouton>  gauche  ;

protected:
	/// contient le texte a afficher
	ref_ptr<osgText::Text> unTexte;



};

