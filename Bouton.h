#pragma once
#include "ObjectView.h"
#include <osg/PositionAttitudeTransform>
#include <osg/Vec4>
#include <osg/Switch>

using namespace osg;

class Bouton : public Referenced
{
public:
	Bouton(std::string, std::string);
	~Bouton(void);

	osg::ref_ptr<osg::Geode> getGeode();
	osg::ref_ptr<osg::Geode> getGeode2();
	ref_ptr<Switch> getSwitchBox(){return switchBox;};

	osg::ref_ptr<osg::PositionAttitudeTransform> getPat();

	void setPosition(int x, int y);


private:
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	osg::ref_ptr<osg::Geode> geode;
	osg::ref_ptr<osg::Geode> geode2;
	std::string textureNameFile;
	std::string textureNameFile2;
	ref_ptr<Switch> switchBox;

};