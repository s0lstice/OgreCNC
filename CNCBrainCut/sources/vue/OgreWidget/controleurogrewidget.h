#ifndef CONTROLEUROGREWIDGET_H
#define CONTROLEUROGREWIDGET_H

#include <QObject>
#include <Ogre.h>

#include "ogrewidget.h"
#include "../../modele/bloc/bloc.h"

namespace OgreCNC {
    class Bloc;
    /*!
     * \brief The ControleurOgreWidget class pour gére l'affichage 3D et dialoguer avec le reste de l'application
     */
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
             * \brief m_BBSize est le rayon des boites englobantes pours les segments
             */
            int m_BBSize;

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
            void changeColorSegment(Ogre::MovableObject * segment, Ogre::ColourValue color);
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

            /*!
             * \brief delete3DBloc detruit un bloc 3D et ses enfants
             * \param bloc est le bloc contenant la bloc 3d à detruire
             */
            void delete3DBloc(Bloc * bloc);
            /*!
             * \brief delete3DBloc detruit un bloc 3D et ses enfants
             * \param i_pSceneNode est le SceneNode à detruire
             */
            void delete3DBloc(Ogre::SceneNode * i_pSceneNode);
            /*!
             * \brief create3DBloc créé un bloc 3d et ses enfants
             * \param bloc est le bloc contenant le bloc 3d
             * \return un code d'erreur
             */
            int create3DBloc(Bloc *bloc);
            /*!
             * \brief updateDimentionBloc adapte le bloc 3d aux nouvelles dimensions
             * \param bloc le bloc a modifier
             * \return l'erreur
             */
            int updateDimentionBloc(Bloc * bloc);
            /*!
             * \brief updatePositionBloc change la postion du bloc 3D
             * \param bloc le bloc a deplacer
             * \return l'erreur
             */
            int updatePositionBloc(Bloc * bloc);

            /*!
             * \brief updateDimentionBloc change la couleur du bloc 3D
             * \param bloc
             * \return
             */
            int updateCouleurBloc(Bloc * bloc);

        signals:
            /*!
             * \brief si_blocFormOgreNode demande quel est le Bloc associé au noeud 3d
             * \param node
             * \return
             */
            OgreCNC::Bloc * si_blocFormOgreNode( Ogre::SceneNode * node);
            /*!
             * \brief si_SelectBloc indique la selection d'un bloc
             * \param bloc
             */
            void si_SelectBloc(Bloc * bloc);
            /*!
             * \brief si_selectSegemnt indique la selection d'un segment
             * \param segment
             */
            void si_selectSegemnt(Ogre::ManualObject * segment);

        public slots:
            /*!
             * \brief selectBloc change la couleur des deux blocs, la nouvelle et l'encienne selection
             * \param bloc
             */
            void selectBloc(Bloc * bloc);
            /*!
             * \brief selectSegment change la couleur des deux segments, la nouvelle et l'encienne selection
             * \param segment
             */
            void selectSegment(Ogre::ManualObject *segment);
            /*!
             * \brief selectOgreBloc gere la selection d'un bloc 3D
             * \param node
             */
            void selectOgreBloc(Ogre::SceneNode * node);
            /*!
             * \brief selectOgreSegment gere la selection d'un segment
             * \param segment
             */
            void selectOgreSegment(Ogre::ManualObject *segment);

    };
}
#endif // CONTROLEUROGREWIDGET_H
