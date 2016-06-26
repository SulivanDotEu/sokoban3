#include "Model.h"
#include <iostream>
#include <ostream>
#include <iomanip>
#include <sstream>

Model *Model::instance = 0;

Model::Model(void)
{
}


Model::~Model(void)
{
	delete instance;
	game = 0;
}
//Singleton
Model *Model::getInstance(){
	if (instance == 0)

		instance = new Model();

	return instance;
}

void Model::setListener(MyView* v){
	this->listener = v;
}

void Model::newGame(string name)
{
	this->game = new Game(name);
	setNewUndo();
}

ref_ptr<Case> Model::getCase(int x, int y)
{
	return game->getCase(x,y);
}


int Model::getSizeX(){
	return game->getSizeX();
}

int Model::getSizeY(){
	return game->getSizeY();
}


void Model::move(int dir){
	//this->listener->setUpInitialPosition(this->game->getPlayer()->getX(), this->game->getPlayer()->getY());
	moveObject = new Move();
	moveObject->setUpInitialPosition(this->game->getPlayer()->getX(), this->game->getPlayer()->getY());
	
	//Si le joueur a gagne, on n'autorise plus de mouvement
	if (this->game->isHeAWinner()) return;
	//Deplacement du joueur
	if (this->game->getPlayer()->move(dir)){
	
		//Si le deplacement s'est effactue
		Do();
		//On ajoute 1 au compteur
		this->game->addDeplacementP();

		//Suppression du dernier message
		this->listener->newEvent("Player : "+game->getNumberDeplacementP()+"\nBox : "+game->getNumberDeplacementB());
		std::cout<<"PLAYER x "<<game->getPlayer()->getX()<<" y"<<game->getPlayer()->getY()<<endl;

		//Update de la vue
		//this->listener->updateView();
		this->listener->performMove(moveObject);

		//Apres chaque deplacement on test si le joueur a gagne
		if (this->game->isHeAWinner())
		{
			std::cout << "YOU WIN\n";
			this->listener->newEvent("YOU WIN\nClick to go to\nthe next level");
			return;
		}
	}
	//Sinon c'est que le deplacement etait interdit
	else this->listener->newEvent("Forbidden move");
}

bool Model::saveTheGame(){
	//Ouverture du fichier
	ofstream fichier("test.txt", ios::out | ios::trunc); 
	
	//Si le fichier s'est bien ouvert
    if(fichier)
	{
		//Sauvegarde du jeu
		fichier << *game;
		//Fermeture du fichier
		fichier.close();
		//Affichage du message
		this->listener->newEvent("Game saved");
	}
	else {
		this->listener->newEvent("ERROR WHILE\nSAVING THE GAME");
	}
	return true;
}


bool Model::restoreGame(string fileName){
	//Ouverture du fichier
	ifstream fichier(fileName+".txt", ios::in);
	//Si le fichier s'est bien ouvert
	if (fichier){
		//Restauration du jeu
		fichier >> game;
		//Reinitialise la pile des undos
		setNewUndo();
		//Affichage du message
		this->listener->newEvent("Game restored");
		//Update de la vue
		this->listener->newGame();
		//Fermeture du fichier
		fichier.close();
	}
	//Sinon
	else {
		this->listener->newEvent("ERROR WHILE\nRESTORING THE GAME");
		}
	return true;
}

const ref_ptr<Player> Model::getPlayer(){
	return game->getPlayer();
}

bool Model::reloadLevel(){
	this->game->reloadLevel();
	//Reinitialise la pile des undos
	setNewUndo();
	this->listener->newEvent("Game reloaded");
	//this->listener->updateView();
	this->listener->newGame();
	return true;
}

bool Model::nextLevel(){
	//Si le joueur n'a pas gagne
	if (this->game->isHeAWinner() == false){
		this->listener->newEvent("You have to win\nbefore going\nto the next level");
		return false;
	}
	//Sinon on charge le niveau suivant
	if (this->game->nextLevel())
	{	//Reinitialise la pile des undos
		setNewUndo();
		this->listener->newEvent("Next level");
		//Update de la vue
		this->listener->newGame();
	}
	//Si le jeu est fini
	else this->listener->newEvent("There is no\nmore levels left");
	return true;
}

void Model::addDeplacementB(){
	this->game->addDeplacementB();
}

void Model::Do(){
	//Si il y a un etat courant on le met dans la pile
	if (!this->currentState.empty()) 
		undoStack.push(this->currentState);
	//Sauvegarde du nouvel etat
	stringstream ss(stringstream::out);
	ss << *game;
	//Cet etat devient l'etat courant
	this->currentState = ss.str();
}

void Model::Undo(){
	//Si la pile est vide on fait rien
	if (this->undoStack.empty()) return;
	
	//Recuperation de l'etat precedent
	string undo = this->undoStack.top();
	//Suppression de cet etat dans la pile
	this->undoStack.pop();


	//Remet le jeu à son etat precedent
	stringstream ss(undo, stringstream::in);
	ss >> game;
	//Cet etat devient l'etat courant
	this->currentState = undo;
	//Affichage du message
	this->listener->newEvent("Player : "+game->getNumberDeplacementP()+"\nBox : "+game->getNumberDeplacementB());
	//Update de la vue
	this->listener->newGame();
	//Fermeture du fichier
}

void Model::setNewUndo(){
	//Vide la pile des undos
	while(!undoStack.empty()){this->undoStack.pop();}
	//Reinitialise à rien l'etat courant
	this->currentState.clear();
	//Sauve le nouvel etat courant
	Do();
}