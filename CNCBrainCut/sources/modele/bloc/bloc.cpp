#include "bloc.h"

#include "nodebloc.h"

/*Constructeurs*/

Bloc::Bloc(NodeBloc *parent)
{
    hauteur = 0;
    longueur = 0;
    largeur = 0;
    utilisation = CHUTE;
    visible = visible;
    parent = parent;

    bloc3d = NULL;
    nodeBloc3d = NULL;
}

Bloc::~Bloc()
{
    assert(bloc3d==NULL); // la desalocation doit etre faite avant la destruction de cette objet
    assert(nodeBloc3d==NULL);
}

void Bloc::updateBloc3d(){
    assert(bloc3d!=NULL); //l'allocation doit etre faite
    bloc3d->begin(matName.toStdString(), Ogre::RenderOperation::OT_TRIANGLE_LIST);

    bloc3d->position(- longueur/2, + hauteur/2, + largeur/2);
    bloc3d->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
    bloc3d->textureCoord(0.0, 1.0);

    bloc3d->position(- longueur/2, - hauteur/2, + largeur/2);
    bloc3d->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
    bloc3d->textureCoord(1.0, 1.0);

    bloc3d->position(+ longueur/2, - hauteur/2, + largeur/2);
    bloc3d->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
    bloc3d->textureCoord(1.0, 0.0);

    bloc3d->position(+ longueur/2, + hauteur/2, + largeur/2);
    bloc3d->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));
    bloc3d->textureCoord(0.0, 0.0);

    bloc3d->position(- longueur/2, + hauteur/2, - largeur/2);
    bloc3d->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
    bloc3d->textureCoord(0.0, 1.0);

    bloc3d->position(- longueur/2, - hauteur/2, - largeur/2);
    bloc3d->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
    bloc3d->textureCoord(1.0, 1.0);

    bloc3d->position(+ longueur/2, - hauteur/2, - largeur/2);
    bloc3d->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
    bloc3d->textureCoord(1.0, 0.0);

    bloc3d->position(+ longueur/2, + hauteur/2, - largeur/2);
    bloc3d->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
    bloc3d->textureCoord(0.0, 0.0);

    // face behind / front
    bloc3d->triangle(0,1,2);
    bloc3d->triangle(2,3,0);
    bloc3d->triangle(4,6,5);
    bloc3d->triangle(6,4,7);

    // face top / down
    bloc3d->triangle(0,4,5);
    bloc3d->triangle(5,1,0);
    bloc3d->triangle(2,6,7);
    bloc3d->triangle(7,3,2);

    // face left / right
    bloc3d->triangle(0,7,4);
    bloc3d->triangle(7,0,3);
    bloc3d->triangle(1,5,6);
    bloc3d->triangle(6,2,1);

    bloc3d->end();
}
