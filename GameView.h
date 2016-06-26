#pragma once

#include <vector>
#include "ObjectView.h"
#include "Move.h"
#include <osg/Vec4>

using namespace osg;

/// cette objet contient la vue du modele, à savoir le joueur, mur, boite et recepteur.
/// on y trouve aussi les dalles composant le sol et tout les autres elemants graphiques
/// lie au jeu

class GameView : public Referenced
{

protected :
	~GameView(void);

	/// coordonnees de la camera affichant la scene
	double cam_x;
	double cam_y;
	double cam_z;

	/// coordonnees precisant le point utilise par la camera pour oriente l'objectif
	osg::Vec3 center;
	/// coordonnees utilise par la camera affichant la scene
	osg::Vec3 up;

	/// affiche la camera au dessus de joueur si le zoom est important
	/// post :  si le zoom est important, la camera est centre sur le joueur, juste au dessus de lui
	bool setUpCameraOnPlayerIfNecessary();

	ref_ptr<osg::Group> groupe;

public:
	GameView();
	/// see View.h::updateVIew()
	void updateView();

	/// initialise l'interface graphique et ses composants decrivant le model
	/// post : l'interface montre l'etat du jeu (modele)
	void init();

	/// camera contenant les elements graphiques du jeu
	ref_ptr<Camera> camera;

	/// renvoie la camera
	/// pre : la camera est initialisee
	ref_ptr<Camera> getCamera();

	/// vecteurs contenant les objets de la map,
	/// boite, murs, joueurs.
	std::vector<ObjectView*> objetsMap;

	/// zoom la vue du jeu
	/// post : la vue du jeu est rapprochee, la camera garde les autres proprietes
	///		SAUF si le zoom est important, la camera est situe au dessus du joueur, vers le joueur
	void zoom();

	/// zoom la vue du jeu
	/// post : la vue du jeu est eloignee, la camera garde les autres proprietes
	///		SAUF si le zoom RESTE important, la camera est situe au dessus du joueur, vers le joueur
	void dezoom();

	void performMove(ref_ptr<Move>);
};



