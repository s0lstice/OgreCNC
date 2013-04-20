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

    /*!
     * \brief The ModeleMain class est le modlee principale de l'application
     */
    class ModeleMain : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief ModeleMain le constructeur
         * \param parent
         */
        explicit ModeleMain(QObject *parent = 0);
        ~ModeleMain();

        /*!
         * \brief getModeleCut renvoie le modele de decoupe
         * \return
         */
        ModeleCut* getModeleCut();

        /*!
         * \brief setVue définit la vue utilisé est etablie la connectiona avec
         * \param vue
         */
        inline void setVue(VueMain * vue){
            if(m_vue != NULL)
                disconnect(m_vue, 0,0,0);
            m_vue = vue;
            m_vue->sl_setTreeBlocModele(m_modeleBloc);
            connect(m_modeleBloc, SIGNAL(si_createBloc(Bloc*)), m_vue, SLOT(sl_creat3Dbloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_hide3DBloc(Bloc*)), m_vue, SLOT(sl_hide3DBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_show3DBloc(Bloc*)), m_vue, SLOT(sl_show3DBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_selectBloc(Bloc*)), m_vue, SLOT(sl_selectBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updateCouleurBloc(Bloc*)), m_vue, SLOT(sl_updateCouleurBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updateDimensionBloc(Bloc*)), m_vue, SLOT(sl_updateDimentionBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_updatePositionBloc(Bloc*)), m_vue, SLOT(sl_updatePositionBloc(Bloc*)));
            connect(m_modeleBloc, SIGNAL(si_delete3DBloc(Bloc*)), m_vue, SLOT(sl_delete3DBloc(Bloc*)));
            Bloc * b = m_modeleBloc->creatBloc(Ogre::Vector3(800,150,600), Ogre::Vector3(0,0,0),m_RootTravailBlocs ); //bloc de départ
            Bloc * b1 = m_modeleBloc->creatBloc(Ogre::Vector3(800,150,600), Ogre::Vector3(0,300,0),m_RootTravailBlocs ); //bloc de départ

            NodeBloc * nb = m_modeleBloc->creatNodeBloc(b1,m_RootTravailBlocs);
            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,0,0), nb);
            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(150,0,0), nb);
            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,150,0), nb);
            m_modeleBloc->creatBloc(Ogre::Vector3(100,100,100), Ogre::Vector3(0,0,150), nb);
        }

        /*!
         * \brief setControleur definit le controleur principale
         * \param controleur
         */
        inline void setControleur(ControleurMain * controleur){
            m_controleur = controleur;
        }
        /*!
         * \brief getModeleBloc renvoie le modele bloc
         * \return
         */
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
        /*!
         * \brief m_controleur est le controleur principale
         */
        ControleurMain * m_controleur;
        /*!
         * \brief m_vue est la vue principale
         */
        VueMain * m_vue;
        /*!
         * \brief m_modeleBloc est le modele de bloc
         */
        ModeleBloc * m_modeleBloc;
        /*!
         * \brief m_RootTravailBlocs est la racine de l'arbre des bloc
         */
        NodeBloc * m_RootTravailBlocs;
        /*!
         * \brief m_modeleCut est le modele de découpe
         */
        ModeleCut* m_modeleCut;
        /*!
         * \brief m_InitialBloc est le bloc initial
         */
        Bloc * m_InitialBloc;

    signals:

    public slots:

    };
}
#endif // MODELEMAIN_H
