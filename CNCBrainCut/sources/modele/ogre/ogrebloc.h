#ifndef OGREBLOC_H
#define OGREBLOC_H

#include "pavet.h"
#include "../point3d.h"

#include <Ogre.h>

class ogreBloc
{
public:
    ogreBloc();

    Pavet * bloc;
    Ogre::SceneNode * nodeBloc;
    Point3d * position;
};

#endif // OGREBLOC_H
