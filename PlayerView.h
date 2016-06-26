#pragma once
#include <osg/Geode>
#include <osg/Geometry>
#include "box.h"
#include "ObjectView.h"
#include "CaseContents.h"

class PlayerView : public ObjectView
{
public:
	PlayerView(CaseContents* c);
	~PlayerView(void);

	static osg::ref_ptr<osg::Geode> getGeode();

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();
	void setPosition(double x, double y);

private:
	//Box model;

	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	static osg::ref_ptr<osg::Geode> geode;
};

