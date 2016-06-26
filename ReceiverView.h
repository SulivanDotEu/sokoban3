#pragma once
#include "ObjectView.h"
#include <osg/PositionAttitudeTransform>

// POUR TOUT COMMENTAIRE DES METHODES: @SEE OBJECT VIEW.H

class ReceiverView
{
public:
	ReceiverView(void);
	~ReceiverView(void);

	static osg::ref_ptr<osg::Geode> getGeode();

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();
	void setPosition(int x, int y);


private:
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	static osg::ref_ptr<osg::Geode> geode;

};
