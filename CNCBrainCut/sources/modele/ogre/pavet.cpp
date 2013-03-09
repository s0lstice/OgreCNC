#include "pavet.h"

#include <QPoint>
#include <QString>

Pavet::Pavet(QString name, QString matName, Point3d  * dimention) : dimention(dimention), name(name), matName(matName)
{
    objet = new Ogre::ManualObject(name.toStdString());
    update();
}
Pavet::~Pavet(){
    delete dimention;
}

void Pavet::update(){

    objet->begin(matName.toStdString(), Ogre::RenderOperation::OT_TRIANGLE_LIST);

    objet->position(- dimention->x/2, + dimention->y/2, + dimention->z/2);
    objet->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
    objet->textureCoord(0.0, 1.0);

    objet->position(- dimention->x/2, - dimention->y/2, + dimention->z/2);
    objet->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
    objet->textureCoord(1.0, 1.0);

    objet->position(+ dimention->x/2, - dimention->y/2, + dimention->z/2);
    objet->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
    objet->textureCoord(1.0, 0.0);

    objet->position(+ dimention->x/2, + dimention->y/2, + dimention->z/2);
    objet->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));
    objet->textureCoord(0.0, 0.0);

    objet->position(- dimention->x/2, + dimention->y/2, - dimention->z/2);
    objet->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
    objet->textureCoord(0.0, 1.0);

    objet->position(- dimention->x/2, - dimention->y/2, - dimention->z/2);
    objet->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
    objet->textureCoord(1.0, 1.0);

    objet->position(+ dimention->x/2, - dimention->y/2, - dimention->z/2);
    objet->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
    objet->textureCoord(1.0, 0.0);

    objet->position(+ dimention->x/2, + dimention->y/2, - dimention->z/2);
    objet->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
    objet->textureCoord(0.0, 0.0);

    // face behind / front
    objet->triangle(0,1,2);
    objet->triangle(2,3,0);
    objet->triangle(4,6,5);
    objet->triangle(6,4,7);

    // face top / down
    objet->triangle(0,4,5);
    objet->triangle(5,1,0);
    objet->triangle(2,6,7);
    objet->triangle(7,3,2);

    // face left / right
    objet->triangle(0,7,4);
    objet->triangle(7,0,3);
    objet->triangle(1,5,6);
    objet->triangle(6,2,1);

    objet->end();
}


/*
 *SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
mNode->setPosition(0,0.5,0);
mNode->attachObject(createCubeMesh("Cube", "myMaterial"));

ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName) {

   ManualObject* cube = new ManualObject(name);
   cube->begin(matName);

   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,0);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(0,0);

   cube->triangle(0,1,2);      cube->triangle(3,1,0);
   cube->triangle(4,5,6);      cube->triangle(4,7,5);
   cube->triangle(8,9,10);      cube->triangle(10,7,8);
   cube->triangle(4,11,12);   cube->triangle(4,13,11);
   cube->triangle(14,8,12);   cube->triangle(14,15,8);
   cube->triangle(16,17,18);   cube->triangle(16,19,17);
   cube->end();

   return cube;

}

*/
