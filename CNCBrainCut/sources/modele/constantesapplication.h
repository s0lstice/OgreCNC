#ifndef CONSTANTESAPPLICATION_H
#define CONSTANTESAPPLICATION_H
#include <QString>
#include <Ogre.h>
namespace OgreCNC {
    /*!
     * \namespace constantes
     * \brief definit les constantes de l'application
     */
    namespace constantes {
        /*!
         * \brief BLOC_USE est le nom du materiau pour le dessin de bloc utilisé
         */
        const QString BLOC_USE = "cube_use";
        /*!
         * \brief BLOC_CHUTE est le nom du materiau pour le dessin de bloc non utilsé (chute)
         */
        const QString BLOC_CHUTE = "cube_chute";
        /*!
         * \brief BLOC_SELECTED est le nom du materiau pour le dssin du bloc sélectionné
         */
        const QString BLOC_SELECTED = "cube_selected";
        /*!
         * \brief SEGMENT_UNSELECTED est la couleur pour le segment non sélectionné
         */
        const Ogre::ColourValue SEGMENT_UNSELECTED = Ogre::ColourValue::Blue;
        /*!
         * \brief SEGMENT_SELECTED est la couleur pour le segment sélectionné
         */
        const Ogre::ColourValue SEGMENT_SELECTED = Ogre::ColourValue::Red;

    }
}

#endif // CONSTANTESAPPLICATION_H
