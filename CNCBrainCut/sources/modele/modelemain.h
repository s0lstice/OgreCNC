#ifndef MODELEMAIN_H
#define MODELEMAIN_H

#include <QObject>
#include <Ogre.h>
#include <QModelIndex>
#include "../vue/vuemain.h"
#include "bloc/modelebloc.h"

namespace OgreCNC{
    class ControleurMain;
    class VueMain;
    class NodeBloc;
    class ModeleCut;
    class Bloc;
    class ModeleBloc;

    class ModeleMain : public QObject
    {
        Q_OBJECT
    public:
        explicit ModeleMain(QObject *parent = 0);
        ~ModeleMain();

        ModeleCut* getModeleCut();

        inline void setVue(VueMain * vue){
            if(m_vue != NULL)
                disconnect(m_vue, 0,0,0);
            m_vue = vue;
            m_vue->sl_setTreeBlocModele(m_modeleBloc);
            connect(m_modeleBloc, SIGNAL(si_createBloc(Bloc*)), m_vue, SLOT(sl_creat3Dbloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_delete3Dbloc(Bloc*)), m_vue, SLOT(sl_delete3Dbloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_selectBloc(Bloc*)), m_vue, SLOT(sl_selectBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updateCouleurBloc(Bloc*)), m_vue, SLOT(sl_updateCouleurBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updateDimensionBloc(Bloc*)), m_vue, SLOT(sl_updateDimentionBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updatePostionBloc(Bloc*)), m_vue, SLOT(sl_updatePositionBloc(Bloc*)));

            Bloc * b = m_modeleBloc->creatBloc(Ogre::Vector3(800,150,600), Ogre::Vector3(0,0,0),m_RootTravailBlocs ); //bloc de départ
//            Bloc * b1 = m_modeleBloc->creatBloc(Ogre::Vector3(800,150,600), Ogre::Vector3(0,300,0),m_RootTravailBlocs ); //bloc de départ

//            NodeBloc * nb = m_modeleBloc->creatNodeBloc(b1,m_RootTravailBlocs);
//            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,0,0), nb);
//            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(150,0,0), nb);
//            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,150,0), nb);
//            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,0,150), nb);
        }


        inline void setControleur(ControleurMain * controleur){
            m_controleur = controleur;
        }

        inline ModeleBloc * getModeleBloc(){
            return m_modeleBloc;
        }

        /*!
         * \brief currentBloc est le bloc sélectionné
         */
        Bloc * currentBloc;
        /*!
         * \brief currentSegment est le segment sélectionné
         */
        Ogre::ManualObject * currentSegment;
        /*!
         * \brief currentIndex designe l'index du bloc sélectionné dans l'arbre, NULL si non connue
         */
        QModelIndex currentIndex;

    private:
        ControleurMain * m_controleur;
        VueMain * m_vue;
        ModeleBloc * m_modeleBloc;
        NodeBloc * m_RootTravailBlocs;

        ModeleCut* m_modeleCut;

        Bloc * m_InitialBloc;

    signals:

    public slots:

    };
}
#endif // MODELEMAIN_H
