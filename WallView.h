#pragma once
#include <osg/Geode>
#include <osg/Geometry>
#include "box.h"
#include <osg/PositionAttitudeTransform>

// POUR TOUT COMMENTAIRE DES METHODES: @SEE OBJECT VIEW.H

class WallView
{
public:
	WallView(void);
	virtual ~WallView(void);

	static osg::ref_ptr<osg::Geode> getGeode();

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();
	void setPosition(int x, int y);

private:
	//Box model;

	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	static osg::ref_ptr<osg::Geode> geode;
};

