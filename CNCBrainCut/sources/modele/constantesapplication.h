#ifndef CONSTANTESAPPLICATION_H
#define CONSTANTESAPPLICATION_H
#include <QString>
#include <Ogre.h>
namespace OgreCNC {
    namespace constantes {
        const QString BLOC_USE = "cube_use";
        const QString BLOC_CHUTE = "cube_chute";
        const QString BLOC_SELECTED = "cube_selected";

        const Ogre::ColourValue SEGMENT_UNSELECTED = Ogre::ColourValue::Blue;
        const Ogre::ColourValue SEGMENT_SELECTED = Ogre::ColourValue::Red;

    }
}

#endif // CONSTANTESAPPLICATION_H
