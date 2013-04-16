#ifndef CONTROLEUROGREWIDGET_H
#define CONTROLEUROGREWIDGET_H

#include <QObject>
#include <Ogre.h>

#include "ogrewidget.h"
#include "../../modele/bloc/bloc.h"

namespace OgreCNC {
    class Bloc;
    class ControleurOgreWidget : public QObject
    {
        Q_OBJECT
        private :
            /*!
             * \brief m_Vue3D est un pointeur sur l'OgreWidget actif
             */
            OgreWidget * m_Vue3D;

            /*!
             * \brief curentBlock est le bloc courent
             */
            Bloc * curentBlock;

            /*!
             * \brief curentSegment est le segment selectionné
             */
            Ogre::MovableObject * curentSegment;

            /*!
             * \brief initConnectionWithWidget initilise les conections avec le widget graphique
             */
            inline void initConnectionsWithWidget(){
                connect(m_Vue3D, SIGNAL(si_selectionObjet(Ogre::SceneNode*)), this, SLOT(selectOgreBloc(Ogre::SceneNode*)));
                connect(m_Vue3D, SIGNAL(si_selectionSegment(Ogre::ManualObject*)), this, SLOT(selectOgreSegment(Ogre::ManualObject*)));
            }

            /*!
             * \brief clearConectionsWithWidget detruit les connections au widget
             */
            inline void clearConectionsWithWidget(){
                if(m_Vue3D != NULL)
                    if(m_Vue3D->isValid())
                        disconnect(m_Vue3D, 0, 0, 0);
            }
            /*!
             * \brief beginSegment créé ou met à jour un segment
             * \param segment le segment a modifier
             * \param debut est le position de debut
             * \param fin est le position de fin
             * \param BBRayon est le rayon de la bounding box
             * \param couleur est le couleur du segment
             * \param matName est le nom du materiaux, appliqué uniquemnet si c'est une creation
             * \param isUpDate inque si c'est une création ou une mise à jour
             */
            void beginSegment(Ogre::ManualObject * segment, Ogre::Vector3 debut, Ogre::Vector3 fin, int BBRayon, Ogre::ColourValue couleur,Ogre::String matName = "", bool isUpDate = false);

            /*!
             * \brief changeSegmentColot modifie la couleur du segment
             * \param segment à modifier
             * \param color est la nouvelle couleur
             */
            void changeSegmentColot(Ogre::MovableObject * segment, Ogre::ColourValue color);
        public:
            /*!
             * \brief ControleurOgreWidget est le constructeur
             */
            ControleurOgreWidget( QObject *parent = NULL);

            /*!
             * \brief setWidget definit le widget graphique utilisé par le controleur
             * \param vue3D est un OgreWidget
             */
            inline void setWidget(OgreWidget * vue3D)
            {
                clearConectionsWithWidget();
                m_Vue3D = vue3D;
                initConnectionsWithWidget();
            }

            int creat3DBloc(Bloc *bloc);

        signals:
            OgreCNC::Bloc * si_blocFormOgreNode( Ogre::SceneNode * node);
            void si_SelectBloc(Bloc * bloc);
            void si_selectSegemnt(Ogre::ManualObject * segment);

        public slots:
            void selectBloc(Bloc * bloc);
            void selectSegment(Ogre::ManualObject *segment);
            void selectOgreBloc(Ogre::SceneNode * node);
            void selectOgreSegment(Ogre::ManualObject *segment);

    };
}
#endif // CONTROLEUROGREWIDGET_H
