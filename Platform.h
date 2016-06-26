#pragma once
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>

// POUR TOUT COMMENTAIRE DES METHODES: @SEE OBJECT VIEW.H


class Platform
{
public:
	Platform(void);
	virtual ~Platform(void);

	static osg::ref_ptr<osg::Geode> getGeode();

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();
	void setPosition(int x, int y);

private:

	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	static osg::ref_ptr<osg::Geode> geode;
};

