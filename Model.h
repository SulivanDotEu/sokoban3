#pragma once

#include "MyView.h"
#include <osg\Array>
#include "Game.h"
#include "Move.h"
#include <string>
#include <stack>

#define LEFT 10
#define RIGHT 20
#define UP 30
#define DOWN 40

using namespace osg;
using namespace std;

class Model
{
public:
	Model(void);
	~Model(void);

	///Renvoie le singleton de la classe
	static Model *getInstance();

	///Ordonne un deplacement
	void move(int);

	///Instancie un nouveau jeu avec en parametre le nom du fichier contenant la liste des niveaux
	void newGame(std::string);

	///Renvoie la case correspondant aux coordonnees passees en parametre
	ref_ptr<Case> getCase(int,int);

	///Renvoie la taille de la map en x
	int getSizeX();

	///Renvoie la taille de la map en y
	int getSizeY();

	///Attache un listener au model
	void setListener(MyView* v);

	///Sauvegarde l'etat du jeu en cours. Renvoie true si la sauvegarde s'est effectuee. False sinon
	bool saveTheGame();

	///Restaure la sauvegarde dont le nom est passe en parametre. Renvoie true si la restauration s'est bien effectuee. False sinon
	bool restoreGame(string);

	///Renvoie le joueur
	const ref_ptr<Player> getPlayer();

	///Demande le rechargement du niveau courant. Renvoie true si ca s'est passe correctement. False sinon
	bool reloadLevel();

	///Demande le chargmement du niveau suivant. Renvoie true si ca s'eet passe correctement. False sinon
	bool nextLevel();
	///Nombre de deplacements des boites
	void addDeplacementB();
	///Sauve l'etat du jeu
	void Do();
	///Remet le jeu dans son etat precedent
	void Undo();

	

private:
	///Instance unique (singleton)
	static Model* instance;	
	///Initialise ou reinitialise la pile des undos
	void setNewUndo();
	///Instance du jeu en cours
	ref_ptr<Game> game;
	///Listener
	MyView* listener;
	///Pile des etats du jeu
	stack<string> undoStack;
	///Etat courant du jeu
	string currentState;
	// objet pour gérer un move dans la vue, permettre la translation de 
	//plusieurs objet en meme temps
	ref_ptr<Move> moveObject;

public:
	//renvoie l'objet move
	ref_ptr<Move> getMove(){return moveObject;};
};

