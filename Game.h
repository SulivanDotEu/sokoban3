#pragma once

#include <string>
#include "Player.h"
#include "Case.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <osg\Array>

using namespace std;
using namespace osg;

class Game : public Referenced
{
protected :
	
public:
	///Sauve l'etat du jeu
	friend ostream & operator<<(ostream& os, const Game& c);

	///Restaure l'etat d'un jeu
	friend Game* operator>>(istream& os, Game* c);

	///Constructeur par defaut
	Game(void);
	~Game(void);
	///Constructeur avec en parametre le nom du fichier qui contient la liste des niveaux
	Game(std::string);

	////Renvoie true si toutes le boites sont sur un socle, false sinon
	bool isHeAWinner();

	///Renvoie la case qui correspond aux coordonnees passees en parametre
	ref_ptr<Case> getCase(int,int);

	///Renvoie le joueur
	ref_ptr<Player> getPlayer();

	///Renvoie true si le chargement du niveau suivant s'est effectuefalse si non
	bool nextLevel();

	///Renvoie true si le rechargement du niveau courant s'est bien effectue, false sinon
	bool reloadLevel();
	///Augmente le compteur de deplacement du joueur de 1
	void addDeplacementP();
	///Augmente le compteur du deplacemet des boites de 1
	void addDeplacementB();
	///Recupere sous forme de string le nombre de deplacement du joueur
	string getNumberDeplacementP();
	///Recupere sous forme de string le nombre de deplacement des boites
	string getNumberDeplacementB();
	///Renvoie la coordonnee X de la map
	int getSizeX();
	///Renvoie la coordonnee Y de la map
	int getSizeY();

private:
	///Nom du fichier contenant la liste des niveaux
	string name;

	///Vecteur contenant le nom des fichiers des niveaux
	vector<string> levels;

	///Position courante dans la liste des niveaux
	int levelNumber;

	///Nombre de deplacements du joueur
	int deplacementP;
	
	///Nombre de deplacements des boites
	int deplacementB;

	///Vecteur contenant la carte du niveau
	vector<vector<ref_ptr<Case>>> map;

	///Vecteur contenant les cases socles
	vector<ref_ptr<Case>> receivers;

	///Joueur
	ref_ptr<Player> player;

	///Boolean renseignant si le niveau est fini ou non
	bool win;

	///Fonction de chargement de la carte courante
	void loadMap();

	///Fonction de chargement de la liste des niveaux
	bool loadListOfLevels(string);
};

