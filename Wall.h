#pragma once
#include "casecontents.h"
class Wall :
	public CaseContents
{
public:
	Wall(void);
	///Demande de deplacement; renvoie false par defaut
	virtual bool move(int dir){
		return false;
	};

protected:
	~Wall(void);
};

