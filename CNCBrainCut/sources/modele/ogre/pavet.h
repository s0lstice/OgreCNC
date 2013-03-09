#ifndef PAVET_H
#define PAVET_H


#include <Ogre.h>
#include <QString>

#include "../point3d.h"

class Pavet
{
public:
    Pavet(QString name,QString matName, Point3d * dimention);
    ~Pavet();
    void update();

    Ogre::ManualObject * objet;
    Point3d * dimention;
    QString name;
    QString matName;
};

#endif // PAVET_H
