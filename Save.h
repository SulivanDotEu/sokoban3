#pragma once
#include "ObjectView.h"
#include <osg/PositionAttitudeTransform>


class SaveBoutonView
{
public:
	SaveBoutonView(void);
	~SaveBoutonView(void);

	static osg::ref_ptr<osg::Geode> getGeode();

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();
	void setPosition(int x, int y);


private:
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	static osg::ref_ptr<osg::Geode> geode;

};