#pragma once
#include "casecontents.h"
class Player :
	public CaseContents
{

protected :
	~Player(void);
public:
	Player(void);
	virtual bool move(int);
};

