#include "BoxView.h"
#include <iostream>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/TexEnv>
#include <osg/Material>


osg::ref_ptr<osg::Geode> BoxView::geode = 0;

BoxView::BoxView(CaseContents* model) : ObjectView(model)
{
	std::cout << "BOXVIEW CONSTRUCTEUR" << "\n";
	pat = 0;
	// Instancie un noeud de geometrie pour accueillir le carre 
	pat = this->getPat();
	pat->addChild(BoxView::geode);
	//pat->setPosition(osg::Vec3(0,0,0));
}

BoxView::~BoxView(void)
{
}

osg::ref_ptr<osg::Geode> BoxView::getGeode(){
	std::cout << "WallView::getGeode" << "\n";
	if(BoxView::geode != 0){
		std::cout << "if(BoxView::geode != 0) >>> YES" << "\n";
		return BoxView::geode;
	}
	
	BoxView::geode = new osg::Geode();

	// ---- FORME ----------------------------------------------------------
	osg::Box* unitCube = new osg::Box(osg::Vec3(0, 0, 0), 1, 1, 1);
	osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(unitCube);
	geode->addDrawable(unitCubeDrawable);




	// ---- TEXTURE --------------------------------------------------------
   // charge une image par la lecture d'un fichier
   osg::Image* textureImage = osgDB::readImageFile("box.png");
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
   osg::StateSet* state = BoxView::geode->getOrCreateStateSet();

   state->ref();
   osg::Material *material = new osg::Material();
   material->setEmission(osg::Material::FRONT, osg::Vec4(0.8, 0.8, 0.8, 1.0));
   state->setAttribute(material);
   state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);


   BoxView::geode->setStateSet(state);


	return BoxView::geode;
}

osg::ref_ptr<osg::PositionAttitudeTransform> BoxView::getPat(){
	if(pat != 0){
		return pat;
	}

	pat = new osg::PositionAttitudeTransform();
	pat->addChild(BoxView::getGeode());


	return pat;
}