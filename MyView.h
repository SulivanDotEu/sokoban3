#pragma once

#include <vector>
#include "GameView.h"
#include "controlView.h"
#include "LogView.h"
#include "ObjectView.h"
#include "CaseContents.h"
#include "Move.h"
#include <osg/Vec4>
#include <osgViewer/Viewer>


const osg::Vec4 ROUGE = osg::Vec4(1,0,0,1);
const osg::Vec4 VERT = osg::Vec4(0,1,0,1);
const osg::Vec4 BLEU = osg::Vec4(0,0,1,1);
const osg::Vec4 JAUNE = osg::Vec4(0,0,1,1);
const osg::Vec4 MAUVE = osg::Vec4(0,0,1,1);
const osg::Vec4 CYAN = osg::Vec4(0,1,1,1);


using namespace osg;

class MyView
{
public:
	MyView();
	~MyView(void);

	/// met à jour la vue selon l'etat du model
	/// pre : le modele est defini et initialise, l'objet est initialise
	/// post : l'interface graphique presente l'etat du modele
	void updateView();

	
	/// methode utilisee le modele pour informe la vue d'un message à afficher
	/// à l'utilisateur
	/// la methode relegue l'exectuation au ControLView
	/// pre : l'objet est initialise
	/// post : le message entre en parametre est affiche à l'utilisateur
	void newEvent(std::string);

	
	/// initialise la vue selon le modele quand un nouveau jeu est lance
	/// nouveau jeu = nouvelle map
	/// Pre : camera est initialise et contient les elements dans l'ancien etat du modele
	/// post : l'interface graphique affiche a present l'etat du jeu
	void newGame();

	/// initialise la vue selon le modele
	/// POST : l'interface graphique affiche l'etat du modele et tout les elements
	///		graphiques sont initialises
	void start();

	/// contient la vue du jeu et des commandes
	ref_ptr<osgViewer::Viewer> viewer;

	/// methode implementant le patern singleton
	static MyView *getInstance();


	/// zoom la vue du jeu
	/// post : la vue du jeu est rapprochee, la camera garde les autres proprietes
	///		SAUF si le zoom est important, la camera est situe au dessus du joueur, vers le joueur
	void zoom();

	/// zoom la vue du jeu
	/// post : la vue du jeu est eloignee, la camera garde les autres proprietes
	///		SAUF si le zoom RESTE important, la camera est situe au dessus du joueur, vers le joueur
	void dezoom();

	// gestion de la translation pour le mouvement d'objet sur la map
	void performMove(ref_ptr<Move>);

	ref_ptr<ControlView> getControlView(){return controlView;};

protected:
	/// objet contenant la vue du jeu
	ref_ptr<GameView> gameView;

	/// objet contenant la vue des messages a afficher
	ref_ptr<LogView> logView;

	/// objet contenant la vue des commandes
	ref_ptr<ControlView> controlView;

	/// objet contenant les vue
	osg::ref_ptr<osg::Group> root;
	
private:

	/// objet contenant l'unique instance du singleton
	static MyView* instance;


	
};

