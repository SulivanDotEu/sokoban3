#pragma once
#include <vector>
#include "ObjectView.h"
#include <osg/Vec4>

using namespace osg;

class Move : public Referenced
{
public:
	Move(void);
	~Move(void);
	void setUpInitialPosition(int, int);
	void setUpEndPosition(int, int);

	int getInitialX(){return initialX;};
	int getInitialY(){return initialY;};
	int getEndX(){return endX;};
	int getEndY(){return endY;};

	void add(ref_ptr<CaseContents>);
	std::vector<osg::ref_ptr<CaseContents>> getCasesContents(){return tableau;};

private:
	// position initial de la translation
	int initialX;
	int initialY;
	// position final de la translation
	int endX;
	int endY;
	// tableau contenant les objet a translaté
	std::vector<osg::ref_ptr<CaseContents>> tableau;
};
