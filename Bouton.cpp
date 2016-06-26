#include "Bouton.h"
#include <iostream>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/TexEnv>
#include <osg/Material>
#include <osg/Switch>



Bouton::Bouton(std::string texture, std::string texture2)
{
	textureNameFile = texture;
	textureNameFile2 = texture2;
	geode = 0;
	pat = 0;
	// Instancie un noeud de geometrie pour accueillir le carre 
	pat = this->getPat();
	switchBox = new Switch();
	switchBox->addChild(getGeode(),false); // geode active par défaut
	switchBox->addChild(getGeode2(),true); // geode inactive par défaut
	pat->addChild(switchBox);
	
}


Bouton::~Bouton(void)
{
}

osg::ref_ptr<osg::Geode> Bouton::getGeode(){
	if(geode != 0){
		return Bouton::geode;
	}

	geode = new osg::Geode();

	// ---- FORME ----------------------------------------------------------
	osg::Box* unitCube = new osg::Box(osg::Vec3(0, 0, 0), 1, 1, 1);
	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
	geode->addDrawable(unitCubeDrawable);




	// ---- TEXTURE --------------------------------------------------------
	// charge une image par la lecture d'un fichier
	osg::Image* textureImage = osgDB::readImageFile(textureNameFile);
	if (!textureImage)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
		return 0;
	} else {
		std::cout << "read ok" << std::endl;
	}
	osg::Texture2D* texture = new osg::Texture2D;
	// protection pour les optimisations:
	texture->setDataVariance(osg::Object::DYNAMIC); 
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	// Assigne la texture que nous avons lue depuis le fichier: 
	texture->setImage(textureImage);

	// Cree un nouveau StateSet avec les options par defaut: 
	osg::StateSet* state = geode->getOrCreateStateSet();

	state->ref();
	osg::Material *material = new osg::Material();
	material->setEmission(osg::Material::FRONT, osg::Vec4(0.8, 0.8, 0.8, 1.0));
	state->setAttribute(material);
	state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);


	Bouton::geode->setStateSet(state);


	return Bouton::geode;
}

osg::ref_ptr<osg::Geode> Bouton::getGeode2(){
	if(geode2 != 0){
		return Bouton::geode2;
	}

	geode2 = new osg::Geode();

	// ---- FORME ----------------------------------------------------------
	osg::Box* unitCube = new osg::Box(osg::Vec3(0, 0, 0), 1, 1, 1);
	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
	geode2->addDrawable(unitCubeDrawable);




	// ---- TEXTURE --------------------------------------------------------
	// charge une image par la lecture d'un fichier
	osg::Image* textureImage = osgDB::readImageFile(textureNameFile2);
	if (!textureImage)
	{
		std::cout << " couldn't find texture, quiting." << std::endl;
		return 0;
	} else {
		std::cout << "read ok" << std::endl;
	}
	osg::Texture2D* texture = new osg::Texture2D;
	// protection pour les optimisations:
	texture->setDataVariance(osg::Object::DYNAMIC); 
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);
	// Assigne la texture que nous avons lue depuis le fichier: 
	texture->setImage(textureImage);

	// Cree un nouveau StateSet avec les options par defaut: 
	osg::StateSet* state = geode2->getOrCreateStateSet();

	state->ref();
	osg::Material *material = new osg::Material();
	material->setEmission(osg::Material::FRONT, osg::Vec4(0.8, 0.8, 0.8, 1.0));
	state->setAttribute(material);
	state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);


	Bouton::geode2->setStateSet(state);


	return Bouton::geode2;
}

osg::ref_ptr<osg::PositionAttitudeTransform> Bouton::getPat(){
	if(pat.get() != 0){
		return pat;
	}

	pat = new osg::PositionAttitudeTransform();
	//pat->addChild(getGeode());


	return pat;
}

void Bouton::setPosition(int x, int y){
	pat = this->getPat();
	pat->setPosition(osg::Vec3(x,y,-1));
}

