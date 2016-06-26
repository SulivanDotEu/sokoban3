#pragma once

#include "CaseContents.h"
#include <string>
#include <osg\Array>

using namespace osg;

class Case : public Referenced
{
public:
	///Constructeur par defaut
	Case(void);
	/**
	*Constructeur recevant en parametre les coordonnees de la case et son contenu
	*ainsi qu'un boolean renseignant si cette case est un socle ou non
	*/
	Case(int x, int y, CaseContents *contents, bool receiver);

	///Renvoie le contenu de la case
	ref_ptr<CaseContents> getContents();

	///Assigne un nouveau contenu à la case
	void setContents(CaseContents *);

	///Renvoie la coordonnee x
	int getX();

	///Renvoie la coordonnee y
	int getY();
	/**
	*Fait le deplacement
	*Renvoie true si le deplacement est possible et effectue
	*false si le deplalcement est impossible
	*/
	bool move(int);

	///Renvoie true si la case est vide; false sinon
	bool isEmpty();

	/**
	*Renvoie true si la case est un socle et qu'elle contient une box
	*false sinon
	*/
	bool isCompleted();

	/**
	*Renvoie true si la case est un socle
	*false sinon
	*/
	bool isReceiver();

protected:
	~Case(void);
	///Renvoie à quel tpye correspond le contenu de la case
	std::string type();

	ref_ptr<CaseContents>contents;
	int x;
	int y;
	bool receiver;
	bool completed;
};