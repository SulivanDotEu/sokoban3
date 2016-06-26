#pragma once
#include "casecontents.h"
class MyBox :
	public CaseContents
{
public:
	MyBox(void);
	~MyBox(void);
	virtual bool move(int);
};

