#include "Game.h"
#include "Wall.h"
#include "Box.h"
#include <iostream>
#include <sstream> 

Game::Game(void)
{

}

Game::Game(string name)
{	//Initialisation des variables
	this->name = name;
	this->player = new Player();
	this->win = false;
	this->levelNumber = 0;
	this->deplacementP = 0;
	this->deplacementB = 0;
	loadListOfLevels(name);
	loadMap();
	cout << "NEW GAME " << name << endl;
}


Game::~Game(void)
{
	player = 0;
	cout << "DELETE GAME\n";
}

ref_ptr<Case> Game::getCase(int i, int j)
{
	return map[i][j];
}

ref_ptr<Player> Game::getPlayer()
{
	return player;
}

bool Game::isHeAWinner()
{	//Parcours des socles
	for (int i = 0; i< receivers.size(); i++)
	{	//Si un socle n'est pas complete, alors le joueur n'a pas gagne
		if (receivers[i]->isCompleted() == false) return false;
	}
	//Sinon c'est qu'il a gagne
	return true;
}

void Game::loadMap()
{
	int xSize, ySize;
	char caractere;
	string contenu;
	deplacementB = 0;
	deplacementP = 0;
	//ouverture du fichier
	ifstream fichier(levels[levelNumber]+".txt", ios::in);
	//si le fichier s'est ouvert correctement
	if (fichier){

		//Chargement de la carte
		fichier >> this;

		//Fermeture du fichier
        fichier.close();
	}
	//S'il y a eu une erreur lors de l'ouverture du fichier
	else 
	{
		cerr<<"ERROR MAP LOADING"<<endl;
	}
}

ostream & operator<<(ostream& os, const Game& c){
	//On retient la taille de la carte courante
	int x = c.map.size();
	int y = c.map[0].size();

	//On indique que c'est une sauvegarde
	os<<"saved"<<endl;

	//Le nom du fichier contenant la liste des niveaux est indique ainsi que le numero du niveau courant
	os<<c.name<< " "<< c.levelNumber<<endl;

	os<<c.deplacementP<< " "<< c.deplacementB<<endl;

	//On indique la taille de la carte
	os << x << " "<< y << endl;

	//Parcour de la carte
	for (int i =0; i< x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				//Si la case n'est pas vide
				if (c.map[i][j]->getContents() !=0)
				{	
					//Si la case contient le joueur
					if (dynamic_cast<Player*> (c.map[i][j]->getContents().get())){
						//Si en plus la case est un socle
						if (c.map[i][j]->isReceiver()){
							os<<"q";
						}
						//Sinon
						else os<<"p";
					}
					//Si la case contient un boite
					else if (dynamic_cast<MyBox*> (c.map[i][j]->getContents().get())){
						//Si en plus la case est un socle
						if (c.map[i][j]->isReceiver()){
							os<<"f";
						}
						//Sinon
						else os<<"b";
					}
					//Si la case contient un mur
					else if (dynamic_cast<Wall*> (c.map[i][j]->getContents().get())){
						os <<"w";
					}
					//Sinon
					else os<<"?";

				}
				//Si la case est vide et que c'est un socle
				else if (c.map[i][j]->isReceiver())
				{
					os<<"r";
				}
				//Sinon c'est juste une case vide
				else os << "c";
			}
			os<<endl;
		}
	return(os);
}

 Game* operator>>(istream& os, Game* c){
	
	int xSize, ySize;
	char caractere;
	string contenu;
	vector<ref_ptr<Case>> rec;

	//Recuperation de la premiere ligne
	getline(os, contenu);

	//Si le fichier est une sauvegarde
	if (contenu == "saved"){
		//On recupere le nom du fichier qui liste les niveaux
		os >> contenu;
		//On l'assigne
		c->name = contenu;
		//On recupere le numero du niveau sauvegarde
		os >> contenu;
		//On le converti et on l'assigne
		c->levelNumber = atoi(contenu.c_str());
		//On demande de charger la liste
		c->loadListOfLevels(c->name);
		
		//On charge le score
		os >> contenu;

		c->deplacementP = atoi(contenu.c_str());

		os >> contenu;

		c->deplacementB = atoi(contenu.c_str());
	}

	//Si ce n'est pas une sauvegarde ni un fichier de carte
	else if (contenu != "map") return NULL;

	//On recupere la taille de la carte
	os >> contenu;
	xSize = atoi(contenu.c_str());
	os >> contenu;
	ySize = atoi(contenu.c_str());
	
	//Creation du vecteur qui contiendra toute la map
	vector<vector<ref_ptr<Case>>> temp(xSize, vector<ref_ptr<Case>>(ySize)); 
	
	//Remplissage de la map
	for (int i =0; i< xSize || os.eof(); i++)
	{
		for (int j = 0; j < ySize || os.eof(); j++)
		{
			os.get(caractere);
			switch(caractere)
			{
				//Simple mur
				case 'w' : temp[i][j] = new Case(i,j, new Wall(), false); break;
				//Case vide
				case 'c' : temp[i][j] = new Case(i,j, 0, false); break;
				//Boite
				case 'b' : temp[i][j] = new Case(i,j, new MyBox(), false); break;
				//Joueur
				case 'p' : temp[i][j] = new Case(i,j, c->getPlayer(), false); break;
				//Joueur sur un socle						
				case 'q' : temp[i][j] = new Case(i,j, c->getPlayer(), true); rec.push_back(temp[i][j]);break;//Sauvegarde des socles dans un vecteur
				//Socle
				case 'r' : temp[i][j] = new Case(i,j, 0, true); rec.push_back(temp[i][j]);break;//Sauvegarde des socles dans un vecteur
				//Boite sur un socle
				case 'f' : temp[i][j] = new Case(i,j, new MyBox(), true);rec.push_back(temp[i][j]);break;//Sauvegarde des socles dans un vecteur
				//On ignore les autres caracteres
				default : j--; break;
			}
		}
	}
	c->receivers = rec;
	c->map = temp;
    return (c);

}

 bool Game::loadListOfLevels(string fileName)
{	//On vide le vecteur de niveau
	levels.clear();

	//Ouverture du fichier
	ifstream fichier(fileName+".txt", ios::in);

	//Si le fichier s'est bien ouvert
	if (fichier){
		string ligne;
	
		//Tant qu'on peut recuperer une ligne
		while(getline(fichier, ligne)){
			//Le nom du niveau est insere dans le vecteur
			levels.push_back(ligne);
		}
		//Tout s'est bien passe
		return true;
	}
	//Erreur d'ouverture du fichier
	else {
		cerr<<"ERROR LIST OF LEVELS LOADING"<<endl;
	}
}

 bool Game::nextLevel(){
	//Sinon le niveau courant est le dernier on renvoie false
	if (levelNumber + 1 >= levels.size()) return false;

	//Sinon on passe au niveau suivant dans la liste
	levelNumber++;

	//On charge la carte
	loadMap();

	return true;
}

 bool Game::reloadLevel(){
	 //On recharge la carte courante
	 loadMap();
	 return true;
 }

 void Game::addDeplacementP(){
	 deplacementP++;
 }

 void Game::addDeplacementB(){
	 deplacementB++;
 }

 string Game::getNumberDeplacementB(){
	 //Conversion d'un integer en string
	 ostringstream convert; 
	 convert << deplacementB;
	 return convert.str();
 }

 string Game::getNumberDeplacementP(){
	 //Conversion d'un integer en string
	 ostringstream convert; 
	 convert << deplacementP;
	 return convert.str();
 }

 int Game::getSizeX(){
	return map.size();
}

 int Game::getSizeY(){
	return map[0].size();
}